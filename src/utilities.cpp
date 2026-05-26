#include "utilities.h"

#include <cmath>
#include <stdexcept>

short int calculateAbilityModifier(const unsigned short int t_abilityScore) {
    double raw = (static_cast<int>(t_abilityScore) - 10) / 2.0;
    return static_cast<short int>(std::floor(raw));
}

Level incrementLevel(Level t_currLevel){

    switch(t_currLevel){
        case Level::Lvl1:
            return Level::Lvl2;
            break;
        case Level::Lvl2:
            return Level::Lvl3;
            break;
        case Level::Lvl3:
            return Level::Lvl4;
            break;
        case Level::Lvl4:
            return Level::Lvl5;
            break;
        case Level::Lvl5:
            return Level::Lvl6;
            break;
        case Level::Lvl6:
            return Level::Lvl7;
            break;
        case Level::Lvl7:
            return Level::Lvl8;
            break;
        case Level::Lvl8:
            return Level::Lvl9;
            break;
        case Level::Lvl9:
            return Level::Lvl10;
            break;
        case Level::Lvl10:
            return Level::Lvl11;
            break;
        case Level::Lvl11:
            return Level::Lvl12;
            break;
        case Level::Lvl12:
            return Level::Lvl13;
            break;
        case Level::Lvl13:
            return Level::Lvl14;
            break;
        case Level::Lvl14:
            return Level::Lvl15;
            break;
        case Level::Lvl15:
            return Level::Lvl16;
            break;
        case Level::Lvl16:
            return Level::Lvl17;
            break;
        case Level::Lvl17:
            return Level::Lvl18;
            break;
        case Level::Lvl18:
            return Level::Lvl19;
            break;
        case Level::Lvl19:
            return Level::Lvl20;
            break;
        case Level::Lvl20:
        default:
            return t_currLevel;
            break;
        
    }
}

std::string alignmentToString(Alignment alignment){
    
    for(auto& mp : alignmentStrMap){
        if(mp.first == alignment){
            return mp.second;
        }
    }
    
    throw std::runtime_error("Invalid alignment");

    return "";
}

std::string sizeCategoryToString(SizeCategory sz){
    for(auto& mp : sizeCategoryStrMap){
        if(mp.first == sz){
            return mp.second;
        }
    }

    throw std::runtime_error("Invalid size category");

    return "";
}

std::string illuminationTypeToString(IlluminationType it){
    for(auto& mp : illumincationTypeStrMap){
        if(mp.first == it){
            return mp.second;
        }
    }

    throw std::runtime_error("Invalid illumincation type");

    return "";
}

Alignment stringToAlignment(const std::string& alignmentStr){
    
    for(auto& mp : alignmentStrMap){
        if(mp.second == alignmentStr){
            return mp.first;
        }
    }
    
    throw std::runtime_error("Invalid alignment string: " + alignmentStr);

    return Alignment::neutral_neutral;
}

SizeCategory stringToSizeCategory(const std::string& sizeCategoryStr){
    for(auto& mp : sizeCategoryStrMap){
        if(mp.second == sizeCategoryStr){
            return mp.first;
        }
    }
    
    throw std::runtime_error("Invalid size category string: " + sizeCategoryStr);

    return SizeCategory::Medium;
}

IlluminationType stringToIlluminationType(const std::string& illuminationTypeStr){

    if(illuminationTypeStr == "normal"){
        return IlluminationType::Normal;
    }
    else if(illuminationTypeStr == "dim"){
        return IlluminationType::Dim;
    }
    else if(illuminationTypeStr == "dark"){
        return IlluminationType::Dark;
    }

    throw std::runtime_error("Invalid illumination category string: " + illuminationTypeStr);

    return IlluminationType::Normal;
}

std::string proficiencyTypeToString(ProficiencyType pt){
    
    for(auto& pft : proficiencyTypeStrMap){
        if(pft.first == pt){
            return pft.second;
        }
    }

    throw std::runtime_error("Invalid ProficiencyType");
    return "";

}

ProficiencyType stringToProficiencyType(const std::string& str){
    for(auto& pft : proficiencyTypeStrMap){
        if(pft.second == str){
            return pft.first;
        }
    }

    throw std::runtime_error("Invalid ProficiencyType string: " + str);
    return ProficiencyType::Weapons;
    
}

std::string jsonKeyToString(JsonKeys jk){
    for(auto& mp : jsonKeysStrMap){
        if(mp.first == jk){
            return mp.second;
        }
    }

    throw std::runtime_error("Invalid JsonKeys enum value");
    return "";
}

JsonKeys stringToJsonKeys(const std::string& str){
    for(auto& mp : jsonKeysStrMap){
        if(mp.second == str){
            return mp.first;
        }
    }

    throw std::runtime_error("Invalid JsonKeys string: " + str);
    return JsonKeys::name;

}