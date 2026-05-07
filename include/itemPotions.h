#pragma once

#include "item.h"

#define POTIONS_MAX_STACK_SIZE 99

#define MINOR_HEALTH_OFFSET     3
#define MINOR_STAMINA_OFFSET    3
#define MINOR_MANA_OFFSET       3


class MinorHealthPotion : public Item{

    public:
        MinorHealthPotion():
            Item(POTIONS_MAX_STACK_SIZE, ItemUtility::Consumable){}
        ~MinorHealthPotion(){}

        void use(void* effect) override {

            ConsumableEffects* consumableEffects = (ConsumableEffects*) effect;

            consumableEffects->healthOffset = MINOR_HEALTH_OFFSET;

        }

        ItemType getItemType() override {
            return ItemType::Minor_Health_Potion;
        }
};

class MinorStaminaPotion : public Item{

    public:
        MinorStaminaPotion():
            Item(POTIONS_MAX_STACK_SIZE, ItemUtility::Consumable){}
        ~MinorStaminaPotion(){}

        void use(void* effect) override {

            ConsumableEffects* consumableEffects = (ConsumableEffects*) effect;

            consumableEffects->staminaOffset = MINOR_STAMINA_OFFSET;

        }

        ItemType getItemType() override {
            return ItemType::Minor_Stamina_Potion;
        }
};

class MinorManaPotion : public Item{

    public:
        MinorManaPotion():
            Item(POTIONS_MAX_STACK_SIZE, ItemUtility::Consumable){}
        ~MinorManaPotion(){}

        void use(void* effect) override {

            ConsumableEffects* consumableEffects = (ConsumableEffects*) effect;

            consumableEffects->manaOffset = MINOR_MANA_OFFSET;

        }

        ItemType getItemType() override {
            return ItemType::Minor_Mana_Potion;
        }
};