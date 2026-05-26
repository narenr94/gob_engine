#include "randomize.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>
#include <set>

using ::testing::Eq;
using ::testing::Ne;
using ::testing::Ge;
using ::testing::Le;
using ::testing::IsEmpty;
using ::testing::Contains;

// Test fixture for Randomize tests
class RandomizeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

//=============================================================================
// rollDie Tests
//=============================================================================

TEST_F(RandomizeTest, RollDie_DefaultSixSided_ReturnsValueInRange) {
    for (int i = 0; i < 100; ++i) {
        unsigned short int result = rollDie();
        EXPECT_GE(result, 1) << "Die roll should be at least 1";
        EXPECT_LE(result, 6) << "Die roll should be at most 6";
    }
}

TEST_F(RandomizeTest, RollDie_FourSided_ReturnsValueInRange) {
    for (int i = 0; i < 100; ++i) {
        unsigned short int result = rollDie(4);
        EXPECT_GE(result, 1) << "4-sided die roll should be at least 1";
        EXPECT_LE(result, 4) << "4-sided die roll should be at most 4";
    }
}

TEST_F(RandomizeTest, RollDie_TwentySided_ReturnsValueInRange) {
    for (int i = 0; i < 100; ++i) {
        unsigned short int result = rollDie(20);
        EXPECT_GE(result, 1) << "20-sided die roll should be at least 1";
        EXPECT_LE(result, 20) << "20-sided die roll should be at most 20";
    }
}

TEST_F(RandomizeTest, RollDie_OneSided_ReturnsOne) {
    for (int i = 0; i < 10; ++i) {
        unsigned short int result = rollDie(1);
        EXPECT_EQ(result, 1) << "1-sided die should always return 1";
    }
}

TEST_F(RandomizeTest, RollDie_TenSided_CoversAllValues) {
    std::set<unsigned short int> results;
    // Roll enough times to likely hit all values
    for (int i = 0; i < 500; ++i) {
        results.insert(rollDie(10));
    }
    // We should see multiple different values
    EXPECT_GT(results.size(), 5) << "Should see variety in die rolls";
}

TEST_F(RandomizeTest, RollDie_OneHundredSided_ReturnsValueInRange) {
    for (int i = 0; i < 50; ++i) {
        unsigned short int result = rollDie(100);
        EXPECT_GE(result, 1) << "100-sided die roll should be at least 1";
        EXPECT_LE(result, 100) << "100-sided die roll should be at most 100";
    }
}

//=============================================================================
// chooseRandomOptions Tests
//=============================================================================

TEST_F(RandomizeTest, ChooseRandomOptions_EmptyInput_ReturnsEmpty) {
    std::vector<std::string> empty;
    auto result = chooseRandomOptions(empty, 5);
    EXPECT_THAT(result, IsEmpty());
}

TEST_F(RandomizeTest, ChooseRandomOptions_CountZero_ReturnsEmpty) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    auto result = chooseRandomOptions(options, 0);
    EXPECT_THAT(result, IsEmpty());
}

TEST_F(RandomizeTest, ChooseRandomOptions_CountEqualsSize_ReturnsAll) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    auto result = chooseRandomOptions(options, 3);
    
    EXPECT_EQ(result.size(), 3);
    // All options should be present
    for (const auto& option : options) {
        EXPECT_THAT(result, Contains(option));
    }
}

TEST_F(RandomizeTest, ChooseRandomOptions_CountGreaterThanSize_ReturnsAll) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    auto result = chooseRandomOptions(options, 10);
    
    EXPECT_EQ(result.size(), 3);
    // All options should be present
    for (const auto& option : options) {
        EXPECT_THAT(result, Contains(option));
    }
}

TEST_F(RandomizeTest, ChooseRandomOptions_SingleSelection_ReturnsOneElement) {
    std::vector<std::string> options = {"option1", "option2", "option3", "option4", "option5"};
    auto result = chooseRandomOptions(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(options, Contains(result[0]));
}

TEST_F(RandomizeTest, ChooseRandomOptions_PartialSelection_ReturnsCorrectCount) {
    std::vector<std::string> options = {"option1", "option2", "option3", "option4", "option5"};
    auto result = chooseRandomOptions(options, 3);
    
    EXPECT_EQ(result.size(), 3);
    // All returned options should be from the original list
    for (const auto& selected : result) {
        EXPECT_THAT(options, Contains(selected));
    }
}

TEST_F(RandomizeTest, ChooseRandomOptions_NoDuplicates) {
    std::vector<std::string> options = {"option1", "option2", "option3", "option4", "option5"};
    auto result = chooseRandomOptions(options, 3);
    
    // Check for uniqueness
    std::set<std::string> uniqueResults(result.begin(), result.end());
    EXPECT_EQ(uniqueResults.size(), result.size()) 
        << "Result should not contain duplicates";
}

TEST_F(RandomizeTest, ChooseRandomOptions_IsRandom) {
    std::vector<std::string> options = {"option1", "option2", "option3", "option4", "option5"};
    
    // Run multiple times and check that we don't always get the same result
    std::set<std::string> firstElements;
    for (int i = 0; i < 20; ++i) {
        auto result = chooseRandomOptions(options, 2);
        if (!result.empty()) {
            firstElements.insert(result[0]);
        }
    }
    
    // If truly random, we should see more than one distinct first element
    EXPECT_GT(firstElements.size(), 1) 
        << "Should see variety in random selection";
}

TEST_F(RandomizeTest, ChooseRandomOptions_SingleOption_ReturnsThatOption) {
    std::vector<std::string> options = {"only_option"};
    auto result = chooseRandomOptions(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "only_option");
}

TEST_F(RandomizeTest, ChooseRandomOptions_LargeSelection_ReturnsCorrectCount) {
    std::vector<std::string> options;
    for (int i = 0; i < 100; ++i) {
        options.push_back("option" + std::to_string(i));
    }
    
    auto result = chooseRandomOptions(options, 50);
    
    EXPECT_EQ(result.size(), 50);
    
    // Check uniqueness
    std::set<std::string> uniqueResults(result.begin(), result.end());
    EXPECT_EQ(uniqueResults.size(), 50);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
