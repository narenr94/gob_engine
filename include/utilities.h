#pragma once

#include "defines.h"

#include <memory>

short int calculateAbilityModifier(const unsigned short int t_abilityScore);

Level incrementLevel(Level t_currLevel);

std::string alignmentToString(Alignment alignment);

std::string sizeCategoryToString(SizeCategory sz);

std::string illuminationTypeToString(IlluminationType it);

Alignment stringToAlignment(const std::string& alignmentStr);

SizeCategory stringToSizeCategory(const std::string& sizeCategoryStr);

IlluminationType stringToIlluminationType(const std::string& illuminationTypeStr);

std::string proficiencyTypeToString(ProficiencyType pt);

ProficiencyType stringToProficiencyType(const std::string& str);

std::string jsonKeyToString(JsonKeys jk);

JsonKeys stringToJsonKeys(const std::string& str);

std::string conditionsToString(conditionsType ct);

conditionsType stringToConditionstype(std::string& str);
