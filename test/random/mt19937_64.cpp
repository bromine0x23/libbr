#include "../test.hpp"
#include <libbr/random/mt19937_64.hpp>

using namespace BR;

TEST(Random, MT19937_64) {
	{
		MT19937_64 engine;
		engine.discard(9999);
		EXPECT_EQ(0x8A8592F5817ED872ULL, engine());
	} {
		MT19937_64 engine(233);
		EXPECT_EQ(0xFFFFFFFFFFFFFFFFULL, engine.max());
		EXPECT_EQ(0x0000000000000000ULL, engine.min());
		EXPECT_EQ(0xE1A9DB5D833E02F9ULL, engine());
		EXPECT_EQ(0xCE66D897E298C671ULL, engine());
		engine.discard(2);
		EXPECT_EQ(0xE64EFB1F851F1817ULL, engine());
		EXPECT_EQ(0x9BDB9C55AD7A7F70ULL, engine());
	}
}