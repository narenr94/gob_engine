#include "gameData.h"
#include "raceData.h"

GameData::GameData(const std::string& t_gameDataPath):
m_gameDataPath(t_gameDataPath)
{
    m_abilitiesVector = extractAndApplyAbilities(m_gameDataPath + "/abilities.json");
    m_paramsVector = extractAndApplyParams(m_gameDataPath + "/params.json");

    //todo : classes

    m_racesVector = findAllRaces(m_gameDataPath + "/races");

    m_languagesVector = extractAllLanguages(m_gameDataPath + "/languages.json");
}

GameData* GameData::getInstance(const std::string& t_gameDataPath){
    static GameData* instance = new GameData(t_gameDataPath);
    return instance;
}

std::vector<std::string> GameData::getAbilitiesVector() const {
    return m_abilitiesVector;
}

std::vector<std::string> GameData::getParamsVector() const {
    return m_paramsVector;
}

std::vector<std::string> GameData::getClassesVector() const {
    return m_classesVector;
}

std::vector<std::string> GameData::getRacesVector() const {
    return m_racesVector;
}

std::vector<std::string> GameData::getLanguagesVector() const {
    return m_languagesVector;
}

RaceData GameData::getRaceData(const std::string& t_raceName) const {
    for(auto& race : m_racesVector){
        if(race == t_raceName){
            RaceData data;
            getRaceDataFrom(m_gameDataPath + "/races/" + race + ".json", data);
            return data;
        }
    }

    // Return an empty RaceData if the race is not found
    return RaceData();
}

std::vector<std::string> GameData::getItemsVector() const {
    return m_itemsVector;
}
