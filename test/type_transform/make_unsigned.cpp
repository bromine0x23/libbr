#include "test.hpp"

#include <libbr/type_transform/make_unsigned.hpp>

using namespace BR;

namespace {

enum ES8 : SInt8 {};
enum EU8 : UInt8 {};

enum ES16 : SInt16 {};
enum EU16 : UInt16 {};

enum ES32 : SInt32 {};
enum EU32 : UInt32 {};

enum ES64 : SInt64 {};
enum EU64 : UInt64 {};

#if defined(BR_HAS_INT128)
enum ES128 : SInt128 {};
enum EU128 : UInt128 {};
#endif

}

TEST(TypeTraits, MakeUnsigned) {
	TRANSFORM_CHECK(MakeUnsigned, unsigned char,          char)
	TRANSFORM_CHECK(MakeUnsigned, unsigned char,   signed char)
	TRANSFORM_CHECK(MakeUnsigned, unsigned char,   signed char)
	TRANSFORM_CHECK(MakeUnsigned, unsigned short,   signed short)
	TRANSFORM_CHECK(MakeUnsigned, unsigned short, unsigned short)
	TRANSFORM_CHECK(MakeUnsigned, unsigned int,   signed int)
	TRANSFORM_CHECK(MakeUnsigned, unsigned int, unsigned int)
	TRANSFORM_CHECK(MakeUnsigned, unsigned long,   signed long)
	TRANSFORM_CHECK(MakeUnsigned, unsigned long, unsigned long)
	TRANSFORM_CHECK(MakeUnsigned, unsigned long long,   signed long long)
	TRANSFORM_CHECK(MakeUnsigned, unsigned long long, unsigned long long)

#if defined(BR_HAS_INT128)
	TRANSFORM_CHECK(MakeUnsigned, UInt128, SInt128)
	TRANSFORM_CHECK(MakeUnsigned, UInt128, UInt128)
#endif

	TRANSFORM_CHECK(MakeUnsigned, UInt8, ES8)
	TRANSFORM_CHECK(MakeUnsigned, UInt8, EU8)
	TRANSFORM_CHECK(MakeUnsigned, UInt16, ES16)
	TRANSFORM_CHECK(MakeUnsigned, UInt16, EU16)
	TRANSFORM_CHECK(MakeUnsigned, UInt32, ES32)
	TRANSFORM_CHECK(MakeUnsigned, UInt32, EU32)
	TRANSFORM_CHECK(MakeUnsigned, UInt64, ES64)
	TRANSFORM_CHECK(MakeUnsigned, UInt64, EU64)

#if defined(BR_HAS_INT128)
	TRANSFORM_CHECK(MakeUnsigned, UInt128, ES128)
	TRANSFORM_CHECK(MakeUnsigned, UInt128, EU128)
#endif
}