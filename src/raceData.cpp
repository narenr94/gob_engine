#include "raceData.h"
#include "character.h"

void RaceData::applyRaceData(Character* t_character){
    //----ability mod data
    for(auto& amd : abilityModData){
        amd.applyData(t_character);
    }

    //-----param mod data
    for(auto& pmd : paramModData){
        pmd.applyData(t_character);
    }

    //----Age data
    ageData.applyData(t_character);

    //------Alignment
    t_character->setAlignment(alignment);

    //------Size
    sizeData.applyData(t_character);
    
    //-----Speed
    t_character->setSpeed(speed);

    //-----Languages
    for(auto& lg : languagesVector){
        lg.applyData(t_character);
    }

    //------Proficiency
    proficiencyData.applyData(t_character);

    //------resilience
    for(auto& rs : resilienceDataVector){
        rs.applyData(t_character);
    }

    //-------Darkvision
    darkvisionData.applyData(t_character);

}

void RaceData::printData(){

    //----ability mod data
    for(auto& amd : abilityModData){
        amd.printData();
    }

    //-----param mod data
    for(auto& pmd : paramModData){
        pmd.printData();
    }

    //----Age data
    ageData.printData();

    //------Alignment
    LOG("Alignment:" + alignmentToString(alignment));

    //------Size
    sizeData.printData();
    
    //-----Speed
    LOG("Speed Data:" + std::to_string(speed));

    //-----Languages
    for(auto& lg : languagesVector){
        lg.printData();
    }

    //------Proficiency
    proficiencyData.printData();

    //------resilience
    for(auto& rs : resilienceDataVector){
        rs.printData();
    }

    //-------Darkvision
    darkvisionData.printData();

}