#include "inventory.h"
#include "character.h"

bool Inventory::useItem(ItemType t_itemType)
{
    if(m_itemMap.find(t_itemType) == m_itemMap.end()){
        return false;
    }

    bool ret = false;

    std::unique_ptr<Item> item = ItemFactory::createItem(t_itemType);
    ItemUtility utility = item->getItemUtility();

    switch(utility){
        case ItemUtility::Consumable:
            ConsumableEffects* effects;
            item->use((void*) effects);
            m_character->applyConsumableEffects(effects);
            ret = true;
            break;
    }

    dropItem(t_itemType, 1);

    return ret;

}