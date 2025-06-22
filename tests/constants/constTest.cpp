#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

#include "fourdst/constants/const.h"

/**
 * @file constTest.cpp
 * @brief Unit tests for the const class.
 */

/**
 * @brief Test suite for the const class.
 */
class constTest : public ::testing::Test {
protected:
    void SetUp() override {
        fourdst::constant::Constants::getInstance();
    }
};

/**
 * @test Verify default constructor initializes correctly.
 */
TEST_F(constTest, DefaultConstructor) {
    EXPECT_NO_THROW(fourdst::constant::Constants::getInstance());
}

/**
 * @test Verify constructor initializes with provided data and metadata.
 */
TEST_F(constTest, isLoaded) {

    EXPECT_NO_THROW(fourdst::constant::Constants::getInstance().isLoaded());
}

/**
 * @test Verify get method returns the correct constant.
 */
TEST_F(constTest, GetMethod) {
    fourdst::constant::Constants& obj = fourdst::constant::Constants::getInstance();
    EXPECT_DOUBLE_EQ(obj.get("c").value, 2.99792458e10);
    EXPECT_EQ(obj.get("c").unit, "cm / s");
    EXPECT_DOUBLE_EQ(obj.get("c").uncertainty, 0.0);
    EXPECT_EQ(obj.get("c").reference, "CODATA2022");
}

/**
 * @test Verify [] opperators returns the correct constant.
 */
TEST_F(constTest, SubscriptOperator) {
    fourdst::constant::Constants& obj = fourdst::constant::Constants::getInstance();
    EXPECT_DOUBLE_EQ(obj["c"].value, 2.99792458e10);
    EXPECT_EQ(obj["c"].unit, "cm / s");
    EXPECT_DOUBLE_EQ(obj["c"].uncertainty, 0.0);
    EXPECT_EQ(obj["c"].reference, "CODATA2022");
}

/**
 * @test Verify that the has method returns the correct values
 */
TEST_F(constTest, HasMethod) {
    fourdst::constant::Constants& obj = fourdst::constant::Constants::getInstance();

    EXPECT_TRUE(obj.has("c"));
    EXPECT_FALSE(obj.has("c4"));
    EXPECT_TRUE(obj.has("hbar"));
}

TEST_F(constTest, KeysMethod) {
    fourdst::constant::Constants& obj = fourdst::constant::Constants::getInstance();
    std::set<std::string> checkKeys;
    checkKeys.insert("c");
    checkKeys.insert("wienK");
    checkKeys.insert("hbar");
    checkKeys.insert("g_h");
    checkKeys.insert("R_sun");

    std::set<std::string> keys = obj.keys();

    for (const auto& key : checkKeys) {
        bool found = keys.find(key) != keys.end();
        EXPECT_TRUE(found);
    }

    std::set<std::string> checkBadKeys;
    checkBadKeys.insert("c4");
    checkBadKeys.insert("wienK4");
    checkBadKeys.insert("hbar4");
    checkBadKeys.insert("g_h4");
    checkBadKeys.insert("R_sun4");

    for (const auto& key : checkBadKeys) {
        bool found = keys.find(key) != keys.end();
        EXPECT_FALSE(found);
    }
}

TEST_F(constTest, StreamOperator) {
    fourdst::constant::Constants& obj = fourdst::constant::Constants::getInstance();
    std::ostringstream os;

    os << obj.get("c");
    std::string expected = "<speed of light in vacuum: 2.99792e+10±0 cm / s (CODATA2022)>\n";

    EXPECT_EQ(os.str(), expected);
}
