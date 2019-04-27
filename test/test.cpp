#include <cstdio>
#include <iostream>
#include "test.hpp"
#include <libbr/libbr.hpp>

auto main(int argc, char * argv[]) -> int {
	printf("Standard = %s\n", BR_STANDARD);
	printf("Compiler = %s\n", BR_COMPILER);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
