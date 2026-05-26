#include "playerInput.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iostream>

using ::testing::UnorderedElementsAre;
using ::testing::Contains;
using ::testing::ElementsAre;
using ::testing::IsEmpty;
using ::testing::SizeIs;

// Test fixture for PlayerInput tests
class PlayerInputTest : public ::testing::Test {
protected:
    std::streambuf* cinbuf;
    std::istringstream testInput;
    
    void SetUp() override {
        // Save original cin buffer
        cinbuf = std::cin.rdbuf();
    }
    
    void TearDown() override {
        // Restore original cin buffer
        std::cin.rdbuf(cinbuf);
    }
    
    // Helper function to simulate user input
    void simulateInput(const std::string& input) {
        testInput.str(input);
        testInput.clear();
        std::cin.rdbuf(testInput.rdbuf());
    }
};

// ============================================================================
// BASIC FUNCTIONALITY TESTS
// ============================================================================

TEST_F(PlayerInputTest, ChooseOneOptionFromThree) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    simulateInput("0\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, Contains("option1"));
}

TEST_F(PlayerInputTest, ChooseTwoOptionsFromThree) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    simulateInput("0\n1\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 2);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, Contains("option1"));
    EXPECT_THAT(result, Contains("option2"));
}

TEST_F(PlayerInputTest, ChooseAllOptions) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    simulateInput("0\n1\n2\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 3);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_THAT(result, UnorderedElementsAre("option1", "option2", "option3"));
}

TEST_F(PlayerInputTest, ChooseOptionsInOrder) {
    std::vector<std::string> options = {"first", "second", "third"};
    simulateInput("0\n1\n2\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 3);
    
    EXPECT_THAT(result, ElementsAre("first", "second", "third"));
}

TEST_F(PlayerInputTest, ChooseLastOption) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    simulateInput("2\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, Contains("option3"));
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

TEST_F(PlayerInputTest, ChooseCountExceedsOptionsSize) {
    std::vector<std::string> options = {"option1", "option2"};
    simulateInput("0\n1\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 5);
    
    // Should only return as many as available (2 options)
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, UnorderedElementsAre("option1", "option2"));
}

TEST_F(PlayerInputTest, ChooseCountEqualsOptionsSize) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    simulateInput("0\n1\n2\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 3);
    
    EXPECT_EQ(result.size(), 3);
}

TEST_F(PlayerInputTest, ChooseZeroOptions) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    simulateInput("");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 0);
    
    EXPECT_THAT(result, IsEmpty());
}

TEST_F(PlayerInputTest, SingleOptionVector) {
    std::vector<std::string> options = {"only_option"};
    simulateInput("0\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, Contains("only_option"));
}

// ============================================================================
// INVALID INPUT HANDLING TESTS
// ============================================================================

TEST_F(PlayerInputTest, InvalidChoiceThenValidChoice) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    // First input (5) is invalid (>= options.size()), then valid input (1)
    simulateInput("5\n1\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, Contains("option2"));
}

TEST_F(PlayerInputTest, MultipleInvalidChoicesThenValid) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    // Multiple invalid inputs (10, 99) then valid (0)
    simulateInput("10\n99\n0\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, Contains("option1"));
}

TEST_F(PlayerInputTest, DuplicateChoiceThenDifferentChoice) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    // Choose 0, then try 0 again (duplicate), then choose 1
    simulateInput("0\n0\n1\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 2);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, UnorderedElementsAre("option1", "option2"));
}

TEST_F(PlayerInputTest, MultipleDuplicateAttempts) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    // Choose 0, then try 0 twice more (duplicates), then choose 1
    simulateInput("0\n0\n0\n1\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 2);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, UnorderedElementsAre("option1", "option2"));
}

TEST_F(PlayerInputTest, MixedInvalidAndDuplicateInputs) {
    std::vector<std::string> options = {"option1", "option2", "option3"};
    // Choose 0, then invalid (10), then duplicate (0), then valid (1)
    simulateInput("0\n10\n0\n1\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 2);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, UnorderedElementsAre("option1", "option2"));
}

// ============================================================================
// COMPLEX SELECTION TESTS
// ============================================================================

TEST_F(PlayerInputTest, ChooseNonSequentialOptions) {
    std::vector<std::string> options = {"opt0", "opt1", "opt2", "opt3", "opt4"};
    simulateInput("4\n0\n2\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 3);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_THAT(result, ElementsAre("opt4", "opt0", "opt2"));
}

TEST_F(PlayerInputTest, ChooseReverseOrder) {
    std::vector<std::string> options = {"first", "second", "third"};
    simulateInput("2\n1\n0\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 3);
    
    EXPECT_THAT(result, ElementsAre("third", "second", "first"));
}

TEST_F(PlayerInputTest, LargeOptionSet) {
    std::vector<std::string> options;
    for (int i = 0; i < 10; i++) {
        options.push_back("option" + std::to_string(i));
    }
    simulateInput("0\n5\n9\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 3);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_THAT(result, ElementsAre("option0", "option5", "option9"));
}

// ============================================================================
// STRING CONTENT TESTS
// ============================================================================

TEST_F(PlayerInputTest, OptionsWithSpecialCharacters) {
    std::vector<std::string> options = {"option-1", "option_2", "option.3"};
    simulateInput("0\n1\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 2);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, UnorderedElementsAre("option-1", "option_2"));
}

TEST_F(PlayerInputTest, OptionsWithSpaces) {
    std::vector<std::string> options = {"option one", "option two", "option three"};
    simulateInput("1\n2\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 2);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, UnorderedElementsAre("option two", "option three"));
}

TEST_F(PlayerInputTest, LongStringOptions) {
    std::vector<std::string> options = {
        "this_is_a_very_long_option_string_for_testing",
        "another_long_option_string",
        "yet_another_one"
    };
    simulateInput("0\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 1);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_THAT(result, Contains("this_is_a_very_long_option_string_for_testing"));
}

// ============================================================================
// INTEGRATION TESTS
// ============================================================================

TEST_F(PlayerInputTest, CompleteWorkflowWithValidInputs) {
    std::vector<std::string> options = {"race1", "race2", "race3", "race4", "race5"};
    simulateInput("1\n3\n4\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 3);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_THAT(result, ElementsAre("race2", "race4", "race5"));
}

TEST_F(PlayerInputTest, CompleteWorkflowWithMixedValidAndInvalidInputs) {
    std::vector<std::string> options = {"ability1", "ability2", "ability3"};
    // Invalid (10), valid (0), duplicate (0), invalid (5), valid (2)
    simulateInput("10\n0\n0\n5\n2\n");
    
    std::vector<std::string> result = getPlayerInputOptionChoices(options, 2);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_THAT(result, ElementsAre("ability1", "ability3"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
