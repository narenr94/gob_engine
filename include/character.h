#pragma once

#include "defines.h"
#include "item.h"
#include "inventory.h"
#include "dice.h"
#include "race.h"
#include "characterClass.h"
#include "utilities.h"

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>


class Character{

    private:

        std::string m_name;

        Level m_level;

        unsigned short int m_proficiencyBonus;

        unsigned int m_expPoints;

        std::unique_ptr<Race> m_race;
        std::unique_ptr<CharacterClass> m_class;

        Alignment m_alignment;

        //ability_name -> ability_score -> ability_mod
        std::map<std::string, std::pair<unsigned short int, unsigned short int>> m_abilitiesMap;

        //param_name -> curr_value -> max_value        
        std::map<std::string, std::pair<unsigned short int, unsigned short int>> m_paramsPairMap;

        std::shared_ptr<Inventory> m_inventory;

        //----------------Utility

        void assignCharacterParams(){
            for(auto& cp : g_characterParamsVector){
                m_paramsPairMap[cp] = {0, 0};
            }
        }

        void assignAbilities(){
            for(auto& ab : g_abilitiesVector){                

                m_abilitiesMap[ab] = {0, 0};
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

                ab.second.first += rolls[0] + rolls[1] + rolls[2];
                ab.second.second = calculateAbilityModifier(ab.second.first);

            }
        }


    public:

        Character(const std::string& t_name, std::unique_ptr<Race> t_race, 
            std::unique_ptr<CharacterClass> t_class, const Level t_level) :
        m_name(t_name), m_level(t_level), m_proficiencyBonus(g_proficiencyBonusLookupTable.at(t_level)),
        m_race(std::move(t_race)), m_class(std::move(t_class)), 
        m_expPoints(g_expPointsLookupTable.at(t_level))
        {

            assignCharacterParams();

            assignAbilities();

            assignRandomValuesToAbilities();

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

        Level getLevel() const {
            return m_level;
        }
        
        void getDrops(unsigned int& exp, std::vector<Item>& items){

        }

        bool getAbilityScore(const std::string& t_ability, unsigned short int& value) const {
            if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end())
            {
                return false;
            }

            value = m_abilitiesMap.at(t_ability).first;

            return true;
        }

        bool getAbilityModifier(const std::string& t_ability, unsigned short int& value) const {
            if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end())
            {
                return false;
            }

            value = m_abilitiesMap.at(t_ability).second;

            return true;
        }

        bool getParamMax(const std::string& t_param, unsigned short int& value) const {
            if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
                return false;
            }

            value = m_paramsPairMap.at(t_param).second;

            return true;
        }

        bool getParamCurr(const std::string& t_param, unsigned short int& value) const {
            if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
                return false;
            }

            value = m_paramsPairMap.at(t_param).first;

            return true;
        }

        Alignment getAlignment() const {
            return m_alignment;
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

            m_level = incrementLevel(m_level);
        }

        bool updateParamMax(const std::string& t_param, const unsigned short int t_value){
            if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
                return false;
            }
            m_paramsPairMap.at(t_param).second = t_value;

            if(m_paramsPairMap.at(t_param).first > m_paramsPairMap.at(t_param).second){
                m_paramsPairMap.at(t_param).first = m_paramsPairMap.at(t_param).second;
            }

            return true;
        }

        bool updateParamCurr(const std::string& t_param, const unsigned short int t_value){
            if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
                return false;
            }
            m_paramsPairMap.at(t_param).first = t_value;

            if(m_paramsPairMap.at(t_param).first > m_paramsPairMap.at(t_param).second){
                m_paramsPairMap.at(t_param).first = m_paramsPairMap.at(t_param).second;
            }

            return true;
        }

        bool updateAbilityScore(const std::string& t_ability, const unsigned short int t_value){
            if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end()){
                return false;
            }
            m_abilitiesMap.at(t_ability).first = t_value;

            m_abilitiesMap.at(t_ability).second = calculateAbilityModifier(m_abilitiesMap.at(t_ability).first);
            
            return true;
        }

        void updateAlignment(Alignment t_alignment){
            m_alignment = t_alignment;
        }

};