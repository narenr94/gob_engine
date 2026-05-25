#pragma once

#include "defines.h"
#include "raceData.h"

class Character; //Forward declaration

class Race {
    private:
        Character* m_character;

        std::string m_race;

    protected:

        virtual void raceBenifitsCharacterCreation() = 0;

    public:
        Race(Character* t_character, const std::string& t_race, bool enablePlayerInput) :
        m_character(t_character), m_race(t_race)
        {

            RaceData m_raceData = GameData::getInstance()->getRaceData(m_race, enablePlayerInput);
            m_raceData.applyRaceData(m_character);

        }

        virtual ~Race() = default;

        virtual void levelUp() = 0;

        std::string getRace() const {
            return m_race;
        }

        
        
};
