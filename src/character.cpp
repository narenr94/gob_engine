#include "character.h"

#include "humanCharacters.h"

std::unique_ptr<Character> CharacterFactory::createCharacter(std::string& t_name, CharacterClass t_type){
    switch(t_type){
        case CharacterClass::Human_Warrior:
            return std::make_unique<Warrior>(t_name);
        case CharacterClass::Human_Mage:
            return std::make_unique<Mage>(t_name);
        case CharacterClass::Human_Ranger:
            return std::make_unique<Ranger>(t_name);
        case CharacterClass::NA:
            return std::make_unique<Character>(t_name, NaOffsets());
        default:
            return std::make_unique<Character>(t_name, NaOffsets());                        
    }
}