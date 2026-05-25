#pragma once

#include "log.h"

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>

#define ABILITY_SCORE_MAX 20

#define DEFAULT_PARAM_DIE 8

class Character; //Forward declaration

enum class SizeCategory{
    Tiny,
    Small,
    Medium,
    Large,
    Huge,
    Garg
};

enum class ProficiencyType{
    Weapons,
    Armors,
    Tools,
    Skills
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

const std::vector<std::pair<Level, unsigned int>> g_expPointsLookupTable = {
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

const std::vector<std::pair<Level, unsigned short int>> g_proficiencyBonusLookupTable = {
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

const std::vector<std::pair<Alignment,std::string>> alignmentStrMap = {
    {Alignment::lawful_good, "lawful_good"},
    {Alignment::lawful_neutral, "lawful_neutral"},
    {Alignment::lawful_evil, "lawful_evil"},
    {Alignment::neutral_good, "neutral_good"},
    {Alignment::neutral_neutral, "neutral_neutral"},
    {Alignment::neutral_evil, "neutral_evil"},
    {Alignment::chaotic_good, "chaotic_good"},
    {Alignment::chaotic_neutral, "chaotic_neutral"},
    {Alignment::chaotic_evil, "chaotic_evil"},
};

const std::vector<std::pair<SizeCategory, std::string>> sizeCategoryStrMap = {
    {SizeCategory::Tiny, "tiny"},
    {SizeCategory::Small, "small"},
    {SizeCategory::Medium, "medium"},
    {SizeCategory::Tiny, "tiny"},
    {SizeCategory::Large, "large"},
    {SizeCategory::Huge, "huge"},
    {SizeCategory::Garg, "gargantuan"},
};

const std::vector<std::pair<IlluminationType, std::string>> illumincationTypeStrMap = {
    {IlluminationType::Normal, "normal"},
    {IlluminationType::Dim, "dim"},
    {IlluminationType::Dark, "dark"}
};


const std::vector<std::pair<ProficiencyType, std::string>> proficiencyTypeStrMap = {
    {ProficiencyType::Weapons, "weapons"},
    {ProficiencyType::Armors, "armors"},
    {ProficiencyType::Tools, "tools"},
    {ProficiencyType::Skills, "skills"}
};

struct AgeData{
    unsigned short int maturityAge;
    unsigned short int avgLifespan;

    void printData();
    void applyData(Character* t_character);
}; 

struct SizeData{
    SizeCategory category;
    std::pair<float, float> dimensions; //height in meters, weight in kgs

    void printData();
    void applyData(Character* t_character);
};

struct LanguageData{
    std::string language;
    bool speak = false;
    bool read = false;
    bool write = false;

    void printData();
    void applyData(Character* t_character);
};

struct ProficiencyData{

    std::vector<std::string> weaponProficiencies;
    std::vector<std::string> armorProficiencies;
    std::vector<std::string> toolProficiencies;
    std::vector<std::string> skillProficiencies;

    void printData();
    void applyData(Character* t_character);

};

struct ResilienceData{
    std::string affliction;
    bool immune = false;
    bool hasAdvantage = false;
    bool hasResistance = false;

    void printData();
    void applyData(Character* t_character);
};

struct DarkvisionData{
    bool hasDarkvision = false;
    IlluminationType dim_light_eq = IlluminationType::Dim;
    float dim_light_eq_dist = 0.0f;
    IlluminationType darkvision_eq = IlluminationType::Dark;
    float darkvision_eq_dist = 0.0f;

    void printData();
    void applyData(Character* t_character);
};

struct AbilityModData{
    std::pair<std::string, int> abilityMod;
    
    void printData();
    void applyData(Character* t_character);
    
};

struct ParamModData{
    std::pair<std::string, int> paramMod;
    
    void printData();
    void applyData(Character* t_character);
    
};


