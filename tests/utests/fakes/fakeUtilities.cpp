#include "utilities.h"

#include <cmath>
#include <stdexcept>

short int calculateAbilityModifier(const unsigned short int t_abilityScore) {
    return 0;
}

Level incrementLevel(Level t_currLevel){

    return Level::Lvl1;
    
}

std::string alignmentToString(Alignment alignment){
    
    return "";
}

std::string sizeCategoryToString(SizeCategory sz){
    return "";
}

std::string illuminationTypeToString(IlluminationType it){
    return "";
}

Alignment stringToAlignment(const std::string& alignmentStr){
    
    return Alignment::neutral_neutral;
}

SizeCategory stringToSizeCategory(const std::string& sizeCategoryStr){
    return SizeCategory::Medium;
}

IlluminationType stringToIlluminationType(const std::string& illuminationTypeStr){

    return IlluminationType::Normal;
}

std::string proficiencyTypeToString(ProficiencyType pt){
    
    return "";

}

ProficiencyType stringToProficiencyType(const std::string& str){
    return ProficiencyType::Weapons;
    
}

std::string jsonKeyToString(JsonKeys jk){
    return "";
}

JsonKeys stringToJsonKeys(const std::string& str){
    return JsonKeys::name;

}