#include "race.h"


Race::Race(Character* t_character, const std::string& t_race, bool enablePlayerInput) :
m_character(t_character), m_race(t_race)
{

    // RaceData m_raceData = GameData::getInstance()->getRaceData(m_race, enablePlayerInput);
    // m_raceData.applyRaceData(m_character);

}

void Race::raceBenifitsCharacterCreation(){

}

void Race::levelUp(){

}

std::string Race::getRace() const {
    return m_race;
}