#pragma once

#include <vector>
#include <string>

//------Setup Default Abilities

std::vector<std::string> g_defaultAbilities = {
    "Strength",
    "Dexterity",
    "Constitution",
    "Intelligence",
    "Wisdom",
    "Charisma"
};

//------All available character list
enum class CharacterClass{

    Fighter,
    Cleric,
    Rouge,
    Wizard,
    NA

};

enum class CharacterRace{
    Hill_Dwarf,
    Mountain_Dwarf,
    High_Elf,
    Wood_Elf,
    Dark_Elf,
    Lightfoot_Halfling,
    Stout_Halfling,
    Human,
    NA
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

