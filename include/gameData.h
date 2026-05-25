#pragma once

#include "commonJsonParser.h"

#include <vector>
#include <string>

struct RaceData; //Forward declaration

class GameData{

    private:

        std::string m_gameDataPath;

        //------Vector of Abilities

        std::vector<std::string> m_abilitiesVector;

        //------Vector of Character Params

        std::vector<std::string> m_paramsVector;

        //------Vector of Classes

        std::vector<std::string> m_classesVector;

        //------Vector of Races

        std::vector<std::string> m_racesVector;

        //------Vector of Languages

        std::vector<std::string> m_languagesVector;

        GameData(const std::string& t_gameDataPath):
        m_gameDataPath(t_gameDataPath)
        {
            m_abilitiesVector = extractAndApplyAbilities(m_gameDataPath + "/abilities.json");
            m_paramsVector = extractAndApplyParams(m_gameDataPath + "/params.json");

            //todo : classes

            m_racesVector = findAllRaces(m_gameDataPath + "/races");

            m_languagesVector = extractAllLanguages(m_gameDataPath + "/languages.json");
        }

    public:

        static GameData* getInstance(const std::string& t_gameDataPath = "game_data"){
            static GameData* instance = new GameData(t_gameDataPath);
            return instance;
        }

        std::vector<std::string> getAbilitiesVector() const {
            return m_abilitiesVector;
        }

        std::vector<std::string> getParamsVector() const {
            return m_paramsVector;
        }

        std::vector<std::string> getClassesVector() const {
            return m_classesVector;
        }

        std::vector<std::string> getRacesVector() const {
            return m_racesVector;
        }

        std::vector<std::string> getLanguagesVector() const {
            return m_languagesVector;
        }

        RaceData getRaceData(const std::string& t_raceName, bool enablePlayerInput) const;

};