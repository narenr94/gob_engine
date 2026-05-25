#pragma once

#include "log.h"

#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> getPlayerInputOptionChoices(std::vector<std::string> optionsVector, unsigned short int chooseCount){

    if(chooseCount > optionsVector.size()){
        chooseCount = optionsVector.size();
    }

    std::vector<std::string> chosenOptions;

    unsigned short int i = 0;

    LOG("Choose " + std::to_string(chooseCount) + " from below options!!!");

    for(auto& ov : optionsVector){

        LOG(std::to_string(i) + " : " + ov);
        i++;

    }

    while(chosenOptions.size() < chooseCount){

        LOG("Enter the number corresponding to your choice : ");
        unsigned short int choice;
        std::cin >> choice;

        if(choice >= optionsVector.size()){
            LOG("Invalid choice, try again!!!");
            continue;
        }

        if(std::find(chosenOptions.begin(), chosenOptions.end(), optionsVector[choice]) != chosenOptions.end()){
            LOG("Option already chosen, try again!!!");
            continue;
        }

        chosenOptions.push_back(optionsVector[choice]);
    }

    return chosenOptions;

    
}