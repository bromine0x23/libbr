#include <cstdio>
#include <iostream>
#include <iomanip>
#include <libbr.hpp>

#include "math/test_math.hpp"

int main() {
	
	puts(BR_COMPILER);
	puts(BR_PLATFORM);
	puts(BR_BYTE_ORDER);

	test_float();

	return 0;
}
