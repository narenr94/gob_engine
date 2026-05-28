#pragma once

#include "defines.h"
#include "race.h"
#include "pack.h"
#include "characterClass.h"

#include <string>
#include <map>
#include <vector>
#include <memory>


class Character{

    private:

        std::string m_name;

        Level m_level;

        unsigned short int m_proficiencyBonus;

        unsigned int m_expPoints;

        std::unique_ptr<Race> m_race;
        
        std::vector<std::unique_ptr<CharacterClass>> m_class;

        std::unique_ptr<Pack> m_pack;

        Alignment m_alignment;

        AgeData m_age;

        SizeData m_size;

        float m_speed;

        float m_sleepDurationHrs;

        std::vector<LanguageData> m_languageData;

        ProficiencyData m_proficiencyData;

        std::vector<ResilienceData> m_resilienceDataVector;

        DarkvisionData m_darkvisionData;

        //ability_name -> ability_score -> ability_mod
        std::map<std::string, std::pair<unsigned short int, unsigned short int>> m_abilitiesMap;

        //param_name -> curr_value -> max_value        
        std::map<std::string, std::pair<unsigned short int, unsigned short int>> m_paramsPairMap;


        //----------------Utility

        void assignCharacterParams();

        void assignAbilities();

        void assignRandomValuesToAbilities();


    public:

        Character(const std::string& t_name, const std::string& t_race, 
            std::vector<std::string> t_class, const Level t_level);

        virtual ~Character();

        //----------------Gets

        std::string getName() const;

        std::string getRace() const;

        std::string getClass() const;

        Level getLevel() const;

        AgeData getAgeData() const;

        SizeData getSizeData() const;

        float getSpeed() const;

        float getSleepDuration() const;

        std::vector<LanguageData> getLanguageData() const;

        ProficiencyData getProficiencyData() const;

        std::vector<ResilienceData> getResilienceDataVector() const;

        DarkvisionData getDarkvisionData() const;

        bool getAbilityScore(const std::string& t_ability, unsigned short int& value) const;

        bool getAbilityModifier(const std::string& t_ability, unsigned short int& value) const;

        bool getParamMax(const std::string& t_param, unsigned short int& value) const;

        bool getParamCurr(const std::string& t_param, unsigned short int& value) const;

        Alignment getAlignment() const;

        std::vector<std::pair<std::string, unsigned short int>> getPackItems() const;


        //----------------Sets

        void setAgeData(const AgeData& t_ageData);

        void setSizeData(const SizeData& t_sizeData);

        void addLanguageProficiency(const std::string& language, bool speak, bool read, bool write);

        void setProficiencyData(const ProficiencyData& t_proficiencyData);

        void addResilienceData(const ResilienceData& t_resilienceData);

        void setDarkvisionData(const DarkvisionData& t_darkvisionData);

        void updateName(const std::string& t_name);

        void levelUp();

        bool updateParamMax(const std::string& t_param, const unsigned short int t_value);

        bool updateParamCurr(const std::string& t_param, const unsigned short int t_value);

        bool updateAbilityScore(const std::string& t_ability, const unsigned short int t_value);

        bool addToAbilityScore(const std::string& t_ability, const short int t_value);

        void addToParamMax(const std::string& t_param, const unsigned short int t_value);

        void updateAlignment(Alignment t_alignment);

        void updateSpeed(float t_speed);

        void updateSleepDuration(float t_sleepDurationHrs);

        void addItemToPack(const std::string& item, unsigned short int count);

        void updatePack(std::unique_ptr<Pack> t_pack);


};