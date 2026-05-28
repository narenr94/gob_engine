#pragma once

#include "defines.h"

#include <string>


class Character; //Forward declaration

struct Race{

    private:

    std::string m_raceName;

    Character* m_character;

    public:

    Race(const std::string& t_raceName, Character* t_character);
    ~Race();

    //-----replace data

    void setData();

    void realizeOptions();

    std::string getRaceName() const;


};
