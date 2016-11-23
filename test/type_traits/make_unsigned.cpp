#include <libbr/type_traits/make_unsigned.hpp>

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
	TYPE_TRAITS_CHECK(unsigned char     , MakeUnsigned,          char     )
	TYPE_TRAITS_CHECK(unsigned char     , MakeUnsigned,   signed char     )
	TYPE_TRAITS_CHECK(unsigned char     , MakeUnsigned, unsigned char     )
	TYPE_TRAITS_CHECK(unsigned short    , MakeUnsigned,   signed short    )
	TYPE_TRAITS_CHECK(unsigned short    , MakeUnsigned, unsigned short    )
	TYPE_TRAITS_CHECK(unsigned int      , MakeUnsigned,   signed int      )
	TYPE_TRAITS_CHECK(unsigned int      , MakeUnsigned, unsigned int      )
	TYPE_TRAITS_CHECK(unsigned long     , MakeUnsigned,   signed long     )
	TYPE_TRAITS_CHECK(unsigned long     , MakeUnsigned, unsigned long     )
	TYPE_TRAITS_CHECK(unsigned long long, MakeUnsigned,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, MakeUnsigned, unsigned long long)

	TYPE_TRAITS_CHECK(unsigned char      const, MakeUnsigned,          char      const)
	TYPE_TRAITS_CHECK(unsigned char      const, MakeUnsigned,   signed char      const)
	TYPE_TRAITS_CHECK(unsigned char      const, MakeUnsigned, unsigned char      const)
	TYPE_TRAITS_CHECK(unsigned short     const, MakeUnsigned,   signed short     const)
	TYPE_TRAITS_CHECK(unsigned short     const, MakeUnsigned, unsigned short     const)
	TYPE_TRAITS_CHECK(unsigned int       const, MakeUnsigned,   signed int       const)
	TYPE_TRAITS_CHECK(unsigned int       const, MakeUnsigned, unsigned int       const)
	TYPE_TRAITS_CHECK(unsigned long      const, MakeUnsigned,   signed long      const)
	TYPE_TRAITS_CHECK(unsigned long      const, MakeUnsigned, unsigned long      const)
	TYPE_TRAITS_CHECK(unsigned long long const, MakeUnsigned,   signed long long const)
	TYPE_TRAITS_CHECK(unsigned long long const, MakeUnsigned, unsigned long long const)

	TYPE_TRAITS_CHECK(unsigned char      volatile, MakeUnsigned,          char      volatile)
	TYPE_TRAITS_CHECK(unsigned char      volatile, MakeUnsigned,   signed char      volatile)
	TYPE_TRAITS_CHECK(unsigned char      volatile, MakeUnsigned, unsigned char      volatile)
	TYPE_TRAITS_CHECK(unsigned short     volatile, MakeUnsigned,   signed short     volatile)
	TYPE_TRAITS_CHECK(unsigned short     volatile, MakeUnsigned, unsigned short     volatile)
	TYPE_TRAITS_CHECK(unsigned int       volatile, MakeUnsigned,   signed int       volatile)
	TYPE_TRAITS_CHECK(unsigned int       volatile, MakeUnsigned, unsigned int       volatile)
	TYPE_TRAITS_CHECK(unsigned long      volatile, MakeUnsigned,   signed long      volatile)
	TYPE_TRAITS_CHECK(unsigned long      volatile, MakeUnsigned, unsigned long      volatile)
	TYPE_TRAITS_CHECK(unsigned long long volatile, MakeUnsigned,   signed long long volatile)
	TYPE_TRAITS_CHECK(unsigned long long volatile, MakeUnsigned, unsigned long long volatile)

	TYPE_TRAITS_CHECK(unsigned char      const volatile, MakeUnsigned,          char      const volatile)
	TYPE_TRAITS_CHECK(unsigned char      const volatile, MakeUnsigned,   signed char      const volatile)
	TYPE_TRAITS_CHECK(unsigned char      const volatile, MakeUnsigned, unsigned char      const volatile)
	TYPE_TRAITS_CHECK(unsigned short     const volatile, MakeUnsigned,   signed short     const volatile)
	TYPE_TRAITS_CHECK(unsigned short     const volatile, MakeUnsigned, unsigned short     const volatile)
	TYPE_TRAITS_CHECK(unsigned int       const volatile, MakeUnsigned,   signed int       const volatile)
	TYPE_TRAITS_CHECK(unsigned int       const volatile, MakeUnsigned, unsigned int       const volatile)
	TYPE_TRAITS_CHECK(unsigned long      const volatile, MakeUnsigned,   signed long      const volatile)
	TYPE_TRAITS_CHECK(unsigned long      const volatile, MakeUnsigned, unsigned long      const volatile)
	TYPE_TRAITS_CHECK(unsigned long long const volatile, MakeUnsigned,   signed long long const volatile)
	TYPE_TRAITS_CHECK(unsigned long long const volatile, MakeUnsigned, unsigned long long const volatile)

#if defined(BR_HAS_INT128)
	TYPE_TRAITS_CHECK(UInt128               , MakeUnsigned, SInt128               )
	TYPE_TRAITS_CHECK(UInt128               , MakeUnsigned, UInt128               )
	TYPE_TRAITS_CHECK(UInt128 const         , MakeUnsigned, SInt128 const         )
	TYPE_TRAITS_CHECK(UInt128 const         , MakeUnsigned, UInt128 const         )
	TYPE_TRAITS_CHECK(UInt128       volatile, MakeUnsigned, SInt128       volatile)
	TYPE_TRAITS_CHECK(UInt128       volatile, MakeUnsigned, UInt128       volatile)
	TYPE_TRAITS_CHECK(UInt128 const volatile, MakeUnsigned, SInt128 const volatile)
	TYPE_TRAITS_CHECK(UInt128 const volatile, MakeUnsigned, UInt128 const volatile)
#endif

	TYPE_TRAITS_CHECK(UInt8 , MakeUnsigned, ES8 )
	TYPE_TRAITS_CHECK(UInt8 , MakeUnsigned, EU8 )
	TYPE_TRAITS_CHECK(UInt16, MakeUnsigned, ES16)
	TYPE_TRAITS_CHECK(UInt16, MakeUnsigned, EU16)
	TYPE_TRAITS_CHECK(UInt32, MakeUnsigned, ES32)
	TYPE_TRAITS_CHECK(UInt32, MakeUnsigned, EU32)
	TYPE_TRAITS_CHECK(UInt64, MakeUnsigned, ES64)
	TYPE_TRAITS_CHECK(UInt64, MakeUnsigned, EU64)

#if defined(BR_HAS_INT128)
	TYPE_TRAITS_CHECK(UInt128, MakeUnsigned, ES128)
	TYPE_TRAITS_CHECK(UInt128, MakeUnsigned, EU128)
#endif
}