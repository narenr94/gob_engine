#include "gameData.h"
#include "raceData.h"

RaceData GameData::getRaceData(const std::string& t_raceName, bool enablePlayerInput) const {
    for(auto& race : m_racesVector){
        if(race == t_raceName){
            RaceData data;
            getRaceDataFrom(m_gameDataPath + "/races/" + race + ".json", data, enablePlayerInput);
            return data;
        }
    }

    // Return an empty RaceData if the race is not found
    return RaceData();
}
