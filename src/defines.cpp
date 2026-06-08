#include "defines.h"
#include "character.h"
#include "utilities.h"
#include "pack.h"
#include "playerInput.h"
#include "randomize.h"

void AgeData::applyData(Character* t_character) const{
    t_character->setAgeData(*this);
}

void SizeData::applyData(Character* t_character) const{
    t_character->setSizeData(*this);
}

void AbilityModData::applyData(Character* t_character) const{
    t_character->addToAbilityScore(abilityMod.first, abilityMod.second);
}

void ParamModData::applyData(Character* t_character) const{
    t_character->addToParamMax(paramMod.first, paramMod.second);
}
    

void LanguageData::applyData(Character* t_character) const{
    t_character->addLanguageProficiency(language, speak, read, write);
}

void ProficiencyData::applyData(Character* t_character) const{
    t_character->setProficiencyData(*this);
}

void ResilienceData::applyData(Character* t_character) const{
    t_character->addResilienceData(*this);
}

void DarkvisionData::applyData(Character* t_character) const{
    t_character->setDarkvisionData(*this);
}

void ItemData::applyData(Character* t_character) const{
    t_character->addItemToPack(itemData.first, itemData.second);
}

void AlignmentData::applyData(Character* t_character) const{
    t_character->updateAlignment(alignment);
}

void SpeedData::applyData(Character* t_character) const{
    t_character->updateSpeed(speed);
}

void SleepDurationData::applyData(Character* t_character) const{
    t_character->updateSleepDuration(sleepDurationHrs);
}

void ConsolidatedData::applyData(Character* t_character) const{

    for(const auto& dt : data){
        dt->applyData(t_character);
    }
}

void ProficiencyOptionData::realizeOptions(Character* t_character, bool enablePlayerInput){

    std::vector<std::string> chosen;

    if(enablePlayerInput){
        chosen = getPlayerInputOptionChoices(choices, chooseCount);
    }
    else{
        chosen = chooseRandomOptions(choices, chooseCount);
    }

    ProficiencyData proficiencyData;

    switch(type){
        case ProficiencyType::Weapons:
            proficiencyData.weaponProficiencies = chosen;
            break;
        case ProficiencyType::Armors:
            proficiencyData.armorProficiencies = chosen;
            break;
        case ProficiencyType::Tools:
            proficiencyData.toolProficiencies = chosen;
            break;
        case ProficiencyType::Skills:
            proficiencyData.skillProficiencies = chosen;
            break;
        case ProficiencyType::SavingThrows:
            proficiencyData.savingThrowsProficiencies = chosen;
            break;
    }

    proficiencyData.applyData(t_character);

}

void LanguageOptionData::realizeOptions(Character* t_character, bool enablePlayerInput){

    std::vector<std::string> chosen;

    if(enablePlayerInput){
        chosen = getPlayerInputOptionChoices(choices, chooseCount);
    }
    else{
        chosen = chooseRandomOptions(choices, chooseCount);
    }

    for(const auto& language : chosen){
        t_character->addLanguageProficiency(language, speak, read, write);
    }
}

void ItemOptionData::realizeOptions(Character* t_character, bool enablePlayerInput){

    std::vector<std::string> chosen;

    std::vector<std::string> optionsStrVec;

    for(const auto& ch : choices){
        optionsStrVec.push_back(ch.first);
    }

    if(enablePlayerInput){
        chosen = getPlayerInputOptionChoices(optionsStrVec, chooseCount);
    }
    else{
        chosen = chooseRandomOptions(optionsStrVec, chooseCount);
    }

    for(const auto& itemName : chosen){
        
        for(const auto& ch : choices){
            if(ch.first == itemName){
                t_character->addItemToPack(ch.first, ch.second);
                break;
            }
        }
    }

}

void AlignmentOptionData::realizeOptions(Character* t_character, bool enablePlayerInput){

    std::vector<std::string> chosen;

    if(enablePlayerInput){
        chosen = getPlayerInputOptionChoices(choices, chooseCount);
    }
    else{
        chosen = chooseRandomOptions(choices, chooseCount);
    }

    if(!chosen.empty()){
        Alignment alignment = stringToAlignment(chosen[0]);
        t_character->updateAlignment(alignment);
    }
}

void ConsolidatedOptionsData::realizeOptions(Character* t_character, bool enablePlayerInput){

    for(auto& op : options){
        op->realizeOptions(t_character, enablePlayerInput);
    }
}


void AgeData::printData() const{

    LOG("Age Data:");
    LOG("maturity:" + std::to_string(maturityAge) + " avgLifespan:" + std::to_string(avgLifespan));
}

void SizeData::printData() const{
    LOG("Size data:");
    LOG("category:" + sizeCategoryToString(category));
    LOG("height:" + std::to_string(dimensions.first) + " weight:" + std::to_string(dimensions.second));
}

void AbilityModData::printData() const{
    LOG("Ability Mod Data:");
    LOG("Ability:" + abilityMod.first + " mod:" + std::to_string(abilityMod.second));
}

void ParamModData::printData() const{
    LOG("Param Mod Data:");
    LOG("Param:" + paramMod.first + " mod:" + std::to_string(paramMod.second));
}

void LanguageData::printData() const{
    LOG("Language Data:");
    LOG("Language:" + language);
    LOG("speak:" + std::to_string(speak));
    LOG("read:" + std::to_string(read));
    LOG("write:" + std::to_string(write));
}

void ProficiencyData::printData() const{
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
    LOG("Saving Throws Proficiencies:");
    for(const auto& sp : savingThrowsProficiencies){
        LOG(sp);
    }
}

void ResilienceData::printData() const{
    LOG("Resilience Data:");
    LOG("Affliction:" + affliction);
    LOG("Immune:" + std::to_string(immune));
    LOG("hasAdvantage:" + std::to_string(hasAdvantage));
    LOG("hasResistance:" + std::to_string(hasResistance));
}

void DarkvisionData::printData() const{
    LOG("Darkvision data:");
    LOG("hasDarkvision" + std::to_string(hasDarkvision));
    LOG("dim_light_eq:" + illuminationTypeToString(dim_light_eq) + " dim_light_eq_dist:" + std::to_string(dim_light_eq_dist));
    LOG("darkvision_eq:" + illuminationTypeToString(darkvision_eq) + " darkvision_eq_dist:" + std::to_string(darkvision_eq_dist));
}

void ItemData::printData() const{
    LOG("Item Data:");
    LOG("item:" + itemData.first + " count:" + std::to_string(itemData.second));
}

void AlignmentData::printData() const{
    LOG("Alignment Data:");
    LOG("alignment:" + alignmentToString(alignment));
}

void SpeedData::printData() const{
    LOG("Speed Data:");
    LOG("speed:" + std::to_string(speed));
}

void SleepDurationData::printData() const{
    LOG("Sleep Duration Data:");
    LOG("sleep duration (hrs):" + std::to_string(sleepDurationHrs));
}

void ConsolidatedData::printData() const{
    LOG("Consolidated Data:");
    for(const auto& dt : data){
        dt->printData();
    }
    
}

void ProficiencyOptionData::printOption(){
    LOG("Proficiency Option Data:");
    LOG("Proficiency type:" + proficiencyTypeToString(type));
    LOG("Choices:");
    for(auto& ch : choices){
        LOG(ch);
    }
    LOG("Choose Count:" + std::to_string(chooseCount));
}

void LanguageOptionData::printOption(){
    LOG("Language Option Data:");
    LOG("Choices:");
    for(auto& l : choices){
        LOG(l);
    }
    LOG("Speak:" + std::to_string(speak));
    LOG("Read:" + std::to_string(read));
    LOG("Write:" + std::to_string(write));
}

void ItemOptionData::printOption(){
    LOG("Item Option Data:");
    LOG("Choices:");
    for(auto& ch : choices){
        LOG(ch.first + ":" + std::to_string(ch.second));
    }
    LOG("Choose Count:" + std::to_string(chooseCount));
}

void AlignmentOptionData::printOption(){
    LOG("Alignment Option Data:");
    LOG("Choices:");
    for(auto& ch : choices){
        LOG(ch);
    }
    LOG("Choose Count:" + std::to_string(chooseCount));
}

void ConsolidatedOptionsData::printOption(){
    LOG("Consolidated Options Data:");
    for(auto& op : options){
        op->printOption();
    }
}
    