#include <cstdio>
#include <iostream>
#include "test.hpp"
#include <libbr/libbr.hpp>

auto main(int argc, char * argv[]) -> int {
	::testing::InitGoogleTest(&argc, argv);
	puts(BR_COMPILER);
	puts(BR_PLATFORM);
	puts(BR_STANDARD);
	std::cout << sizeof(BR::RawString<BR::NChar>) << std::endl;
	return RUN_ALL_TESTS();
}
