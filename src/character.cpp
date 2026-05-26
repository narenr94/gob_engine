#include "character.h"
#include "gameData.h"
#include "utilities.h"
#include "randomize.h"

#include <algorithm>
#include <utility>
#include <unordered_set>


void Character::assignCharacterParams(){
    GameData* gameData = GameData::getInstance();

    for(auto& cp : gameData->getParamsVector()){
        m_paramsPairMap[cp] = {0, 0};
    }
}

void Character::assignAbilities(){
    GameData* gameData = GameData::getInstance();

    for(auto& ab : gameData->getAbilitiesVector()){                

        m_abilitiesMap[ab] = {0, 0};
    }
        
}

void Character::assignRandomValuesToAbilities(){
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

Character::Character(const std::string& t_name, std::unique_ptr<Race> t_race, 
    std::vector<std::unique_ptr<CharacterClass>> t_class, const Level t_level) :
m_name(t_name), m_level(t_level), m_race(std::move(t_race)), m_class(std::move(t_class))
{
    for(auto& ex : g_expPointsLookupTable){
        if(ex.first == t_level){
            m_expPoints = ex.second;
            break;
        }
    }

    for(auto& pb : g_proficiencyBonusLookupTable){
        if(pb.first == t_level){
            m_proficiencyBonus = pb.second;
            break;
        }
    }

    assignCharacterParams();

    assignAbilities();

    assignRandomValuesToAbilities();

    //assign maxHP - class specific

}

Character::~Character(){
    
}

//----------------Gets

std::string Character::getName() const {
    return m_name;
}

std::string Character::getRace() const {
    return m_race->getRace();
}

std::string Character::getClass() const {

    //return m_class->getClass();
    return "";
}

Level Character::getLevel() const {
    return m_level;
}

AgeData Character::getAgeData() const {
    return m_age;
}

SizeData Character::getSizeData() const {
    return m_size;
}

float Character::getSpeed() const {
    return m_speed;
}

std::vector<LanguageData> Character::getLanguageData() const {
    return m_languageData;
}

ProficiencyData Character::getProficiencyData() const {
    return m_proficiencyData;
}

std::vector<ResilienceData> Character::getResilienceDataVector() const {
    return m_resilienceDataVector;
}

DarkvisionData Character::getDarkvisionData() const {
    return m_darkvisionData;
}

bool Character::getAbilityScore(const std::string& t_ability, unsigned short int& value) const {
    if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end())
    {
        return false;
    }

    value = m_abilitiesMap.at(t_ability).first;

    return true;
}

bool Character::getAbilityModifier(const std::string& t_ability, unsigned short int& value) const {
    if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end())
    {
        return false;
    }

    value = m_abilitiesMap.at(t_ability).second;

    return true;
}

bool Character::getParamMax(const std::string& t_param, unsigned short int& value) const {
    if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
        return false;
    }

    value = m_paramsPairMap.at(t_param).second;

    return true;
}

bool Character::getParamCurr(const std::string& t_param, unsigned short int& value) const {
    if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
        return false;
    }

    value = m_paramsPairMap.at(t_param).first;

    return true;
}

Alignment Character::getAlignment() const {
    return m_alignment;
}


//----------------Sets

void Character::setAgeData(const AgeData& t_ageData){
    m_age = t_ageData;
}

void Character::setSizeData(const SizeData& t_sizeData){
    m_size = t_sizeData;
}

void Character::addLanguageProficiency(const std::string& language, bool speak, bool read, bool write){
    for(auto& lg : m_languageData){
        if(lg.language == language){

            if(speak){
                lg.speak = true;
            }

            if(read){
                lg.read = true;
            }
            if(write){
                lg.write = true;
            }

            return;
        }
    }
    
    m_languageData.push_back({language, speak, read, write});
}

void Character::setProficiencyData(const ProficiencyData& t_proficiencyData){
    // 1. Populate a set with everything currently in vector A for instant lookups
    std::unordered_set<std::string> existingItems(m_proficiencyData.weaponProficiencies.begin(), m_proficiencyData.weaponProficiencies.end());

    // 2. Loop through vector B and append only the missing items
    for (const auto& item : t_proficiencyData.weaponProficiencies) {
        // if insert succeeds, it means the item wasn't a duplicate
        if (existingItems.insert(item).second) { 
            m_proficiencyData.weaponProficiencies.push_back(item);
        }
    }

    existingItems.clear();

    existingItems.insert(m_proficiencyData.armorProficiencies.begin(), m_proficiencyData.armorProficiencies.end());
    for (const auto& item : t_proficiencyData.armorProficiencies) {
        if (existingItems.insert(item).second) { 
            m_proficiencyData.armorProficiencies.push_back(item);
        }
    }

    existingItems.clear();

    existingItems.insert(m_proficiencyData.toolProficiencies.begin(), m_proficiencyData.toolProficiencies.end());
    for (const auto& item : t_proficiencyData.toolProficiencies) {
        if (existingItems.insert(item).second) { 
            m_proficiencyData.toolProficiencies.push_back(item);
        }
    }

    existingItems.clear();

    existingItems.insert(m_proficiencyData.skillProficiencies.begin(), m_proficiencyData.skillProficiencies.end());
    for (const auto& item : t_proficiencyData.skillProficiencies) {
        if (existingItems.insert(item).second) { 
            m_proficiencyData.skillProficiencies.push_back(item);
        }
    }

}

void Character::addResilienceData(const ResilienceData& t_resilienceData){
    for(auto& res : m_resilienceDataVector){
        if(res.affliction == t_resilienceData.affliction){
            if(t_resilienceData.immune){
                res.immune = true;
            }
            if(t_resilienceData.hasAdvantage){
                res.hasAdvantage = true;
            }
            if(t_resilienceData.hasResistance){
                res.hasResistance = true;
            }
            return;
        }
    }

    m_resilienceDataVector.push_back(t_resilienceData);
}

void Character::setDarkvisionData(const DarkvisionData& t_darkvisionData){
    m_darkvisionData = t_darkvisionData;
}

void Character::updateName(const std::string& t_name){
    m_name = t_name;
}

void Character::levelUp(){

    m_race->levelUp();
    //m_class->levelUp();

    m_level = incrementLevel(m_level);
}

bool Character::updateParamMax(const std::string& t_param, const unsigned short int t_value){
    if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
        return false;
    }
    m_paramsPairMap.at(t_param).second = t_value;

    if(m_paramsPairMap.at(t_param).first > m_paramsPairMap.at(t_param).second){
        m_paramsPairMap.at(t_param).first = m_paramsPairMap.at(t_param).second;
    }

    return true;
}

bool Character::updateParamCurr(const std::string& t_param, const unsigned short int t_value){
    if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
        return false;
    }
    m_paramsPairMap.at(t_param).first = t_value;

    if(m_paramsPairMap.at(t_param).first > m_paramsPairMap.at(t_param).second){
        m_paramsPairMap.at(t_param).first = m_paramsPairMap.at(t_param).second;
    }

    return true;
}

bool Character::updateAbilityScore(const std::string& t_ability, const unsigned short int t_value){
    if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end()){
        return false;
    }
    m_abilitiesMap.at(t_ability).first = t_value;

    if(m_abilitiesMap.at(t_ability).first > ABILITY_SCORE_MAX){
        m_abilitiesMap.at(t_ability).first = ABILITY_SCORE_MAX;
    }

    m_abilitiesMap.at(t_ability).second = calculateAbilityModifier(m_abilitiesMap.at(t_ability).first);
    
    return true;
}

bool Character::addToAbilityScore(const std::string& t_ability, const short int t_value){
    if(m_abilitiesMap.find(t_ability) == m_abilitiesMap.end()){
        return false;
    }

    if(t_value < 0){
        if(m_abilitiesMap.at(t_ability).first < static_cast<unsigned short int>(-1 * t_value)){
            m_abilitiesMap.at(t_ability).first = 0;
        }
        else{
            m_abilitiesMap.at(t_ability).first += t_value;
        }

        
    }
    else{
        m_abilitiesMap.at(t_ability).first += t_value;
    }
    
    if(m_abilitiesMap.at(t_ability).first > ABILITY_SCORE_MAX){
        m_abilitiesMap.at(t_ability).first = ABILITY_SCORE_MAX;
    }

    m_abilitiesMap.at(t_ability).second = calculateAbilityModifier(m_abilitiesMap.at(t_ability).first);
    
    return true;
}

void Character::addToParamMax(const std::string& t_param, const unsigned short int t_value){
    if(m_paramsPairMap.find(t_param) == m_paramsPairMap.end()){
        return;
    }

    if(t_value < 0){
        if(m_paramsPairMap.at(t_param).second < static_cast<unsigned short int>(-1 * t_value)){
            m_paramsPairMap.at(t_param).second = 0;
        }
        else{
            m_paramsPairMap.at(t_param).second += t_value;
        }

        
    }
    else{
        m_paramsPairMap.at(t_param).second += t_value;
    }

    if(m_paramsPairMap.at(t_param).first > m_paramsPairMap.at(t_param).second){
        m_paramsPairMap.at(t_param).first = m_paramsPairMap.at(t_param).second;
    }
}

void Character::updateAlignment(Alignment t_alignment){
    m_alignment = t_alignment;
}

void Character::updateSpeed(float t_speed){
    m_speed = t_speed;
}