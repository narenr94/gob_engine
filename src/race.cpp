#include "race.h"
#include "character.h"
#include "gameData.h"

#include <filesystem>


Race::Race(const std::string& t_raceName, Character* t_character)
: m_character(t_character), m_raceName(t_raceName)
{
    ConsolidatedData* conData = new ConsolidatedData();
    ConsolidatedOptionsData* conOptionData = new ConsolidatedOptionsData();

    GameData* gameData = GameData::getInstance();

    gameData->getRaceData(gameData->getRaceFilePath(m_raceName), *conData, *conOptionData);
}

Race::~Race(){
    m_character = nullptr;
}


std::string Race::getRaceName() const{
    return m_raceName;
}