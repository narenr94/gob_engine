#include "commonJsonParser.h"
#include "utilities.h"
#include "gameData.h"
#include "randomize.h"
#include "defines.h"
#include "json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;


//------------Declarations


bool readJsonFile(const std::string& filePath, json& j);

void printJson(const json& j);

void extractAndApplyAbilityMods(json& j, std::vector<AbilityModData*>& abilityModsData);
void extractAndApplyParamMods(json& j, std::vector<ParamModData*>& paramModsData);
void extractAndApplyAlignmentData(json& j, AlignmentData* alignmentData);
void extractAndApplySizeData(json& j, SizeData* sizeData);
void extractAndApplyAgeData(json& j, AgeData* ageData);
void extractAndApplySpeedData(json& j, SpeedData* speedData);
void extractAndApplyLanguagesData(json& j, std::vector<LanguageData*>& languageData);
void extractAndApplyDarkVisionData(json& j, DarkvisionData* darkvisionData);
void extractAndApplyResilienceData(json& j, std::vector<ResilienceData*>& resilienceData);
void extractAndApplyProficiencyData(json& j, ProficiencyData* proficiencyData);
void extractAndApplySleepDurationData(json& j, SleepDurationData* sleepDurationData);
void extractAndApplyItemData(json& j, std::vector<ItemData*>& itemData);



//------------------------


bool readJsonFile(const std::string& filePath, json& j){
    std::ifstream i(filePath);
    if(!i.is_open()){
        return false;
    }
    j = json::parse(i);
    return true;
}

void printJson(const json& j){
    std::cout << j.dump(4) << std::endl;
}

void extractAndApplyAbilityMods(json& j, std::vector<AbilityModData*>& abilityModsData){
    for (const auto& mod : j[jsonKeyToString(JsonKeys::ability_mods)]) {

        //confirm all mandatory fields are available
        if(!mod.contains(jsonKeyToString(JsonKeys::ability))
        || !mod.contains(jsonKeyToString(JsonKeys::mod))){
            throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::ability_mods));
        }

        std::string ability = mod[jsonKeyToString(JsonKeys::ability)];
        int value = mod[jsonKeyToString(JsonKeys::mod)];
        AbilityModData* temp = new AbilityModData();
        temp->abilityMod = {ability, value};
        abilityModsData.push_back(temp);
    }
}

void extractAndApplyParamMods(json& j, std::vector<ParamModData*>& paramModsData){
    for (const auto& mod : j[jsonKeyToString(JsonKeys::param_mods)]) {

        //confirm all mandatory fields are available
        if(!mod.contains(jsonKeyToString(JsonKeys::param))
        || !mod.contains(jsonKeyToString(JsonKeys::mod))){
            throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::param_mods));
        }

        std::string param = mod[jsonKeyToString(JsonKeys::param)];
        int value = mod[jsonKeyToString(JsonKeys::mod)];

        ParamModData* temp = new ParamModData();
        temp->paramMod = {param, value};

        paramModsData.push_back(temp);
    }
}

void extractAndApplyAgeData(json& j, AgeData* ageData){
    //confirm all mandatory fields are available
    if(!j[jsonKeyToString(JsonKeys::age)].contains(jsonKeyToString(JsonKeys::maturity))
    || !j[jsonKeyToString(JsonKeys::age)].contains(jsonKeyToString(JsonKeys::life_span))){
        throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::age));
    }

    ageData->maturityAge = j[jsonKeyToString(JsonKeys::age)][jsonKeyToString(JsonKeys::maturity)];
    ageData->avgLifespan = j[jsonKeyToString(JsonKeys::age)][jsonKeyToString(JsonKeys::life_span)];

}

void extractAndApplyAlignmentData(json& j, AlignmentData* alignmentData){
    alignmentData->alignment = stringToAlignment(j[jsonKeyToString(JsonKeys::alignment)]);
}

void extractAndApplySizeData(json& j, SizeData* sizeData){
    //confirm all mandatory fields are available
    if(!j[jsonKeyToString(JsonKeys::size)].contains(jsonKeyToString(JsonKeys::avg_height_m))
    || !j[jsonKeyToString(JsonKeys::size)].contains(jsonKeyToString(JsonKeys::avg_weight_kg))){
        throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::size));
    }


    sizeData->category = stringToSizeCategory(j[jsonKeyToString(JsonKeys::size)][jsonKeyToString(JsonKeys::category)]);
    sizeData->dimensions = {j[jsonKeyToString(JsonKeys::size)][jsonKeyToString(JsonKeys::avg_height_m)],
                        j[jsonKeyToString(JsonKeys::size)][jsonKeyToString(JsonKeys::avg_weight_kg)]};

}

void extractAndApplySpeedData(json& j, SpeedData* speedData){
    speedData->speed = j[jsonKeyToString(JsonKeys::speed_mps)];
}

void extractAndApplyLanguagesData(json& j, std::vector<LanguageData*>& languageData){
   for (const auto& lang : j[jsonKeyToString(JsonKeys::languages)]) {

        //confirm all mandatory fields are available
        if(!lang.contains(jsonKeyToString(JsonKeys::name))
        || !lang.contains(jsonKeyToString(JsonKeys::speak))
        || !lang.contains(jsonKeyToString(JsonKeys::read))
        || !lang.contains(jsonKeyToString(JsonKeys::write))){
            throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::languages));
        }

        LanguageData* temp = new LanguageData();

        temp->language = lang[jsonKeyToString(JsonKeys::name)];
        temp->speak = lang[jsonKeyToString(JsonKeys::speak)];
        temp->read = lang[jsonKeyToString(JsonKeys::read)];
        temp->write = lang[jsonKeyToString(JsonKeys::write)];
        languageData.push_back(temp);
    }
}

void extractAndApplyDarkVisionData(json& j, DarkvisionData* darkvisionData){
    //confirm all mandatory fields are available
    if(!j[jsonKeyToString(JsonKeys::dark_vision)].contains(jsonKeyToString(JsonKeys::has_darkvision))
    || !j[jsonKeyToString(JsonKeys::dark_vision)].contains(jsonKeyToString(JsonKeys::dim_light_eq))
    || !j[jsonKeyToString(JsonKeys::dark_vision)].contains(jsonKeyToString(JsonKeys::darkness_eq))
    || !j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::dim_light_eq)].contains(jsonKeyToString(JsonKeys::as_ambient))
    || !j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::dim_light_eq)].contains(jsonKeyToString(JsonKeys::distance_m))
    || !j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::darkness_eq)].contains(jsonKeyToString(JsonKeys::as_ambient))
    || !j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::darkness_eq)].contains(jsonKeyToString(JsonKeys::distance_m)))
    {
        throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::dark_vision));
    }

    darkvisionData->hasDarkvision = j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::has_darkvision)];

    darkvisionData->dim_light_eq = stringToIlluminationType(j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::dim_light_eq)][jsonKeyToString(JsonKeys::as_ambient)]); 
    darkvisionData->dim_light_eq_dist = j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::dim_light_eq)][jsonKeyToString(JsonKeys::distance_m)];
    darkvisionData->darkvision_eq = stringToIlluminationType(j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::darkness_eq)][jsonKeyToString(JsonKeys::as_ambient)]);
    darkvisionData->darkvision_eq_dist = j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::darkness_eq)][jsonKeyToString(JsonKeys::distance_m)];

}

void extractAndApplyResilienceData(json& j, std::vector<ResilienceData*>& resilienceData){
    for(const auto& res : j[jsonKeyToString(JsonKeys::resilience)]){

        //confirm all mandatory fields are available
        if(!res.contains(jsonKeyToString(JsonKeys::affliction))){
            throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::resilience));
        }

        ResilienceData* temp = new ResilienceData();

        temp->affliction = res[jsonKeyToString(JsonKeys::affliction)];
        
        temp->immune = false;
        if(res.contains(jsonKeyToString(JsonKeys::immune))){
            temp->immune = res[jsonKeyToString(JsonKeys::immune)];
        }
        temp->hasAdvantage = false;
        if(res.contains(jsonKeyToString(JsonKeys::has_advantage))){
            temp->hasAdvantage = res[jsonKeyToString(JsonKeys::has_advantage)];
        }
        temp->hasResistance = false;
        if(res.contains(jsonKeyToString(JsonKeys::has_resistance))){
            temp->hasResistance = res[jsonKeyToString(JsonKeys::has_resistance)];
        }

        resilienceData.push_back(temp);
    }
}

void extractAndApplyProficiencyData(json& j, ProficiencyData* proficiencyData){
    if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::weapons))){
        for(const auto& wp : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::weapons)]){
            proficiencyData->weaponProficiencies.push_back(wp);
        }
    }

    if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::armors))){
        for(const auto& ar : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::armors)]){
            proficiencyData->armorProficiencies.push_back(ar);
        }
    }

    if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::tools))){
        for(const auto& tl : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::tools)]){
            proficiencyData->toolProficiencies.push_back(tl);
        }
    }

    if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::skills))){
        for(const auto& sk : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::skills)]){
            proficiencyData->skillProficiencies.push_back(sk);
        }
    }

    if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::saving_throws))){
        for(const auto& st : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::saving_throws)]){
            proficiencyData->savingThrowsProficiencies.push_back(st);
        }
    }
}

std::vector<std::string> extractAndApplyAbilities(const std::string& t_abilityPath){
    json j;
    std::vector<std::string> abilitiesVector;
    if(readJsonFile(t_abilityPath, j)){
        if(j.contains(jsonKeyToString(JsonKeys::abilities)) && j[jsonKeyToString(JsonKeys::abilities)].is_array()){
            for(const auto& ability : j[jsonKeyToString(JsonKeys::abilities)]){
                abilitiesVector.push_back(ability);
            }
        }
        else{
            throw std::runtime_error("Key 'abilities' not found or is not an array in abilities JSON file:" + t_abilityPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_abilityPath);
    }

    return abilitiesVector;
}

std::vector<std::string> extractAndApplyParams(const std::string& t_paramPath){
    json j;
    std::vector<std::string> paramsVector;
    if(readJsonFile(t_paramPath, j)){
        if(j.contains(jsonKeyToString(JsonKeys::params)) && j[jsonKeyToString(JsonKeys::params)].is_array()){
            for(const auto& param : j[jsonKeyToString(JsonKeys::params)]){
                paramsVector.push_back(param);
            }
        }
        else{
            throw std::runtime_error("Key 'params' not found or is not an array in params JSON file:" + t_paramPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_paramPath);
    }

    return paramsVector;
}

void extractAndApplySleepDurationData(json& j, SleepDurationData* sleepDurationData){
    sleepDurationData->sleepDurationHrs = j[jsonKeyToString(JsonKeys::sleep_duration_hrs)];
}

void extractAndApplyItemData(json& j, std::vector<ItemData*>& itemData){

    for(const auto& it : j[jsonKeyToString(JsonKeys::item)]){

        if(!it.contains(jsonKeyToString(JsonKeys::name)) || !it.contains(jsonKeyToString(JsonKeys::count))){
            throw std::runtime_error("mandatory fields not available for " + jsonKeyToString(JsonKeys::item));
        }

        ItemData* temp = new ItemData();
        temp->itemData = {it[jsonKeyToString(JsonKeys::name)], it[jsonKeyToString(JsonKeys::count)]};

        itemData.push_back(temp);
    }
}

void getProficiencyOptions(json& j, ProficiencyOptionData* profData){

    if(j[jsonKeyToString(JsonKeys::arguments)].size() != 1 
    || (!(j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::weapons) || j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::armors) || j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::tools) || j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::skills) || j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::saving_throws)))){
        throw std::runtime_error("invalid number of arguments for proficiency options");
    }

    if(j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::weapons)){
        profData->type = ProficiencyType::Weapons;
    }
    else if(j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::armors)){
        profData->type = ProficiencyType::Armors;
    }
    else if(j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::tools)){
        profData->type = ProficiencyType::Tools;
    }
    else if(j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::skills)){
        profData->type = ProficiencyType::Skills;
    }
    else if(j[jsonKeyToString(JsonKeys::arguments)][0] == jsonKeyToString(JsonKeys::saving_throws)){
        profData->type = ProficiencyType::SavingThrows;
    }

    profData->choices = j[jsonKeyToString(JsonKeys::choices)].get<std::vector<std::string>>();

    profData->chooseCount = j[jsonKeyToString(JsonKeys::choose)].get<unsigned short int>();


}

void getLanguageOptions(json& j, LanguageOptionData* langData){

    if((!j[jsonKeyToString(JsonKeys::arguments)].size() <= 3) || (!j[jsonKeyToString(JsonKeys::arguments)].size() >=1)){
        throw std::runtime_error("invalid number of arguments for language options");
    }

    for(const auto& arg : j[jsonKeyToString(JsonKeys::arguments)]){
        if(arg != jsonKeyToString(JsonKeys::speak) && arg != jsonKeyToString(JsonKeys::read) && arg != jsonKeyToString(JsonKeys::write)){
            throw std::runtime_error("invalid argument for language options: " + arg.get<std::string>());
        }

        if(arg == jsonKeyToString(JsonKeys::speak)){
            langData->speak = true;
        }
        else if(arg == jsonKeyToString(JsonKeys::read)){
            langData->read = true;
        }
        else if(arg == jsonKeyToString(JsonKeys::write)){
            langData->write = true;
        }
    }

    langData->choices = j[jsonKeyToString(JsonKeys::choices)].get<std::vector<std::string>>();
    langData->chooseCount = j[jsonKeyToString(JsonKeys::choose)].get<unsigned short int>();
    
}

void getItemOptions(json& j, ItemOptionData* itemData){

    if( (j.contains(jsonKeyToString(JsonKeys::arguments)))
        && (j.contains(jsonKeyToString(JsonKeys::choices))
        && (j.contains(jsonKeyToString(JsonKeys::choose)))
        && (j[jsonKeyToString(JsonKeys::choices)].size() == j[jsonKeyToString(JsonKeys::arguments)].size())))
    {
        throw std::runtime_error("invalid number of arguments for item options, currently expecting 0");
    }

    std::vector<std::string> choices = j[jsonKeyToString(JsonKeys::choices)].get<std::vector<std::string>>();
    std::vector<std::string>  counts = j[jsonKeyToString(JsonKeys::arguments)].get<std::vector<std::string>>();

    for(size_t i = 0; i < choices.size(); i++){
        unsigned short int count = std::stoi(counts[i]);
        itemData->choices.push_back({choices[i], count});
    }

    itemData->chooseCount = j[jsonKeyToString(JsonKeys::choose)].get<unsigned short int>();
}

void getAlignmentOptions(json& j, AlignmentOptionData* alignmentData){

    if((j[jsonKeyToString(JsonKeys::arguments)].size() != 0) && (j[jsonKeyToString(JsonKeys::choose)].get<unsigned short int>() != 1)){
        throw std::runtime_error("invalid number of arguments for alignment options, currently expecting 0 or invalid choose count");
    }

    alignmentData->choices = j[jsonKeyToString(JsonKeys::choices)].get<std::vector<std::string>>();
    alignmentData->chooseCount = j[jsonKeyToString(JsonKeys::choose)].get<unsigned short int>();
}

std::vector<std::string> extractAllLanguages(const std::string& t_languagesPath){
    json j;
    std::vector<std::string> languagesVector;
    if(readJsonFile(t_languagesPath, j)){
        if(j.contains(jsonKeyToString(JsonKeys::languages)) && j[jsonKeyToString(JsonKeys::languages)].is_array()){
            for(const auto& language : j[jsonKeyToString(JsonKeys::languages)]){
                languagesVector.push_back(language);
            }
        }
        else{
            throw std::runtime_error("Key 'languages' not found or is not an array in languages JSON file:" + t_languagesPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_languagesPath);
    }

    return languagesVector;
}

void updateConsolidatedData(const std::string& t_path, ConsolidatedData& conData){

    json j;

    if(readJsonFile(t_path, j)){

        if(j.contains(jsonKeyToString(JsonKeys::ability_mods))){

            std::vector<AbilityModData*> abilityModsData;
            extractAndApplyAbilityMods(j, abilityModsData);
            for(auto& mod : abilityModsData){
                conData.data.push_back(mod);
            }
        }

        if(j.contains(jsonKeyToString(JsonKeys::param_mods))){
            std::vector<ParamModData*> paramModsData;
            extractAndApplyParamMods(j, paramModsData);
            for(auto& mod : paramModsData){
                conData.data.push_back(mod);
            }
        }

        if(j.contains(jsonKeyToString(JsonKeys::age))){
            AgeData* ageData = new AgeData();
            extractAndApplyAgeData(j, ageData);
            conData.data.push_back(ageData);
        }

        if(j.contains(jsonKeyToString(JsonKeys::alignment))){
            AlignmentData* alignmentData = new AlignmentData();
            extractAndApplyAlignmentData(j, alignmentData);
            conData.data.push_back(alignmentData);
        }

        if(j.contains(jsonKeyToString(JsonKeys::size))){
            SizeData* sizeData = new SizeData();
            extractAndApplySizeData(j, sizeData);
            conData.data.push_back(sizeData);
        }

        if(j.contains(jsonKeyToString(JsonKeys::speed_mps))){
            SpeedData* speedData = new SpeedData();
            extractAndApplySpeedData(j, speedData);
            conData.data.push_back(speedData);
        }

        if(j.contains(jsonKeyToString(JsonKeys::languages))){
            std::vector<LanguageData*> languageData;
            extractAndApplyLanguagesData(j, languageData);
            for(auto& ln : languageData){
                conData.data.push_back(ln);
            }
        }

        if(j.contains(jsonKeyToString(JsonKeys::dark_vision))){
            DarkvisionData* darkvisionData = new DarkvisionData();
            extractAndApplyDarkVisionData(j, darkvisionData);
            conData.data.push_back(darkvisionData);
        }

        if(j.contains(jsonKeyToString(JsonKeys::resilience))){
            std::vector<ResilienceData*> resilienceData;
            extractAndApplyResilienceData(j, resilienceData);
            for(auto& rd : resilienceData){
                conData.data.push_back(rd);
            }
        }

        if(j.contains(jsonKeyToString(JsonKeys::proficiency))){
            ProficiencyData* proficiencyData = new ProficiencyData();
            extractAndApplyProficiencyData(j, proficiencyData);
            conData.data.push_back(proficiencyData);
        }

        if(j.contains(jsonKeyToString(JsonKeys::sleep_duration_hrs))){
            SleepDurationData* sleepDuration = new SleepDurationData();
            extractAndApplySleepDurationData(j, sleepDuration);
            conData.data.push_back(sleepDuration);
        }

        if(j.contains(jsonKeyToString(JsonKeys::item))){
            std::vector<ItemData*> itemData;
            extractAndApplyItemData(j, itemData);
            for(auto& item : itemData){
                conData.data.push_back(item);
            }
        }

    }
    else{
        throw std::runtime_error("Couldnt read file" + t_path);
    }
}

void updateConsolidatedOptionsData(const std::string& t_path, ConsolidatedOptionsData& optionsData){

    json j;
    if(readJsonFile(t_path, j)){
        if(j.contains(jsonKeyToString(JsonKeys::options))){
            for(auto& op : j[jsonKeyToString(JsonKeys::options)]){
                if(!op.contains(jsonKeyToString(JsonKeys::attribute))){
                    throw std::runtime_error("mandatory field 'attribute' not available in options JSON data: " + op.dump());
                }

                if(op[jsonKeyToString(JsonKeys::attribute)] == jsonKeyToString(JsonKeys::proficiency)){
                    ProficiencyOptionData* profData;
                    getProficiencyOptions(op, profData);
                    optionsData.options.push_back(profData);
                }
                else if (op[jsonKeyToString(JsonKeys::attribute)] == jsonKeyToString(JsonKeys::languages)){
                    LanguageOptionData* langData;
                    getLanguageOptions(op, langData);
                    optionsData.options.push_back(langData);
                }
                else if(op[jsonKeyToString(JsonKeys::attribute)] == jsonKeyToString(JsonKeys::item)){
                    ItemOptionData* itemData;
                    getItemOptions(op, itemData);
                    optionsData.options.push_back(itemData);
                }
                else if(op[jsonKeyToString(JsonKeys::attribute)] == jsonKeyToString(JsonKeys::alignment)){
                    AlignmentOptionData* alignmentData = new AlignmentOptionData();
                    getAlignmentOptions(op, alignmentData);
                    optionsData.options.push_back(alignmentData);
                }
                else{
                    throw std::runtime_error("unsupported attribute type in options: " + op[jsonKeyToString(JsonKeys::attribute)].get<std::string>());
                }
            }
        }
    }
    else{
        throw std::runtime_error("Couldnt read file" + t_path);
    }
}

std::string getName(const std::string& t_path){
    json j;
    if (readJsonFile(t_path, j)){
        if(j.contains(jsonKeyToString(JsonKeys::name))){

            return j[jsonKeyToString(JsonKeys::name)];

        }
        else{

            throw std::runtime_error("Key 'name' not found in race JSON file:" + t_path);
        }
    }
    else{
        throw std::runtime_error("Path doesnt exist:" + t_path);
    }
    return "";
}

bool getIfAbstract(const std::string& t_path){
    json j;
    if (readJsonFile(t_path, j)){
        if(j.contains(jsonKeyToString(JsonKeys::is_abstract))){

            return j[jsonKeyToString(JsonKeys::is_abstract)];

        }
        else{

            throw std::runtime_error("Key 'is_abstract' not found in race JSON file:" + t_path);
        }
    }
    else{
        throw std::runtime_error("Path doesnt exist:" + t_path);
    }
    return false;
}



bool getBaseRace(const std::string& t_racePath, std::string& baseRace){
    
    json j;
    if (readJsonFile(t_racePath, j)){

        if(j.contains(jsonKeyToString(JsonKeys::base_race))){

            if(j[jsonKeyToString(JsonKeys::base_race)].is_string()){
                baseRace = j[jsonKeyToString(JsonKeys::base_race)];
                return true;
            }
            else{
                return false;
            }
        }
        else{
            throw std::runtime_error("Key 'base_race' missing in " + t_racePath);
        }

    }
    else{
        throw std::runtime_error("Path doesnt exist:" + t_racePath);
    }
    return false;
}


bool getBaseClass(const std::string& t_classPath, std::string& baseClass){
    
    json j;
    if (readJsonFile(t_classPath, j)){

        if(j.contains(jsonKeyToString(JsonKeys::base_class))){

            if(j[jsonKeyToString(JsonKeys::base_class)].is_string()){
                baseClass = j[jsonKeyToString(JsonKeys::base_class)];
                return true;
            }
            else{
                return false;
            }
        }
        else{
            throw std::runtime_error("Key 'base_class' missing in " + t_classPath);
        }

    }
    else{
        throw std::runtime_error("Path doesnt exist:" + t_classPath);
    }
    return false;
}