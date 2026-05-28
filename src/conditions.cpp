#include "conditions.h"

#include "character.h"

bool if_character_has_item(void* arg){

    ifCharacterHasItemArg* args = static_cast<ifCharacterHasItemArg*>(arg);

    std::vector<std::pair<std::string, unsigned short int>> itemsList = args->character->getPackItems();

    for(auto& g : itemsList){
        if((g.first == args->ind) && (args->count <= g.second)){
            return true;
        }
    }

    return false;
}