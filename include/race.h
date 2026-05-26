#pragma once

#include <string>

class Character; //Forward declaration

class Race {
    private:
        Character* m_character;

        std::string m_race;

    protected:

        void raceBenifitsCharacterCreation();

    public:
        Race(Character* t_character, const std::string& t_race, bool enablePlayerInput);

        ~Race() = default;

        void levelUp();

        std::string getRace() const;        
        
};
