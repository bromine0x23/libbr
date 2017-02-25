#include "../test.hpp"
#include <libbr/random/independent_bits_engine.hpp>
#include <libbr/random/discard_block_engine.hpp>
#include <libbr/random/mersenne_twister_engine.hpp>

using namespace BR;

TEST(IndependentBitsEngine, Ranlux24) {
	IndependentBitsEngine< Ranlux24, 24, UInt32 > engine(233);
	EXPECT_EQ(0x3597D6U, engine());
	EXPECT_EQ(0xF44C24U, engine());
	engine.discard(2);
	EXPECT_EQ(0xC104AFU, engine());
	EXPECT_EQ(0xBB673FU, engine());
}

TEST(IndependentBitsEngine, Ranlux24_28) {
	IndependentBitsEngine< Ranlux24, 28, UInt32 > engine(233);
	EXPECT_EQ(0x5F58C24U, engine());
	EXPECT_EQ(0x68CC74CU, engine());
	engine.discard(2);
	EXPECT_EQ(0xC2FBF8BU, engine());
	EXPECT_EQ(0xDEF46FFU, engine());
}

TEST(IndependentBitsEngine, Ranlux24_32) {
	IndependentBitsEngine< Ranlux24, 32, UInt32 > engine(233);
	EXPECT_EQ(0x97D64C24U, engine());
	EXPECT_EQ(0x9A33074CU, engine());
	engine.discard(2);
	EXPECT_EQ(0xB0BE3F8BU, engine());
	EXPECT_EQ(0x77BD46FFU, engine());
}

TEST(IndependentBitsEngine, MT19937) {
	IndependentBitsEngine< MT19937, 32, UInt32 > engine(233);
	EXPECT_EQ(0x26439BE7U, engine());
	EXPECT_EQ(0x7D120F27U, engine());
	engine.discard(2);
	EXPECT_EQ(0x954A57FCU, engine());
	EXPECT_EQ(0x8FEA4483U, engine());
}

TEST(IndependentBitsEngine, Ranlux48) {
	IndependentBitsEngine< Ranlux48, 48, UInt64 > engine(233);
	EXPECT_EQ(0x4C243F3597D6ULL, engine());
	EXPECT_EQ(0x074D74CC9A34ULL, engine());
	engine.discard(2);
	EXPECT_EQ(0x3F8AF3ADB0BFULL, engine());
	EXPECT_EQ(0x46FFE8DE77BDULL, engine());
}

TEST(IndependentBitsEngine, Ranlux48_56) {
	IndependentBitsEngine< Ranlux48, 56, UInt64 > engine(233);
	EXPECT_EQ(0xF3597D64CC9A34ULL, engine());
	EXPECT_EQ(0xAC104AF1DFDC3EULL, engine());
	engine.discard(2);
	EXPECT_EQ(0x2998A52F863902ULL, engine());
	EXPECT_EQ(0xDB271EEC385513ULL, engine());
}

TEST(IndependentBitsEngine, Ranlux48_64) {
	IndependentBitsEngine< Ranlux48, 64, UInt64 > engine(233);
	EXPECT_EQ(0x3F3597D674CC9A34ULL, engine());
	EXPECT_EQ(0x2AC104AFB1DFDC3EULL, engine());
	engine.discard(2);
	EXPECT_EQ(0x32998A528F863902ULL, engine());
	EXPECT_EQ(0xBDB271EE0C385513ULL, engine());
}

TEST(IndependentBitsEngine, MT19937_64) {
	IndependentBitsEngine< MT19937_64, 64, UInt64 > engine(233);
	EXPECT_EQ(0xE1A9DB5D833E02F9ULL, engine());
	EXPECT_EQ(0xCE66D897E298C671ULL, engine());
	engine.discard(2);
	EXPECT_EQ(0xE64EFB1F851F1817ULL, engine());
	EXPECT_EQ(0x9BDB9C55AD7A7F70ULL, engine());
}