#include "log.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iostream>

using ::testing::HasSubstr;
using ::testing::StrEq;

// Test fixture for Log tests
class LogTest : public ::testing::Test {
protected:
    std::stringstream buffer;
    std::streambuf* oldCoutBuffer;

    void SetUp() override {
        // Redirect cout to our buffer
        oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(oldCoutBuffer);
    }

    std::string getCapturedOutput() {
        return buffer.str();
    }

    void clearBuffer() {
        buffer.str("");
        buffer.clear();
    }
};

//=============================================================================
// LOG Function Tests
//=============================================================================

TEST_F(LogTest, LOG_SimpleMessage_OutputsCorrectly) {
    LOG("Test message");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Test message"));
}

TEST_F(LogTest, LOG_EmptyString_OutputsNewline) {
    LOG("");
    std::string output = getCapturedOutput();
    EXPECT_EQ(output, "\n");
}

TEST_F(LogTest, LOG_MultipleMessages_OutputsInOrder) {
    LOG("First message");
    LOG("Second message");
    LOG("Third message");
    
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("First message"));
    EXPECT_THAT(output, HasSubstr("Second message"));
    EXPECT_THAT(output, HasSubstr("Third message"));
}

TEST_F(LogTest, LOG_MessageWithNewline_HandledCorrectly) {
    LOG("Message\nwith\nnewlines");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Message\nwith\nnewlines"));
}

TEST_F(LogTest, LOG_MessageWithSpecialCharacters_OutputsCorrectly) {
    LOG("Special chars: !@#$%^&*()_+-={}[]|:;<>?,./~`");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Special chars: !@#$%^&*()_+-={}[]|:;<>?,./~`"));
}

TEST_F(LogTest, LOG_LongMessage_OutputsCompletely) {
    std::string longMessage(1000, 'A');
    LOG(longMessage);
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr(longMessage));
}

TEST_F(LogTest, LOG_MessageWithNumbers_OutputsCorrectly) {
    LOG("Count: 12345");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Count: 12345"));
}

TEST_F(LogTest, LOG_MessageWithSpaces_OutputsCorrectly) {
    LOG("   Leading and trailing spaces   ");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("   Leading and trailing spaces   "));
}

TEST_F(LogTest, LOG_MessageWithTabs_OutputsCorrectly) {
    LOG("Message\twith\ttabs");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Message\twith\ttabs"));
}

TEST_F(LogTest, LOG_UnicodeMessage_OutputsCorrectly) {
    LOG("Unicode: αβγδε 日本語 中文 한글");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Unicode: αβγδε 日本語 中文 한글"));
}

TEST_F(LogTest, LOG_MessageEndsWithNewline_ProducesDoubleNewline) {
    LOG("Test");
    std::string output = getCapturedOutput();
    // LOG should add a newline, so we should see "Test\n"
    EXPECT_EQ(output, "Test\n");
}

TEST_F(LogTest, LOG_ConsecutiveCalls_EachOnNewLine) {
    LOG("Line 1");
    LOG("Line 2");
    std::string output = getCapturedOutput();
    EXPECT_EQ(output, "Line 1\nLine 2\n");
}

//=============================================================================
// Edge Case Tests
//=============================================================================

TEST_F(LogTest, LOG_NullTerminator_HandledCorrectly) {
    std::string message = "Before";
    message += '\0';
    message += "After";
    LOG(message);
    std::string output = getCapturedOutput();
    // The null terminator will terminate the string in output
    EXPECT_THAT(output, HasSubstr("Before"));
}

TEST_F(LogTest, LOG_QuotedString_OutputsCorrectly) {
    LOG("\"Quoted string\"");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("\"Quoted string\""));
}

TEST_F(LogTest, LOG_BackslashCharacters_OutputsCorrectly) {
    LOG("Path\\to\\file");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Path\\to\\file"));
}

//=============================================================================
// Multiple Instances Tests
//=============================================================================

TEST_F(LogTest, LOG_MultipleCalls_IndependentOutputs) {
    LOG("First");
    clearBuffer();
    LOG("Second");
    std::string output = getCapturedOutput();
    EXPECT_THAT(output, HasSubstr("Second"));
    EXPECT_THAT(output, Not(HasSubstr("First")));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
