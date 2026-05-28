#include "race.h"


Race::Race(const std::string& t_raceName, Character* t_character)
: m_character(t_character), m_raceName(t_raceName)
{
    // Stub: Race data loading not tested in unit tests
}

Race::~Race(){
    m_character = nullptr;
}

std::string Race::getRaceName() const {
    return m_raceName;
}

void Race::setData(){
    // Stub: Race data application not tested in unit tests
}

void Race::realizeOptions(){
    // Stub: Options realization not tested in unit tests  
}