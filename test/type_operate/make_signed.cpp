#include "test.hpp"

#include<libbr/type_operate/make_signed.hpp>

using namespace BR;

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

TEST(TypeOperate, MakeSigned) {
	OPERATE_CHECK(signed char     , MakeSigned,          char     )
	OPERATE_CHECK(signed char     , MakeSigned,   signed char     )
	OPERATE_CHECK(signed char     , MakeSigned, unsigned char     )
	OPERATE_CHECK(signed short    , MakeSigned,   signed short    )
	OPERATE_CHECK(signed short    , MakeSigned, unsigned short    )
	OPERATE_CHECK(signed int      , MakeSigned,   signed int      )
	OPERATE_CHECK(signed int      , MakeSigned, unsigned int      )
	OPERATE_CHECK(signed long     , MakeSigned,   signed long     )
	OPERATE_CHECK(signed long     , MakeSigned, unsigned long     )
	OPERATE_CHECK(signed long long, MakeSigned,   signed long long)
	OPERATE_CHECK(signed long long, MakeSigned, unsigned long long)

	OPERATE_CHECK(signed char      const, MakeSigned,          char      const)
	OPERATE_CHECK(signed char      const, MakeSigned,   signed char      const)
	OPERATE_CHECK(signed char      const, MakeSigned, unsigned char      const)
	OPERATE_CHECK(signed short     const, MakeSigned,   signed short     const)
	OPERATE_CHECK(signed short     const, MakeSigned, unsigned short     const)
	OPERATE_CHECK(signed int       const, MakeSigned,   signed int       const)
	OPERATE_CHECK(signed int       const, MakeSigned, unsigned int       const)
	OPERATE_CHECK(signed long      const, MakeSigned,   signed long      const)
	OPERATE_CHECK(signed long      const, MakeSigned, unsigned long      const)
	OPERATE_CHECK(signed long long const, MakeSigned,   signed long long const)
	OPERATE_CHECK(signed long long const, MakeSigned, unsigned long long const)

	OPERATE_CHECK(signed char      volatile, MakeSigned,          char      volatile)
	OPERATE_CHECK(signed char      volatile, MakeSigned,   signed char      volatile)
	OPERATE_CHECK(signed char      volatile, MakeSigned, unsigned char      volatile)
	OPERATE_CHECK(signed short     volatile, MakeSigned,   signed short     volatile)
	OPERATE_CHECK(signed short     volatile, MakeSigned, unsigned short     volatile)
	OPERATE_CHECK(signed int       volatile, MakeSigned,   signed int       volatile)
	OPERATE_CHECK(signed int       volatile, MakeSigned, unsigned int       volatile)
	OPERATE_CHECK(signed long      volatile, MakeSigned,   signed long      volatile)
	OPERATE_CHECK(signed long      volatile, MakeSigned, unsigned long      volatile)
	OPERATE_CHECK(signed long long volatile, MakeSigned,   signed long long volatile)
	OPERATE_CHECK(signed long long volatile, MakeSigned, unsigned long long volatile)

	OPERATE_CHECK(signed char      const volatile, MakeSigned,          char      const volatile)
	OPERATE_CHECK(signed char      const volatile, MakeSigned,   signed char      const volatile)
	OPERATE_CHECK(signed char      const volatile, MakeSigned, unsigned char      const volatile)
	OPERATE_CHECK(signed short     const volatile, MakeSigned,   signed short     const volatile)
	OPERATE_CHECK(signed short     const volatile, MakeSigned, unsigned short     const volatile)
	OPERATE_CHECK(signed int       const volatile, MakeSigned,   signed int       const volatile)
	OPERATE_CHECK(signed int       const volatile, MakeSigned, unsigned int       const volatile)
	OPERATE_CHECK(signed long      const volatile, MakeSigned,   signed long      const volatile)
	OPERATE_CHECK(signed long      const volatile, MakeSigned, unsigned long      const volatile)
	OPERATE_CHECK(signed long long const volatile, MakeSigned,   signed long long const volatile)
	OPERATE_CHECK(signed long long const volatile, MakeSigned, unsigned long long const volatile)

#if defined(BR_HAS_INT128)
	OPERATE_CHECK(SInt128               , MakeSigned, SInt128               )
	OPERATE_CHECK(SInt128               , MakeSigned, UInt128               )
	OPERATE_CHECK(SInt128 const         , MakeSigned, SInt128 const         )
	OPERATE_CHECK(SInt128 const         , MakeSigned, UInt128 const         )
	OPERATE_CHECK(SInt128       volatile, MakeSigned, SInt128       volatile)
	OPERATE_CHECK(SInt128       volatile, MakeSigned, UInt128       volatile)
	OPERATE_CHECK(SInt128 const volatile, MakeSigned, SInt128 const volatile)
	OPERATE_CHECK(SInt128 const volatile, MakeSigned, UInt128 const volatile)
#endif

	OPERATE_CHECK(SInt8 , MakeSigned, ES8 )
	OPERATE_CHECK(SInt8 , MakeSigned, EU8 )
	OPERATE_CHECK(SInt16, MakeSigned, ES16)
	OPERATE_CHECK(SInt16, MakeSigned, EU16)
	OPERATE_CHECK(SInt32, MakeSigned, ES32)
	OPERATE_CHECK(SInt32, MakeSigned, EU32)
	OPERATE_CHECK(SInt64, MakeSigned, ES64)
	OPERATE_CHECK(SInt64, MakeSigned, EU64)

#if defined(BR_HAS_INT128)
	OPERATE_CHECK(SInt128, MakeSigned, ES128)
	OPERATE_CHECK(SInt128, MakeSigned, EU128)
#endif
}