#include <cstdio>
#include <gtest/gtest.h>
#include <libbr/libbr.hpp>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	puts(BR_COMPILER);
	puts(BR_PLATFORM);

	return RUN_ALL_TESTS();
}
