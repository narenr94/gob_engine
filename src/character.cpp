#include "character.h"

#include "humanCharacters.h"

std::unique_ptr<Character> CharacterFactory::createCharacter(std::string& t_name, CharacterClass t_type){
    switch(t_type){
        case CharacterClass::Warrior:
            return std::make_unique<Warrior>(t_name);
        case CharacterClass::Mage:
            return std::make_unique<Mage>(t_name);
        case CharacterClass::Ranger:
            return std::make_unique<Ranger>(t_name);
        case CharacterClass::NA:
            return std::make_unique<Character>(t_name, NaOffsets());
        default:
            return std::make_unique<Character>(t_name, NaOffsets());                        
    }
}