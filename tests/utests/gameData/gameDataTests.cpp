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

TEST_F(GameDataTest, ValidateRaceDataWithTestPrints) {
    GameData* gameData = GameData::getInstance(testDataPath);
    
    // Test Human race data
    {
        ConsolidatedData conData;
        ConsolidatedOptionsData conOptData;
        std::string racePath = gameData->getRaceFilePath("human");
        
        ASSERT_NO_THROW({
            gameData->getRaceData(racePath, conData, conOptData);
        }) << "Failed to load race data for human";
        
#if defined(TEST_PRINTS)
        std::cout << "\n=== Validating race: human ===" << std::endl;
#endif
        
        // Verify consolidated data is populated
        EXPECT_FALSE(conData.data.empty()) << "Human race data should not be empty";
        
        // Check for specific data types in consolidated data
        bool hasAgeData = false;
        bool hasSizeData = false;
        bool hasSpeedData = false;
        bool hasLanguageData = false;
        bool hasAlignmentData = false;
        
        for (const auto* dataPtr : conData.data) {
            if (dynamic_cast<const AgeData*>(dataPtr)) {
                hasAgeData = true;
                const AgeData* ageData = static_cast<const AgeData*>(dataPtr);
                EXPECT_EQ(ageData->maturityAge, 18) << "Human maturity age should be 18";
                EXPECT_EQ(ageData->avgLifespan, 100) << "Human lifespan should be 100";
            }
            else if (dynamic_cast<const SizeData*>(dataPtr)) {
                hasSizeData = true;
                const SizeData* sizeData = static_cast<const SizeData*>(dataPtr);
                EXPECT_EQ(sizeData->category, SizeCategory::Medium) << "Human size should be Medium";
                EXPECT_FLOAT_EQ(sizeData->dimensions.first, 1.7f) << "Human height should be 1.7m";
                EXPECT_FLOAT_EQ(sizeData->dimensions.second, 70.0f) << "Human weight should be 70kg";
            }
            else if (dynamic_cast<const SpeedData*>(dataPtr)) {
                hasSpeedData = true;
                const SpeedData* speedData = static_cast<const SpeedData*>(dataPtr);
                EXPECT_FLOAT_EQ(speedData->speed, 9.0f) << "Human speed should be 9 m/s";
            }
            else if (dynamic_cast<const LanguageData*>(dataPtr)) {
                hasLanguageData = true;
                const LanguageData* langData = static_cast<const LanguageData*>(dataPtr);
                EXPECT_EQ(langData->language, "common") << "Human should speak Common";
                EXPECT_TRUE(langData->speak) << "Human should be able to speak Common";
                EXPECT_TRUE(langData->read) << "Human should be able to read Common";
                EXPECT_TRUE(langData->write) << "Human should be able to write Common";
            }
            else if (dynamic_cast<const AlignmentData*>(dataPtr)) {
                hasAlignmentData = true;
                const AlignmentData* alignData = static_cast<const AlignmentData*>(dataPtr);
                EXPECT_EQ(alignData->alignment, Alignment::neutral_neutral) << "Human alignment should be neutral_neutral";
            }
        }
        
        EXPECT_TRUE(hasAgeData) << "Human race should have age data";
        EXPECT_TRUE(hasSizeData) << "Human race should have size data";
        EXPECT_TRUE(hasSpeedData) << "Human race should have speed data";
        EXPECT_TRUE(hasLanguageData) << "Human race should have language data";
        EXPECT_TRUE(hasAlignmentData) << "Human race should have alignment data";
    }
    
    // Test Dwarf race data
    {
        ConsolidatedData conData;
        ConsolidatedOptionsData conOptData;
        std::string racePath = gameData->getRaceFilePath("dwarf");
        
        ASSERT_NO_THROW({
            gameData->getRaceData(racePath, conData, conOptData);
        }) << "Failed to load race data for dwarf";
        
#if defined(TEST_PRINTS)
        std::cout << "\n=== Validating race: dwarf ===" << std::endl;
#endif
        
        EXPECT_FALSE(conData.data.empty()) << "Dwarf race data should not be empty";
        
        // Check dwarf-specific values
        for (const auto* dataPtr : conData.data) {
            if (const AgeData* ageData = dynamic_cast<const AgeData*>(dataPtr)) {
                EXPECT_EQ(ageData->maturityAge, 50) << "Dwarf maturity age should be 50";
                EXPECT_EQ(ageData->avgLifespan, 350) << "Dwarf lifespan should be 350";
            }
            else if (const SpeedData* speedData = dynamic_cast<const SpeedData*>(dataPtr)) {
                EXPECT_FLOAT_EQ(speedData->speed, 7.5f) << "Dwarf speed should be 7.5 m/s";
            }
            else if (const LanguageData* langData = dynamic_cast<const LanguageData*>(dataPtr)) {
                EXPECT_EQ(langData->language, "dwarvish") << "Dwarf should speak Dwarvish";
            }
        }
    }
    
    // Test HighElf race data
    {
        ConsolidatedData conData;
        ConsolidatedOptionsData conOptData;
        std::string racePath = gameData->getRaceFilePath("high_elf");
        
        ASSERT_NO_THROW({
            gameData->getRaceData(racePath, conData, conOptData);
        }) << "Failed to load race data for high_elf";
        
#if defined(TEST_PRINTS)
        std::cout << "\n=== Validating race: high_elf ===" << std::endl;
#endif
        
        EXPECT_FALSE(conData.data.empty()) << "High Elf race data should not be empty";
        
        // Check high elf-specific values
        for (const auto* dataPtr : conData.data) {
            if (const AgeData* ageData = dynamic_cast<const AgeData*>(dataPtr)) {
                EXPECT_EQ(ageData->maturityAge, 100) << "High Elf maturity age should be 100";
                EXPECT_EQ(ageData->avgLifespan, 750) << "High Elf lifespan should be 750";
            }
            else if (const LanguageData* langData = dynamic_cast<const LanguageData*>(dataPtr)) {
                EXPECT_EQ(langData->language, "elvish") << "High Elf should speak Elvish";
            }
        }
    }
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
