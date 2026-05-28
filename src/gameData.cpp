#include "gameData.h"
#include "commonJsonParser.h"

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

void GameData::getRaceData(const std::string& t_racePath, ConsolidatedData& t_conData, ConsolidatedOptionsData& t_conOptdata) const {
    
    json j;
    if(readJsonFile(t_racePath, j)){

        if(j.contains("base_race")){

            if(j["base_race"].is_string()){
                std::string baseRaceName = j["base_race"];
                std::string baseRacePath = std::filesystem::path(t_racePath).parent_path().string() + "/" + baseRaceName + ".json";
                getRaceData(baseRacePath, t_conData, t_conOptdata);
            }
            updateConsolidatedData(j, t_conData);
            updateConsolidatedOptionsData(j, t_conOptdata);
        }
        else{
            throw std::runtime_error("base_race key not found in race JSON file:" + t_racePath);
        }
    }


}

std::vector<std::string> GameData::getItemsVector() const {
    return m_itemsVector;
}

std::string GameData::getRaceFilePath(const std::string& t_raceName) const{

    return m_gameDataPath + "/races/" + t_raceName + ".json";

}
