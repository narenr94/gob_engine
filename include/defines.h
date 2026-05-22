#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

//------Vector of Abilities

std::vector<std::string> g_abilitiesVector;

//------Vector of Character Params

std::vector<std::string> g_characterParamsVector;

//------Vector of Classes

std::vector<std::string> g_classesVector;

enum class SizeCategory{
    Tiny,
    Small,
    Medium,
    Large,
    Huge,
    Garg
};

enum class ProficiencyType{
    Weapon,
    Armor,
    Tool
};

enum class IlluminationType{
    Normal,
    Dim,
    Dark
};

//------Level enum

enum class Level{
    Lvl1,
    Lvl2,
    Lvl3,
    Lvl4,
    Lvl5,
    Lvl6,
    Lvl7,
    Lvl8,
    Lvl9,
    Lvl10,
    Lvl11,
    Lvl12,
    Lvl13,
    Lvl14,
    Lvl15,
    Lvl16,
    Lvl17,
    Lvl18,
    Lvl19,
    Lvl20
};

//------Alignment

enum class Alignment{

    lawful_good,
    lawful_neutral,
    lawful_evil,

    neutral_good,
    neutral_neutral,
    neutral_evil,

    chaotic_good,
    chaotic_neutral,
    chaotic_evil

};

//------All items list
enum class ItemType{
    Minor_Health_Potion,
    Minor_Stamina_Potion,
    Minor_Mana_Potion
};


//-----Item Utility

enum class ItemUtility{
    Consumable,
    CraftingIngredient,
    Armor,
    Weapon,
    Quest,
    NonCombat
};


//--------Lookup Tables

const std::map<Level, unsigned int> g_expPointsLookupTable = {
    {Level::Lvl1, 0},
    {Level::Lvl2, 300},
    {Level::Lvl3, 900},
    {Level::Lvl4, 2700},
    {Level::Lvl5, 6500},
    {Level::Lvl6, 14000},
    {Level::Lvl7, 23000},
    {Level::Lvl8, 34000},
    {Level::Lvl9, 48000},
    {Level::Lvl10, 64000},
    {Level::Lvl11, 85000},
    {Level::Lvl12, 100000},
    {Level::Lvl13, 120000},
    {Level::Lvl14, 140000},
    {Level::Lvl15, 165000},
    {Level::Lvl16, 195000},
    {Level::Lvl17, 225000},
    {Level::Lvl18, 265000},
    {Level::Lvl19, 305000},
    {Level::Lvl20, 355000}

};

const std::map<Level, unsigned short int> g_proficiencyBonusLookupTable = {
    {Level::Lvl1, 2},
    {Level::Lvl2, 2},
    {Level::Lvl3, 2},
    {Level::Lvl4, 2},
    {Level::Lvl5, 3},
    {Level::Lvl6, 3},
    {Level::Lvl7, 3},
    {Level::Lvl8, 3},
    {Level::Lvl9, 4},
    {Level::Lvl10, 4},
    {Level::Lvl11, 4},
    {Level::Lvl12, 4},
    {Level::Lvl13, 5},
    {Level::Lvl14, 5},
    {Level::Lvl15, 5},
    {Level::Lvl16, 5},
    {Level::Lvl17, 6},
    {Level::Lvl18, 6},
    {Level::Lvl19, 6},
    {Level::Lvl20, 6}
};


struct AgeData{
    unsigned short int maturityAge;
    unsigned short int avgLifespan;
}; 

struct SizeData{
    SizeCategory category;
    std::pair<float, float> dimensions; //height in meters, weight in kgs
};

struct LanguageData{
    std::string language;
    bool speak = false;
    bool read = false;
    bool write = false;
};

struct ProficiencyData{

    std::vector<std::string> weaponProficiencies;
    std::vector<std::pair<std::vector<std::string>, unsigned short int>> weaponProficienciesOptions;
    std::vector<std::string> armorProficiencies;
    std::vector<std::pair<std::vector<std::string>, unsigned short int>> armorProficienciesOptions;
    std::vector<std::string> toolProficiencies;
    std::vector<std::pair<std::vector<std::string>, unsigned short int>> toolProficienciesOptions;

};

struct ResilienceData{
    std::string affliction;
    bool immune = false;
    bool hasAdvantage = false;
    bool hasResistance = false;
};

struct DarkvisionData{
    bool hasDarkvision = false;
    IlluminationType dim_light_eq = IlluminationType::Dim;
    float dim_light_eq_dist = 0.0f;
    IlluminationType darkvision_eq = IlluminationType::Dark;
    float darkvision_eq_dist = 0.0f;
};

struct AttributeModData{
    std::pair<std::string, int> abilityMod;
    AttributeModData() = default;
    
};

struct RaceData{

    private:

    std::vector<AttributeModData> attributeModData;
    AgeData ageData;
    Alignment alignment;
    SizeData sizeData;
    float speed;
    std::vector<LanguageData> languagesVector;
    ProficiencyData proficiencyData;
    std::vector<ResilienceData> resilienceDataVector;
    DarkvisionData darkvisionData;

    public:

    //-----replace data

    void setAgeData(unsigned short int maturityAge, unsigned short int avgLifespan){
        ageData.maturityAge = maturityAge;
        ageData.avgLifespan = avgLifespan;
    }

    void setAlignment(Alignment t_alignment){
        alignment = t_alignment;
    }

    void setSizeData(const SizeCategory category, float height, float weight){
        sizeData.category = category;
        sizeData.dimensions = {height, weight};
    }

    void setSpeed(float t_speed){
        speed = t_speed;
    }

    void setDarkvisionData(bool hasDarkvision, std::pair<IlluminationType, float> dim_light_eq, std::pair<IlluminationType, float> darkvision_eq){
        darkvisionData.hasDarkvision = hasDarkvision;
        darkvisionData.dim_light_eq = dim_light_eq.first;
        darkvisionData.dim_light_eq_dist = dim_light_eq.second;
        darkvisionData.darkvision_eq = darkvision_eq.first;
        darkvisionData.darkvision_eq_dist = darkvision_eq.second;
    }


    //-----additive data

    void setProficiencyData(const ProficiencyType t_type, const std::string& proficiency){
    
        switch (t_type)
        {
        case ProficiencyType::Weapon:
            proficiencyData.weaponProficiencies.push_back(proficiency);
            break;
        case ProficiencyType::Armor:
            proficiencyData.armorProficiencies.push_back(proficiency);
            break;
        case ProficiencyType::Tool:
            proficiencyData.toolProficiencies.push_back(proficiency);
            break;
        default:
            break;
        }
    
    }

    

    void addAttributeMod(const std::string& ability, int mod){
        bool modExists = false;

        for(const auto& am : attributeModData){
            if(am.abilityMod.first == ability){
                modExists = true;
                const_cast<std::pair<std::string, int>&>(am.abilityMod).second += mod;
                break;
            }
        }

        if(!modExists){
            AttributeModData newMod;
            newMod.abilityMod = {ability, mod};

            attributeModData.push_back(newMod);
        }

    }

    void addLanguageProficiency(const std::string& language, bool speak, bool read, bool write){
    
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

    void addResilience(const std::string& affliction, bool immune, bool hasAdvantage, bool hasResistance){
        
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
            data.immune = immune;
            data.hasAdvantage = hasAdvantage;
            data.hasResistance = hasResistance;

            resilienceDataVector.push_back(data);
        }
    }

};

//------Vector of Races

std::vector<std::pair<std::string, RaceData>> g_racesVector;


Alignment stringToAlignment(const std::string& alignmentStr){
    if(alignmentStr == "lawful_good"){
        return Alignment::lawful_good;
    }
    else if(alignmentStr == "lawful_neutral"){
        return Alignment::lawful_neutral;
    }
    else if(alignmentStr == "lawful_evil"){
        return Alignment::lawful_evil;
    }
    else if(alignmentStr == "neutral_good"){
        return Alignment::neutral_good;
    }
    else if(alignmentStr == "neutral_neutral"){
        return Alignment::neutral_neutral;
    }
    else if(alignmentStr == "neutral_evil"){
        return Alignment::neutral_evil;
    }
    else if(alignmentStr == "chaotic_good"){
        return Alignment::chaotic_good;
    }
    else if(alignmentStr == "chaotic_neutral"){
        return Alignment::chaotic_neutral;
    }
    else if(alignmentStr == "chaotic_evil"){
        return Alignment::chaotic_evil;
    }
    
    throw std::runtime_error("Invalid alignment string: " + alignmentStr);

    return Alignment::neutral_neutral;
}

SizeCategory stringToSizeCategory(const std::string& sizeCategoryStr){
    if(sizeCategoryStr == "tiny"){
        return SizeCategory::Tiny;
    }
    else if(sizeCategoryStr == "small"){
        return SizeCategory::Small;
    }
    else if(sizeCategoryStr == "medium"){
        return SizeCategory::Medium;
    }
    else if(sizeCategoryStr == "large"){
        return SizeCategory::Large;
    }
    else if(sizeCategoryStr == "huge"){
        return SizeCategory::Huge;
    }
    else if(sizeCategoryStr == "gargantuan"){
        return SizeCategory::Garg;
    }

    throw std::runtime_error("Invalid size category string: " + sizeCategoryStr);

    return SizeCategory::Medium;
}

IlluminationType stringToIlluminationType(const std::string& illuminationTypeStr){

    if(illuminationTypeStr == "normal"){
        return IlluminationType::Normal;
    }
    else if(illuminationTypeStr == "dim"){
        return IlluminationType::Dim;
    }
    else if(illuminationTypeStr == "dark"){
        return IlluminationType::Dark;
    }

    throw std::runtime_error("Invalid illumination category string: " + illuminationTypeStr);

    return IlluminationType::Normal;
}


