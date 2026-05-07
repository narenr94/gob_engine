#pragma once

#include <map>
#include "item.h"

class Character; //Forward-declaration

class Inventory{
    private:
        unsigned short int m_slots;
        std::map<ItemType, unsigned int> m_itemMap;

        Character* m_character;

        bool addNewItem(ItemType t_itemType, unsigned int short t_amount){

            if(m_itemMap.size() >= m_slots){
                return false;
            }

            std::unique_ptr<Item> item = ItemFactory::createItem(t_itemType);
            unsigned short int stackSize = item->getStackSize();

            if(t_amount < stackSize){
                m_itemMap[t_itemType] = t_amount;
            }
            else{
                m_itemMap[t_itemType] = stackSize;
            }            

        }

        bool addExistingItem(ItemType t_itemType, unsigned int short t_amount){

            std::unique_ptr<Item> item = ItemFactory::createItem(t_itemType);
            unsigned short int stackSize = item->getStackSize();

            if(m_itemMap[t_itemType] + t_amount < stackSize){
                m_itemMap[t_itemType] += t_amount;
            }
            else{
                m_itemMap[t_itemType] = stackSize;
            }

        }

    public:
        Inventory(Character* t_character, unsigned short int t_slots):
        m_slots(t_slots), m_character(t_character)
        {}

        ~Inventory(){
            m_character = nullptr;
        }

        //----Gets
        unsigned short int getNumberOfSlots() const {
            return m_slots;
        }

        //----Sets
        void setNumberOfSlots(unsigned short int t_slots){

        }

        bool addItem(ItemType t_itemType, unsigned int short t_amount){
            if(m_itemMap.find(t_itemType) == m_itemMap.end()){
                return addNewItem(t_itemType, t_amount);
            }
            else{
                addExistingItem(t_itemType, t_amount);
            }

            return true;
        }

        bool dropItem(ItemType t_itemType, unsigned int short t_amount){
            if(m_itemMap.find(t_itemType) == m_itemMap.end()){
                return false;
            }

            if(m_itemMap[t_itemType] > t_amount){
                m_itemMap[t_itemType] -= 1;
            }
            else{
                m_itemMap[t_itemType] = 0;
            }
            
            if(m_itemMap[t_itemType] == 0){
                m_itemMap.erase(t_itemType);
            }
        }

        bool useItem(ItemType t_itemType);


};