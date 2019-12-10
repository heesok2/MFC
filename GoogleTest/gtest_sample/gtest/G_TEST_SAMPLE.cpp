#include "pch.h"

#pragma comment(lib, "gtest_lib.lib")

extern "C" __declspec(dllimport) int doubleNum(int x);

TEST(G_TEST_SAMPLE, ALL_PASS)
{
	ASSERT_EQ(12, doubleNum(6));
}