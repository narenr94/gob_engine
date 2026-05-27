#include "defines.h"
#include "utilities.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::Ne;

// Test fixture for Defines tests
class DefinesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

//=============================================================================
// Experience Points Lookup Table Tests
//=============================================================================

TEST_F(DefinesTest, ExpPointsLookupTable_Level1_IsZero) {
    auto it = std::find_if(g_expPointsLookupTable.begin(), 
                           g_expPointsLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl1; });
    ASSERT_NE(it, g_expPointsLookupTable.end());
    EXPECT_EQ(it->second, 0);
}

TEST_F(DefinesTest, ExpPointsLookupTable_Level20_IsMaximum) {
    auto it = std::find_if(g_expPointsLookupTable.begin(), 
                           g_expPointsLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl20; });
    ASSERT_NE(it, g_expPointsLookupTable.end());
    EXPECT_EQ(it->second, 355000);
}

TEST_F(DefinesTest, ExpPointsLookupTable_ContainsAllLevels) {
    EXPECT_EQ(g_expPointsLookupTable.size(), 20);
}

TEST_F(DefinesTest, ExpPointsLookupTable_IsMonotonicallyIncreasing) {
    for (size_t i = 1; i < g_expPointsLookupTable.size(); ++i) {
        EXPECT_GT(g_expPointsLookupTable[i].second, 
                  g_expPointsLookupTable[i-1].second)
            << "XP at level " << i+1 << " should be greater than level " << i;
    }
}

TEST_F(DefinesTest, ExpPointsLookupTable_Level5HasCorrectXP) {
    auto it = std::find_if(g_expPointsLookupTable.begin(), 
                           g_expPointsLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl5; });
    ASSERT_NE(it, g_expPointsLookupTable.end());
    EXPECT_EQ(it->second, 6500);
}

TEST_F(DefinesTest, ExpPointsLookupTable_Level10HasCorrectXP) {
    auto it = std::find_if(g_expPointsLookupTable.begin(), 
                           g_expPointsLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl10; });
    ASSERT_NE(it, g_expPointsLookupTable.end());
    EXPECT_EQ(it->second, 64000);
}

//=============================================================================
// Proficiency Bonus Lookup Table Tests
//=============================================================================

TEST_F(DefinesTest, ProficiencyBonusLookupTable_Level1_IsTwo) {
    auto it = std::find_if(g_proficiencyBonusLookupTable.begin(), 
                           g_proficiencyBonusLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl1; });
    ASSERT_NE(it, g_proficiencyBonusLookupTable.end());
    EXPECT_EQ(it->second, 2);
}

TEST_F(DefinesTest, ProficiencyBonusLookupTable_Level20_IsSix) {
    auto it = std::find_if(g_proficiencyBonusLookupTable.begin(), 
                           g_proficiencyBonusLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl20; });
    ASSERT_NE(it, g_proficiencyBonusLookupTable.end());
    EXPECT_EQ(it->second, 6);
}

TEST_F(DefinesTest, ProficiencyBonusLookupTable_ContainsAllLevels) {
    EXPECT_EQ(g_proficiencyBonusLookupTable.size(), 20);
}

TEST_F(DefinesTest, ProficiencyBonusLookupTable_IsMonotonicallyIncreasing) {
    for (size_t i = 1; i < g_proficiencyBonusLookupTable.size(); ++i) {
        EXPECT_GE(g_proficiencyBonusLookupTable[i].second, 
                  g_proficiencyBonusLookupTable[i-1].second)
            << "Proficiency bonus at level " << i+1 << " should be >= level " << i;
    }
}

TEST_F(DefinesTest, ProficiencyBonusLookupTable_Level5HasBonusThree) {
    auto it = std::find_if(g_proficiencyBonusLookupTable.begin(), 
                           g_proficiencyBonusLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl5; });
    ASSERT_NE(it, g_proficiencyBonusLookupTable.end());
    EXPECT_EQ(it->second, 3);
}

TEST_F(DefinesTest, ProficiencyBonusLookupTable_Level9HasBonusFour) {
    auto it = std::find_if(g_proficiencyBonusLookupTable.begin(), 
                           g_proficiencyBonusLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl9; });
    ASSERT_NE(it, g_proficiencyBonusLookupTable.end());
    EXPECT_EQ(it->second, 4);
}

TEST_F(DefinesTest, ProficiencyBonusLookupTable_Level17HasBonusSix) {
    auto it = std::find_if(g_proficiencyBonusLookupTable.begin(), 
                           g_proficiencyBonusLookupTable.end(),
                           [](const auto& pair) { return pair.first == Level::Lvl17; });
    ASSERT_NE(it, g_proficiencyBonusLookupTable.end());
    EXPECT_EQ(it->second, 6);
}

//=============================================================================
// Alignment String Mapping Tests
//=============================================================================

TEST_F(DefinesTest, AlignmentStringConversion_LawfulGood) {
    std::string result = alignmentToString(Alignment::lawful_good);
    EXPECT_EQ(result, "lawful_good");
    
    Alignment alignment = stringToAlignment("lawful_good");
    EXPECT_EQ(alignment, Alignment::lawful_good);
}

TEST_F(DefinesTest, AlignmentStringConversion_NeutralNeutral) {
    std::string result = alignmentToString(Alignment::neutral_neutral);
    EXPECT_EQ(result, "neutral_neutral");
    
    Alignment alignment = stringToAlignment("neutral_neutral");
    EXPECT_EQ(alignment, Alignment::neutral_neutral);
}

TEST_F(DefinesTest, AlignmentStringConversion_ChaoticEvil) {
    std::string result = alignmentToString(Alignment::chaotic_evil);
    EXPECT_EQ(result, "chaotic_evil");
    
    Alignment alignment = stringToAlignment("chaotic_evil");
    EXPECT_EQ(alignment, Alignment::chaotic_evil);
}

TEST_F(DefinesTest, AlignmentStrMap_ContainsAllAlignments) {
    EXPECT_EQ(alignmentStrMap.size(), 9);
}

TEST_F(DefinesTest, AlignmentStrMap_AllStringsAreUnique) {
    std::set<std::string> uniqueStrings;
    for (const auto& pair : alignmentStrMap) {
        uniqueStrings.insert(pair.second);
    }
    EXPECT_EQ(uniqueStrings.size(), alignmentStrMap.size());
}

//=============================================================================
// Size Category String Mapping Tests
//=============================================================================

TEST_F(DefinesTest, SizeCategoryStringConversion_Medium) {
    std::string result = sizeCategoryToString(SizeCategory::Medium);
    EXPECT_EQ(result, "medium");
    
    SizeCategory size = stringToSizeCategory("medium");
    EXPECT_EQ(size, SizeCategory::Medium);
}

TEST_F(DefinesTest, SizeCategoryStringConversion_Small) {
    std::string result = sizeCategoryToString(SizeCategory::Small);
    EXPECT_EQ(result, "small");
    
    SizeCategory size = stringToSizeCategory("small");
    EXPECT_EQ(size, SizeCategory::Small);
}

TEST_F(DefinesTest, SizeCategoryStringConversion_Huge) {
    std::string result = sizeCategoryToString(SizeCategory::Huge);
    EXPECT_EQ(result, "huge");
    
    SizeCategory size = stringToSizeCategory("huge");
    EXPECT_EQ(size, SizeCategory::Huge);
}

TEST_F(DefinesTest, SizeCategoryStringConversion_Gargantuan) {
    std::string result = sizeCategoryToString(SizeCategory::Garg);
    EXPECT_EQ(result, "gargantuan");
    
    SizeCategory size = stringToSizeCategory("gargantuan");
    EXPECT_EQ(size, SizeCategory::Garg);
}

//=============================================================================
// Illumination Type String Mapping Tests
//=============================================================================

TEST_F(DefinesTest, IlluminationTypeStringConversion_Normal) {
    std::string result = illuminationTypeToString(IlluminationType::Normal);
    EXPECT_EQ(result, "normal");
    
    IlluminationType illum = stringToIlluminationType("normal");
    EXPECT_EQ(illum, IlluminationType::Normal);
}

TEST_F(DefinesTest, IlluminationTypeStringConversion_Dim) {
    std::string result = illuminationTypeToString(IlluminationType::Dim);
    EXPECT_EQ(result, "dim");
    
    IlluminationType illum = stringToIlluminationType("dim");
    EXPECT_EQ(illum, IlluminationType::Dim);
}

TEST_F(DefinesTest, IlluminationTypeStringConversion_Dark) {
    std::string result = illuminationTypeToString(IlluminationType::Dark);
    EXPECT_EQ(result, "dark");
    
    IlluminationType illum = stringToIlluminationType("dark");
    EXPECT_EQ(illum, IlluminationType::Dark);
}

TEST_F(DefinesTest, IlluminationTypeStrMap_ContainsAllTypes) {
    EXPECT_EQ(illumincationTypeStrMap.size(), 3);
}

//=============================================================================
// Proficiency Type String Mapping Tests
//=============================================================================

TEST_F(DefinesTest, ProficiencyTypeStringConversion_Weapons) {
    std::string result = proficiencyTypeToString(ProficiencyType::Weapons);
    EXPECT_EQ(result, "weapons");
    
    ProficiencyType prof = stringToProficiencyType("weapons");
    EXPECT_EQ(prof, ProficiencyType::Weapons);
}

TEST_F(DefinesTest, ProficiencyTypeStringConversion_Armors) {
    std::string result = proficiencyTypeToString(ProficiencyType::Armors);
    EXPECT_EQ(result, "armors");
    
    ProficiencyType prof = stringToProficiencyType("armors");
    EXPECT_EQ(prof, ProficiencyType::Armors);
}

TEST_F(DefinesTest, ProficiencyTypeStringConversion_Tools) {
    std::string result = proficiencyTypeToString(ProficiencyType::Tools);
    EXPECT_EQ(result, "tools");
    
    ProficiencyType prof = stringToProficiencyType("tools");
    EXPECT_EQ(prof, ProficiencyType::Tools);
}

TEST_F(DefinesTest, ProficiencyTypeStringConversion_Skills) {
    std::string result = proficiencyTypeToString(ProficiencyType::Skills);
    EXPECT_EQ(result, "skills");
    
    ProficiencyType prof = stringToProficiencyType("skills");
    EXPECT_EQ(prof, ProficiencyType::Skills);
}

TEST_F(DefinesTest, ProficiencyTypeStringConversion_SavingThrows) {
    std::string result = proficiencyTypeToString(ProficiencyType::SavingThrows);
    EXPECT_EQ(result, "saving_throws");
    
    ProficiencyType prof = stringToProficiencyType("saving_throws");
    EXPECT_EQ(prof, ProficiencyType::SavingThrows);
}

TEST_F(DefinesTest, ProficiencyTypeStrMap_ContainsAllTypes) {
    EXPECT_EQ(proficiencyTypeStrMap.size(), 5);
}

//=============================================================================
// JsonKeys String Mapping Tests
//=============================================================================

TEST_F(DefinesTest, JsonKeyStringConversion_Name) {
    std::string result = jsonKeyToString(JsonKeys::name);
    EXPECT_EQ(result, "name");
    
    JsonKeys key = stringToJsonKeys("name");
    EXPECT_EQ(key, JsonKeys::name);
}

TEST_F(DefinesTest, JsonKeyStringConversion_IsAbstract) {
    std::string result = jsonKeyToString(JsonKeys::is_abstract);
    EXPECT_EQ(result, "is_abstract");
    
    JsonKeys key = stringToJsonKeys("is_abstract");
    EXPECT_EQ(key, JsonKeys::is_abstract);
}

TEST_F(DefinesTest, JsonKeyStringConversion_AbilityMods) {
    std::string result = jsonKeyToString(JsonKeys::ability_mods);
    EXPECT_EQ(result, "ability_mods");
    
    JsonKeys key = stringToJsonKeys("ability_mods");
    EXPECT_EQ(key, JsonKeys::ability_mods);
}

TEST_F(DefinesTest, JsonKeyStringConversion_Languages) {
    std::string result = jsonKeyToString(JsonKeys::languages);
    EXPECT_EQ(result, "languages");
    
    JsonKeys key = stringToJsonKeys("languages");
    EXPECT_EQ(key, JsonKeys::languages);
}

TEST_F(DefinesTest, JsonKeysStrMap_ContainsExpectedSize) {
    // The jsonKeysStrMap should contain all JsonKeys enum values
    EXPECT_GE(jsonKeysStrMap.size(), 40);
}

//=============================================================================
// Struct Initialization Tests - AgeData
//=============================================================================

TEST_F(DefinesTest, AgeData_CanBeInitialized) {
    AgeData ageData;
    ageData.maturityAge = 18;
    ageData.avgLifespan = 100;
    
    EXPECT_EQ(ageData.maturityAge, 18);
    EXPECT_EQ(ageData.avgLifespan, 100);
}

TEST_F(DefinesTest, AgeData_PrintDataDoesNotCrash) {
    AgeData ageData;
    ageData.maturityAge = 18;
    ageData.avgLifespan = 100;
    
    EXPECT_NO_THROW(ageData.printData());
}

//=============================================================================
// Struct Initialization Tests - SizeData
//=============================================================================

TEST_F(DefinesTest, SizeData_CanBeInitialized) {
    SizeData sizeData;
    sizeData.category = SizeCategory::Medium;
    sizeData.dimensions = std::make_pair(1.75f, 70.0f);
    
    EXPECT_EQ(sizeData.category, SizeCategory::Medium);
    EXPECT_FLOAT_EQ(sizeData.dimensions.first, 1.75f);
    EXPECT_FLOAT_EQ(sizeData.dimensions.second, 70.0f);
}

TEST_F(DefinesTest, SizeData_PrintDataDoesNotCrash) {
    SizeData sizeData;
    sizeData.category = SizeCategory::Small;
    sizeData.dimensions = std::make_pair(1.0f, 40.0f);
    
    EXPECT_NO_THROW(sizeData.printData());
}

//=============================================================================
// Struct Initialization Tests - LanguageData
//=============================================================================

TEST_F(DefinesTest, LanguageData_CanBeInitialized) {
    LanguageData langData;
    langData.language = "elvish";
    langData.speak = true;
    langData.read = true;
    langData.write = false;
    
    EXPECT_EQ(langData.language, "elvish");
    EXPECT_TRUE(langData.speak);
    EXPECT_TRUE(langData.read);
    EXPECT_FALSE(langData.write);
}

TEST_F(DefinesTest, LanguageData_DefaultValues) {
    LanguageData langData;
    langData.language = "common";
    
    EXPECT_FALSE(langData.speak);
    EXPECT_FALSE(langData.read);
    EXPECT_FALSE(langData.write);
}

TEST_F(DefinesTest, LanguageData_PrintDataDoesNotCrash) {
    LanguageData langData;
    langData.language = "dwarvish";
    langData.speak = true;
    langData.read = true;
    langData.write = true;
    
    EXPECT_NO_THROW(langData.printData());
}

//=============================================================================
// Struct Initialization Tests - ProficiencyData
//=============================================================================

TEST_F(DefinesTest, ProficiencyData_CanBeInitialized) {
    ProficiencyData profData;
    profData.weaponProficiencies = {"longsword", "shortbow"};
    profData.armorProficiencies = {"light_armor", "medium_armor"};
    profData.toolProficiencies = {"thieves_tools"};
    profData.skillProficiencies = {"stealth", "perception"};
    profData.savingThrowsProficiencies = {"wisdom", "dexterity"};
    
    EXPECT_EQ(profData.weaponProficiencies.size(), 2);
    EXPECT_EQ(profData.armorProficiencies.size(), 2);
    EXPECT_EQ(profData.toolProficiencies.size(), 1);
    EXPECT_EQ(profData.skillProficiencies.size(), 2);
    EXPECT_EQ(profData.savingThrowsProficiencies.size(), 2);
}

TEST_F(DefinesTest, ProficiencyData_PrintDataDoesNotCrash) {
    ProficiencyData profData;
    profData.weaponProficiencies = {"dagger"};
    
    EXPECT_NO_THROW(profData.printData());
}

//=============================================================================
// Struct Initialization Tests - ResilienceData
//=============================================================================

TEST_F(DefinesTest, ResilienceData_CanBeInitialized) {
    ResilienceData resilData;
    resilData.affliction = "poison";
    resilData.immune = true;
    resilData.hasAdvantage = false;
    resilData.hasResistance = false;
    
    EXPECT_EQ(resilData.affliction, "poison");
    EXPECT_TRUE(resilData.immune);
    EXPECT_FALSE(resilData.hasAdvantage);
    EXPECT_FALSE(resilData.hasResistance);
}

TEST_F(DefinesTest, ResilienceData_DefaultValues) {
    ResilienceData resilData;
    resilData.affliction = "fire";
    
    EXPECT_FALSE(resilData.immune);
    EXPECT_FALSE(resilData.hasAdvantage);
    EXPECT_FALSE(resilData.hasResistance);
}

TEST_F(DefinesTest, ResilienceData_PrintDataDoesNotCrash) {
    ResilienceData resilData;
    resilData.affliction = "charm";
    resilData.hasAdvantage = true;
    
    EXPECT_NO_THROW(resilData.printData());
}

//=============================================================================
// Struct Initialization Tests - DarkvisionData
//=============================================================================

TEST_F(DefinesTest, DarkvisionData_CanBeInitialized) {
    DarkvisionData darkData;
    darkData.hasDarkvision = true;
    darkData.dim_light_eq = IlluminationType::Normal;
    darkData.dim_light_eq_dist = 18.0f;
    darkData.darkvision_eq = IlluminationType::Dim;
    darkData.darkvision_eq_dist = 18.0f;
    
    EXPECT_TRUE(darkData.hasDarkvision);
    EXPECT_EQ(darkData.dim_light_eq, IlluminationType::Normal);
    EXPECT_FLOAT_EQ(darkData.dim_light_eq_dist, 18.0f);
    EXPECT_EQ(darkData.darkvision_eq, IlluminationType::Dim);
    EXPECT_FLOAT_EQ(darkData.darkvision_eq_dist, 18.0f);
}

TEST_F(DefinesTest, DarkvisionData_DefaultValues) {
    DarkvisionData darkData;
    
    EXPECT_FALSE(darkData.hasDarkvision);
    EXPECT_EQ(darkData.dim_light_eq, IlluminationType::Dim);
    EXPECT_FLOAT_EQ(darkData.dim_light_eq_dist, 0.0f);
    EXPECT_EQ(darkData.darkvision_eq, IlluminationType::Dark);
    EXPECT_FLOAT_EQ(darkData.darkvision_eq_dist, 0.0f);
}

TEST_F(DefinesTest, DarkvisionData_PrintDataDoesNotCrash) {
    DarkvisionData darkData;
    darkData.hasDarkvision = true;
    
    EXPECT_NO_THROW(darkData.printData());
}

//=============================================================================
// Struct Initialization Tests - AbilityModData
//=============================================================================

TEST_F(DefinesTest, AbilityModData_CanBeInitialized) {
    AbilityModData abilityData;
    abilityData.abilityMod = std::make_pair("strength", 2);
    
    EXPECT_EQ(abilityData.abilityMod.first, "strength");
    EXPECT_EQ(abilityData.abilityMod.second, 2);
}

TEST_F(DefinesTest, AbilityModData_PrintDataDoesNotCrash) {
    AbilityModData abilityData;
    abilityData.abilityMod = std::make_pair("dexterity", 1);
    
    EXPECT_NO_THROW(abilityData.printData());
}

//=============================================================================
// Struct Initialization Tests - ParamModData
//=============================================================================

TEST_F(DefinesTest, ParamModData_CanBeInitialized) {
    ParamModData paramData;
    paramData.paramMod = std::make_pair("hit_points", 10);
    
    EXPECT_EQ(paramData.paramMod.first, "hit_points");
    EXPECT_EQ(paramData.paramMod.second, 10);
}

TEST_F(DefinesTest, ParamModData_PrintDataDoesNotCrash) {
    ParamModData paramData;
    paramData.paramMod = std::make_pair("mana", 5);
    
    EXPECT_NO_THROW(paramData.printData());
}

//=============================================================================
// Constants Tests
//=============================================================================

TEST_F(DefinesTest, Constants_AbilityScoreMax) {
    EXPECT_EQ(ABILITY_SCORE_MAX, 20);
}

TEST_F(DefinesTest, Constants_DefaultParamDie) {
    EXPECT_EQ(DEFAULT_PARAM_DIE, 8);
}

//=============================================================================
// Main function
//=============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
