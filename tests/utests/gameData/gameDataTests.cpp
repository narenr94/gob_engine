#include "gameData.h"
#include "defines.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <filesystem>

using ::testing::UnorderedElementsAre;
using ::testing::Contains;
using ::testing::Not;
using ::testing::IsEmpty;
using ::testing::Ge;

namespace fs = std::filesystem;

// Test fixture for GameData tests - uses single shared JSON files
class GameDataTest : public ::testing::Test {
protected:
    static std::string testDataPath;
    static std::string testRacesPath;

    // SetUpTestSuite runs once before all tests in this fixture
    static void SetUpTestSuite() {
        testDataPath = "test_game_data_temp";
        testRacesPath = testDataPath + "/races";
        
        // Clean up any existing test directory
        if (fs::exists(testDataPath)) {
            fs::remove_all(testDataPath);
        }
        
        fs::create_directories(testRacesPath);
        
        // Create comprehensive JSON files once for all tests
        createAbilitiesJson();
        createParamsJson();
        createLanguagesJson();
        createTestRaces();
    }

    // TearDownTestSuite runs once after all tests in this fixture
    static void TearDownTestSuite() {
        // Clean up test directory
        if (fs::exists(testDataPath)) {
            fs::remove_all(testDataPath);
        }
    }

    static void createAbilitiesJson() {
        std::ofstream file(testDataPath + "/abilities.json");
        file << "{\"abilities\":[";
        file << "\"strength\",\"dexterity\",\"constitution\",";
        file << "\"intelligence\",\"wisdom\",\"charisma\"";
        file << "]}";
        file.close();
    }

    static void createParamsJson() {
        std::ofstream file(testDataPath + "/params.json");
        file << "{\"params\":[\"hit_points\",\"mana\",\"stamina\"]}";
        file.close();
    }

    static void createLanguagesJson() {
        std::ofstream file(testDataPath + "/languages.json");
        file << "{\"languages\":[";
        file << "\"common\",\"elvish\",\"dwarvish\",\"orcish\",";
        file << "\"draconic\",\"giant\",\"gnomish\",\"goblin\",\"halfling\",\"abyssal\"";
        file << "]}";
        file.close();
    }

    static void createTestRaces() {
        // Create human (non-abstract)
        std::ofstream human(testRacesPath + "/human.json");
        human << "{\n";
        human << "  \"name\": \"human\",\n";
        human << "  \"is_abstract\": false,\n";
        human << "  \"base_race\": null,\n";
        human << "  \"ability_mods\": [],\n";
        human << "  \"age\": {\"maturity\": 18, \"life_span\": 100},\n";
        human << "  \"alignment\": \"neutral_neutral\",\n";
        human << "  \"size\": {\"category\": \"medium\", \"avg_height_m\": 1.7, \"avg_weight_kg\": 70},\n";
        human << "  \"speed_mps\": 9,\n";
        human << "  \"languages\": [{\"name\": \"common\", \"speak\": true, \"read\": true, \"write\": true}]\n";
        human << "}";
        human.close();

        // Create elf (abstract base)
        std::ofstream elf(testRacesPath + "/elf.json");
        elf << "{\n";
        elf << "  \"name\": \"elf\",\n";
        elf << "  \"is_abstract\": true,\n";
        elf << "  \"base_race\": null\n";
        elf << "}";
        elf.close();

        // Create high_elf (non-abstract, based on elf)
        std::ofstream high_elf(testRacesPath + "/high_elf.json");
        high_elf << "{\n";
        high_elf << "  \"name\": \"high_elf\",\n";
        high_elf << "  \"is_abstract\": false,\n";
        high_elf << "  \"base_race\": null,\n";
        high_elf << "  \"ability_mods\": [],\n";
        high_elf << "  \"age\": {\"maturity\": 100, \"life_span\": 750},\n";
        high_elf << "  \"alignment\": \"neutral_neutral\",\n";
        high_elf << "  \"size\": {\"category\": \"medium\", \"avg_height_m\": 1.8, \"avg_weight_kg\": 60},\n";
        high_elf << "  \"speed_mps\": 9,\n";
        high_elf << "  \"languages\": [{\"name\": \"elvish\", \"speak\": true, \"read\": true, \"write\": true}]\n";
        high_elf << "}";
        high_elf.close();

        // Create dwarf (non-abstract)
        std::ofstream dwarf(testRacesPath + "/dwarf.json");
        dwarf << "{\n";
        dwarf << "  \"name\": \"dwarf\",\n";
        dwarf << "  \"is_abstract\": false,\n";
        dwarf << "  \"base_race\": null,\n";
        dwarf << "  \"ability_mods\": [],\n";
        dwarf << "  \"age\": {\"maturity\": 50, \"life_span\": 350},\n";
        dwarf << "  \"alignment\": \"neutral_neutral\",\n";
        dwarf << "  \"size\": {\"category\": \"medium\", \"avg_height_m\": 1.4, \"avg_weight_kg\": 75},\n";
        dwarf << "  \"speed_mps\": 7.5,\n";
        dwarf << "  \"languages\": [{\"name\": \"dwarvish\", \"speak\": true, \"read\": true, \"write\": true}]\n";
        dwarf << "}";
        dwarf.close();
    }
};

// Initialize static members
std::string GameDataTest::testDataPath;
std::string GameDataTest::testRacesPath;

// ============================================================================
// SINGLETON PATTERN TESTS
// ============================================================================

TEST_F(GameDataTest, SingletonReturnsConsistentInstance) {
    GameData* instance1 = GameData::getInstance(testDataPath);
    GameData* instance2 = GameData::getInstance(testDataPath);
    
    EXPECT_EQ(instance1, instance2) << "getInstance should return the same instance";
}

// ============================================================================
// ABILITIES TESTS
// ============================================================================

TEST_F(GameDataTest, LoadsAbilitiesCorrectly) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto abilities = gameData->getAbilitiesVector();
    
    EXPECT_EQ(abilities.size(), 6);
    EXPECT_THAT(abilities, UnorderedElementsAre("strength", "dexterity", "constitution", 
                                                  "intelligence", "wisdom", "charisma"));
}

TEST_F(GameDataTest, AbilitiesVectorNotEmpty) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto abilities = gameData->getAbilitiesVector();
    
    EXPECT_FALSE(abilities.empty());
}

// ============================================================================
// PARAMS TESTS
// ============================================================================

TEST_F(GameDataTest, LoadsParamsCorrectly) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto params = gameData->getParamsVector();
    
    EXPECT_EQ(params.size(), 3);
    EXPECT_THAT(params, UnorderedElementsAre("hit_points", "mana", "stamina"));
}

TEST_F(GameDataTest, ParamsVectorNotEmpty) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto params = gameData->getParamsVector();
    
    EXPECT_FALSE(params.empty());
}

// ============================================================================
// LANGUAGES TESTS
// ============================================================================

TEST_F(GameDataTest, LoadsLanguagesCorrectly) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto languages = gameData->getLanguagesVector();
    
    EXPECT_EQ(languages.size(), 10);
    EXPECT_THAT(languages, Contains("common"));
    EXPECT_THAT(languages, Contains("elvish"));
    EXPECT_THAT(languages, Contains("dwarvish"));
    EXPECT_THAT(languages, Contains("draconic"));
}

TEST_F(GameDataTest, LanguagesVectorNotEmpty) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto languages = gameData->getLanguagesVector();
    
    EXPECT_FALSE(languages.empty());
}

// ============================================================================
// RACES TESTS
// ============================================================================

TEST_F(GameDataTest, LoadsNonAbstractRacesOnly) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto races = gameData->getRacesVector();
    
    // Should include non-abstract races
    EXPECT_THAT(races, Contains("human"));
    EXPECT_THAT(races, Contains("high_elf"));
    EXPECT_THAT(races, Contains("dwarf"));
    
    // Should NOT include abstract race
    EXPECT_THAT(races, Not(Contains("elf")));
}

TEST_F(GameDataTest, RacesVectorNotEmpty) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto races = gameData->getRacesVector();
    
    EXPECT_FALSE(races.empty());
    EXPECT_GE(races.size(), 3);
}

// ============================================================================
// GET RACE DATA TESTS
// ============================================================================

TEST_F(GameDataTest, GetRaceFilePathReturnsCorrectPath) {
    GameData* gameData = GameData::getInstance(testDataPath);
    
    EXPECT_NO_THROW({
        std::string path = gameData->getRaceFilePath("human");
        EXPECT_FALSE(path.empty());
    });
}

TEST_F(GameDataTest, GetRaceDataDoesNotThrowForValidRace) {
    GameData* gameData = GameData::getInstance(testDataPath);
    ConsolidatedData conData;
    ConsolidatedOptionsData conOptData;
    
    std::string racePath = gameData->getRaceFilePath("human");
    EXPECT_NO_THROW({
        gameData->getRaceData(racePath, conData, conOptData);
    });
}

TEST_F(GameDataTest, GetRaceDataForMultipleRaces) {
    GameData* gameData = GameData::getInstance(testDataPath);
    ConsolidatedData conData1, conData2, conData3;
    ConsolidatedOptionsData conOptData1, conOptData2, conOptData3;
    
    EXPECT_NO_THROW({
        gameData->getRaceData(gameData->getRaceFilePath("human"), conData1, conOptData1);
        gameData->getRaceData(gameData->getRaceFilePath("high_elf"), conData2, conOptData2);
        gameData->getRaceData(gameData->getRaceFilePath("dwarf"), conData3, conOptData3);
    });
}

// ============================================================================
// CLASSES TESTS (Currently Todo in Implementation)
// ============================================================================

TEST_F(GameDataTest, ClassesVectorIsEmpty_TodoNotImplemented) {
    GameData* gameData = GameData::getInstance(testDataPath);
    auto classes = gameData->getClassesVector();
    
    // Classes are not yet implemented (marked as TODO in code)
    EXPECT_THAT(classes, IsEmpty());
}

// ============================================================================
// INTEGRATION TESTS
// ============================================================================

TEST_F(GameDataTest, LoadsAllDataComponentsSuccessfully) {
    GameData* gameData = GameData::getInstance(testDataPath);
    
    EXPECT_EQ(gameData->getAbilitiesVector().size(), 6);
    EXPECT_EQ(gameData->getParamsVector().size(), 3);
    EXPECT_EQ(gameData->getLanguagesVector().size(), 10);
    EXPECT_GE(gameData->getRacesVector().size(), 3);
}

TEST_F(GameDataTest, GettersReturnCopies) {
    GameData* gameData = GameData::getInstance(testDataPath);
    
    auto abilities1 = gameData->getAbilitiesVector();
    auto abilities2 = gameData->getAbilitiesVector();
    
    // Should return copies, not references
    EXPECT_EQ(abilities1.size(), abilities2.size());
    
    // Modifying one should not affect the other
    abilities1.push_back("new_ability");
    EXPECT_NE(abilities1.size(), abilities2.size());
}

// ============================================================================
// MAIN
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
