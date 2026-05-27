#pragma once

#include <vector>
#include <string>
#include <utility>

class Pack{

    private:

        std::vector<std::pair<std::string, unsigned short int>> m_items;

        unsigned short int m_maxWeight;

        unsigned short int m_maxVolume;

    public:

        void addItem(const std::string& item, unsigned short int count);

        std::vector<std::pair<std::string, unsigned short int>> getItems() const;
};