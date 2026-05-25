#include "commonJsonParser.h"
#include "raceData.h"
#include "utilities.h"
#include "playerInput.h"
#include "gameData.h"
#include "randomize.h"


void extractAndApplyAbilityMods(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::ability_mods))){
        for (const auto& mod : j[jsonKeyToString(JsonKeys::ability_mods)]) {
            std::string ability = mod[jsonKeyToString(JsonKeys::ability)];
            int value = mod[jsonKeyToString(JsonKeys::mod)];
            raceData.addAbilityMod(ability, value);
        }
    }
}

void extractAndApplyParamMods(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::param_mods))){
        for (const auto& mod : j[jsonKeyToString(JsonKeys::param_mods)]) {
            std::string param = mod[jsonKeyToString(JsonKeys::param)];
            int value = mod[jsonKeyToString(JsonKeys::mod)];
            raceData.addParamMod(param, value);
        }
    }
}

void extractAndApplyAgeData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::age))){
        unsigned short int maturityAge = j[jsonKeyToString(JsonKeys::age)][jsonKeyToString(JsonKeys::maturity)];
        unsigned short int avgLifespan = j[jsonKeyToString(JsonKeys::age)][jsonKeyToString(JsonKeys::life_span)];
        raceData.setAgeData(maturityAge, avgLifespan);
    }
}

void extractAndApplyAlignmentData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::alignment))){
        Alignment alignment = stringToAlignment(j[jsonKeyToString(JsonKeys::alignment)]);
        raceData.setAlignment(alignment);
    }
}

void extractAndApplySizeData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::size))){
        SizeCategory szCat = stringToSizeCategory(j[jsonKeyToString(JsonKeys::size)][jsonKeyToString(JsonKeys::category)]);
        raceData.setSizeData(szCat, j[jsonKeyToString(JsonKeys::size)][jsonKeyToString(JsonKeys::avg_height_m)], j[jsonKeyToString(JsonKeys::size)][jsonKeyToString(JsonKeys::avg_weight_kg)]);
    }
}

void extractAndApplySpeedData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::speed_mps))){
        raceData.setSpeed(j[jsonKeyToString(JsonKeys::speed_mps)]);
    }
}

void extractAndApplyLanguagesData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::languages))){
        for (const auto& lang : j[jsonKeyToString(JsonKeys::languages)]) {
            std::string language = lang[jsonKeyToString(JsonKeys::name)];
            bool speak = lang[jsonKeyToString(JsonKeys::speak)];
            bool read = lang[jsonKeyToString(JsonKeys::read)];
            bool write = lang[jsonKeyToString(JsonKeys::write)];
            raceData.addLanguageProficiency(language, speak, read, write);
        }
    }
}

void extractAndApplyDarkVisionData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::dark_vision))){
        bool hasDarkvision = j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::has_darkvision)];

        IlluminationType dimLightEq = stringToIlluminationType(j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::dim_light_eq)][jsonKeyToString(JsonKeys::as_ambient)]); 
        float hasDimLightEqDist = j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::dim_light_eq)][jsonKeyToString(JsonKeys::distance_m)];
        IlluminationType darkLightEq = stringToIlluminationType(j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::darkness_eq)][jsonKeyToString(JsonKeys::as_ambient)]);
        float hasDarkvisionEqDist = j[jsonKeyToString(JsonKeys::dark_vision)][jsonKeyToString(JsonKeys::darkness_eq)][jsonKeyToString(JsonKeys::distance_m)];

        raceData.setDarkvisionData(hasDarkvision, std::pair<IlluminationType, float>(dimLightEq, hasDimLightEqDist), 
        std::pair<IlluminationType, float>(darkLightEq, hasDarkvisionEqDist));
    }
}

void extractAndApplyResilienceData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::resilience))){
        for(const auto& res : j[jsonKeyToString(JsonKeys::resilience)]){

            std::string affliction = res[jsonKeyToString(JsonKeys::affliction)];
            bool immune = false;
            if(res.contains(jsonKeyToString(JsonKeys::immune))){
                immune = res[jsonKeyToString(JsonKeys::immune)];
            }
            bool hasAdvantage = false;
            if(res.contains(jsonKeyToString(JsonKeys::has_advantage))){
                hasAdvantage = res[jsonKeyToString(JsonKeys::has_advantage)];
            }
            bool hasResistance = false;
            if(res.contains(jsonKeyToString(JsonKeys::has_resistance))){
                hasResistance = res[jsonKeyToString(JsonKeys::has_resistance)];
            }

            raceData.addResilience(affliction, immune, hasAdvantage, hasResistance);
        }
    }
}

void extractAndApplyProficiencyData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::proficiency))){
        if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::weapons))){
            for(const auto& wp : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::weapons)]){
                raceData.setProficiencyData(ProficiencyType::Weapons, wp);
            }
        }

        if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::armors))){
            for(const auto& ar : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::armors)]){
                raceData.setProficiencyData(ProficiencyType::Armors, ar);
            }
        }

        if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::tools))){
            for(const auto& tl : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::tools)]){
                raceData.setProficiencyData(ProficiencyType::Tools, tl);
            }
        }

        if(j[jsonKeyToString(JsonKeys::proficiency)].contains(jsonKeyToString(JsonKeys::skills))){
            for(const auto& sk : j[jsonKeyToString(JsonKeys::proficiency)][jsonKeyToString(JsonKeys::skills)]){
                raceData.setProficiencyData(ProficiencyType::Skills, sk);
            }
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


std::vector<std::string> findAllRaces(const std::string& t_racePath){

    std::vector<std::string> racesVector;

    if (!std::filesystem::exists(t_racePath) || !std::filesystem::is_directory(t_racePath)) {
        return racesVector;
    }

    for (const auto& entry : std::filesystem::directory_iterator(t_racePath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            
            json j;
            if (readJsonFile(entry.path().string(), j)){
                if(j.contains(jsonKeyToString(JsonKeys::name))){

                    if(j.contains(jsonKeyToString(JsonKeys::is_abstract))){

                        if(j[jsonKeyToString(JsonKeys::is_abstract)] == false){
                            racesVector.push_back(j[jsonKeyToString(JsonKeys::name)]);
                        }

                    }
                    else{
                        throw std::runtime_error("Key 'is_abstract' not found in race JSON file:" + entry.path().string());
                    }

                }
                else{

                    throw std::runtime_error("Key 'name' not found in race JSON file:" + entry.path().string());
                }
            }
            
        }
    }

    return racesVector;
}

void extractAndApplySleepDurationData(json& j, RaceData& raceData){
    if(j.contains(jsonKeyToString(JsonKeys::sleep_duration_hrs))){
        float sleepDuration = j[jsonKeyToString(JsonKeys::sleep_duration_hrs)];
        raceData.setSleepDuration(sleepDuration);
    }
}

std::vector<std::string> getProficiencyChoices(json& j, const std::string& profType, bool enablePlayerInputs){

    std::pair<std::vector<std::string>, unsigned short int> profOptions;

    profOptions.second = j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::proficiency)][profType][jsonKeyToString(JsonKeys::choose)].get<unsigned short int>();

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::proficiency)][profType][jsonKeyToString(JsonKeys::all)] == false){
        profOptions.first = j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::proficiency)][profType][jsonKeyToString(JsonKeys::choices)].get<std::vector<std::string>>();            
    }
    else{
        //todo : after getting complete prof list
    }

    std::vector<std::string> chosenProficiencies;
    
    if(!profOptions.first.empty() && enablePlayerInputs){
        if(enablePlayerInputs){
            chosenProficiencies = getPlayerInputOptionChoices(profOptions.first, profOptions.second);
        }
        else{
            chosenProficiencies = chooseRandomOptions(profOptions.first, profOptions.second);
        }
        
    }

    return chosenProficiencies;

}

void processProficiencyOptions(json& j, RaceData& raceData, bool enablePlayerInputs){

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::proficiency)].contains(proficiencyTypeToString(ProficiencyType::Weapons))){

        std::vector<std::string> choices = getProficiencyChoices(j, proficiencyTypeToString(ProficiencyType::Weapons), enablePlayerInputs);

        for(auto&ch : choices){
            raceData.setProficiencyData(ProficiencyType::Weapons, ch);
        }
            
    }

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::proficiency)].contains(proficiencyTypeToString(ProficiencyType::Armors))){

        std::vector<std::string> choices = getProficiencyChoices(j, proficiencyTypeToString(ProficiencyType::Armors), enablePlayerInputs);

        for(auto&ch : choices){
            raceData.setProficiencyData(ProficiencyType::Armors, ch);
        }
        
    }

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::proficiency)].contains(proficiencyTypeToString(ProficiencyType::Tools))){

        std::vector<std::string> choices = getProficiencyChoices(j, proficiencyTypeToString(ProficiencyType::Tools), enablePlayerInputs);

        for(auto&ch : choices){
            raceData.setProficiencyData(ProficiencyType::Tools, ch);
        }
        
    }

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::proficiency)].contains(proficiencyTypeToString(ProficiencyType::Skills))){

        std::vector<std::string> choices = getProficiencyChoices(j, proficiencyTypeToString(ProficiencyType::Skills), enablePlayerInputs);

        for(auto&ch : choices){
            raceData.setProficiencyData(ProficiencyType::Skills, ch);
        }
        
    }


}

void processLanguageOptions(json& j, RaceData& raceData, bool enablePlayerInputs){

    std::pair<std::vector<std::string>, unsigned short int> langOptions;

    langOptions.second = j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)][jsonKeyToString(JsonKeys::choose)].get<unsigned short int>();

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)][jsonKeyToString(JsonKeys::all)] == false){
        langOptions.first = j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)][jsonKeyToString(JsonKeys::choices)].get<std::vector<std::string>>();            
    }
    else{
        for(auto& lo : GameData::getInstance()->getLanguagesVector()){
            langOptions.first.push_back(lo);
        }
    }

    std::vector<std::string> chosenLanguages;
    
    if(!langOptions.first.empty()){
        if(enablePlayerInputs){
            chosenLanguages = getPlayerInputOptionChoices(langOptions.first, langOptions.second);
        }
        else{
            chosenLanguages = chooseRandomOptions(langOptions.first, langOptions.second);
        }
        
    }

    bool lnSpeak = true;
    bool lnRead = true;
    bool lnWrite = true;

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)].contains(jsonKeyToString(JsonKeys::speak))){
        lnSpeak = j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)][jsonKeyToString(JsonKeys::speak)];
    }

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)].contains(jsonKeyToString(JsonKeys::read))){
        lnRead = j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)][jsonKeyToString(JsonKeys::read)];
    }

    if(j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)].contains(jsonKeyToString(JsonKeys::write))){
        lnWrite = j[jsonKeyToString(JsonKeys::options)][jsonKeyToString(JsonKeys::languages)][jsonKeyToString(JsonKeys::write)];
    }

    for(auto& ch : chosenLanguages){
        raceData.addLanguageProficiency(ch, lnSpeak, lnRead, lnWrite);
    }

}

void extractAndApplyOptionsData(json& j, RaceData& raceData, bool enablePlayerInputs){


    if(j.contains(jsonKeyToString(JsonKeys::options))){
        if(j[jsonKeyToString(JsonKeys::options)].contains(jsonKeyToString(JsonKeys::proficiency))){
            processProficiencyOptions(j, raceData, enablePlayerInputs);
        }

        if(j[jsonKeyToString(JsonKeys::options)].contains(jsonKeyToString(JsonKeys::languages))){
            processLanguageOptions(j, raceData, enablePlayerInputs);
        }
            
    }



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