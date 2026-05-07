#include "character.h"

#include "humanCharacters.h"

static CharacterParamOffsets NaOffsets(){
    return {0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
            };
}

std::shared_ptr<Character> CharacterFactory::createCharacter(std::string& t_name, CharacterClass t_type){
    switch(t_type){
        case CharacterClass::Human_Warrior:
            return std::make_shared<Warrior>(t_name);
        case CharacterClass::Human_Mage:
            return std::make_shared<Mage>(t_name);
        case CharacterClass::Human_Ranger:
            return std::make_shared<Ranger>(t_name);
        case CharacterClass::NA:
            return std::make_shared<Character>(t_name, NaOffsets());
        default:
            return std::make_shared<Character>(t_name, NaOffsets());                        
    }
}