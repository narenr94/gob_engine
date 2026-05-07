#pragma once

#include "character.h"

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
            return CharacterClass::Warrior;
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
            return CharacterClass::Mage;
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
            return CharacterClass::Ranger;
        }
};

static CharacterParamOffsets NaOffsets(){
    return {0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
            };
}