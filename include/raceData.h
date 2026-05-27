#pragma once

#include "defines.h"
#include "commonJsonParser.h"

#include <string>
#include <filesystem>

class Character; //Forward declaration

struct RaceData{

    private:

    std::vector<AbilityModData> abilityModData;
    std::vector<ParamModData> paramModData;
    AgeData ageData;
    Alignment alignment;
    SizeData sizeData;
    float speed;
    std::vector<LanguageData> languagesVector;
    ProficiencyData proficiencyData;
    std::vector<ResilienceData> resilienceDataVector;
    DarkvisionData darkvisionData;
    float sleepDurationHrs = 8.0f;
    OptionsData optionsData;

    public:

    RaceData() = default;
    ~RaceData() = default;

    //-----replace data

    void setAgeData(unsigned short int maturityAge, unsigned short int avgLifespan);

    void setAlignment(Alignment t_alignment);

    void setSizeData(const SizeCategory category, float height, float weight);

    void setSpeed(float t_speed);

    void setDarkvisionData(bool hasDarkvision, std::pair<IlluminationType, float> dim_light_eq, std::pair<IlluminationType, float> darkvision_eq);

    void setSleepDuration(float duration);


    //-----additive data

    void setProficiencyData(const ProficiencyType t_type, const std::string& proficiency);    

    void addAbilityMod(const std::string& ability, int mod);

    void addParamMod(const std::string& param, int mod);

    void addLanguageProficiency(const std::string& language, bool speak, bool read, bool write);

    void addResilience(const std::string& affliction, bool immune, bool hasAdvantage, bool hasResistance);

    void printData();

    void applyRaceData(Character* t_character);

    void updateOptionsData(const OptionsData& t_optionsData);


};


//----------------------



void getRaceDataFrom(const std::string& t_racePath, RaceData& raceData);
