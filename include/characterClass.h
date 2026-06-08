#pragma once

#include <string>

class Character; //Forward Declaration

class CharacterClass{

        private:

    std::string m_className;

    Character* m_character;

    public:

    CharacterClass(const std::string& t_className, Character* t_character);
    ~CharacterClass();

    //-----replace data

    void setData();

    void realizeOptions();

    std::string getClassName() const;

};