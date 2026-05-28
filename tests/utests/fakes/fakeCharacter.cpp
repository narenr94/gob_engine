#include "character.h"



void Character::assignCharacterParams(){
    
}

void Character::assignAbilities(){
    
        
}

void Character::assignRandomValuesToAbilities(){
    
}

Character::Character(const std::string& t_name, const std::string& t_race, 
            std::vector<std::string> t_class, const Level t_level) :
m_name(t_name), m_level(t_level), m_race(nullptr)
{
    

}

Character::~Character(){
    
}

//----------------Gets

std::string Character::getName() const {
    return "";
}

std::string Character::getRace() const {
    return "";
}

std::string Character::getClass() const {

    //return m_class->getClass();
    return "";
}

Level Character::getLevel() const {
    return Level::Lvl1;
}

AgeData Character::getAgeData() const {
    return AgeData{};
}

SizeData Character::getSizeData() const {
    return SizeData{};
}

float Character::getSpeed() const {
    return 0.0f;
}

std::vector<LanguageData> Character::getLanguageData() const {
    return {};
}

ProficiencyData Character::getProficiencyData() const {
    return ProficiencyData{};
}

std::vector<ResilienceData> Character::getResilienceDataVector() const {
    return {};
}

DarkvisionData Character::getDarkvisionData() const {
    return DarkvisionData{};
}

bool Character::getAbilityScore(const std::string& t_ability, unsigned short int& value) const {
   return false;
}

bool Character::getAbilityModifier(const std::string& t_ability, unsigned short int& value) const {
    return false;
}

bool Character::getParamMax(const std::string& t_param, unsigned short int& value) const {
    return false;
}

bool Character::getParamCurr(const std::string& t_param, unsigned short int& value) const {
    return false;
}

Alignment Character::getAlignment() const {
    return Alignment::lawful_good;
}

std::vector<std::pair<std::string, unsigned short int>> Character::getPackItems() const {
    return {};
}

float Character::getSleepDuration() const {
    return 0.0f;
}


//----------------Sets

void Character::setAgeData(const AgeData& t_ageData){
    
}

void Character::setSizeData(const SizeData& t_sizeData){
}

void Character::addLanguageProficiency(const std::string& language, bool speak, bool read, bool write){
    
}

void Character::setProficiencyData(const ProficiencyData& t_proficiencyData){
    
}

void Character::addResilienceData(const ResilienceData& t_resilienceData){
    
}

void Character::setDarkvisionData(const DarkvisionData& t_darkvisionData){
    
}

void Character::updateName(const std::string& t_name){
  
}

void Character::levelUp(){

}

bool Character::updateParamMax(const std::string& t_param, const unsigned short int t_value){
    return false;
}

bool Character::updateParamCurr(const std::string& t_param, const unsigned short int t_value){
    return false;
}

bool Character::updateAbilityScore(const std::string& t_ability, const unsigned short int t_value){
   return false;
}

bool Character::addToAbilityScore(const std::string& t_ability, const short int t_value){
   return false;
}

void Character::addToParamMax(const std::string& t_param, const unsigned short int t_value){
    
}

void Character::updateAlignment(Alignment t_alignment){
    
}

void Character::updateSpeed(float t_speed){
    
}

void Character::updateSleepDuration(float t_sleepDurationHrs){
    
}

void Character::addItemToPack(const std::string& item, unsigned short int count){
    
}

void Character::updatePack(std::unique_ptr<Pack> t_pack){
    
}