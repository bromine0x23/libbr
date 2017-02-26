#include "../test.hpp"
#include <libbr/random/independent_bits_engine.hpp>
#include <libbr/random/mt19937.hpp>
#include <libbr/random/mt19937_64.hpp>
#include <libbr/random/ranlux24.hpp>
#include <libbr/random/ranlux48.hpp>

using namespace BR;

TEST(Random, IndependentBitsEngine) {
	{
		IndependentBitsEngine< Ranlux24, 24, UInt32 > engine(233);
		EXPECT_EQ(0xFFFFFFU, engine.max());
		EXPECT_EQ(0x000000U, engine.min());
		EXPECT_EQ(0x3597D6U, engine());
		EXPECT_EQ(0xF44C24U, engine());
		engine.discard(2);
		EXPECT_EQ(0xC104AFU, engine());
		EXPECT_EQ(0xBB673FU, engine());
	} {
		IndependentBitsEngine< Ranlux24, 28, UInt32 > engine(233);
		EXPECT_EQ(0xFFFFFFFU, engine.max());
		EXPECT_EQ(0x0000000U, engine.min());
		EXPECT_EQ(0x5F58C24U, engine());
		EXPECT_EQ(0x68CC74CU, engine());
		engine.discard(2);
		EXPECT_EQ(0xC2FBF8BU, engine());
		EXPECT_EQ(0xDEF46FFU, engine());
	} {
		IndependentBitsEngine< Ranlux24, 32, UInt32 > engine(233);
		EXPECT_EQ(0xFFFFFFFFU, engine.max());
		EXPECT_EQ(0x00000000U, engine.min());
		EXPECT_EQ(0x97D64C24U, engine());
		EXPECT_EQ(0x9A33074CU, engine());
		engine.discard(2);
		EXPECT_EQ(0xB0BE3F8BU, engine());
		EXPECT_EQ(0x77BD46FFU, engine());
	} {
		IndependentBitsEngine< MT19937, 32, UInt32 > engine(233);
		EXPECT_EQ(0xFFFFFFFFU, engine.max());
		EXPECT_EQ(0x00000000U, engine.min());
		EXPECT_EQ(0x26439BE7U, engine());
		EXPECT_EQ(0x7D120F27U, engine());
		engine.discard(2);
		EXPECT_EQ(0x954A57FCU, engine());
		EXPECT_EQ(0x8FEA4483U, engine());
	} {
		IndependentBitsEngine< Ranlux48, 48, UInt64 > engine(233);
		EXPECT_EQ(0xFFFFFFFFFFFFULL, engine.max());
		EXPECT_EQ(0x000000000000ULL, engine.min());
		EXPECT_EQ(0x4C243F3597D6ULL, engine());
		EXPECT_EQ(0x074D74CC9A34ULL, engine());
		engine.discard(2);
		EXPECT_EQ(0x3F8AF3ADB0BFULL, engine());
		EXPECT_EQ(0x46FFE8DE77BDULL, engine());
	} {
		IndependentBitsEngine< Ranlux48, 56, UInt64 > engine(233);
		EXPECT_EQ(0xFFFFFFFFFFFFFFULL, engine.max());
		EXPECT_EQ(0x00000000000000ULL, engine.min());
		EXPECT_EQ(0xF3597D64CC9A34ULL, engine());
		EXPECT_EQ(0xAC104AF1DFDC3EULL, engine());
		engine.discard(2);
		EXPECT_EQ(0x2998A52F863902ULL, engine());
		EXPECT_EQ(0xDB271EEC385513ULL, engine());
	} {
		IndependentBitsEngine< Ranlux48, 64, UInt64 > engine(233);
		EXPECT_EQ(0xFFFFFFFFFFFFFFFFULL, engine.max());
		EXPECT_EQ(0x0000000000000000ULL, engine.min());
		EXPECT_EQ(0x3F3597D674CC9A34ULL, engine());
		EXPECT_EQ(0x2AC104AFB1DFDC3EULL, engine());
		engine.discard(2);
		EXPECT_EQ(0x32998A528F863902ULL, engine());
		EXPECT_EQ(0xBDB271EE0C385513ULL, engine());
	} {
		IndependentBitsEngine< MT19937_64, 64, UInt64 > engine(233);
		EXPECT_EQ(0xFFFFFFFFFFFFFFFFULL, engine.max());
		EXPECT_EQ(0x0000000000000000ULL, engine.min());
		EXPECT_EQ(0xE1A9DB5D833E02F9ULL, engine());
		EXPECT_EQ(0xCE66D897E298C671ULL, engine());
		engine.discard(2);
		EXPECT_EQ(0xE64EFB1F851F1817ULL, engine());
		EXPECT_EQ(0x9BDB9C55AD7A7F70ULL, engine());
	}
}