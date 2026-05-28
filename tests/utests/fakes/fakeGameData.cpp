#include "gameData.h"
#include "commonJsonParser.h"

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

std::vector<std::string> GameData::getItemsVector() const {
    return {};
}

void GameData::getRaceData(const std::string& t_racePath, ConsolidatedData& t_conData, ConsolidatedOptionsData& t_conOptdata) const {
    // Stub: Race data loading not tested in unit tests
}

std::string GameData::getRaceFilePath(const std::string& t_raceName) const{
    return "";
}
