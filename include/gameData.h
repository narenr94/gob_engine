#pragma once

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

        GameData(const std::string& t_gameDataPath);

    public:

        static GameData* getInstance(const std::string& t_gameDataPath = "game_data");

        std::vector<std::string> getAbilitiesVector() const;

        std::vector<std::string> getParamsVector() const;

        std::vector<std::string> getClassesVector() const;

        std::vector<std::string> getRacesVector() const;

        std::vector<std::string> getLanguagesVector() const;

        RaceData getRaceData(const std::string& t_raceName, bool enablePlayerInput) const;

};