#include "item.h"
#include "itemPotions.h"

std::unique_ptr<Item> ItemFactory::createItem (ItemType t_type){
    switch(t_type){
        case ItemType::Minor_Health_Potion:
            return std::make_unique<MinorHealthPotion>();
        case ItemType::Minor_Stamina_Potion:
            return std::make_unique<MinorStaminaPotion>();
        case ItemType::Minor_Mana_Potion:
            return std::make_unique<MinorManaPotion>();
    }
}