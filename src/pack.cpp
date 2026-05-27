#include "pack.h"

void Pack::addItem(const std::string& item, unsigned short int count){

    for(auto& it : m_items){
        if(it.first == item){
            it.second += count;
            return;
        }
    }

    m_items.push_back({item, count});

}

std::vector<std::pair<std::string, unsigned short int>> Pack::getItems() const {
    return m_items;
}