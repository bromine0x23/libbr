#include<libbr/type_operate/make_unsigned.hpp>

#include "test.hpp"

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

TEST(TypeOperate, MakeUnsigned) {
	OPERATE_CHECK(unsigned char     , MakeUnsigned,          char     )
	OPERATE_CHECK(unsigned char     , MakeUnsigned,   signed char     )
	OPERATE_CHECK(unsigned char     , MakeUnsigned, unsigned char     )
	OPERATE_CHECK(unsigned short    , MakeUnsigned,   signed short    )
	OPERATE_CHECK(unsigned short    , MakeUnsigned, unsigned short    )
	OPERATE_CHECK(unsigned int      , MakeUnsigned,   signed int      )
	OPERATE_CHECK(unsigned int      , MakeUnsigned, unsigned int      )
	OPERATE_CHECK(unsigned long     , MakeUnsigned,   signed long     )
	OPERATE_CHECK(unsigned long     , MakeUnsigned, unsigned long     )
	OPERATE_CHECK(unsigned long long, MakeUnsigned,   signed long long)
	OPERATE_CHECK(unsigned long long, MakeUnsigned, unsigned long long)

	OPERATE_CHECK(unsigned char      const, MakeUnsigned,          char      const)
	OPERATE_CHECK(unsigned char      const, MakeUnsigned,   signed char      const)
	OPERATE_CHECK(unsigned char      const, MakeUnsigned, unsigned char      const)
	OPERATE_CHECK(unsigned short     const, MakeUnsigned,   signed short     const)
	OPERATE_CHECK(unsigned short     const, MakeUnsigned, unsigned short     const)
	OPERATE_CHECK(unsigned int       const, MakeUnsigned,   signed int       const)
	OPERATE_CHECK(unsigned int       const, MakeUnsigned, unsigned int       const)
	OPERATE_CHECK(unsigned long      const, MakeUnsigned,   signed long      const)
	OPERATE_CHECK(unsigned long      const, MakeUnsigned, unsigned long      const)
	OPERATE_CHECK(unsigned long long const, MakeUnsigned,   signed long long const)
	OPERATE_CHECK(unsigned long long const, MakeUnsigned, unsigned long long const)

	OPERATE_CHECK(unsigned char      volatile, MakeUnsigned,          char      volatile)
	OPERATE_CHECK(unsigned char      volatile, MakeUnsigned,   signed char      volatile)
	OPERATE_CHECK(unsigned char      volatile, MakeUnsigned, unsigned char      volatile)
	OPERATE_CHECK(unsigned short     volatile, MakeUnsigned,   signed short     volatile)
	OPERATE_CHECK(unsigned short     volatile, MakeUnsigned, unsigned short     volatile)
	OPERATE_CHECK(unsigned int       volatile, MakeUnsigned,   signed int       volatile)
	OPERATE_CHECK(unsigned int       volatile, MakeUnsigned, unsigned int       volatile)
	OPERATE_CHECK(unsigned long      volatile, MakeUnsigned,   signed long      volatile)
	OPERATE_CHECK(unsigned long      volatile, MakeUnsigned, unsigned long      volatile)
	OPERATE_CHECK(unsigned long long volatile, MakeUnsigned,   signed long long volatile)
	OPERATE_CHECK(unsigned long long volatile, MakeUnsigned, unsigned long long volatile)

	OPERATE_CHECK(unsigned char      const volatile, MakeUnsigned,          char      const volatile)
	OPERATE_CHECK(unsigned char      const volatile, MakeUnsigned,   signed char      const volatile)
	OPERATE_CHECK(unsigned char      const volatile, MakeUnsigned, unsigned char      const volatile)
	OPERATE_CHECK(unsigned short     const volatile, MakeUnsigned,   signed short     const volatile)
	OPERATE_CHECK(unsigned short     const volatile, MakeUnsigned, unsigned short     const volatile)
	OPERATE_CHECK(unsigned int       const volatile, MakeUnsigned,   signed int       const volatile)
	OPERATE_CHECK(unsigned int       const volatile, MakeUnsigned, unsigned int       const volatile)
	OPERATE_CHECK(unsigned long      const volatile, MakeUnsigned,   signed long      const volatile)
	OPERATE_CHECK(unsigned long      const volatile, MakeUnsigned, unsigned long      const volatile)
	OPERATE_CHECK(unsigned long long const volatile, MakeUnsigned,   signed long long const volatile)
	OPERATE_CHECK(unsigned long long const volatile, MakeUnsigned, unsigned long long const volatile)

#if defined(BR_HAS_INT128)
	OPERATE_CHECK(UInt128               , MakeUnsigned, SInt128               )
	OPERATE_CHECK(UInt128               , MakeUnsigned, UInt128               )
	OPERATE_CHECK(UInt128 const         , MakeUnsigned, SInt128 const         )
	OPERATE_CHECK(UInt128 const         , MakeUnsigned, UInt128 const         )
	OPERATE_CHECK(UInt128       volatile, MakeUnsigned, SInt128       volatile)
	OPERATE_CHECK(UInt128       volatile, MakeUnsigned, UInt128       volatile)
	OPERATE_CHECK(UInt128 const volatile, MakeUnsigned, SInt128 const volatile)
	OPERATE_CHECK(UInt128 const volatile, MakeUnsigned, UInt128 const volatile)
#endif

	OPERATE_CHECK(UInt8 , MakeUnsigned, ES8 )
	OPERATE_CHECK(UInt8 , MakeUnsigned, EU8 )
	OPERATE_CHECK(UInt16, MakeUnsigned, ES16)
	OPERATE_CHECK(UInt16, MakeUnsigned, EU16)
	OPERATE_CHECK(UInt32, MakeUnsigned, ES32)
	OPERATE_CHECK(UInt32, MakeUnsigned, EU32)
	OPERATE_CHECK(UInt64, MakeUnsigned, ES64)
	OPERATE_CHECK(UInt64, MakeUnsigned, EU64)

#if defined(BR_HAS_INT128)
	OPERATE_CHECK(UInt128, MakeUnsigned, ES128)
	OPERATE_CHECK(UInt128, MakeUnsigned, EU128)
#endif
}