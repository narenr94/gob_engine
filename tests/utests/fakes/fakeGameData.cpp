#include "gameData.h"
#include "raceData.h"

GameData::GameData(const std::string& t_gameDataPath)
{
    
}

GameData* GameData::getInstance(const std::string& t_gameDataPath){
    static GameData* instance = new GameData(t_gameDataPath);
    return instance;
}

std::vector<std::string> GameData::getAbilitiesVector() const {
    return {};
}

std::vector<std::string> GameData::getParamsVector() const {
    return {};
}

std::vector<std::string> GameData::getClassesVector() const {
    return {};
}

std::vector<std::string> GameData::getRacesVector() const {
    return {};
}

std::vector<std::string> GameData::getLanguagesVector() const {
    return {};
}

RaceData GameData::getRaceData(const std::string& t_raceName, bool enablePlayerInput) const {
    return RaceData();
}
