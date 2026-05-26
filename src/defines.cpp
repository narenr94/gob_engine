#include "defines.h"
#include "character.h"
#include "utilities.h"

void AgeData::applyData(Character* t_character){
    t_character->setAgeData(*this);
}

void SizeData::applyData(Character* t_character){
    t_character->setSizeData(*this);
}

void AbilityModData::applyData(Character* t_character){
    t_character->addToAbilityScore(abilityMod.first, abilityMod.second);
}

void ParamModData::applyData(Character* t_character){
    t_character->addToParamMax(paramMod.first, paramMod.second);
}
    

void LanguageData::applyData(Character* t_character){
    t_character->addLanguageProficiency(language, speak, read, write);
}

void ProficiencyData::applyData(Character* t_character){
    t_character->setProficiencyData(*this);
}

void ResilienceData::applyData(Character* t_character){
    t_character->addResilienceData(*this);
}

void DarkvisionData::applyData(Character* t_character){
    t_character->setDarkvisionData(*this);
}

void AgeData::printData(){

    LOG("Age Data:");
    LOG("maturity:" + std::to_string(maturityAge) + " avgLifespan:" + std::to_string(avgLifespan));
}

void SizeData::printData(){
    LOG("Size data:");
    LOG("category:" + sizeCategoryToString(category));
    LOG("height:" + std::to_string(dimensions.first) + " weight:" + std::to_string(dimensions.second));
}

void AbilityModData::printData(){
    LOG("Ability Mod Data:");
    LOG("Ability:" + abilityMod.first + " mod:" + std::to_string(abilityMod.second));
}

void ParamModData::printData(){
    LOG("Param Mod Data:");
    LOG("Param:" + paramMod.first + " mod:" + std::to_string(paramMod.second));
}

void LanguageData::printData(){
    LOG("Language Data:");
    LOG("Language:" + language);
    LOG("speak:" + std::to_string(speak));
    LOG("read:" + std::to_string(read));
    LOG("write:" + std::to_string(write));
}

void ProficiencyData::printData(){
    LOG("Proficiency Data:");
    LOG("Weapon Proficiencies:");
    for(const auto& wp : weaponProficiencies){
        LOG(wp);
    }
    LOG("Armor Proficiencies:");
    for(const auto& ap : armorProficiencies){
        LOG(ap);
    }
    LOG("Tool Proficiencies:");
    for(const auto& tp : toolProficiencies){
        LOG(tp);
    }
    LOG("Skill Proficiencies:");
    for(const auto& op : skillProficiencies){
        LOG(op);
    }
}

void ResilienceData::printData(){
    LOG("Resilience Data:");
    LOG("Affliction:" + affliction);
    LOG("Immune:" + std::to_string(immune));
    LOG("hasAdvantage:" + std::to_string(hasAdvantage));
    LOG("hasResistance:" + std::to_string(hasResistance));
}

void DarkvisionData::printData(){
    LOG("Darkvision data:");
    LOG("hasDarkvision" + std::to_string(hasDarkvision));
    LOG("dim_light_eq:" + illuminationTypeToString(dim_light_eq) + " dim_light_eq_dist:" + std::to_string(dim_light_eq_dist));
    LOG("darkvision_eq:" + illuminationTypeToString(darkvision_eq) + " darkvision_eq_dist:" + std::to_string(darkvision_eq_dist));
}