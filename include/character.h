#pragma once

#include <string>
#include <memory>

#define DEFAULT_BASE_INTELLIGENCE   5
#define DEFAULT_BASE_STRENGTH       5
#define DEFAULT_BASE_CHARISMA       5
#define DEFAULT_BASE_DEXTERITY      5
#define DEFAULT_BASE_AGILITY        5

#define DEFAULT_MAX_HEALTH  10
#define DEFAULT_MAX_STAMINA 10
#define DEFAULT_MAX_MANA    10

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


enum class CharacterClass{

    Warrior,
    Mage,
    Ranger,
    NA

};


struct CharacterParamOffsets{
    int maxHealthOffset = 0;
    int maxStaminaOffset = 0;
    int maxManaOffset = 0;

    int intelligenceOffset = 0;
    int strengthOffset = 0;
    int charismaOffset = 0;
    int dexterityOffset = 0;
    int agilityOffset = 0;

    CharacterParamOffsets operator+ (const CharacterParamOffsets& other) const {
        CharacterParamOffsets ret;

        ret.maxHealthOffset = maxHealthOffset + other.maxHealthOffset;
        ret.maxStaminaOffset = maxStaminaOffset + other.maxStaminaOffset;
        ret.maxManaOffset = maxManaOffset + other.maxManaOffset;

        ret.intelligenceOffset = intelligenceOffset + other.intelligenceOffset;
        ret.strengthOffset = strengthOffset + other.strengthOffset;
        ret.charismaOffset = charismaOffset + other.charismaOffset;
        ret.dexterityOffset = dexterityOffset + other.dexterityOffset;
        ret.agilityOffset = agilityOffset + other.agilityOffset;

        return ret;
    }
};



class Character{

    private:
        std::string m_name;

        unsigned int m_maxHealth;
        unsigned int m_maxStamina;
        unsigned int m_maxMana;

        unsigned int m_health;
        unsigned int m_stamina;
        unsigned int m_mana;

        unsigned short int m_intelligence;
        unsigned short int m_strength;
        unsigned short int m_charisma;
        unsigned short int m_dexterity;
        unsigned short int m_agility;

        //----------------Utility

        int lowerLimitOffset(unsigned int t_orgVal, int t_offset){
            if(t_offset < 0){
                if((t_offset * -1) > t_orgVal){
                    return ((-1) * static_cast<int>(t_orgVal));
                }                
            }
            return t_offset;
        }

    public:

        Character(const std::string& t_name, const CharacterParamOffsets& t_offsets) :
        m_name(t_name),
        m_maxHealth(DEFAULT_MAX_HEALTH), m_maxStamina(DEFAULT_MAX_STAMINA), m_maxMana(DEFAULT_MAX_MANA),
        m_health(DEFAULT_MAX_HEALTH), m_stamina(DEFAULT_MAX_STAMINA), m_mana(DEFAULT_MAX_MANA),
        m_intelligence(DEFAULT_BASE_INTELLIGENCE), m_charisma(DEFAULT_BASE_CHARISMA),
        m_strength(DEFAULT_BASE_STRENGTH), m_dexterity(DEFAULT_BASE_DEXTERITY), m_agility(DEFAULT_BASE_AGILITY)
        {
            offsetMaxHealth(t_offsets.maxHealthOffset);
            m_health = m_maxHealth;

            offsetMaxStamina(t_offsets.maxStaminaOffset);
            m_stamina = m_maxStamina;
            
            offsetMaxMana(t_offsets.maxManaOffset);
            m_mana = m_maxMana;

            offsetIntelligence(t_offsets.intelligenceOffset);
            offsetStrength(t_offsets.strengthOffset);
            offsetCharisma(t_offsets.charismaOffset);
            offsetDexterity(t_offsets.dexterityOffset);
            offsetAgility(t_offsets.agilityOffset);

        }

        virtual ~Character() = default;

        //----------------Gets

        std::string getName() const {
            return m_name;
        }

        virtual CharacterClass getClass() const {
            return CharacterClass::NA;
        }

        unsigned int getMaxHealth() const {
            return m_maxHealth;
        }

        unsigned int getMaxStamina() const {
            return m_maxStamina;
        }

        unsigned int getMaxMana() const {
            return m_maxMana;
        }

        unsigned int getHealth() const {
            return m_health;
        }

        unsigned int getStamina() const {
            return m_stamina;
        }

        unsigned int getMana() const {
            return m_mana;
        }

        unsigned int getIntelligence() const {
            return m_intelligence;
        }

        unsigned int getStrength() const {
            return m_strength;
        }

        unsigned int getCharisma() const {
            return m_charisma;
        }

        unsigned int getDexterity() const {
            return m_dexterity;
        }

        unsigned int getAgility() const {
            return m_agility;
        }

        //----------------Sets

        void setName(const std::string& t_name){
            m_name = t_name;
        }

        void setMaxHealth(unsigned int t_maxHealth){
            m_maxHealth = t_maxHealth;
            if(m_health > m_maxHealth){
                m_health = m_maxHealth;
            }
        }

        void setMaxStamina(unsigned int t_maxStamina){
            m_maxStamina = t_maxStamina;
            if(m_stamina > m_maxStamina){
                m_stamina = m_maxStamina;
            }
        }

        void setMaxMana(unsigned int t_maxMana){
            m_maxMana = t_maxMana;
            if(m_mana > m_maxMana){
                m_mana = m_maxMana;
            }
        }

        void setHealth(unsigned int t_health){
            if(t_health > m_maxHealth){
                m_health = m_maxHealth;
            }
            else{
                m_health = t_health;
            }
        }

        void setStamina(unsigned int t_stamina){
            if(t_stamina > m_maxStamina){
                m_stamina = m_maxStamina;
            }
            else{
                m_stamina = t_stamina;
            }
        }

        void setMana(unsigned int t_mana){
            if(t_mana > m_maxMana){
                m_mana = m_maxMana;
            }
            else{
                m_mana = t_mana;
            }
        }

        void setIntelligence(unsigned int t_intelligence){
            m_intelligence = t_intelligence;
        }

        void setStrength(unsigned int t_strength){
            m_strength = t_strength;
        }

        void setCharisma(unsigned int t_charisma){
            m_charisma = t_charisma;
        }

        void setDexterity(unsigned int t_dexterity){
            m_dexterity = t_dexterity;
        }

        void setAgility(unsigned int t_agility){
            m_agility = t_agility;
        }


        void offsetMaxHealth(int t_offset){
            m_maxHealth += lowerLimitOffset(m_maxHealth, t_offset);
            if(m_health > m_maxHealth){
                m_health = m_maxHealth;
            }
        }

        void offsetMaxStamina(int t_offset){
            m_maxStamina += lowerLimitOffset(m_maxStamina, t_offset);
            if(m_stamina > m_maxStamina){
                m_stamina = m_maxStamina;
            }
        }

        void offsetMaxMana(int t_offset){
            m_maxMana += lowerLimitOffset(m_maxMana, t_offset);
            if(m_mana > m_maxMana){
                m_mana = m_maxMana;
            }
        }

        void offsetHealth(int t_offset){
            m_health += lowerLimitOffset(m_health, t_offset);
            if(m_health > m_maxHealth){
                m_health = m_maxHealth;
            }
        }

        void offsetStamina(int t_offset){
            m_stamina += lowerLimitOffset(m_stamina, t_offset);
            if(m_stamina > m_maxStamina){
                m_stamina = m_maxStamina;
            }
        }

        void offsetMana(int t_offset){
            m_mana += lowerLimitOffset(m_mana, t_offset);
            if(m_mana > m_maxMana){
                m_mana = m_maxMana;
            }
        }

        void offsetIntelligence(int t_offset){
            m_intelligence += lowerLimitOffset(m_intelligence, t_offset);
        }

        void offsetStrength(int t_offset){
            m_strength += lowerLimitOffset(m_strength, t_offset);
        }

        void offsetCharisma(int t_offset){
            m_charisma += lowerLimitOffset(m_charisma, t_offset);
        }

        void offsetDexterity(int t_offset){
            m_dexterity += lowerLimitOffset(m_dexterity, t_offset);
        }

        void offsetAgility(int t_offset){
            m_agility += lowerLimitOffset(m_agility, t_offset);
        }

        

};

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


class CharacterFactory{
    public:
        static std::unique_ptr<Character> createCharacter(std::string& t_name, CharacterClass t_type){
            switch(t_type){
                case CharacterClass::Warrior:
                    return std::make_unique<Warrior>(t_name);
                case CharacterClass::Mage:
                    return std::make_unique<Mage>(t_name);
                case CharacterClass::Ranger:
                    return std::make_unique<Ranger>(t_name);
                case CharacterClass::NA:
                    return std::make_unique<Character>(t_name, NaOffsets());
                default:
                    return std::make_unique<Character>(t_name, NaOffsets());                        
            }
        }
};