#pragma once

#include "defines.h"

#include <vector>
#include <string>


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

        //------Vector of all items

        std::vector<std::string> m_itemsVector;

        GameData(const std::string& t_gameDataPath);

    public:

        static GameData* getInstance(const std::string& t_gameDataPath = "game_data");

        std::vector<std::string> getAbilitiesVector() const;

        std::vector<std::string> getParamsVector() const;

        std::vector<std::string> getClassesVector() const;

        std::vector<std::string> getRacesVector() const;

        std::vector<std::string> getLanguagesVector() const;

        std::vector<std::string> getItemsVector() const;

        std::string getRaceFilePath(const std::string& t_raceName) const;

        void getRaceData(const std::string& t_raceName, ConsolidatedData& conData, ConsolidatedOptionsData& conOptdata) const;

};