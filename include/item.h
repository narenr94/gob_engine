#pragma once

#include <memory>
#include "defines.h"

class Item{
    private:
        unsigned short int m_stackSize;
        ItemUtility m_utility;
    public:
        Item(unsigned short int t_stackSize, ItemUtility t_utility) :
            m_stackSize(t_stackSize), m_utility(t_utility)
            {}

        virtual ~Item() = default;

        //----Gets

        unsigned short int getStackSize() const {
            return m_stackSize;
        }

        ItemUtility getItemUtility() const {
            return m_utility;
        }

        //----Sets

        void setStackSize(unsigned short int t_stackSize){
            m_stackSize = t_stackSize;
        }

        void setItemUtility(ItemUtility t_utility){
            m_utility = t_utility;
        }

        //----Interface
        virtual void use(void* effect) = 0;

        virtual ItemType getItemType() = 0;
};

class ItemFactory{
    public:
        static std::unique_ptr<Item> createItem (ItemType t_type);
};