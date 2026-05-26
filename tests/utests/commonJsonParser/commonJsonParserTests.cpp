#include "commonJsonParser.h"
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

// Test fixture for CommonJsonParser tests
class CommonJsonParserTest : public ::testing::Test {
protected:
    static std::string testDataPath;
    static std::string testRacesPath;

    // SetUpTestSuite runs once before all tests in this fixture
    static void SetUpTestSuite() {
        testDataPath = "test_common_json_parser_temp";
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
        createInvalidJson();
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

    static void createInvalidJson() {
        std::ofstream file(testDataPath + "/invalid.json");
        file << "{\"invalid_key\": \"value\"}";
        file.close();
    }

    static void createTestRaces() {
        // Create human (non-abstract)
        std::ofstream human(testRacesPath + "/human.json");
        human << "{\n";
        human << "  \"name\": \"human\",\n";
        human << "  \"is_abstract\": false,\n";
        human << "  \"base_race\": null\n";
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

        // Create high_elf (non-abstract)
        std::ofstream high_elf(testRacesPath + "/high_elf.json");
        high_elf << "{\n";
        high_elf << "  \"name\": \"high_elf\",\n";
        high_elf << "  \"is_abstract\": false,\n";
        high_elf << "  \"base_race\": null\n";
        high_elf << "}";
        high_elf.close();

        // Create dwarf (non-abstract)
        std::ofstream dwarf(testRacesPath + "/dwarf.json");
        dwarf << "{\n";
        dwarf << "  \"name\": \"dwarf\",\n";
        dwarf << "  \"is_abstract\": false,\n";
        dwarf << "  \"base_race\": null\n";
        dwarf << "}";
        dwarf.close();

        // Create halfling (non-abstract)
        std::ofstream halfling(testRacesPath + "/halfling.json");
        halfling << "{\n";
        halfling << "  \"name\": \"halfling\",\n";
        halfling << "  \"is_abstract\": false,\n";
        halfling << "  \"base_race\": null\n";
        halfling << "}";
        halfling.close();
    }
};

// Initialize static members
std::string CommonJsonParserTest::testDataPath;
std::string CommonJsonParserTest::testRacesPath;

// ============================================================================
// readJsonFile TESTS
// ============================================================================

TEST_F(CommonJsonParserTest, ReadValidJsonFile) {
    json j;
    std::string filePath = testDataPath + "/abilities.json";
    
    bool result = readJsonFile(filePath, j);
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(j.empty());
    EXPECT_TRUE(j.contains("abilities"));
}

TEST_F(CommonJsonParserTest, ReadNonExistentFile) {
    json j;
    std::string filePath = testDataPath + "/nonexistent.json";
    
    bool result = readJsonFile(filePath, j);
    
    EXPECT_FALSE(result);
}

TEST_F(CommonJsonParserTest, ReadJsonFilePopulatesJsonObject) {
    json j;
    std::string filePath = testDataPath + "/params.json";
    
    bool result = readJsonFile(filePath, j);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(j.contains("params"));
    EXPECT_TRUE(j["params"].is_array());
}

// ============================================================================
// extractAndApplyAbilities TESTS
// ============================================================================

TEST_F(CommonJsonParserTest, ExtractAbilitiesFromValidFile) {
    std::string filePath = testDataPath + "/abilities.json";
    
    std::vector<std::string> abilities = extractAndApplyAbilities(filePath);
    
    EXPECT_EQ(abilities.size(), 6);
    EXPECT_THAT(abilities, UnorderedElementsAre("strength", "dexterity", "constitution", 
                                                  "intelligence", "wisdom", "charisma"));
}

TEST_F(CommonJsonParserTest, ExtractAbilitiesNotEmpty) {
    std::string filePath = testDataPath + "/abilities.json";
    
    std::vector<std::string> abilities = extractAndApplyAbilities(filePath);
    
    EXPECT_FALSE(abilities.empty());
    EXPECT_GE(abilities.size(), 1);
}

TEST_F(CommonJsonParserTest, ExtractAbilitiesThrowsOnNonExistentFile) {
    std::string filePath = testDataPath + "/nonexistent.json";
    
    EXPECT_THROW({
        extractAndApplyAbilities(filePath);
    }, std::runtime_error);
}

TEST_F(CommonJsonParserTest, ExtractAbilitiesThrowsOnInvalidKey) {
    std::string filePath = testDataPath + "/invalid.json";
    
    EXPECT_THROW({
        extractAndApplyAbilities(filePath);
    }, std::runtime_error);
}

// ============================================================================
// extractAndApplyParams TESTS
// ============================================================================

TEST_F(CommonJsonParserTest, ExtractParamsFromValidFile) {
    std::string filePath = testDataPath + "/params.json";
    
    std::vector<std::string> params = extractAndApplyParams(filePath);
    
    EXPECT_EQ(params.size(), 3);
    EXPECT_THAT(params, UnorderedElementsAre("hit_points", "mana", "stamina"));
}

TEST_F(CommonJsonParserTest, ExtractParamsNotEmpty) {
    std::string filePath = testDataPath + "/params.json";
    
    std::vector<std::string> params = extractAndApplyParams(filePath);
    
    EXPECT_FALSE(params.empty());
}

TEST_F(CommonJsonParserTest, ExtractParamsThrowsOnNonExistentFile) {
    std::string filePath = testDataPath + "/nonexistent.json";
    
    EXPECT_THROW({
        extractAndApplyParams(filePath);
    }, std::runtime_error);
}

TEST_F(CommonJsonParserTest, ExtractParamsThrowsOnInvalidKey) {
    std::string filePath = testDataPath + "/invalid.json";
    
    EXPECT_THROW({
        extractAndApplyParams(filePath);
    }, std::runtime_error);
}

// ============================================================================
// extractAllLanguages TESTS
// ============================================================================

TEST_F(CommonJsonParserTest, ExtractLanguagesFromValidFile) {
    std::string filePath = testDataPath + "/languages.json";
    
    std::vector<std::string> languages = extractAllLanguages(filePath);
    
    EXPECT_EQ(languages.size(), 10);
    EXPECT_THAT(languages, Contains("common"));
    EXPECT_THAT(languages, Contains("elvish"));
    EXPECT_THAT(languages, Contains("dwarvish"));
    EXPECT_THAT(languages, Contains("draconic"));
}

TEST_F(CommonJsonParserTest, ExtractLanguagesNotEmpty) {
    std::string filePath = testDataPath + "/languages.json";
    
    std::vector<std::string> languages = extractAllLanguages(filePath);
    
    EXPECT_FALSE(languages.empty());
}

TEST_F(CommonJsonParserTest, ExtractLanguagesThrowsOnNonExistentFile) {
    std::string filePath = testDataPath + "/nonexistent.json";
    
    EXPECT_THROW({
        extractAllLanguages(filePath);
    }, std::runtime_error);
}

TEST_F(CommonJsonParserTest, ExtractLanguagesThrowsOnInvalidKey) {
    std::string filePath = testDataPath + "/invalid.json";
    
    EXPECT_THROW({
        extractAllLanguages(filePath);
    }, std::runtime_error);
}

// ============================================================================
// findAllRaces TESTS
// ============================================================================

TEST_F(CommonJsonParserTest, FindAllRacesInDirectory) {
    std::vector<std::string> races = findAllRaces(testRacesPath);
    
    EXPECT_GE(races.size(), 4);
    EXPECT_THAT(races, Contains("human"));
    EXPECT_THAT(races, Contains("high_elf"));
    EXPECT_THAT(races, Contains("dwarf"));
    EXPECT_THAT(races, Contains("halfling"));
}

TEST_F(CommonJsonParserTest, FindAllRacesExcludesAbstractRaces) {
    std::vector<std::string> races = findAllRaces(testRacesPath);
    
    // Should NOT include abstract race
    EXPECT_THAT(races, Not(Contains("elf")));
}

TEST_F(CommonJsonParserTest, FindAllRacesFromNonExistentDirectory) {
    std::vector<std::string> races = findAllRaces(testDataPath + "/nonexistent");
    
    EXPECT_TRUE(races.empty());
}

TEST_F(CommonJsonParserTest, FindAllRacesNotEmpty) {
    std::vector<std::string> races = findAllRaces(testRacesPath);
    
    EXPECT_FALSE(races.empty());
}

TEST_F(CommonJsonParserTest, FindAllRacesReturnsOnlyNonAbstract) {
    std::vector<std::string> races = findAllRaces(testRacesPath);
    
    // Verify count matches non-abstract races only
    // We created 5 races: human, elf (abstract), high_elf, dwarf, halfling
    // So we should have 4 non-abstract races
    EXPECT_EQ(races.size(), 4);
}

// ============================================================================
// ADDITIONAL INTEGRATION TESTS
// ============================================================================

TEST_F(CommonJsonParserTest, ReadAndParseDifferentJsonFiles) {
    json abilitiesJson;
    json paramsJson;
    json languagesJson;
    
    EXPECT_TRUE(readJsonFile(testDataPath + "/abilities.json", abilitiesJson));
    EXPECT_TRUE(readJsonFile(testDataPath + "/params.json", paramsJson));
    EXPECT_TRUE(readJsonFile(testDataPath + "/languages.json", languagesJson));
    
    EXPECT_TRUE(abilitiesJson.contains("abilities"));
    EXPECT_TRUE(paramsJson.contains("params"));
    EXPECT_TRUE(languagesJson.contains("languages"));
}

TEST_F(CommonJsonParserTest, ExtractFunctionsReturnConsistentResults) {
    // Test that calling functions multiple times returns consistent results
    std::string abilitiesPath = testDataPath + "/abilities.json";
    
    auto abilities1 = extractAndApplyAbilities(abilitiesPath);
    auto abilities2 = extractAndApplyAbilities(abilitiesPath);
    
    EXPECT_EQ(abilities1, abilities2);
}

// ============================================================================
// MAIN
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
