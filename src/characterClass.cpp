#include "characterClass.h"
#include "character.h"
#include "gameData.h"


CharacterClass::CharacterClass(const std::string& t_className, Character* t_character)
: m_character(t_character), m_className(t_className)
{
    ConsolidatedData* conData = new ConsolidatedData();
    ConsolidatedOptionsData* conOptionData = new ConsolidatedOptionsData();

    GameData* gameData = GameData::getInstance();

    gameData->getClassData(gameData->getClassFilePath(m_className), *conData, *conOptionData);
}

CharacterClass::~CharacterClass(){
    m_character = nullptr;
}


std::string CharacterClass::getClassName() const{
    return m_className;
}