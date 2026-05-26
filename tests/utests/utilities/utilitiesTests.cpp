#include "utilities.h"
#include "defines.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::Ne;

// Test fixture for Utilities tests
class UtilitiesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

//=============================================================================
// Calculate Ability Modifier Tests
//=============================================================================

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score10_ReturnsZero) {
    EXPECT_EQ(calculateAbilityModifier(10), 0);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score11_ReturnsZero) {
    EXPECT_EQ(calculateAbilityModifier(11), 0);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score12_ReturnsOne) {
    EXPECT_EQ(calculateAbilityModifier(12), 1);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score13_ReturnsOne) {
    EXPECT_EQ(calculateAbilityModifier(13), 1);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score20_ReturnsFive) {
    EXPECT_EQ(calculateAbilityModifier(20), 5);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score8_ReturnsNegativeOne) {
    EXPECT_EQ(calculateAbilityModifier(8), -1);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score9_ReturnsNegativeOne) {
    EXPECT_EQ(calculateAbilityModifier(9), -1);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score1_ReturnsNegativeFive) {
    EXPECT_EQ(calculateAbilityModifier(1), -5);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score3_ReturnsNegativeFour) {
    EXPECT_EQ(calculateAbilityModifier(3), -4);
}

TEST_F(UtilitiesTest, CalculateAbilityModifier_Score18_ReturnsFour) {
    EXPECT_EQ(calculateAbilityModifier(18), 4);
}

//=============================================================================
// Increment Level Tests
//=============================================================================

TEST_F(UtilitiesTest, IncrementLevel_Lvl1_ReturnsLvl2) {
    EXPECT_EQ(incrementLevel(Level::Lvl1), Level::Lvl2);
}

TEST_F(UtilitiesTest, IncrementLevel_Lvl5_ReturnsLvl6) {
    EXPECT_EQ(incrementLevel(Level::Lvl5), Level::Lvl6);
}

TEST_F(UtilitiesTest, IncrementLevel_Lvl10_ReturnsLvl11) {
    EXPECT_EQ(incrementLevel(Level::Lvl10), Level::Lvl11);
}

TEST_F(UtilitiesTest, IncrementLevel_Lvl19_ReturnsLvl20) {
    EXPECT_EQ(incrementLevel(Level::Lvl19), Level::Lvl20);
}

TEST_F(UtilitiesTest, IncrementLevel_Lvl20_ReturnsLvl20) {
    EXPECT_EQ(incrementLevel(Level::Lvl20), Level::Lvl20);
}

TEST_F(UtilitiesTest, IncrementLevel_AllLevelsExceptMax) {
    EXPECT_EQ(incrementLevel(Level::Lvl2), Level::Lvl3);
    EXPECT_EQ(incrementLevel(Level::Lvl3), Level::Lvl4);
    EXPECT_EQ(incrementLevel(Level::Lvl4), Level::Lvl5);
    EXPECT_EQ(incrementLevel(Level::Lvl6), Level::Lvl7);
    EXPECT_EQ(incrementLevel(Level::Lvl7), Level::Lvl8);
    EXPECT_EQ(incrementLevel(Level::Lvl8), Level::Lvl9);
    EXPECT_EQ(incrementLevel(Level::Lvl9), Level::Lvl10);
    EXPECT_EQ(incrementLevel(Level::Lvl11), Level::Lvl12);
    EXPECT_EQ(incrementLevel(Level::Lvl12), Level::Lvl13);
    EXPECT_EQ(incrementLevel(Level::Lvl13), Level::Lvl14);
    EXPECT_EQ(incrementLevel(Level::Lvl14), Level::Lvl15);
    EXPECT_EQ(incrementLevel(Level::Lvl15), Level::Lvl16);
    EXPECT_EQ(incrementLevel(Level::Lvl16), Level::Lvl17);
    EXPECT_EQ(incrementLevel(Level::Lvl17), Level::Lvl18);
    EXPECT_EQ(incrementLevel(Level::Lvl18), Level::Lvl19);
}

//=============================================================================
// Alignment Conversion Tests
//=============================================================================

TEST_F(UtilitiesTest, AlignmentToString_LawfulGood) {
    EXPECT_EQ(alignmentToString(Alignment::lawful_good), "lawful_good");
}

TEST_F(UtilitiesTest, AlignmentToString_ChaoticEvil) {
    EXPECT_EQ(alignmentToString(Alignment::chaotic_evil), "chaotic_evil");
}

TEST_F(UtilitiesTest, AlignmentToString_NeutralNeutral) {
    EXPECT_EQ(alignmentToString(Alignment::neutral_neutral), "neutral_neutral");
}

TEST_F(UtilitiesTest, AlignmentToString_AllAlignments) {
    EXPECT_EQ(alignmentToString(Alignment::lawful_neutral), "lawful_neutral");
    EXPECT_EQ(alignmentToString(Alignment::lawful_evil), "lawful_evil");
    EXPECT_EQ(alignmentToString(Alignment::neutral_good), "neutral_good");
    EXPECT_EQ(alignmentToString(Alignment::neutral_evil), "neutral_evil");
    EXPECT_EQ(alignmentToString(Alignment::chaotic_good), "chaotic_good");
    EXPECT_EQ(alignmentToString(Alignment::chaotic_neutral), "chaotic_neutral");
}

TEST_F(UtilitiesTest, StringToAlignment_LawfulGood) {
    EXPECT_EQ(stringToAlignment("lawful_good"), Alignment::lawful_good);
}

TEST_F(UtilitiesTest, StringToAlignment_ChaoticEvil) {
    EXPECT_EQ(stringToAlignment("chaotic_evil"), Alignment::chaotic_evil);
}

TEST_F(UtilitiesTest, StringToAlignment_NeutralNeutral) {
    EXPECT_EQ(stringToAlignment("neutral_neutral"), Alignment::neutral_neutral);
}

TEST_F(UtilitiesTest, StringToAlignment_InvalidString_ThrowsException) {
    EXPECT_THROW(stringToAlignment("invalid_alignment"), std::runtime_error);
}

TEST_F(UtilitiesTest, StringToAlignment_RoundTrip) {
    // Test that converting to string and back works for all alignments
    EXPECT_EQ(stringToAlignment(alignmentToString(Alignment::lawful_good)), Alignment::lawful_good);
    EXPECT_EQ(stringToAlignment(alignmentToString(Alignment::chaotic_evil)), Alignment::chaotic_evil);
    EXPECT_EQ(stringToAlignment(alignmentToString(Alignment::neutral_neutral)), Alignment::neutral_neutral);
}

//=============================================================================
// Size Category Conversion Tests
//=============================================================================

TEST_F(UtilitiesTest, SizeCategoryToString_Tiny) {
    EXPECT_EQ(sizeCategoryToString(SizeCategory::Tiny), "tiny");
}

TEST_F(UtilitiesTest, SizeCategoryToString_Medium) {
    EXPECT_EQ(sizeCategoryToString(SizeCategory::Medium), "medium");
}

TEST_F(UtilitiesTest, SizeCategoryToString_Large) {
    EXPECT_EQ(sizeCategoryToString(SizeCategory::Large), "large");
}

TEST_F(UtilitiesTest, SizeCategoryToString_Gargantuan) {
    EXPECT_EQ(sizeCategoryToString(SizeCategory::Garg), "gargantuan");
}

TEST_F(UtilitiesTest, SizeCategoryToString_AllCategories) {
    EXPECT_EQ(sizeCategoryToString(SizeCategory::Small), "small");
    EXPECT_EQ(sizeCategoryToString(SizeCategory::Huge), "huge");
}

TEST_F(UtilitiesTest, StringToSizeCategory_Tiny) {
    EXPECT_EQ(stringToSizeCategory("tiny"), SizeCategory::Tiny);
}

TEST_F(UtilitiesTest, StringToSizeCategory_Medium) {
    EXPECT_EQ(stringToSizeCategory("medium"), SizeCategory::Medium);
}

TEST_F(UtilitiesTest, StringToSizeCategory_Gargantuan) {
    EXPECT_EQ(stringToSizeCategory("gargantuan"), SizeCategory::Garg);
}

TEST_F(UtilitiesTest, StringToSizeCategory_InvalidString_ThrowsException) {
    EXPECT_THROW(stringToSizeCategory("gigantic"), std::runtime_error);
}

TEST_F(UtilitiesTest, StringToSizeCategory_RoundTrip) {
    EXPECT_EQ(stringToSizeCategory(sizeCategoryToString(SizeCategory::Medium)), SizeCategory::Medium);
    EXPECT_EQ(stringToSizeCategory(sizeCategoryToString(SizeCategory::Large)), SizeCategory::Large);
}

//=============================================================================
// Illumination Type Conversion Tests
//=============================================================================

TEST_F(UtilitiesTest, IlluminationTypeToString_Normal) {
    EXPECT_EQ(illuminationTypeToString(IlluminationType::Normal), "normal");
}

TEST_F(UtilitiesTest, IlluminationTypeToString_Dim) {
    EXPECT_EQ(illuminationTypeToString(IlluminationType::Dim), "dim");
}

TEST_F(UtilitiesTest, IlluminationTypeToString_Dark) {
    EXPECT_EQ(illuminationTypeToString(IlluminationType::Dark), "dark");
}

TEST_F(UtilitiesTest, StringToIlluminationType_Normal) {
    EXPECT_EQ(stringToIlluminationType("normal"), IlluminationType::Normal);
}

TEST_F(UtilitiesTest, StringToIlluminationType_Dim) {
    EXPECT_EQ(stringToIlluminationType("dim"), IlluminationType::Dim);
}

TEST_F(UtilitiesTest, StringToIlluminationType_Dark) {
    EXPECT_EQ(stringToIlluminationType("dark"), IlluminationType::Dark);
}

TEST_F(UtilitiesTest, StringToIlluminationType_InvalidString_ThrowsException) {
    EXPECT_THROW(stringToIlluminationType("bright"), std::runtime_error);
}

TEST_F(UtilitiesTest, StringToIlluminationType_RoundTrip) {
    EXPECT_EQ(stringToIlluminationType(illuminationTypeToString(IlluminationType::Normal)), IlluminationType::Normal);
    EXPECT_EQ(stringToIlluminationType(illuminationTypeToString(IlluminationType::Dim)), IlluminationType::Dim);
    EXPECT_EQ(stringToIlluminationType(illuminationTypeToString(IlluminationType::Dark)), IlluminationType::Dark);
}

//=============================================================================
// Proficiency Type Conversion Tests
//=============================================================================

TEST_F(UtilitiesTest, ProficiencyTypeToString_Weapons) {
    EXPECT_EQ(proficiencyTypeToString(ProficiencyType::Weapons), "weapons");
}

TEST_F(UtilitiesTest, ProficiencyTypeToString_Armors) {
    EXPECT_EQ(proficiencyTypeToString(ProficiencyType::Armors), "armors");
}

TEST_F(UtilitiesTest, ProficiencyTypeToString_Tools) {
    EXPECT_EQ(proficiencyTypeToString(ProficiencyType::Tools), "tools");
}

TEST_F(UtilitiesTest, ProficiencyTypeToString_Skills) {
    EXPECT_EQ(proficiencyTypeToString(ProficiencyType::Skills), "skills");
}

TEST_F(UtilitiesTest, StringToProficiencyType_Weapons) {
    EXPECT_EQ(stringToProficiencyType("weapons"), ProficiencyType::Weapons);
}

TEST_F(UtilitiesTest, StringToProficiencyType_Armors) {
    EXPECT_EQ(stringToProficiencyType("armors"), ProficiencyType::Armors);
}

TEST_F(UtilitiesTest, StringToProficiencyType_Tools) {
    EXPECT_EQ(stringToProficiencyType("tools"), ProficiencyType::Tools);
}

TEST_F(UtilitiesTest, StringToProficiencyType_Skills) {
    EXPECT_EQ(stringToProficiencyType("skills"), ProficiencyType::Skills);
}

TEST_F(UtilitiesTest, StringToProficiencyType_InvalidString_ThrowsException) {
    EXPECT_THROW(stringToProficiencyType("magic"), std::runtime_error);
}

TEST_F(UtilitiesTest, StringToProficiencyType_RoundTrip) {
    EXPECT_EQ(stringToProficiencyType(proficiencyTypeToString(ProficiencyType::Weapons)), ProficiencyType::Weapons);
    EXPECT_EQ(stringToProficiencyType(proficiencyTypeToString(ProficiencyType::Armors)), ProficiencyType::Armors);
    EXPECT_EQ(stringToProficiencyType(proficiencyTypeToString(ProficiencyType::Tools)), ProficiencyType::Tools);
    EXPECT_EQ(stringToProficiencyType(proficiencyTypeToString(ProficiencyType::Skills)), ProficiencyType::Skills);
}

//=============================================================================
// JsonKeys Conversion Tests
//=============================================================================

TEST_F(UtilitiesTest, JsonKeyToString_Name) {
    EXPECT_EQ(jsonKeyToString(JsonKeys::name), "name");
}

TEST_F(UtilitiesTest, JsonKeyToString_IsAbstract) {
    EXPECT_EQ(jsonKeyToString(JsonKeys::is_abstract), "is_abstract");
}

TEST_F(UtilitiesTest, JsonKeyToString_BaseRace) {
    EXPECT_EQ(jsonKeyToString(JsonKeys::base_race), "base_race");
}

TEST_F(UtilitiesTest, JsonKeyToString_AbilityMods) {
    EXPECT_EQ(jsonKeyToString(JsonKeys::ability_mods), "ability_mods");
}

TEST_F(UtilitiesTest, JsonKeyToString_ParamMods) {
    EXPECT_EQ(jsonKeyToString(JsonKeys::param_mods), "param_mods");
}

TEST_F(UtilitiesTest, JsonKeyToString_SampleKeys) {
    EXPECT_EQ(jsonKeyToString(JsonKeys::ability), "ability");
    EXPECT_EQ(jsonKeyToString(JsonKeys::param), "param");
    EXPECT_EQ(jsonKeyToString(JsonKeys::mod), "mod");
    EXPECT_EQ(jsonKeyToString(JsonKeys::age), "age");
    EXPECT_EQ(jsonKeyToString(JsonKeys::maturity), "maturity");
    EXPECT_EQ(jsonKeyToString(JsonKeys::life_span), "life_span");
    EXPECT_EQ(jsonKeyToString(JsonKeys::alignment), "alignment");
    EXPECT_EQ(jsonKeyToString(JsonKeys::size), "size");
    EXPECT_EQ(jsonKeyToString(JsonKeys::category), "category");
}

TEST_F(UtilitiesTest, StringToJsonKeys_Name) {
    EXPECT_EQ(stringToJsonKeys("name"), JsonKeys::name);
}

TEST_F(UtilitiesTest, StringToJsonKeys_IsAbstract) {
    EXPECT_EQ(stringToJsonKeys("is_abstract"), JsonKeys::is_abstract);
}

TEST_F(UtilitiesTest, StringToJsonKeys_BaseRace) {
    EXPECT_EQ(stringToJsonKeys("base_race"), JsonKeys::base_race);
}

TEST_F(UtilitiesTest, StringToJsonKeys_AbilityMods) {
    EXPECT_EQ(stringToJsonKeys("ability_mods"), JsonKeys::ability_mods);
}

TEST_F(UtilitiesTest, StringToJsonKeys_InvalidString_ThrowsException) {
    EXPECT_THROW(stringToJsonKeys("invalid_key"), std::runtime_error);
}

TEST_F(UtilitiesTest, StringToJsonKeys_RoundTrip) {
    EXPECT_EQ(stringToJsonKeys(jsonKeyToString(JsonKeys::name)), JsonKeys::name);
    EXPECT_EQ(stringToJsonKeys(jsonKeyToString(JsonKeys::is_abstract)), JsonKeys::is_abstract);
    EXPECT_EQ(stringToJsonKeys(jsonKeyToString(JsonKeys::base_race)), JsonKeys::base_race);
    EXPECT_EQ(stringToJsonKeys(jsonKeyToString(JsonKeys::ability_mods)), JsonKeys::ability_mods);
    EXPECT_EQ(stringToJsonKeys(jsonKeyToString(JsonKeys::languages)), JsonKeys::languages);
    EXPECT_EQ(stringToJsonKeys(jsonKeyToString(JsonKeys::dark_vision)), JsonKeys::dark_vision);
    EXPECT_EQ(stringToJsonKeys(jsonKeyToString(JsonKeys::proficiency)), JsonKeys::proficiency);
}

TEST_F(UtilitiesTest, StringToJsonKeys_ComplexKeys) {
    EXPECT_EQ(stringToJsonKeys("avg_height_m"), JsonKeys::avg_height_m);
    EXPECT_EQ(stringToJsonKeys("avg_weight_kg"), JsonKeys::avg_weight_kg);
    EXPECT_EQ(stringToJsonKeys("speed_mps"), JsonKeys::speed_mps);
    EXPECT_EQ(stringToJsonKeys("has_darkvision"), JsonKeys::has_darkvision);
    EXPECT_EQ(stringToJsonKeys("sleep_duration_hrs"), JsonKeys::sleep_duration_hrs);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
