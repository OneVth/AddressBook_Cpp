#include "pch.h"
#include <gtest/gtest.h>
#include "..\AddressBook_Cpp\include\common.h"

TEST(ValidatorTest, TestIsAllDigit)
{
	EXPECT_TRUE(Validator::IsAllDigit("12345"));	// Pass
	EXPECT_FALSE(Validator::IsAllDigit("123a5"));	// Fail	
	EXPECT_FALSE(Validator::IsAllDigit("1@345"));	// Fail	
	EXPECT_FALSE(Validator::IsAllDigit(""));		// Fail
}

TEST(ValidatorTest, TestIsAllAlpha)
{
	EXPECT_TRUE(Validator::IsAllAlpha("abcDEF"));	// Pass
	EXPECT_FALSE(Validator::IsAllAlpha("abc123"));	// Fail
	EXPECT_FALSE(Validator::IsAllAlpha("abc DEF"));	// Fail
	EXPECT_FALSE(Validator::IsAllAlpha(""));	// Fail
}

TEST(ValidatorTest, TestIsPhoneFormat)
{
	EXPECT_TRUE(Validator::IsPhoneFormat("000-0000-0000"));		// Pass
	EXPECT_FALSE(Validator::IsPhoneFormat("0000-0000-0000"));	// Fail
	EXPECT_FALSE(Validator::IsPhoneFormat("000-aaaa-0000"));	// Fail
	EXPECT_FALSE(Validator::IsPhoneFormat(""));	// Fail
}