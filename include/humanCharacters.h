#pragma once

#include "character.h"

#define WARRIOR_MAX_HEALTH_OFFSET   20
#define WARRIOR_MAX_STAMINA_OFFSET  10
#define WARRIOR_MAX_MANA_OFFSET     -5
#define WARRIOR_INTELLIGENCE_OFFSET -2
#define WARRIOR_STRENGTH_OFFSET      8
#define WARRIOR_CHARISMA_OFFSET     0
#define WARRIOR_DEXTERITY_OFFSET    3
#define WARRIOR_AGILITY_OFFSET      2

#define MAGE_MAX_HEALTH_OFFSET      -5
#define MAGE_MAX_STAMINA_OFFSET     -5
#define MAGE_MAX_MANA_OFFSET        25
#define MAGE_INTELLIGENCE_OFFSET    10
#define MAGE_STRENGTH_OFFSET        -3
#define MAGE_CHARISMA_OFFSET        4
#define MAGE_DEXTERITY_OFFSET       2
#define MAGE_AGILITY_OFFSET         1

#define RANGER_MAX_HEALTH_OFFSET      10
#define RANGER_MAX_STAMINA_OFFSET     15
#define RANGER_MAX_MANA_OFFSET        5
#define RANGER_INTELLIGENCE_OFFSET    2
#define RANGER_STRENGTH_OFFSET        4
#define RANGER_CHARISMA_OFFSET        1
#define RANGER_DEXTERITY_OFFSET       8
#define RANGER_AGILITY_OFFSET         6

static CharacterParamOffsets WarriorOffsets(){
    return {WARRIOR_MAX_HEALTH_OFFSET,
            WARRIOR_MAX_STAMINA_OFFSET,
            WARRIOR_MAX_MANA_OFFSET,
            WARRIOR_INTELLIGENCE_OFFSET,
            WARRIOR_STRENGTH_OFFSET,
            WARRIOR_CHARISMA_OFFSET,
            WARRIOR_DEXTERITY_OFFSET,
            WARRIOR_AGILITY_OFFSET
            };
}

class Warrior : public Character{
    public:
        Warrior(const std::string& t_name) :
        Character(t_name, WarriorOffsets()){}

        CharacterClass getClass() const override{
            return CharacterClass::Human_Warrior;
        }
};

static CharacterParamOffsets MageOffsets(){
    return {MAGE_MAX_HEALTH_OFFSET,
            MAGE_MAX_STAMINA_OFFSET,
            MAGE_MAX_MANA_OFFSET,
            MAGE_INTELLIGENCE_OFFSET,
            MAGE_STRENGTH_OFFSET,
            MAGE_CHARISMA_OFFSET,
            MAGE_DEXTERITY_OFFSET,
            MAGE_AGILITY_OFFSET
            };
}

class Mage : public Character{
    public:
        Mage(const std::string& t_name) :
        Character(t_name, MageOffsets()){}

        CharacterClass getClass() const override{
            return CharacterClass::Human_Mage;
        }
};

static CharacterParamOffsets RangerOffsets(){
    return {RANGER_MAX_HEALTH_OFFSET,
            RANGER_MAX_STAMINA_OFFSET,
            RANGER_MAX_MANA_OFFSET,
            RANGER_INTELLIGENCE_OFFSET,
            RANGER_STRENGTH_OFFSET,
            RANGER_CHARISMA_OFFSET,
            RANGER_DEXTERITY_OFFSET,
            RANGER_AGILITY_OFFSET
            };
}

class Ranger : public Character{
    public:
        Ranger(const std::string& t_name) :
        Character(t_name, RangerOffsets()){}

        CharacterClass getClass() const override{
            return CharacterClass::Human_Ranger;
        }
};