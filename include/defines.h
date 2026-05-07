#pragma once

//------All available character list
enum class CharacterClass{

    Human_Warrior,
    Human_Mage,
    Human_Ranger,
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

struct ConsumableEffects{
    int healthOffset = 0;
    int staminaOffset = 0;
    int manaOffset = 0;

    int intelligenceOffset = 0;
    int strengthOffset = 0;
    int charismaOffset = 0;
    int dexterityOffset = 0;
    int agilityOffset = 0;
};

