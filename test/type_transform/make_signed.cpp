#include "test.hpp"

#include <libbr/type_transform/make_signed.hpp>

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

TEST(TypeTraits, MakeSigned) {
	TRANSFORM_CHECK(MakeSigned, signed char,          char)
	TRANSFORM_CHECK(MakeSigned, signed char,   signed char)
	TRANSFORM_CHECK(MakeSigned, signed char,   signed char)
	TRANSFORM_CHECK(MakeSigned, signed short,   signed short)
	TRANSFORM_CHECK(MakeSigned, signed short, unsigned short)
	TRANSFORM_CHECK(MakeSigned, signed int,   signed int)
	TRANSFORM_CHECK(MakeSigned, signed int, unsigned int)
	TRANSFORM_CHECK(MakeSigned, signed long,   signed long)
	TRANSFORM_CHECK(MakeSigned, signed long, unsigned long)
	TRANSFORM_CHECK(MakeSigned, signed long long,   signed long long)
	TRANSFORM_CHECK(MakeSigned, signed long long, unsigned long long)

#if defined(BR_HAS_INT128)
	TRANSFORM_CHECK(MakeSigned, SInt128, SInt128)
	TRANSFORM_CHECK(MakeSigned, SInt128, UInt128)
#endif

	TRANSFORM_CHECK(MakeSigned, SInt8, ES8)
	TRANSFORM_CHECK(MakeSigned, SInt8, EU8)
	TRANSFORM_CHECK(MakeSigned, SInt16, ES16)
	TRANSFORM_CHECK(MakeSigned, SInt16, EU16)
	TRANSFORM_CHECK(MakeSigned, SInt32, ES32)
	TRANSFORM_CHECK(MakeSigned, SInt32, EU32)
	TRANSFORM_CHECK(MakeSigned, SInt64, ES64)
	TRANSFORM_CHECK(MakeSigned, SInt64, EU64)

#if defined(BR_HAS_INT128)
	TRANSFORM_CHECK(MakeSigned, SInt128, ES128)
	TRANSFORM_CHECK(MakeSigned, SInt128, EU128)
#endif
}