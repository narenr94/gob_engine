#include "race.h"
#include "character.h"
#include "gameData.h"


Race::Race(const std::string& t_raceName, Character* t_character)
: m_character(t_character), m_raceName(t_raceName)
{
    ConsolidatedData* conData = new ConsolidatedData();
    ConsolidatedOptionsData* conOptionData = new ConsolidatedOptionsData();

    GameData* gameData = GameData::getInstance();

    try{
        gameData->getRaceData(gameData->getRaceFilePath(m_raceName), *conData, *conOptionData);
    }
    catch(const std::exception& e){
        LOG("Error loading race data for " + m_raceName + ": " + e.what());
    }

}

Race::~Race(){
    m_character = nullptr;
}


std::string Race::getRaceName() const{
    return m_raceName;
}