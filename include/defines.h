#pragma once

#include <vector>
#include <string>
#include <cmath>

//------Vector of Abilities

std::vector<std::string> g_abilitiesVector = {
    "Strength",
    "Dexterity",
    "Constitution",
    "Intelligence",
    "Wisdom",
    "Charisma"
};

//------Vector of Character Params

std::vector<std::string> g_characterParamsVector = {
    "HitPoints"
};

//------Vector of Races

std::vector<std::string> g_racesVector = {
    "Hill Dwarf",
    "Mountain Dwarf",
    "High Elf",
    "Wood Elf",
    "Dark Elf",
    "LightFoot Halfling",
    "Stout Halfling",
    "Human"
};

//------Vector of Classes

std::vector<std::string> g_classesVector = {
    "Fighter",
    "Cleric",
    "Rogue",
    "Wizard"
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


//------custom race data struct

struct CustomRaceData{

};
