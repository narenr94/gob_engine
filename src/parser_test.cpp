#include "jsonRaceParser.h"

#define RACE_JSON_DIR "/home/user/gob_engine/game_data/race"



int main()
{

    try{

        findAllRaces(RACE_JSON_DIR);

        for(auto& rc : g_racesVector){
            LOG("Race:" + rc.first);
            rc.second.printData();
            LOG("");
            LOG("");
        }

    }
    catch(std::exception& ex){
        LOG("Exception:" + std::string(ex.what()));
    }

    return 0;
}