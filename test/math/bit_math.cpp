#include "../test.hpp"
#include <libbr/math/function/count_leading_zeros.hpp>
#include <libbr/math/function/count_trailing_zeros.hpp>
#include <libbr/math/function/count_ones.hpp>

using namespace BR;

TEST(BitMath, count_leading_zeros) {
	{
		UInt8 x = 0xAAU;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_leading_zeros_8(x));
			x >>= 1;
			++expect;
		} while (x != 0);
	} {
		UInt16 x = 0xAAAAU;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_leading_zeros_16(x));
			x >>= 1;
			++expect;
		} while (x != 0);
	} {
		UInt32 x = 0xAAAAAAAAU;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_leading_zeros_32(x));
			x >>= 1;
			++expect;
		} while (x != 0);
	} {
		UInt64 x = 0xAAAAAAAAAAAAAAAAULL;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_leading_zeros_64(x));
			x >>= 1;
			++expect;
		} while (x != 0);
	}
}

TEST(BitMath, count_ones) {
	{
		UInt8 x = 0xFFU;
		UInt8 expect = 8;
		do {
			EXPECT_EQ(expect, libbr_count_ones_8(x));
			x >>= 1;
			--expect;
		} while (x != 0);
	} {
		UInt16 x = 0xFFFFU;
		UInt8 expect = 16;
		do {
			EXPECT_EQ(expect, libbr_count_ones_16(x));
			x >>= 1;
			--expect;
		} while (x != 0);
	} {
		UInt32 x = 0xFFFFFFFFU;
		UInt8 expect = 32;
		do {
			EXPECT_EQ(expect, libbr_count_ones_32(x));
			x >>= 1;
			--expect;
		} while (x != 0);
	} {
		UInt64 x = 0xFFFFFFFFFFFFFFFFULL;
		UInt8 expect = 64;
		do {
			EXPECT_EQ(expect, libbr_count_ones_64(x));
			x >>= 1;
			--expect;
		} while (x != 0);
	}
}

TEST(BitMath, count_trailing_zeros) {
	{
		UInt8 x = 0x01U;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_trailing_zeros_8(x));
			x <<= 1;
			++expect;
		} while (x != 0x80U);
	} {
		UInt16 x = 0x01U;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_trailing_zeros_16(x));
			x <<= 1;
			++expect;
		} while (x != 0x8000U);
	} {
		UInt32 x = 0x01U;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_trailing_zeros_32(x));
			x <<= 1;
			++expect;
		} while (x != 0x80000000U);
	} {
		UInt64 x = 0x01U;
		UInt8 expect = 0;
		do {
			EXPECT_EQ(expect, libbr_count_trailing_zeros_64(x));
			x <<= 1;
			++expect;
		} while (x != 0x8000000000000000ULL);
	}
}


