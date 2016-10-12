#include <cstdio>
#include "test.hpp"
#include <libbr/libbr.hpp>

auto main(int argc, char * argv[]) -> int {
	::testing::InitGoogleTest(&argc, argv);
	puts(BR_COMPILER);
	puts(BR_PLATFORM);
	puts(BR_STANDARD);
	return RUN_ALL_TESTS();
}
