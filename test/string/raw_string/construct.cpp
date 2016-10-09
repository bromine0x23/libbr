#include "../../test.hpp"
#include "../../support/allocator.hpp"
#include <libbr/string/raw_string.hpp>

using namespace BR;

using RS8  = RawString<Char8>;
using RS16 = RawString<Char16>;
using RS32 = RawString<Char32>;

TEST(RawString, DefaultConstruct) {
	{
		RS8 s();
	} {
		RS16 s();
	} {
		RS32 s();
	}
}

template< typename TString >
static void test_literal(TString s) {
	BR_FORCE_USE(s);
}

TEST(RawString, Literal) {
	test_literal("12345"_rs);
	test_literal(u8"高槻やよい"_rs);
	test_literal(u8"私はアイドル♡"_rs);
	test_literal(u"12345"_rs);
	test_literal(u"高槻やよい"_rs);
	test_literal(u"私はアイドル♡"_rs);
	test_literal(U"12345"_rs);
	test_literal(U"高槻やよい"_rs);
	test_literal(U"私はアイドル♡"_rs);
}

template< typename TString >
static void test_copy_construct(TString s) {
	TString ss = s;
	EXPECT_EQ(s, ss);
	EXPECT_LE(ss.size(), ss.capacity());
	EXPECT_EQ(s.allocator(), ss.allocator());
}

TEST(RawString, CopyConstruct) {
	test_copy_construct(RS8());
	test_copy_construct(""_rs);
	test_copy_construct("01"_rs);
	test_copy_construct("01234567890123456789012345678901234567890123456789012345678901234567890123456789"_rs);
	test_copy_construct(RS16());
	test_copy_construct(u""_rs);
	test_copy_construct(u"01"_rs);
	test_copy_construct(u"01234567890123456789012345678901234567890123456789012345678901234567890123456789"_rs);
	test_copy_construct(RS32());
	test_copy_construct(U""_rs);
	test_copy_construct(U"01"_rs);
	test_copy_construct(U"01234567890123456789012345678901234567890123456789012345678901234567890123456789"_rs);
}

template< typename TString >
static void test_move_construct(TString s) {
	TString ss = s;
	EXPECT_EQ(s, ss);
	EXPECT_LE(ss.size(), ss.capacity());
	EXPECT_EQ(s.allocator(), ss.allocator());
}

TEST(RawString, MoveConstruct) {
	test_move_construct(RS8());
	test_move_construct(""_rs);
	test_move_construct("01"_rs);
	test_move_construct("01234567890123456789012345678901234567890123456789012345678901234567890123456789"_rs);
	test_move_construct(RS16());
	test_move_construct(u""_rs);
	test_move_construct(u"01"_rs);
	test_move_construct(u"01234567890123456789012345678901234567890123456789012345678901234567890123456789"_rs);
	test_move_construct(RS32());
	test_move_construct(U""_rs);
	test_move_construct(U"01"_rs);
	test_move_construct(U"01234567890123456789012345678901234567890123456789012345678901234567890123456789"_rs);
}

template< typename TString >
static void test_initializer_list_construct(TString s0, TString s1) {
	EXPECT_EQ(s0, s1);
}

TEST(RawString, InitializerListConstruct) {
	test_initializer_list_construct(RS8{}, RS8());
	test_initializer_list_construct(RS8{'A', 'B'}, "AB"_rs);
	test_initializer_list_construct(RS8{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"_rs);
	test_initializer_list_construct(RS16{}, RS16());
	test_initializer_list_construct(RS16{u'A', u'B'}, u"AB"_rs);
	test_initializer_list_construct(RS16{u'A', u'B', u'C', u'D', u'E', u'F', u'G', u'H', u'I', u'J', u'K', u'L', u'M', u'N', u'O', u'P', u'Q', u'R', u'S', u'T', u'U', u'V', u'W', u'X', u'Y', u'Z'}, u"ABCDEFGHIJKLMNOPQRSTUVWXYZ"_rs);
	test_initializer_list_construct(RS32{}, RS32());
	test_initializer_list_construct(RS32{U'A', U'B'}, U"AB"_rs);
	test_initializer_list_construct(RS32{U'A', U'B', U'C', U'D', U'E', U'F', U'G', U'H', U'I', U'J', U'K', U'L', U'M', U'N', U'O', U'P', U'Q', U'R', U'S', U'T', U'U', U'V', U'W', U'X', U'Y', U'Z'}, U"ABCDEFGHIJKLMNOPQRSTUVWXYZ"_rs);
}
