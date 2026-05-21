#pragma once

#include "defines.h"

#include <memory>

class Race;
class Character;

std::unique_ptr<Race> raceFactory(const std::string& t_race, Character* t_character, CustomRaceData* t_customData = nullptr);

short int calculateAbilityModifier(const unsigned short int t_abilityScore) {
    double raw = (static_cast<int>(t_abilityScore) - 10) / 2.0;
    return static_cast<short int>(std::floor(raw));
}

Level incrementLevel(Level t_currLevel){

    switch(t_currLevel){
        case Level::Lvl1:
            return Level::Lvl2;
            break;
        case Level::Lvl2:
            return Level::Lvl3;
            break;
        case Level::Lvl3:
            return Level::Lvl4;
            break;
        case Level::Lvl4:
            return Level::Lvl5;
            break;
        case Level::Lvl5:
            return Level::Lvl6;
            break;
        case Level::Lvl6:
            return Level::Lvl7;
            break;
        case Level::Lvl7:
            return Level::Lvl8;
            break;
        case Level::Lvl8:
            return Level::Lvl9;
            break;
        case Level::Lvl9:
            return Level::Lvl10;
            break;
        case Level::Lvl10:
            return Level::Lvl11;
            break;
        case Level::Lvl11:
            return Level::Lvl12;
            break;
        case Level::Lvl12:
            return Level::Lvl13;
            break;
        case Level::Lvl13:
            return Level::Lvl14;
            break;
        case Level::Lvl14:
            return Level::Lvl15;
            break;
        case Level::Lvl15:
            return Level::Lvl16;
            break;
        case Level::Lvl16:
            return Level::Lvl17;
            break;
        case Level::Lvl17:
            return Level::Lvl18;
            break;
        case Level::Lvl18:
            return Level::Lvl19;
            break;
        case Level::Lvl19:
            return Level::Lvl20;
            break;
        case Level::Lvl20:
        default:
            return t_currLevel;
            break;
        
    }
}
