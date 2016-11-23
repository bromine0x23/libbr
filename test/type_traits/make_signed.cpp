#include "test.hpp"

#include <libbr/type_traits/make_signed.hpp>

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
	TYPE_TRAITS_CHECK(signed char     , MakeSigned,          char     )
	TYPE_TRAITS_CHECK(signed char     , MakeSigned,   signed char     )
	TYPE_TRAITS_CHECK(signed char     , MakeSigned, unsigned char     )
	TYPE_TRAITS_CHECK(signed short    , MakeSigned,   signed short    )
	TYPE_TRAITS_CHECK(signed short    , MakeSigned, unsigned short    )
	TYPE_TRAITS_CHECK(signed int      , MakeSigned,   signed int      )
	TYPE_TRAITS_CHECK(signed int      , MakeSigned, unsigned int      )
	TYPE_TRAITS_CHECK(signed long     , MakeSigned,   signed long     )
	TYPE_TRAITS_CHECK(signed long     , MakeSigned, unsigned long     )
	TYPE_TRAITS_CHECK(signed long long, MakeSigned,   signed long long)
	TYPE_TRAITS_CHECK(signed long long, MakeSigned, unsigned long long)

	TYPE_TRAITS_CHECK(signed char      const, MakeSigned,          char      const)
	TYPE_TRAITS_CHECK(signed char      const, MakeSigned,   signed char      const)
	TYPE_TRAITS_CHECK(signed char      const, MakeSigned, unsigned char      const)
	TYPE_TRAITS_CHECK(signed short     const, MakeSigned,   signed short     const)
	TYPE_TRAITS_CHECK(signed short     const, MakeSigned, unsigned short     const)
	TYPE_TRAITS_CHECK(signed int       const, MakeSigned,   signed int       const)
	TYPE_TRAITS_CHECK(signed int       const, MakeSigned, unsigned int       const)
	TYPE_TRAITS_CHECK(signed long      const, MakeSigned,   signed long      const)
	TYPE_TRAITS_CHECK(signed long      const, MakeSigned, unsigned long      const)
	TYPE_TRAITS_CHECK(signed long long const, MakeSigned,   signed long long const)
	TYPE_TRAITS_CHECK(signed long long const, MakeSigned, unsigned long long const)

	TYPE_TRAITS_CHECK(signed char      volatile, MakeSigned,          char      volatile)
	TYPE_TRAITS_CHECK(signed char      volatile, MakeSigned,   signed char      volatile)
	TYPE_TRAITS_CHECK(signed char      volatile, MakeSigned, unsigned char      volatile)
	TYPE_TRAITS_CHECK(signed short     volatile, MakeSigned,   signed short     volatile)
	TYPE_TRAITS_CHECK(signed short     volatile, MakeSigned, unsigned short     volatile)
	TYPE_TRAITS_CHECK(signed int       volatile, MakeSigned,   signed int       volatile)
	TYPE_TRAITS_CHECK(signed int       volatile, MakeSigned, unsigned int       volatile)
	TYPE_TRAITS_CHECK(signed long      volatile, MakeSigned,   signed long      volatile)
	TYPE_TRAITS_CHECK(signed long      volatile, MakeSigned, unsigned long      volatile)
	TYPE_TRAITS_CHECK(signed long long volatile, MakeSigned,   signed long long volatile)
	TYPE_TRAITS_CHECK(signed long long volatile, MakeSigned, unsigned long long volatile)

	TYPE_TRAITS_CHECK(signed char      const volatile, MakeSigned,          char      const volatile)
	TYPE_TRAITS_CHECK(signed char      const volatile, MakeSigned,   signed char      const volatile)
	TYPE_TRAITS_CHECK(signed char      const volatile, MakeSigned, unsigned char      const volatile)
	TYPE_TRAITS_CHECK(signed short     const volatile, MakeSigned,   signed short     const volatile)
	TYPE_TRAITS_CHECK(signed short     const volatile, MakeSigned, unsigned short     const volatile)
	TYPE_TRAITS_CHECK(signed int       const volatile, MakeSigned,   signed int       const volatile)
	TYPE_TRAITS_CHECK(signed int       const volatile, MakeSigned, unsigned int       const volatile)
	TYPE_TRAITS_CHECK(signed long      const volatile, MakeSigned,   signed long      const volatile)
	TYPE_TRAITS_CHECK(signed long      const volatile, MakeSigned, unsigned long      const volatile)
	TYPE_TRAITS_CHECK(signed long long const volatile, MakeSigned,   signed long long const volatile)
	TYPE_TRAITS_CHECK(signed long long const volatile, MakeSigned, unsigned long long const volatile)

#if defined(BR_HAS_INT128)
	TYPE_TRAITS_CHECK(SInt128               , MakeSigned, SInt128               )
	TYPE_TRAITS_CHECK(SInt128               , MakeSigned, UInt128               )
	TYPE_TRAITS_CHECK(SInt128 const         , MakeSigned, SInt128 const         )
	TYPE_TRAITS_CHECK(SInt128 const         , MakeSigned, UInt128 const         )
	TYPE_TRAITS_CHECK(SInt128       volatile, MakeSigned, SInt128       volatile)
	TYPE_TRAITS_CHECK(SInt128       volatile, MakeSigned, UInt128       volatile)
	TYPE_TRAITS_CHECK(SInt128 const volatile, MakeSigned, SInt128 const volatile)
	TYPE_TRAITS_CHECK(SInt128 const volatile, MakeSigned, UInt128 const volatile)
#endif

	TYPE_TRAITS_CHECK(SInt8 , MakeSigned, ES8 )
	TYPE_TRAITS_CHECK(SInt8 , MakeSigned, EU8 )
	TYPE_TRAITS_CHECK(SInt16, MakeSigned, ES16)
	TYPE_TRAITS_CHECK(SInt16, MakeSigned, EU16)
	TYPE_TRAITS_CHECK(SInt32, MakeSigned, ES32)
	TYPE_TRAITS_CHECK(SInt32, MakeSigned, EU32)
	TYPE_TRAITS_CHECK(SInt64, MakeSigned, ES64)
	TYPE_TRAITS_CHECK(SInt64, MakeSigned, EU64)

#if defined(BR_HAS_INT128)
	TYPE_TRAITS_CHECK(SInt128, MakeSigned, ES128)
	TYPE_TRAITS_CHECK(SInt128, MakeSigned, EU128)
#endif
}