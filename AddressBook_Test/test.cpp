#include "pch.h"
#include <gtest/gtest.h>
#include "..\AddressBook_Cpp\include\common.h"

TEST(ValidatorTest, TestIsAllDigit)
{
	EXPECT_TRUE(Validator::IsAllDigit("12345"));
	EXPECT_FALSE(Validator::IsAllDigit("123a5"));
	EXPECT_FALSE(Validator::IsAllDigit(""));
}