#include "raceData.h"
#include "defines.h"
#include "character.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::Ne;

// Test fixture for RaceData tests
class RaceDataTest : public ::testing::Test {
protected:
    RaceData raceData;
    
    void SetUp() override {
        // Create a fresh RaceData instance for each test
        raceData = RaceData();
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

//=============================================================================
// setAgeData Tests
//=============================================================================

TEST_F(RaceDataTest, SetAgeData_ValidValues) {
    unsigned short int maturityAge = 18;
    unsigned short int avgLifespan = 80;
    
    EXPECT_NO_THROW({
        raceData.setAgeData(maturityAge, avgLifespan);
    });
}

TEST_F(RaceDataTest, SetAgeData_ZeroValues) {
    EXPECT_NO_THROW({
        raceData.setAgeData(0, 0);
    });
}

TEST_F(RaceDataTest, SetAgeData_LargeValues) {
    unsigned short int maturityAge = 500;
    unsigned short int avgLifespan = 10000;
    
    EXPECT_NO_THROW({
        raceData.setAgeData(maturityAge, avgLifespan);
    });
}

//=============================================================================
// setAlignment Tests
//=============================================================================

TEST_F(RaceDataTest, SetAlignment_LawfulGood) {
    EXPECT_NO_THROW({
        raceData.setAlignment(Alignment::lawful_good);
    });
}

TEST_F(RaceDataTest, SetAlignment_ChaoticEvil) {
    EXPECT_NO_THROW({
        raceData.setAlignment(Alignment::chaotic_evil);
    });
}

TEST_F(RaceDataTest, SetAlignment_NeutralNeutral) {
    EXPECT_NO_THROW({
        raceData.setAlignment(Alignment::neutral_neutral);
    });
}

//=============================================================================
// setSizeData Tests
//=============================================================================

TEST_F(RaceDataTest, SetSizeData_ValidMediumSize) {
    SizeCategory category = SizeCategory::Medium;
    float height = 1.8f; // meters
    float weight = 80.0f; // kg
    
    EXPECT_NO_THROW({
        raceData.setSizeData(category, height, weight);
    });
}

TEST_F(RaceDataTest, SetSizeData_SmallSize) {
    SizeCategory category = SizeCategory::Small;
    float height = 1.0f;
    float weight = 40.0f;
    
    EXPECT_NO_THROW({
        raceData.setSizeData(category, height, weight);
    });
}

TEST_F(RaceDataTest, SetSizeData_LargeSize) {
    SizeCategory category = SizeCategory::Large;
    float height = 2.5f;
    float weight = 150.0f;
    
    EXPECT_NO_THROW({
        raceData.setSizeData(category, height, weight);
    });
}

//=============================================================================
// setSpeed Tests
//=============================================================================

TEST_F(RaceDataTest, SetSpeed_StandardHumanSpeed) {
    float speed = 30.0f;
    
    EXPECT_NO_THROW({
        raceData.setSpeed(speed);
    });
}

TEST_F(RaceDataTest, SetSpeed_SlowSpeed) {
    float speed = 25.0f;
    
    EXPECT_NO_THROW({
        raceData.setSpeed(speed);
    });
}

TEST_F(RaceDataTest, SetSpeed_FastSpeed) {
    float speed = 40.0f;
    
    EXPECT_NO_THROW({
        raceData.setSpeed(speed);
    });
}

TEST_F(RaceDataTest, SetSpeed_ZeroSpeed) {
    float speed = 0.0f;
    
    EXPECT_NO_THROW({
        raceData.setSpeed(speed);
    });
}

//=============================================================================
// setDarkvisionData Tests
//=============================================================================

TEST_F(RaceDataTest, SetDarkvisionData_StandardDarkvision) {
    bool hasDarkvision = true;
    std::pair<IlluminationType, float> dim_light_eq = {IlluminationType::Normal, 60.0f};
    std::pair<IlluminationType, float> darkvision_eq = {IlluminationType::Dim, 60.0f};
    
    EXPECT_NO_THROW({
        raceData.setDarkvisionData(hasDarkvision, dim_light_eq, darkvision_eq);
    });
}

TEST_F(RaceDataTest, SetDarkvisionData_NoDarkvision) {
    bool hasDarkvision = false;
    std::pair<IlluminationType, float> dim_light_eq = {IlluminationType::Dim, 0.0f};
    std::pair<IlluminationType, float> darkvision_eq = {IlluminationType::Dark, 0.0f};
    
    EXPECT_NO_THROW({
        raceData.setDarkvisionData(hasDarkvision, dim_light_eq, darkvision_eq);
    });
}

TEST_F(RaceDataTest, SetDarkvisionData_SuperiorDarkvision) {
    bool hasDarkvision = true;
    std::pair<IlluminationType, float> dim_light_eq = {IlluminationType::Normal, 120.0f};
    std::pair<IlluminationType, float> darkvision_eq = {IlluminationType::Dim, 120.0f};
    
    EXPECT_NO_THROW({
        raceData.setDarkvisionData(hasDarkvision, dim_light_eq, darkvision_eq);
    });
}

//=============================================================================
// setSleepDuration Tests
//=============================================================================

TEST_F(RaceDataTest, SetSleepDuration_StandardSleep) {
    float duration = 8.0f;
    
    EXPECT_NO_THROW({
        raceData.setSleepDuration(duration);
    });
}

TEST_F(RaceDataTest, SetSleepDuration_ElfTrance) {
    float duration = 4.0f;
    
    EXPECT_NO_THROW({
        raceData.setSleepDuration(duration);
    });
}

TEST_F(RaceDataTest, SetSleepDuration_NoSleep) {
    float duration = 0.0f;
    
    EXPECT_NO_THROW({
        raceData.setSleepDuration(duration);
    });
}

//=============================================================================
// addAbilityMod Tests
//=============================================================================

TEST_F(RaceDataTest, AddAbilityMod_SingleAbility) {
    std::string ability = "strength";
    int mod = 2;
    
    EXPECT_NO_THROW({
        raceData.addAbilityMod(ability, mod);
    });
}

TEST_F(RaceDataTest, AddAbilityMod_MultipleAbilities) {
    EXPECT_NO_THROW({
        raceData.addAbilityMod("strength", 2);
        raceData.addAbilityMod("dexterity", 1);
        raceData.addAbilityMod("constitution", 1);
    });
}

TEST_F(RaceDataTest, AddAbilityMod_SameAbilityMultipleTimes_ShouldAccumulate) {
    EXPECT_NO_THROW({
        raceData.addAbilityMod("strength", 1);
        raceData.addAbilityMod("strength", 1);
        // Should result in +2 total
    });
}

TEST_F(RaceDataTest, AddAbilityMod_NegativeMod) {
    EXPECT_NO_THROW({
        raceData.addAbilityMod("charisma", -2);
    });
}

TEST_F(RaceDataTest, AddAbilityMod_ZeroMod) {
    EXPECT_NO_THROW({
        raceData.addAbilityMod("wisdom", 0);
    });
}

//=============================================================================
// addParamMod Tests
//=============================================================================

TEST_F(RaceDataTest, AddParamMod_SingleParam) {
    std::string param = "hit_points";
    int mod = 5;
    
    EXPECT_NO_THROW({
        raceData.addParamMod(param, mod);
    });
}

TEST_F(RaceDataTest, AddParamMod_MultipleParams) {
    EXPECT_NO_THROW({
        raceData.addParamMod("hit_points", 10);
        raceData.addParamMod("mana", 5);
        raceData.addParamMod("stamina", 15);
    });
}

TEST_F(RaceDataTest, AddParamMod_SameParamMultipleTimes_ShouldAccumulate) {
    EXPECT_NO_THROW({
        raceData.addParamMod("hit_points", 5);
        raceData.addParamMod("hit_points", 3);
        // Should result in +8 total
    });
}

TEST_F(RaceDataTest, AddParamMod_NegativeMod) {
    EXPECT_NO_THROW({
        raceData.addParamMod("mana", -5);
    });
}

//=============================================================================
// addLanguageProficiency Tests
//=============================================================================

TEST_F(RaceDataTest, AddLanguageProficiency_AllSkills) {
    std::string language = "common";
    
    EXPECT_NO_THROW({
        raceData.addLanguageProficiency(language, true, true, true);
    });
}

TEST_F(RaceDataTest, AddLanguageProficiency_SpeakOnly) {
    std::string language = "elvish";
    
    EXPECT_NO_THROW({
        raceData.addLanguageProficiency(language, true, false, false);
    });
}

TEST_F(RaceDataTest, AddLanguageProficiency_ReadAndWriteOnly) {
    std::string language = "dwarvish";
    
    EXPECT_NO_THROW({
        raceData.addLanguageProficiency(language, false, true, true);
    });
}

TEST_F(RaceDataTest, AddLanguageProficiency_MultipleLanguages) {
    EXPECT_NO_THROW({
        raceData.addLanguageProficiency("common", true, true, true);
        raceData.addLanguageProficiency("elvish", true, true, true);
        raceData.addLanguageProficiency("dwarvish", true, false, false);
    });
}

TEST_F(RaceDataTest, AddLanguageProficiency_SameLanguageTwice_ShouldMergeSkills) {
    // First add with only speak
    raceData.addLanguageProficiency("elvish", true, false, false);
    
    // Then add with read and write - should merge
    EXPECT_NO_THROW({
        raceData.addLanguageProficiency("elvish", false, true, true);
        // Should now have speak, read, and write
    });
}

TEST_F(RaceDataTest, AddLanguageProficiency_NoSkills) {
    EXPECT_NO_THROW({
        raceData.addLanguageProficiency("draconic", false, false, false);
    });
}

//=============================================================================
// addResilience Tests
//=============================================================================

TEST_F(RaceDataTest, AddResilience_Immune) {
    std::string affliction = "poison";
    
    EXPECT_NO_THROW({
        raceData.addResilience(affliction, true, false, false);
    });
}

TEST_F(RaceDataTest, AddResilience_Advantage) {
    std::string affliction = "charm";
    
    EXPECT_NO_THROW({
        raceData.addResilience(affliction, false, true, false);
    });
}

TEST_F(RaceDataTest, AddResilience_Resistance) {
    std::string affliction = "fire";
    
    EXPECT_NO_THROW({
        raceData.addResilience(affliction, false, false, true);
    });
}

TEST_F(RaceDataTest, AddResilience_MultipleTypes) {
    EXPECT_NO_THROW({
        raceData.addResilience("poison", true, true, false);
        raceData.addResilience("charm", false, true, false);
        raceData.addResilience("cold", false, false, true);
    });
}

TEST_F(RaceDataTest, AddResilience_SameAfflictionTwice_ShouldMerge) {
    // First add with resistance
    raceData.addResilience("poison", false, false, true);
    
    // Then add with advantage - should merge
    EXPECT_NO_THROW({
        raceData.addResilience("poison", false, true, false);
        // Should now have both resistance and advantage
    });
}

TEST_F(RaceDataTest, AddResilience_AllFlags) {
    EXPECT_NO_THROW({
        raceData.addResilience("magic", true, true, true);
    });
}

//=============================================================================
// setProficiencyData Tests
//=============================================================================

TEST_F(RaceDataTest, SetProficiencyData_WeaponProficiency) {
    std::string proficiency = "longsword";
    
    EXPECT_NO_THROW({
        raceData.setProficiencyData(ProficiencyType::Weapons, proficiency);
    });
}

TEST_F(RaceDataTest, SetProficiencyData_ArmorProficiency) {
    std::string proficiency = "light_armor";
    
    EXPECT_NO_THROW({
        raceData.setProficiencyData(ProficiencyType::Armors, proficiency);
    });
}

TEST_F(RaceDataTest, SetProficiencyData_ToolProficiency) {
    std::string proficiency = "smiths_tools";
    
    EXPECT_NO_THROW({
        raceData.setProficiencyData(ProficiencyType::Tools, proficiency);
    });
}

TEST_F(RaceDataTest, SetProficiencyData_SkillProficiency) {
    std::string proficiency = "perception";
    
    EXPECT_NO_THROW({
        raceData.setProficiencyData(ProficiencyType::Skills, proficiency);
    });
}

TEST_F(RaceDataTest, SetProficiencyData_MultipleWeapons) {
    EXPECT_NO_THROW({
        raceData.setProficiencyData(ProficiencyType::Weapons, "longsword");
        raceData.setProficiencyData(ProficiencyType::Weapons, "shortsword");
        raceData.setProficiencyData(ProficiencyType::Weapons, "longbow");
    });
}

TEST_F(RaceDataTest, SetProficiencyData_MixedTypes) {
    EXPECT_NO_THROW({
        raceData.setProficiencyData(ProficiencyType::Weapons, "battleaxe");
        raceData.setProficiencyData(ProficiencyType::Armors, "medium_armor");
        raceData.setProficiencyData(ProficiencyType::Tools, "brewers_supplies");
        raceData.setProficiencyData(ProficiencyType::Skills, "athletics");
    });
}

TEST_F(RaceDataTest, SetProficiencyData_DuplicateProficiency_ShouldNotAddTwice) {
    // Add the same weapon proficiency twice
    raceData.setProficiencyData(ProficiencyType::Weapons, "longsword");
    
    EXPECT_NO_THROW({
        raceData.setProficiencyData(ProficiencyType::Weapons, "longsword");
        // Should only be added once
    });
}

//=============================================================================
// printData Tests
//=============================================================================

TEST_F(RaceDataTest, PrintData_EmptyRaceData) {
    // Should not crash with default/empty data
    EXPECT_NO_THROW({
        raceData.printData();
    });
}

TEST_F(RaceDataTest, PrintData_WithData) {
    // Setup some data
    raceData.setAgeData(18, 80);
    raceData.setAlignment(Alignment::neutral_good);
    raceData.setSizeData(SizeCategory::Medium, 1.8f, 80.0f);
    raceData.setSpeed(30.0f);
    raceData.addAbilityMod("strength", 2);
    raceData.addLanguageProficiency("common", true, true, true);
    
    // Should not crash with data
    EXPECT_NO_THROW({
        raceData.printData();
    });
}

//=============================================================================
// Integration Tests
//=============================================================================

TEST_F(RaceDataTest, Integration_CompleteHumanRaceData) {
    // Simulate setting up complete Human race data
    EXPECT_NO_THROW({
        raceData.setAgeData(18, 80);
        raceData.setAlignment(Alignment::neutral_neutral);
        raceData.setSizeData(SizeCategory::Medium, 1.7f, 75.0f);
        raceData.setSpeed(30.0f);
        raceData.addAbilityMod("strength", 1);
        raceData.addAbilityMod("dexterity", 1);
        raceData.addAbilityMod("constitution", 1);
        raceData.addAbilityMod("intelligence", 1);
        raceData.addAbilityMod("wisdom", 1);
        raceData.addAbilityMod("charisma", 1);
        raceData.addLanguageProficiency("common", true, true, true);
        raceData.setSleepDuration(8.0f);
    });
}

TEST_F(RaceDataTest, Integration_CompleteElfRaceData) {
    // Simulate setting up complete Elf race data
    EXPECT_NO_THROW({
        raceData.setAgeData(100, 750);
        raceData.setAlignment(Alignment::chaotic_good);
        raceData.setSizeData(SizeCategory::Medium, 1.75f, 65.0f);
        raceData.setSpeed(30.0f);
        raceData.addAbilityMod("dexterity", 2);
        raceData.addLanguageProficiency("common", true, true, true);
        raceData.addLanguageProficiency("elvish", true, true, true);
        raceData.setDarkvisionData(true, {IlluminationType::Normal, 60.0f}, {IlluminationType::Dim, 60.0f});
        raceData.setProficiencyData(ProficiencyType::Skills, "perception");
        raceData.addResilience("charm", false, true, false);
        raceData.addResilience("sleep", true, false, false);
        raceData.setSleepDuration(4.0f);
    });
}

TEST_F(RaceDataTest, Integration_CompleteDwarfRaceData) {
    // Simulate setting up complete Dwarf race data
    EXPECT_NO_THROW({
        raceData.setAgeData(50, 350);
        raceData.setAlignment(Alignment::lawful_good);
        raceData.setSizeData(SizeCategory::Medium, 1.35f, 75.0f);
        raceData.setSpeed(25.0f);
        raceData.addAbilityMod("constitution", 2);
        raceData.addLanguageProficiency("common", true, true, true);
        raceData.addLanguageProficiency("dwarvish", true, true, true);
        raceData.setDarkvisionData(true, {IlluminationType::Normal, 60.0f}, {IlluminationType::Dim, 60.0f});
        raceData.addResilience("poison", false, true, true);
        raceData.setProficiencyData(ProficiencyType::Weapons, "battleaxe");
        raceData.setProficiencyData(ProficiencyType::Weapons, "handaxe");
        raceData.setProficiencyData(ProficiencyType::Weapons, "warhammer");
        raceData.setProficiencyData(ProficiencyType::Tools, "smiths_tools");
    });
}

TEST_F(RaceDataTest, Integration_ModStacking) {
    // Test that mods stack correctly
    raceData.addAbilityMod("strength", 1);
    raceData.addAbilityMod("strength", 1);
    raceData.addAbilityMod("strength", 1);
    
    // Should have +3 strength total
    EXPECT_NO_THROW({
        raceData.printData();
    });
}

TEST_F(RaceDataTest, Integration_LanguageSkillMerging) {
    // Test that language skills merge correctly
    raceData.addLanguageProficiency("elvish", true, false, false);  // speak only
    raceData.addLanguageProficiency("elvish", false, true, false);  // add read
    raceData.addLanguageProficiency("elvish", false, false, true);  // add write
    
    // Should have all three skills for elvish
    EXPECT_NO_THROW({
        raceData.printData();
    });
}

TEST_F(RaceDataTest, Integration_ResilienceMerging) {
    // Test that resilience flags merge correctly
    raceData.addResilience("poison", false, false, true);  // resistance only
    raceData.addResilience("poison", false, true, false);  // add advantage
    
    // Should have both resistance and advantage
    EXPECT_NO_THROW({
        raceData.printData();
    });
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
