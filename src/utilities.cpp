#include "utilities.h"
#include "race.h"
#include "character.h"

#include <algorithm> 

std::unique_ptr<Race> raceFactory(const std::string& t_race, Character* t_character, CustomRaceData* t_customData = nullptr){

    auto it = std::find(g_racesVector.begin(), g_racesVector.end(), t_race);

    if(t_race == "Hill Dwarf"){
        return std::make_unique<HillDwarf>(t_character, t_race);
    }
    else if (t_race == "Mountain Dwarf"){
        return std::make_unique<MountainDwarf>(t_character, t_race);
    }
    else if (t_race == "High Elf"){
        return std::make_unique<HighElf>(t_character, t_race);
    }
    else if (t_race == "Wood Elf"){
        return std::make_unique<WoodElf>(t_character, t_race);
    }
    else if (t_race == "Dark Elf"){
        return std::make_unique<DarkElf>(t_character, t_race);
    }
    else if (t_race == "LightFoot Halfling"){
        return std::make_unique<LightfootHalfling>(t_character, t_race);
    }
    else if (t_race == "Stout Halfling"){
        return std::make_unique<StoutHalfling>(t_character, t_race);
    }
    else if (t_race == "Human"){
        return std::make_unique<Human>(t_character, t_race);
    }
    else if (it != g_racesVector.end()){
        return std::make_unique<CustomRace>(t_character, t_race, t_customData);
    }
    
    return std::make_unique<Human>(t_character);
    
}