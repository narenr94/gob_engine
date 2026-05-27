#include "raceData.h"
#include "character.h"
#include "utilities.h"

void RaceData::applyRaceData(Character* t_character){
    //----ability mod data
    for(auto& amd : abilityModData){
        amd.applyData(t_character);
    }

    //-----param mod data
    for(auto& pmd : paramModData){
        pmd.applyData(t_character);
    }

    //----Age data
    ageData.applyData(t_character);

    //------Alignment
    t_character->updateAlignment(alignment);

    //------Size
    sizeData.applyData(t_character);
    
    //-----Speed
    t_character->updateSpeed(speed);

    //-----Languages
    for(auto& lg : languagesVector){
        lg.applyData(t_character);
    }

    //------Proficiency
    proficiencyData.applyData(t_character);

    //------resilience
    for(auto& rs : resilienceDataVector){
        rs.applyData(t_character);
    }

    //-------Darkvision
    darkvisionData.applyData(t_character);

}

void RaceData::printData(){

    //----ability mod data
    for(auto& amd : abilityModData){
        amd.printData();
    }

    //-----param mod data
    for(auto& pmd : paramModData){
        pmd.printData();
    }

    //----Age data
    ageData.printData();

    //------Alignment
    LOG("Alignment:" + alignmentToString(alignment));

    //------Size
    sizeData.printData();
    
    //-----Speed
    LOG("Speed Data:" + std::to_string(speed));

    //-----Languages
    for(auto& lg : languagesVector){
        lg.printData();
    }

    //------Proficiency
    proficiencyData.printData();

    //------resilience
    for(auto& rs : resilienceDataVector){
        rs.printData();
    }

    //-------Darkvision
    darkvisionData.printData();

}

void RaceData::setAgeData(unsigned short int maturityAge, unsigned short int avgLifespan){
    ageData.maturityAge = maturityAge;
    ageData.avgLifespan = avgLifespan;
}

void RaceData::setAlignment(Alignment t_alignment){
    alignment = t_alignment;
}

void RaceData::setSizeData(const SizeCategory category, float height, float weight){
    sizeData.category = category;
    sizeData.dimensions = {height, weight};
}

void RaceData::setSpeed(float t_speed){
    speed = t_speed;
}

void RaceData::setDarkvisionData(bool hasDarkvision, std::pair<IlluminationType, float> dim_light_eq, std::pair<IlluminationType, float> darkvision_eq){
    darkvisionData.hasDarkvision = hasDarkvision;
    darkvisionData.dim_light_eq = dim_light_eq.first;
    darkvisionData.dim_light_eq_dist = dim_light_eq.second;
    darkvisionData.darkvision_eq = darkvision_eq.first;
    darkvisionData.darkvision_eq_dist = darkvision_eq.second;
}

void RaceData::setSleepDuration(float duration){
    sleepDurationHrs = duration;
}


//-----additive data

void RaceData::setProficiencyData(const ProficiencyType t_type, const std::string& proficiency){

    switch (t_type)
    {
    case ProficiencyType::Weapons:
        for(const auto& wp : proficiencyData.weaponProficiencies){
            if(wp == proficiency){
                return;
            }
        }
        proficiencyData.weaponProficiencies.push_back(proficiency);      
        break;
    case ProficiencyType::Armors:
        for(const auto& ap : proficiencyData.armorProficiencies){
            if(ap == proficiency){
                return;
            }
        }
        proficiencyData.armorProficiencies.push_back(proficiency);
        break;
    case ProficiencyType::Tools:
        for(const auto& tp : proficiencyData.toolProficiencies){
            if(tp == proficiency){
                return;
            }
        }
        proficiencyData.toolProficiencies.push_back(proficiency);
        break;
    case ProficiencyType::Skills:
        for(const auto& sp : proficiencyData.skillProficiencies){
            if(sp == proficiency){
                return;
            }
        }
        proficiencyData.skillProficiencies.push_back(proficiency);
        break;
    case ProficiencyType::SavingThrows:
        for(const auto& sp : proficiencyData.savingThrowsProficiencies){
            if(sp == proficiency){
                return;
            }
        }
        proficiencyData.savingThrowsProficiencies.push_back(proficiency);
    default:
        break;
    }

}



void RaceData::addAbilityMod(const std::string& ability, int mod){
    bool modExists = false;

    for(const auto& am : abilityModData){
        if(am.abilityMod.first == ability){
            modExists = true;
            const_cast<std::pair<std::string, int>&>(am.abilityMod).second += mod;
            break;
        }
    }

    if(!modExists){
        AbilityModData newMod;
        newMod.abilityMod = {ability, mod};

        abilityModData.push_back(newMod);
    }

}

void RaceData::addParamMod(const std::string& param, int mod){
    bool modExists = false;

    for(const auto& pm : paramModData){
        if(pm.paramMod.first == param){
            modExists = true;
            const_cast<std::pair<std::string, int>&>(pm.paramMod).second += mod;
            break;
        }
    }

    if(!modExists){
        ParamModData newMod;
        newMod.paramMod = {param, mod};

        paramModData.push_back(newMod);
    }

}

void RaceData::addLanguageProficiency(const std::string& language, bool speak, bool read, bool write){

    bool languageExists = false;

    for(const auto& lang : languagesVector){
        if(lang.language == language){
            languageExists = true;

            if(speak){
                const_cast<LanguageData&>(lang).speak = true;
            }

            if(read){
                const_cast<LanguageData&>(lang).read = true;
            }
            if(write){
                const_cast<LanguageData&>(lang).write = true;
            }

            break;
        }
    }

    if(!languageExists){
        LanguageData newLanguage;
        newLanguage.language = language;
        newLanguage.speak = speak;
        newLanguage.read = read;
        newLanguage.write = write;

        languagesVector.push_back(newLanguage);
    }

}

void RaceData::addResilience(const std::string& affliction, bool immune, bool hasAdvantage, bool hasResistance){
    
    bool resilienceExists = false;
    for(const auto& res : resilienceDataVector){
        if(res.affliction == affliction){
            resilienceExists = true;
            if(immune){
                const_cast<ResilienceData&>(res).immune = true;
            }
            if(hasAdvantage){
                const_cast<ResilienceData&>(res).hasAdvantage = true;
            }
            if(hasResistance){
                const_cast<ResilienceData&>(res).hasResistance = true;
            }
            break;
        }
    }

    if(!resilienceExists){
        ResilienceData data;
        data.affliction = affliction;
        data.immune = immune;
        data.hasAdvantage = hasAdvantage;
        data.hasResistance = hasResistance;

        resilienceDataVector.push_back(data);
    }
}

void RaceData::updateOptionsData(const OptionsData& t_optionsData){
    optionsData += t_optionsData;
}

void getRaceDataFrom(const std::string& t_racePath, RaceData& raceData){
    
    json j;
    if(readJsonFile(t_racePath, j)){

        if(j.contains("base_race")){

            if(j["base_race"].is_string()){
                std::string baseRaceName = j["base_race"];
                std::string baseRacePath = std::filesystem::path(t_racePath).parent_path().string() + "/" + baseRaceName + ".json";
                getRaceDataFrom(baseRacePath, raceData);
            }
            
            //ability mods
            if(j.contains(jsonKeyToString(JsonKeys::ability_mods))){
                std::vector<AbilityModData> abilityModsData;
                extractAndApplyAbilityMods(j, abilityModsData);
                for(const auto& am : abilityModsData){
                    raceData.addAbilityMod(am.abilityMod.first, am.abilityMod.second);
                }
            }

            //param mods
            if(j.contains(jsonKeyToString(JsonKeys::param_mods))){
                std::vector<ParamModData> paramModData;
                extractAndApplyParamMods(j, paramModData);
                for(const auto& pm : paramModData){
                    raceData.addParamMod(pm.paramMod.first, pm.paramMod.second);
                }
            }

            //age
            if(j.contains(jsonKeyToString(JsonKeys::age))){
                AgeData ageData;
                extractAndApplyAgeData(j, ageData);
                raceData.setAgeData(ageData.maturityAge, ageData.avgLifespan);
            }

            //alignment
            if(j.contains(jsonKeyToString(JsonKeys::alignment))){
                Alignment alignment;
                extractAndApplyAlignmentData(j, alignment);
                raceData.setAlignment(alignment);
            }
            

            //size
            if(j.contains(jsonKeyToString(JsonKeys::size)))
            {
                SizeData sizeData;
                extractAndApplySizeData(j, sizeData);
                raceData.setSizeData(sizeData.category, sizeData.dimensions.first, sizeData.dimensions.second);
            }            

            //speed
            if(j.contains(jsonKeyToString(JsonKeys::speed_mps))){
                float speedData;
                extractAndApplySpeedData(j, speedData);
                raceData.setSpeed(speedData);
            }

            //languages
            if(j.contains(jsonKeyToString(JsonKeys::languages))){
                std::vector<LanguageData> languageData;
                extractAndApplyLanguagesData(j, languageData);
                for(const auto& lg : languageData){
                    raceData.addLanguageProficiency(lg.language, lg.speak, lg.read, lg.write);
                }
            }

            //darkvision
            if(j.contains(jsonKeyToString(JsonKeys::dark_vision))){
                    DarkvisionData darkvisionData;
                    extractAndApplyDarkVisionData(j, darkvisionData);
                    raceData.setDarkvisionData(darkvisionData.hasDarkvision, {darkvisionData.dim_light_eq, darkvisionData.dim_light_eq_dist}, {darkvisionData.darkvision_eq, darkvisionData.darkvision_eq_dist});
            }

            //resilience
            if(j.contains(jsonKeyToString(JsonKeys::resilience))){
                std::vector<ResilienceData> resilienceData;
                extractAndApplyResilienceData(j, resilienceData);
                for(const auto& rs : resilienceData){
                    raceData.addResilience(rs.affliction, rs.immune, rs.hasAdvantage, rs.hasResistance);
                }
            }

            //proficiencies
            if(j.contains(jsonKeyToString(JsonKeys::proficiency))){
                ProficiencyData proficiencyData;
                extractAndApplyProficiencyData(j, proficiencyData);
                for(const auto& wp : proficiencyData.weaponProficiencies){
                    raceData.setProficiencyData(ProficiencyType::Weapons, wp);
                }
            }

            //sleep duration
            if(j.contains(jsonKeyToString(JsonKeys::sleep_duration_hrs))){
                float sleepDuration;
                extractAndApplySleepDurationData(j, sleepDuration);
                raceData.setSleepDuration(sleepDuration);
            }

            //options
            if(j.contains(jsonKeyToString(JsonKeys::options))){
                OptionsData optionsData;
                extractAndApplyOptionsData(j, optionsData);
                raceData.updateOptionsData(optionsData);
            }
            

            //todo : traits

        }
        else{
            throw std::runtime_error("base_race key not found in race JSON file:" + t_racePath);
        }

    }
}