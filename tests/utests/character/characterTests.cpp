#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "character.h"

// ============================================================================
// CharacterParamOffsets Tests
// ============================================================================

class CharacterParamOffsetsTest : public ::testing::Test {
protected:
    CharacterParamOffsets offsets;
};

TEST_F(CharacterParamOffsetsTest, DefaultConstructor_InitializesAllFieldsToZero) {
    EXPECT_EQ(0, offsets.maxHealthOffset);
    EXPECT_EQ(0, offsets.maxStaminaOffset);
    EXPECT_EQ(0, offsets.maxManaOffset);
    EXPECT_EQ(0, offsets.intelligenceOffset);
    EXPECT_EQ(0, offsets.strengthOffset);
    EXPECT_EQ(0, offsets.charismaOffset);
    EXPECT_EQ(0, offsets.dexterityOffset);
    EXPECT_EQ(0, offsets.agilityOffset);
}

TEST_F(CharacterParamOffsetsTest, OperatorPlus_AddsAllOffsets) {
    CharacterParamOffsets offset1;
    offset1.maxHealthOffset = 10;
    offset1.maxStaminaOffset = 5;
    offset1.maxManaOffset = -3;
    offset1.intelligenceOffset = 7;
    offset1.strengthOffset = 2;
    offset1.charismaOffset = -1;
    offset1.dexterityOffset = 4;
    offset1.agilityOffset = 3;

    CharacterParamOffsets offset2;
    offset2.maxHealthOffset = 5;
    offset2.maxStaminaOffset = -2;
    offset2.maxManaOffset = 8;
    offset2.intelligenceOffset = -3;
    offset2.strengthOffset = 6;
    offset2.charismaOffset = 2;
    offset2.dexterityOffset = -1;
    offset2.agilityOffset = 1;

    CharacterParamOffsets result = offset1 + offset2;

    EXPECT_EQ(15, result.maxHealthOffset);
    EXPECT_EQ(3, result.maxStaminaOffset);
    EXPECT_EQ(5, result.maxManaOffset);
    EXPECT_EQ(4, result.intelligenceOffset);
    EXPECT_EQ(8, result.strengthOffset);
    EXPECT_EQ(1, result.charismaOffset);
    EXPECT_EQ(3, result.dexterityOffset);
    EXPECT_EQ(4, result.agilityOffset);
}

TEST_F(CharacterParamOffsetsTest, OperatorPlus_HandlesNegativeResults) {
    CharacterParamOffsets offset1;
    offset1.maxHealthOffset = 5;
    offset1.strengthOffset = 3;

    CharacterParamOffsets offset2;
    offset2.maxHealthOffset = -10;
    offset2.strengthOffset = -8;

    CharacterParamOffsets result = offset1 + offset2;

    EXPECT_EQ(-5, result.maxHealthOffset);
    EXPECT_EQ(-5, result.strengthOffset);
}

// ============================================================================
// Character Base Class Tests
// ============================================================================

class CharacterTest : public ::testing::Test {
protected:
    CharacterParamOffsets zeroOffsets;
};

TEST_F(CharacterTest, Constructor_WithZeroOffsets_InitializesWithDefaults) {
    Character character("TestHero", zeroOffsets);

    EXPECT_EQ("TestHero", character.getName());
    EXPECT_EQ(DEFAULT_MAX_HEALTH, character.getMaxHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA, character.getMaxStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA, character.getMaxMana());
    EXPECT_EQ(DEFAULT_MAX_HEALTH, character.getHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA, character.getStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA, character.getMana());
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE, character.getIntelligence());
    EXPECT_EQ(DEFAULT_BASE_STRENGTH, character.getStrength());
    EXPECT_EQ(DEFAULT_BASE_CHARISMA, character.getCharisma());
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY, character.getDexterity());
    EXPECT_EQ(DEFAULT_BASE_AGILITY, character.getAgility());
}

TEST_F(CharacterTest, Constructor_WithPositiveOffsets_AppliesCorrectly) {
    CharacterParamOffsets offsets;
    offsets.maxHealthOffset = 15;
    offsets.maxStaminaOffset = 10;
    offsets.maxManaOffset = 20;
    offsets.intelligenceOffset = 5;
    offsets.strengthOffset = 7;
    offsets.charismaOffset = 3;
    offsets.dexterityOffset = 4;
    offsets.agilityOffset = 6;

    Character character("StrongHero", offsets);

    EXPECT_EQ(DEFAULT_MAX_HEALTH + 15, character.getMaxHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA + 10, character.getMaxStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA + 20, character.getMaxMana());
    EXPECT_EQ(DEFAULT_MAX_HEALTH + 15, character.getHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA + 10, character.getStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA + 20, character.getMana());
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE + 5, character.getIntelligence());
    EXPECT_EQ(DEFAULT_BASE_STRENGTH + 7, character.getStrength());
    EXPECT_EQ(DEFAULT_BASE_CHARISMA + 3, character.getCharisma());
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY + 4, character.getDexterity());
    EXPECT_EQ(DEFAULT_BASE_AGILITY + 6, character.getAgility());
}

TEST_F(CharacterTest, Constructor_WithLargeNegativeOffsets_ClampsToZero) {
    CharacterParamOffsets offsets;
    offsets.maxHealthOffset = -100;
    offsets.maxStaminaOffset = -100;
    offsets.maxManaOffset = -100;
    offsets.intelligenceOffset = -100;
    offsets.strengthOffset = -100;
    offsets.charismaOffset = -100;
    offsets.dexterityOffset = -100;
    offsets.agilityOffset = -100;

    Character character("WeakHero", offsets);

    EXPECT_EQ(0, character.getMaxHealth());
    EXPECT_EQ(0, character.getMaxStamina());
    EXPECT_EQ(0, character.getMaxMana());
    EXPECT_EQ(0, character.getHealth());
    EXPECT_EQ(0, character.getStamina());
    EXPECT_EQ(0, character.getMana());
    EXPECT_EQ(0, character.getIntelligence());
    EXPECT_EQ(0, character.getStrength());
    EXPECT_EQ(0, character.getCharisma());
    EXPECT_EQ(0, character.getDexterity());
    EXPECT_EQ(0, character.getAgility());
}

TEST_F(CharacterTest, GetClass_BaseCharacter_ReturnsNA) {
    Character character("TestHero", zeroOffsets);
    EXPECT_EQ(CharacterClass::NA, character.getClass());
}

// ============================================================================
// Setter Tests
// ============================================================================

TEST_F(CharacterTest, SetName_ChangesName) {
    Character character("OldName", zeroOffsets);
    character.setName("NewName");
    EXPECT_EQ("NewName", character.getName());
}

TEST_F(CharacterTest, SetMaxHealth_IncreasesMaxHealth) {
    Character character("TestHero", zeroOffsets);
    character.setMaxHealth(50);
    EXPECT_EQ(50, character.getMaxHealth());
}

TEST_F(CharacterTest, SetMaxHealth_WhenCurrentHealthExceedsNew_ClampsCurrentHealth) {
    Character character("TestHero", zeroOffsets);
    character.setHealth(10);
    character.setMaxHealth(5);
    EXPECT_EQ(5, character.getMaxHealth());
    EXPECT_EQ(5, character.getHealth());
}

TEST_F(CharacterTest, SetMaxStamina_IncreasesMaxStamina) {
    Character character("TestHero", zeroOffsets);
    character.setMaxStamina(40);
    EXPECT_EQ(40, character.getMaxStamina());
}

TEST_F(CharacterTest, SetMaxStamina_WhenCurrentStaminaExceedsNew_ClampsCurrentStamina) {
    Character character("TestHero", zeroOffsets);
    character.setStamina(10);
    character.setMaxStamina(5);
    EXPECT_EQ(5, character.getMaxStamina());
    EXPECT_EQ(5, character.getStamina());
}

TEST_F(CharacterTest, SetMaxMana_IncreasesMaxMana) {
    Character character("TestHero", zeroOffsets);
    character.setMaxMana(60);
    EXPECT_EQ(60, character.getMaxMana());
}

TEST_F(CharacterTest, SetMaxMana_WhenCurrentManaExceedsNew_ClampsCurrentMana) {
    Character character("TestHero", zeroOffsets);
    character.setMana(10);
    character.setMaxMana(5);
    EXPECT_EQ(5, character.getMaxMana());
    EXPECT_EQ(5, character.getMana());
}

TEST_F(CharacterTest, SetHealth_WithinBounds_SetsCorrectly) {
    Character character("TestHero", zeroOffsets);
    character.setHealth(5);
    EXPECT_EQ(5, character.getHealth());
}

TEST_F(CharacterTest, SetHealth_AboveMax_ClampsToMax) {
    Character character("TestHero", zeroOffsets);
    character.setHealth(999);
    EXPECT_EQ(DEFAULT_MAX_HEALTH, character.getHealth());
}

TEST_F(CharacterTest, SetStamina_WithinBounds_SetsCorrectly) {
    Character character("TestHero", zeroOffsets);
    character.setStamina(7);
    EXPECT_EQ(7, character.getStamina());
}

TEST_F(CharacterTest, SetStamina_AboveMax_ClampsToMax) {
    Character character("TestHero", zeroOffsets);
    character.setStamina(999);
    EXPECT_EQ(DEFAULT_MAX_STAMINA, character.getStamina());
}

TEST_F(CharacterTest, SetMana_WithinBounds_SetsCorrectly) {
    Character character("TestHero", zeroOffsets);
    character.setMana(8);
    EXPECT_EQ(8, character.getMana());
}

TEST_F(CharacterTest, SetMana_AboveMax_ClampsToMax) {
    Character character("TestHero", zeroOffsets);
    character.setMana(999);
    EXPECT_EQ(DEFAULT_MAX_MANA, character.getMana());
}

TEST_F(CharacterTest, SetIntelligence_SetsValue) {
    Character character("TestHero", zeroOffsets);
    character.setIntelligence(15);
    EXPECT_EQ(15, character.getIntelligence());
}

TEST_F(CharacterTest, SetStrength_SetsValue) {
    Character character("TestHero", zeroOffsets);
    character.setStrength(20);
    EXPECT_EQ(20, character.getStrength());
}

TEST_F(CharacterTest, SetCharisma_SetsValue) {
    Character character("TestHero", zeroOffsets);
    character.setCharisma(12);
    EXPECT_EQ(12, character.getCharisma());
}

TEST_F(CharacterTest, SetDexterity_SetsValue) {
    Character character("TestHero", zeroOffsets);
    character.setDexterity(18);
    EXPECT_EQ(18, character.getDexterity());
}

TEST_F(CharacterTest, SetAgility_SetsValue) {
    Character character("TestHero", zeroOffsets);
    character.setAgility(14);
    EXPECT_EQ(14, character.getAgility());
}

// ============================================================================
// Offset Method Tests
// ============================================================================

TEST_F(CharacterTest, OffsetMaxHealth_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getMaxHealth();
    character.offsetMaxHealth(10);
    EXPECT_EQ(initial + 10, character.getMaxHealth());
}

TEST_F(CharacterTest, OffsetMaxHealth_SmallNegativeOffset_Decreases) {
    Character character("TestHero", zeroOffsets);
    character.setMaxHealth(20);
    character.offsetMaxHealth(-5);
    EXPECT_EQ(15, character.getMaxHealth());
}

TEST_F(CharacterTest, OffsetMaxHealth_LargeNegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetMaxHealth(-100);
    EXPECT_EQ(0, character.getMaxHealth());
}

TEST_F(CharacterTest, OffsetMaxStamina_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getMaxStamina();
    character.offsetMaxStamina(8);
    EXPECT_EQ(initial + 8, character.getMaxStamina());
}

TEST_F(CharacterTest, OffsetMaxStamina_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetMaxStamina(-100);
    EXPECT_EQ(0, character.getMaxStamina());
}

TEST_F(CharacterTest, OffsetMaxMana_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getMaxMana();
    character.offsetMaxMana(15);
    EXPECT_EQ(initial + 15, character.getMaxMana());
}

TEST_F(CharacterTest, OffsetMaxMana_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetMaxMana(-100);
    EXPECT_EQ(0, character.getMaxMana());
}

TEST_F(CharacterTest, OffsetHealth_PositiveOffset_IncreasesButClampsToMax) {
    Character character("TestHero", zeroOffsets);
    character.setHealth(5);
    character.offsetHealth(100);
    EXPECT_EQ(character.getMaxHealth(), character.getHealth());
}

TEST_F(CharacterTest, OffsetHealth_SmallPositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    character.setHealth(5);
    character.offsetHealth(2);
    EXPECT_EQ(7, character.getHealth());
}

TEST_F(CharacterTest, OffsetHealth_NegativeOffset_Decreases) {
    Character character("TestHero", zeroOffsets);
    character.setHealth(8);
    character.offsetHealth(-3);
    EXPECT_EQ(5, character.getHealth());
}

TEST_F(CharacterTest, OffsetHealth_LargeNegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetHealth(-100);
    EXPECT_EQ(0, character.getHealth());
}

TEST_F(CharacterTest, OffsetStamina_PositiveOffset_IncreasesButClampsToMax) {
    Character character("TestHero", zeroOffsets);
    character.setStamina(5);
    character.offsetStamina(100);
    EXPECT_EQ(character.getMaxStamina(), character.getStamina());
}

TEST_F(CharacterTest, OffsetStamina_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetStamina(-100);
    EXPECT_EQ(0, character.getStamina());
}

TEST_F(CharacterTest, OffsetMana_PositiveOffset_IncreasesButClampsToMax) {
    Character character("TestHero", zeroOffsets);
    character.setMana(5);
    character.offsetMana(100);
    EXPECT_EQ(character.getMaxMana(), character.getMana());
}

TEST_F(CharacterTest, OffsetMana_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetMana(-100);
    EXPECT_EQ(0, character.getMana());
}

TEST_F(CharacterTest, OffsetIntelligence_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getIntelligence();
    character.offsetIntelligence(7);
    EXPECT_EQ(initial + 7, character.getIntelligence());
}

TEST_F(CharacterTest, OffsetIntelligence_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetIntelligence(-100);
    EXPECT_EQ(0, character.getIntelligence());
}

TEST_F(CharacterTest, OffsetStrength_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getStrength();
    character.offsetStrength(9);
    EXPECT_EQ(initial + 9, character.getStrength());
}

TEST_F(CharacterTest, OffsetStrength_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetStrength(-100);
    EXPECT_EQ(0, character.getStrength());
}

TEST_F(CharacterTest, OffsetCharisma_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getCharisma();
    character.offsetCharisma(4);
    EXPECT_EQ(initial + 4, character.getCharisma());
}

TEST_F(CharacterTest, OffsetCharisma_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetCharisma(-100);
    EXPECT_EQ(0, character.getCharisma());
}

TEST_F(CharacterTest, OffsetDexterity_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getDexterity();
    character.offsetDexterity(6);
    EXPECT_EQ(initial + 6, character.getDexterity());
}

TEST_F(CharacterTest, OffsetDexterity_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetDexterity(-100);
    EXPECT_EQ(0, character.getDexterity());
}

TEST_F(CharacterTest, OffsetAgility_PositiveOffset_Increases) {
    Character character("TestHero", zeroOffsets);
    unsigned int initial = character.getAgility();
    character.offsetAgility(5);
    EXPECT_EQ(initial + 5, character.getAgility());
}

TEST_F(CharacterTest, OffsetAgility_NegativeOffset_ClampsToZero) {
    Character character("TestHero", zeroOffsets);
    character.offsetAgility(-100);
    EXPECT_EQ(0, character.getAgility());
}

// ============================================================================
// Warrior Class Tests
// ============================================================================

class WarriorTest : public ::testing::Test {};

TEST_F(WarriorTest, Constructor_AppliesWarriorOffsets) {
    Warrior warrior("Conan");

    EXPECT_EQ("Conan", warrior.getName());
    EXPECT_EQ(DEFAULT_MAX_HEALTH + WARRIOR_MAX_HEALTH_OFFSET, warrior.getMaxHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA + WARRIOR_MAX_STAMINA_OFFSET, warrior.getMaxStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA + WARRIOR_MAX_MANA_OFFSET, warrior.getMaxMana());
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE + WARRIOR_INTELLIGENCE_OFFSET, warrior.getIntelligence());
    EXPECT_EQ(DEFAULT_BASE_STRENGTH + WARRIOR_STRENGTH_OFFSET, warrior.getStrength());
    EXPECT_EQ(DEFAULT_BASE_CHARISMA + WARRIOR_CHARISMA_OFFSET, warrior.getCharisma());
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY + WARRIOR_DEXTERITY_OFFSET, warrior.getDexterity());
    EXPECT_EQ(DEFAULT_BASE_AGILITY + WARRIOR_AGILITY_OFFSET, warrior.getAgility());
}

TEST_F(WarriorTest, Constructor_InitializesCurrentStatsToMax) {
    Warrior warrior("Conan");

    EXPECT_EQ(warrior.getMaxHealth(), warrior.getHealth());
    EXPECT_EQ(warrior.getMaxStamina(), warrior.getStamina());
    EXPECT_EQ(warrior.getMaxMana(), warrior.getMana());
}

TEST_F(WarriorTest, GetClass_ReturnsWarrior) {
    Warrior warrior("Conan");
    EXPECT_EQ(CharacterClass::Warrior, warrior.getClass());
}

TEST_F(WarriorTest, WarriorOffsets_ReturnsCorrectValues) {
    CharacterParamOffsets offsets = WarriorOffsets();

    EXPECT_EQ(WARRIOR_MAX_HEALTH_OFFSET, offsets.maxHealthOffset);
    EXPECT_EQ(WARRIOR_MAX_STAMINA_OFFSET, offsets.maxStaminaOffset);
    EXPECT_EQ(WARRIOR_MAX_MANA_OFFSET, offsets.maxManaOffset);
    EXPECT_EQ(WARRIOR_INTELLIGENCE_OFFSET, offsets.intelligenceOffset);
    EXPECT_EQ(WARRIOR_STRENGTH_OFFSET, offsets.strengthOffset);
    EXPECT_EQ(WARRIOR_CHARISMA_OFFSET, offsets.charismaOffset);
    EXPECT_EQ(WARRIOR_DEXTERITY_OFFSET, offsets.dexterityOffset);
    EXPECT_EQ(WARRIOR_AGILITY_OFFSET, offsets.agilityOffset);
}

TEST_F(WarriorTest, WarriorInheritsCharacterMethods) {
    Warrior warrior("Conan");
    
    warrior.setName("Conan the Barbarian");
    EXPECT_EQ("Conan the Barbarian", warrior.getName());
    
    warrior.setHealth(10);
    EXPECT_EQ(10, warrior.getHealth());
    
    warrior.offsetStrength(5);
    EXPECT_EQ(DEFAULT_BASE_STRENGTH + WARRIOR_STRENGTH_OFFSET + 5, warrior.getStrength());
}

// ============================================================================
// Mage Class Tests
// ============================================================================

class MageTest : public ::testing::Test {};

TEST_F(MageTest, Constructor_AppliesMageOffsets) {
    Mage mage("Gandalf");

    EXPECT_EQ("Gandalf", mage.getName());
    EXPECT_EQ(DEFAULT_MAX_HEALTH + MAGE_MAX_HEALTH_OFFSET, mage.getMaxHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA + MAGE_MAX_STAMINA_OFFSET, mage.getMaxStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA + MAGE_MAX_MANA_OFFSET, mage.getMaxMana());
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE + MAGE_INTELLIGENCE_OFFSET, mage.getIntelligence());
    EXPECT_EQ(DEFAULT_BASE_STRENGTH + MAGE_STRENGTH_OFFSET, mage.getStrength());
    EXPECT_EQ(DEFAULT_BASE_CHARISMA + MAGE_CHARISMA_OFFSET, mage.getCharisma());
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY + MAGE_DEXTERITY_OFFSET, mage.getDexterity());
    EXPECT_EQ(DEFAULT_BASE_AGILITY + MAGE_AGILITY_OFFSET, mage.getAgility());
}

TEST_F(MageTest, Constructor_InitializesCurrentStatsToMax) {
    Mage mage("Gandalf");

    EXPECT_EQ(mage.getMaxHealth(), mage.getHealth());
    EXPECT_EQ(mage.getMaxStamina(), mage.getStamina());
    EXPECT_EQ(mage.getMaxMana(), mage.getMana());
}

TEST_F(MageTest, GetClass_ReturnsMage) {
    Mage mage("Gandalf");
    EXPECT_EQ(CharacterClass::Mage, mage.getClass());
}

TEST_F(MageTest, MageOffsets_ReturnsCorrectValues) {
    CharacterParamOffsets offsets = MageOffsets();

    EXPECT_EQ(MAGE_MAX_HEALTH_OFFSET, offsets.maxHealthOffset);
    EXPECT_EQ(MAGE_MAX_STAMINA_OFFSET, offsets.maxStaminaOffset);
    EXPECT_EQ(MAGE_MAX_MANA_OFFSET, offsets.maxManaOffset);
    EXPECT_EQ(MAGE_INTELLIGENCE_OFFSET, offsets.intelligenceOffset);
    EXPECT_EQ(MAGE_STRENGTH_OFFSET, offsets.strengthOffset);
    EXPECT_EQ(MAGE_CHARISMA_OFFSET, offsets.charismaOffset);
    EXPECT_EQ(MAGE_DEXTERITY_OFFSET, offsets.dexterityOffset);
    EXPECT_EQ(MAGE_AGILITY_OFFSET, offsets.agilityOffset);
}

TEST_F(MageTest, MageHasHighIntelligenceAndMana) {
    Mage mage("Gandalf");
    
    // Mage should have high intelligence and mana
    EXPECT_GT(mage.getIntelligence(), DEFAULT_BASE_INTELLIGENCE);
    EXPECT_GT(mage.getMaxMana(), DEFAULT_MAX_MANA);
}

TEST_F(MageTest, MageInheritsCharacterMethods) {
    Mage mage("Gandalf");
    
    mage.setName("Gandalf the Grey");
    EXPECT_EQ("Gandalf the Grey", mage.getName());
    
    mage.setMana(20);
    EXPECT_EQ(20, mage.getMana());
    
    mage.offsetIntelligence(5);
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE + MAGE_INTELLIGENCE_OFFSET + 5, mage.getIntelligence());
}

// ============================================================================
// Ranger Class Tests
// ============================================================================

class RangerTest : public ::testing::Test {};

TEST_F(RangerTest, Constructor_AppliesRangerOffsets) {
    Ranger ranger("Aragorn");

    EXPECT_EQ("Aragorn", ranger.getName());
    EXPECT_EQ(DEFAULT_MAX_HEALTH + RANGER_MAX_HEALTH_OFFSET, ranger.getMaxHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA + RANGER_MAX_STAMINA_OFFSET, ranger.getMaxStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA + RANGER_MAX_MANA_OFFSET, ranger.getMaxMana());
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE + RANGER_INTELLIGENCE_OFFSET, ranger.getIntelligence());
    EXPECT_EQ(DEFAULT_BASE_STRENGTH + RANGER_STRENGTH_OFFSET, ranger.getStrength());
    EXPECT_EQ(DEFAULT_BASE_CHARISMA + RANGER_CHARISMA_OFFSET, ranger.getCharisma());
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY + RANGER_DEXTERITY_OFFSET, ranger.getDexterity());
    EXPECT_EQ(DEFAULT_BASE_AGILITY + RANGER_AGILITY_OFFSET, ranger.getAgility());
}

TEST_F(RangerTest, Constructor_InitializesCurrentStatsToMax) {
    Ranger ranger("Aragorn");

    EXPECT_EQ(ranger.getMaxHealth(), ranger.getHealth());
    EXPECT_EQ(ranger.getMaxStamina(), ranger.getStamina());
    EXPECT_EQ(ranger.getMaxMana(), ranger.getMana());
}

TEST_F(RangerTest, GetClass_ReturnsRanger) {
    Ranger ranger("Aragorn");
    EXPECT_EQ(CharacterClass::Ranger, ranger.getClass());
}

TEST_F(RangerTest, RangerOffsets_ReturnsCorrectValues) {
    CharacterParamOffsets offsets = RangerOffsets();

    EXPECT_EQ(RANGER_MAX_HEALTH_OFFSET, offsets.maxHealthOffset);
    EXPECT_EQ(RANGER_MAX_STAMINA_OFFSET, offsets.maxStaminaOffset);
    EXPECT_EQ(RANGER_MAX_MANA_OFFSET, offsets.maxManaOffset);
    EXPECT_EQ(RANGER_INTELLIGENCE_OFFSET, offsets.intelligenceOffset);
    EXPECT_EQ(RANGER_STRENGTH_OFFSET, offsets.strengthOffset);
    EXPECT_EQ(RANGER_CHARISMA_OFFSET, offsets.charismaOffset);
    EXPECT_EQ(RANGER_DEXTERITY_OFFSET, offsets.dexterityOffset);
    EXPECT_EQ(RANGER_AGILITY_OFFSET, offsets.agilityOffset);
}

TEST_F(RangerTest, RangerHasHighDexterityAndAgility) {
    Ranger ranger("Aragorn");
    
    // Ranger should have high dexterity and agility
    EXPECT_GT(ranger.getDexterity(), DEFAULT_BASE_DEXTERITY);
    EXPECT_GT(ranger.getAgility(), DEFAULT_BASE_AGILITY);
}

TEST_F(RangerTest, RangerInheritsCharacterMethods) {
    Ranger ranger("Aragorn");
    
    ranger.setName("Aragorn son of Arathorn");
    EXPECT_EQ("Aragorn son of Arathorn", ranger.getName());
    
    ranger.setStamina(15);
    EXPECT_EQ(15, ranger.getStamina());
    
    ranger.offsetDexterity(3);
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY + RANGER_DEXTERITY_OFFSET + 3, ranger.getDexterity());
}

// ============================================================================
// CharacterFactory Tests
// ============================================================================

class CharacterFactoryTest : public ::testing::Test {};

TEST_F(CharacterFactoryTest, CreateCharacter_Warrior_ReturnsWarriorInstance) {
    std::string name = "TestWarrior";
    auto character = CharacterFactory::createCharacter(name, CharacterClass::Warrior);

    ASSERT_NE(nullptr, character);
    EXPECT_EQ("TestWarrior", character->getName());
    EXPECT_EQ(CharacterClass::Warrior, character->getClass());
    EXPECT_EQ(DEFAULT_MAX_HEALTH + WARRIOR_MAX_HEALTH_OFFSET, character->getMaxHealth());
}

TEST_F(CharacterFactoryTest, CreateCharacter_Mage_ReturnsMageInstance) {
    std::string name = "TestMage";
    auto character = CharacterFactory::createCharacter(name, CharacterClass::Mage);

    ASSERT_NE(nullptr, character);
    EXPECT_EQ("TestMage", character->getName());
    EXPECT_EQ(CharacterClass::Mage, character->getClass());
    EXPECT_EQ(DEFAULT_MAX_MANA + MAGE_MAX_MANA_OFFSET, character->getMaxMana());
}

TEST_F(CharacterFactoryTest, CreateCharacter_Ranger_ReturnsRangerInstance) {
    std::string name = "TestRanger";
    auto character = CharacterFactory::createCharacter(name, CharacterClass::Ranger);

    ASSERT_NE(nullptr, character);
    EXPECT_EQ("TestRanger", character->getName());
    EXPECT_EQ(CharacterClass::Ranger, character->getClass());
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY + RANGER_DEXTERITY_OFFSET, character->getDexterity());
}

TEST_F(CharacterFactoryTest, CreateCharacter_NA_ReturnsBaseCharacterInstance) {
    std::string name = "TestNA";
    auto character = CharacterFactory::createCharacter(name, CharacterClass::NA);

    ASSERT_NE(nullptr, character);
    EXPECT_EQ("TestNA", character->getName());
    EXPECT_EQ(CharacterClass::NA, character->getClass());
    EXPECT_EQ(DEFAULT_MAX_HEALTH, character->getMaxHealth());
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE, character->getIntelligence());
}

TEST_F(CharacterFactoryTest, CreateCharacter_DefaultCase_ReturnsBaseCharacterInstance) {
    std::string name = "TestDefault";
    auto character = CharacterFactory::createCharacter(name, static_cast<CharacterClass>(999));

    ASSERT_NE(nullptr, character);
    EXPECT_EQ("TestDefault", character->getName());
    EXPECT_EQ(CharacterClass::NA, character->getClass());
}

// ============================================================================
// Integration Tests - Complex Scenarios
// ============================================================================

class CharacterIntegrationTest : public ::testing::Test {};

TEST_F(CharacterIntegrationTest, CombatScenario_TakeDamageAndHeal) {
    Warrior warrior("Tank");
    
    unsigned int maxHealth = warrior.getMaxHealth();
    
    // Take damage
    warrior.offsetHealth(-15);
    EXPECT_EQ(maxHealth - 15, warrior.getHealth());
    
    // Heal partially
    warrior.offsetHealth(8);
    EXPECT_EQ(maxHealth - 7, warrior.getHealth());
    
    // Over-heal (should clamp to max)
    warrior.offsetHealth(100);
    EXPECT_EQ(maxHealth, warrior.getHealth());
}

TEST_F(CharacterIntegrationTest, ResourceManagement_ManaUsageAndRegeneration) {
    Mage mage("Wizard");
    
    unsigned int maxMana = mage.getMaxMana();
    
    // Use mana for spell
    mage.offsetMana(-10);
    EXPECT_EQ(maxMana - 10, mage.getMana());
    
    // Use more mana
    mage.offsetMana(-15);
    EXPECT_EQ(maxMana - 25, mage.getMana());
    
    // Regenerate mana
    mage.offsetMana(20);
    EXPECT_EQ(maxMana - 5, mage.getMana());
    
    // Full restore
    mage.setMana(maxMana);
    EXPECT_EQ(maxMana, mage.getMana());
}

TEST_F(CharacterIntegrationTest, StaminaManagement_ExhaustionAndRecovery) {
    Ranger ranger("Scout");
    
    unsigned int maxStamina = ranger.getMaxStamina();
    
    // Use stamina
    ranger.offsetStamina(-20);
    EXPECT_LT(ranger.getStamina(), maxStamina);
    
    // Complete exhaustion
    ranger.offsetStamina(-1000);
    EXPECT_EQ(0, ranger.getStamina());
    
    // Recovery
    ranger.offsetStamina(10);
    EXPECT_EQ(10, ranger.getStamina());
}

TEST_F(CharacterIntegrationTest, LevelUpScenario_IncreaseStats) {
    Character character("Hero", CharacterParamOffsets());
    
    // Simulate level up - increase all stats
    character.offsetIntelligence(2);
    character.offsetStrength(3);
    character.offsetCharisma(1);
    character.offsetDexterity(2);
    character.offsetAgility(2);
    character.offsetMaxHealth(5);
    character.offsetMaxStamina(5);
    character.offsetMaxMana(5);
    
    EXPECT_EQ(DEFAULT_BASE_INTELLIGENCE + 2, character.getIntelligence());
    EXPECT_EQ(DEFAULT_BASE_STRENGTH + 3, character.getStrength());
    EXPECT_EQ(DEFAULT_BASE_CHARISMA + 1, character.getCharisma());
    EXPECT_EQ(DEFAULT_BASE_DEXTERITY + 2, character.getDexterity());
    EXPECT_EQ(DEFAULT_BASE_AGILITY + 2, character.getAgility());
    EXPECT_EQ(DEFAULT_MAX_HEALTH + 5, character.getMaxHealth());
    EXPECT_EQ(DEFAULT_MAX_STAMINA + 5, character.getMaxStamina());
    EXPECT_EQ(DEFAULT_MAX_MANA + 5, character.getMaxMana());
}

TEST_F(CharacterIntegrationTest, DebuffScenario_DecreaseStats) {
    Warrior warrior("Cursed");
    
    unsigned int originalStrength = warrior.getStrength();
    unsigned int originalMaxHealth = warrior.getMaxHealth();
    
    // Apply debuffs
    warrior.offsetStrength(-5);
    warrior.offsetMaxHealth(-10);
    
    EXPECT_EQ(originalStrength - 5, warrior.getStrength());
    EXPECT_EQ(originalMaxHealth - 10, warrior.getMaxHealth());
    
    // Health should adjust if it exceeds new max
    if (warrior.getHealth() > warrior.getMaxHealth()) {
        FAIL() << "Health should not exceed max health after debuff";
    }
}

TEST_F(CharacterIntegrationTest, PolymorphicBehavior_UsingBasePointer) {
    std::vector<std::unique_ptr<Character>> party;
    
    party.push_back(std::make_unique<Warrior>("Tank"));
    party.push_back(std::make_unique<Mage>("Healer"));
    party.push_back(std::make_unique<Ranger>("DPS"));
    
    EXPECT_EQ(CharacterClass::Warrior, party[0]->getClass());
    EXPECT_EQ(CharacterClass::Mage, party[1]->getClass());
    EXPECT_EQ(CharacterClass::Ranger, party[2]->getClass());
    
    // All characters should have different stat distributions
    EXPECT_GT(party[0]->getStrength(), party[1]->getStrength()); // Warrior > Mage strength
    EXPECT_GT(party[1]->getIntelligence(), party[0]->getIntelligence()); // Mage > Warrior intelligence
    EXPECT_GT(party[2]->getDexterity(), party[1]->getDexterity()); // Ranger > Mage dexterity
}

TEST_F(CharacterIntegrationTest, FactoryCreatesCorrectPolymorphicTypes) {
    std::string name1 = "FactoryWarrior";
    std::string name2 = "FactoryMage";
    std::string name3 = "FactoryRanger";
    
    auto warrior = CharacterFactory::createCharacter(name1, CharacterClass::Warrior);
    auto mage = CharacterFactory::createCharacter(name2, CharacterClass::Mage);
    auto ranger = CharacterFactory::createCharacter(name3, CharacterClass::Ranger);
    
    // Each should have distinct characteristics
    EXPECT_GT(warrior->getMaxHealth(), mage->getMaxHealth());
    EXPECT_GT(mage->getMaxMana(), warrior->getMaxMana());
    EXPECT_GT(ranger->getMaxStamina(), mage->getMaxStamina());
}

// ============================================================================
// Edge Case Tests
// ============================================================================

class CharacterEdgeCaseTest : public ::testing::Test {};

TEST_F(CharacterEdgeCaseTest, EmptyName_AcceptsEmptyString) {
    Character character("", CharacterParamOffsets());
    EXPECT_EQ("", character.getName());
}

TEST_F(CharacterEdgeCaseTest, VeryLongName_AcceptsLongString) {
    std::string longName(1000, 'X');
    Character character(longName, CharacterParamOffsets());
    EXPECT_EQ(longName, character.getName());
}

TEST_F(CharacterEdgeCaseTest, SetHealthToZero_CharacterAtZeroHealth) {
    Character character("Dying", CharacterParamOffsets());
    character.setHealth(0);
    EXPECT_EQ(0, character.getHealth());
}

TEST_F(CharacterEdgeCaseTest, MultipleOffsetsInSequence_AccumulateCorrectly) {
    Character character("Hero", CharacterParamOffsets());
    
    character.offsetStrength(5);
    character.offsetStrength(3);
    character.offsetStrength(-2);
    
    EXPECT_EQ(DEFAULT_BASE_STRENGTH + 6, character.getStrength());
}

TEST_F(CharacterEdgeCaseTest, SetMaxBelowCurrentValue_AdjustsCurrent) {
    Character character("Hero", CharacterParamOffsets());
    
    character.setHealth(10);
    character.setMaxHealth(5);
    
    EXPECT_EQ(5, character.getMaxHealth());
    EXPECT_EQ(5, character.getHealth());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
