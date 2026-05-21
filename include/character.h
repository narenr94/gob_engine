#pragma once

#include "defines.h"
#include "item.h"
#include "inventory.h"
#include "dice.h"
#include "race.h"

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>


class Character{

    private:

        std::string m_name;

        unsigned int m_maxHitPoints = 0;
        
        unsigned int m_currentHitPoints = 0;

        unsigned short int m_level = 1;

        std::unique_ptr<Race> m_race;
        //std::unique_ptr<Class> m_class;

        std::map<std::string, unsigned short int> m_abilitiesMap;        

        std::shared_ptr<Inventory> m_inventory;

        //----------------Utility

        void assignAbilities(){
            for(auto& ab : g_defaultAbilities){                

                m_abilitiesMap[ab] = 0;

                //assignCustomAbilities(); - todo
            }
                
        }

        void assignRandomValuesToAbilities(){
            for(auto& ab : m_abilitiesMap){

                //roll die four times and take sum of max 3
                std::vector<int> rolls;
                for (int i = 0; i < 4; ++i) {
                    rolls.push_back(rollDie(6));
                }

                // sort descending
                std::sort(rolls.begin(), rolls.end(), std::greater<unsigned short int>());

                ab.second = rolls[0] + rolls[1] + rolls[2];

            }
        }

        static std::unique_ptr<Race> raceFactory(const CharacterRace t_race, Character* t_character){
            switch(t_race){
                case CharacterRace::Hill_Dwarf:
                    return std::make_unique<HillDwarf>(t_character);
                case CharacterRace::Mountain_Dwarf:
                    return std::make_unique<MountainDwarf>(t_character);
                case CharacterRace::High_Elf:
                    return std::make_unique<HighElf>(t_character);
                case CharacterRace::Wood_Elf:
                    return std::make_unique<WoodElf>(t_character);
                case CharacterRace::Dark_Elf:
                    return std::make_unique<DarkElf>(t_character);
                case CharacterRace::Lightfoot_Halfling:
                    return std::make_unique<LightfootHalfling>(t_character);
                case CharacterRace::Stout_Halfling:
                    return std::make_unique<StoutHalfling>(t_character);
                case CharacterRace::Human:
                    return std::make_unique<Human>(t_character);
                default:
                    return std::make_unique<Human>(t_character);
            }

            //todo : custom races
        }

    public:

        Character(const std::string& t_name, const CharacterRace t_race, const CharacterClass t_class) :
        m_name(t_name), m_level(1)
        {

            assignAbilities();

            assignRandomValuesToAbilities();

            m_race = raceFactory(t_race, this);

            //assign maxHP - class specific

        }

        virtual ~Character(){
            m_inventory = nullptr;
        }

        //----------------Gets

        std::string getName() const {
            return m_name;
        }

        CharacterRace getRace() const {
            return m_race->getRace();
        }

        virtual CharacterClass getClass() const {

            //return m_class->getClass();
            return CharacterClass::NA;
        }

        unsigned short int getLevel() const {
            return m_level;
        }
        
        void getDrops(unsigned int& exp, std::vector<Item>& items){

        }

        bool getAbilityScore(const std::string& t_ability, unsigned short int& value) const {
            if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end())
            {
                return false;
            }

            value = m_abilitiesMap.at(t_ability);

            return true;
        }

        unsigned int getMaxHitPoints() const {
            return m_maxHitPoints;
        }

        unsigned int getCurrentHitPoints() const {
            return m_currentHitPoints;
        }

        std::shared_ptr<Inventory> getInventory(){
            return m_inventory;
        }

        //----------------Sets

        void updateName(const std::string& t_name){
            m_name = t_name;
        }

        void levelUp(){

            m_race->levelUp();
            //m_class->levelUp();

            m_level += 1;
        }

        void updateMaxHitPoints(unsigned short int t_maxHitPoints){
            m_maxHitPoints = t_maxHitPoints;
            if(m_currentHitPoints > m_maxHitPoints){
                m_currentHitPoints = m_maxHitPoints;
            }
        }

        void updateCurretHitPoints(unsigned short int t_currHitPoints){
            if(t_currHitPoints > m_maxHitPoints){
                m_currentHitPoints = m_maxHitPoints;
            }
            else{
                m_currentHitPoints = t_currHitPoints;
            }
        }

        void updateAbilityScore(const std::string& t_ability, const unsigned short int t_value){
            if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end()){
                return;
            }
            m_abilitiesMap[t_ability] = t_value;
        }

};