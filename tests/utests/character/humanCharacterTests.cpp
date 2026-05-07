#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "humanCharacters.h"

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

class HumanCharacterIntegrationTest : public ::testing::Test {};

TEST_F(HumanCharacterIntegrationTest, CombatScenario_TakeDamageAndHeal) {
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

TEST_F(HumanCharacterIntegrationTest, ResourceManagement_ManaUsageAndRegeneration) {
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

TEST_F(HumanCharacterIntegrationTest, StaminaManagement_ExhaustionAndRecovery) {
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

TEST_F(HumanCharacterIntegrationTest, DebuffScenario_DecreaseStats) {
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

TEST_F(HumanCharacterIntegrationTest, PolymorphicBehavior_UsingBasePointer) {
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

TEST_F(HumanCharacterIntegrationTest, FactoryCreatesCorrectPolymorphicTypes) {
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
