#include <cstdio>
#include <iostream>
#include "test.hpp"
#include <libbr/libbr.hpp>

auto main(int argc, char * argv[]) -> int {
	printf("Standard: %s\n", BR_STANDARD);
	printf("Compiler: %s\n", BR_COMPILER);
#if defined(BR_GCC)
	printf("GCC: %d\n", BR_GCC_FULL_VER);
#endif
#if defined(BR_CLANG)
	printf("Clang: %d\n", BR_CLANG_VER);
#endif
#if defined(BR_MSVC)
	printf("MSVC: %d\n", BR_MSVC_FULL_VER);
#endif
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
