#include "gameData.h"
#include "commonJsonParser.h"
#include <filesystem>

GameData::GameData(const std::string& t_gameDataPath):
m_gameDataPath(t_gameDataPath)
{
    try{
        m_abilitiesVector = extractAndApplyAbilities(m_gameDataPath + "/abilities.json");
    }
    catch(const std::exception& e){
        LOG("Exception will finding all available abilities " + std::string(e.what()));
    }

    try{
        m_paramsVector = extractAndApplyParams(m_gameDataPath + "/params.json");
    }
    catch(const std::exception& e){
        LOG("Exception will finding all available params " + std::string(e.what()));
    }

    try{
        m_languagesVector = extractAllLanguages(m_gameDataPath + "/languages.json");
    }
    catch(const std::exception& e){
        LOG("Exception will finding all available languages " + std::string(e.what()));
    }

    try{
        m_racesVector = findAllRaces(m_gameDataPath + "/races");
    }
    catch(const std::exception& e){
        LOG("Exception will finding all available races " + std::string(e.what()));
    }

    try{
        m_classesVector = findAllClasses(m_gameDataPath + "/classes");
    }
    catch(const std::exception& e){
        LOG("Exception will finding all available classes " + std::string(e.what()));
    }

    
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
    
    std::string baseRaceName;

    if(getBaseRace(t_racePath, baseRaceName)){
        std::string baseRacePath = std::filesystem::path(t_racePath).parent_path().string() + "/" + baseRaceName + ".json";
        getRaceData(baseRacePath, t_conData, t_conOptdata);
    }

    try{
        updateConsolidatedData(t_racePath, t_conData);
        updateConsolidatedOptionsData(t_racePath, t_conOptdata);
    }
    catch(const std::exception& e){
        LOG("Error loading race Data : " + t_racePath + " - " + std::string(e.what()));
    }

#if defined(TEST_PRINTS)
    LOG("Race data for " + t_racePath);
    t_conData.printData();
    t_conOptdata.printOption();
#endif  

}

void GameData::getClassData(const std::string& t_classPath, ConsolidatedData& t_conData, ConsolidatedOptionsData& t_conOptdata) const {

    std::string baseClass;

    if(getBaseClass(t_classPath, baseClass)){
        std::string baseClassPath = std::filesystem::path(t_classPath).parent_path().string() + "/" + baseClass + ".json";
        getClassData(baseClassPath, t_conData, t_conOptdata);
    }

    try{
        updateConsolidatedData(t_classPath, t_conData);
        updateConsolidatedOptionsData(t_classPath, t_conOptdata);
    }
    catch(const std::exception& e){
        LOG("Error loading class Data : " + t_classPath + " - " + std::string(e.what()));
    }
}

std::vector<std::string> GameData::getItemsVector() const {
    return m_itemsVector;
}

std::string GameData::getRaceFilePath(const std::string& t_raceName) const{

    std::string raceFilePath = m_gameDataPath + "/races/";

    for (const auto& entry : std::filesystem::recursive_directory_iterator(raceFilePath)){
        if (entry.is_regular_file()){
            if(entry.path().filename() == t_raceName + ".json"){
                return entry.path().string();
            }
        }
    }

    throw std::runtime_error("Race file not found: " + t_raceName + " in path: " + raceFilePath);

}

std::string GameData::getClassFilePath(const std::string& t_className) const{
    
    std::string classFilePath = m_gameDataPath + "/classes/";

    for (const auto& entry : std::filesystem::recursive_directory_iterator(classFilePath)){
        if (entry.is_regular_file()){
            if(entry.path().filename() == t_className + ".json"){
                return entry.path().string();
            }
        }
    }

    throw std::runtime_error("Class file not found: " + t_className + " in path: " + classFilePath);
}

std::vector<std::string> GameData::findAllRaces(const std::string& t_racePath){

    std::vector<std::string> racesVector;

    if (!std::filesystem::exists(t_racePath) || !std::filesystem::is_directory(t_racePath)) {
        throw std::runtime_error("Races directory doest exist: " + t_racePath);
        return racesVector;
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(t_racePath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            
            try{

                if(!getIfAbstract(entry.path().string())){
                    std::string raceName = getName(entry.path().string());
                    racesVector.push_back(raceName);
                }

            }
            catch(const std::exception& e){
                LOG("Error processing Race Data file: " + entry.path().string() + " - " + std::string(e.what()));
            }
            
        }
    }

    return racesVector;
}

std::vector<std::string> GameData::findAllClasses(const std::string& t_classPath){

    std::vector<std::string> classesVector;

    if (!std::filesystem::exists(t_classPath) || !std::filesystem::is_directory(t_classPath)) {
        throw std::runtime_error("Classes directory doest exist: " + t_classPath);
        return classesVector;
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(t_classPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            
            try{

                if(!getIfAbstract(entry.path().string())){
                    std::string className = getName(entry.path().string());
                    classesVector.push_back(className);
                }

            }
            catch(const std::exception& e){
                LOG("Error processing Class Data file: " + entry.path().string() + " - " + std::string(e.what()));
            }
            
        }
    }

    return classesVector;

}
