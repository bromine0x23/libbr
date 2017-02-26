#include <libbr/type_traits/common.hpp>

#include "test.hpp"

struct C1 {};

struct C2 {};

struct C3 : C2 {};

struct C1C2 {
	C1C2() {}
	C1C2(C1 const &) {}
	C1C2(C2 const &) {}
	auto operator=(C1C2 const &) -> C1C2 & {
		return *this;
	}
};

using namespace BR;

TEST(TypeTraits, Common) {
	TYPE_TRAITS_CHECKS(Common, BR_EMPTY, BR_EMPTY)

	TYPE_TRAITS_CHECK(C1C2, Common, C1, C1C2)
	TYPE_TRAITS_CHECK(C1C2, Common, C1, C1C2, C2)
	TYPE_TRAITS_CHECK(C1C2, Common, C2, C1C2)
	TYPE_TRAITS_CHECK(C1C2, Common, C2, C1C2, C1)
	TYPE_TRAITS_CHECK(C1C2, Common, C1C2, C1)
	TYPE_TRAITS_CHECK(C1C2, Common, C1C2, C2)
	TYPE_TRAITS_CHECK(C1C2, Common, C1C2, C1, C2)

	TYPE_TRAITS_CHECK(C1C2, Common, C1C2 &, C1 &)
	TYPE_TRAITS_CHECK(C2 *, Common, C3 *, C2 *)

	TYPE_TRAITS_CHECK(int const          *, Common, int       *, int const *)
	TYPE_TRAITS_CHECK(int       volatile *, Common, int       *, int volatile *)
	TYPE_TRAITS_CHECK(int const volatile *, Common, int const *, int volatile *)
	TYPE_TRAITS_CHECK(int const volatile *, Common, int       *, int const *, int volatile *)

	TYPE_TRAITS_CHECK(         char,      Common, char,          char)
	TYPE_TRAITS_CHECK(  signed int,       Common, char,   signed char)
	TYPE_TRAITS_CHECK(  signed int,       Common, char, unsigned char)
	TYPE_TRAITS_CHECK(  signed int,       Common, char,   signed short)
	TYPE_TRAITS_CHECK(  signed int,       Common, char, unsigned short)
	TYPE_TRAITS_CHECK(  signed int,       Common, char,   signed int)
	TYPE_TRAITS_CHECK(unsigned int,       Common, char, unsigned int)
	TYPE_TRAITS_CHECK(  signed long long, Common, char,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, Common, char, unsigned long long)
	TYPE_TRAITS_CHECK(double,             Common, char, double)

	TYPE_TRAITS_CHECK(  signed int,       Common, signed char,          char)
	TYPE_TRAITS_CHECK(  signed char,      Common, signed char,   signed char)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed char, unsigned char)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed char,   signed short)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed char, unsigned short)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed char,   signed int)
	TYPE_TRAITS_CHECK(unsigned int,       Common, signed char, unsigned int)
	TYPE_TRAITS_CHECK(  signed long long, Common, signed char,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, Common, signed char, unsigned long long)
	TYPE_TRAITS_CHECK(double,             Common, signed char, double)

	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned char,          char)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned char,   signed char)
	TYPE_TRAITS_CHECK(unsigned char,      Common, unsigned char, unsigned char)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned char,   signed short)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned char, unsigned short)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned char,   signed int)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned char, unsigned int)
	TYPE_TRAITS_CHECK(  signed long long, Common, unsigned char,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, Common, unsigned char, unsigned long long)
	TYPE_TRAITS_CHECK(double,             Common, unsigned char, double)

	TYPE_TRAITS_CHECK(  signed int,       Common, signed short,          char)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed short,   signed char)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed short, unsigned char)
	TYPE_TRAITS_CHECK(  signed short,     Common, signed short,   signed short)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed short, unsigned short)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed short,   signed int)
	TYPE_TRAITS_CHECK(unsigned int,       Common, signed short, unsigned int)
	TYPE_TRAITS_CHECK(  signed long long, Common, signed short,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, Common, signed short, unsigned long long)
	TYPE_TRAITS_CHECK(double,             Common, signed short, double)

	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned short,          char)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned short,   signed char)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned short, unsigned char)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned short,   signed short)
	TYPE_TRAITS_CHECK(unsigned short,     Common, unsigned short, unsigned short)
	TYPE_TRAITS_CHECK(  signed int,       Common, unsigned short,   signed int)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned short, unsigned int)
	TYPE_TRAITS_CHECK(  signed long long, Common, unsigned short,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, Common, unsigned short, unsigned long long)
	TYPE_TRAITS_CHECK(double,             Common, unsigned short, double)

	TYPE_TRAITS_CHECK(  signed int,       Common, signed int,          char)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed int,   signed char)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed int, unsigned char)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed int,   signed short)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed int, unsigned short)
	TYPE_TRAITS_CHECK(  signed int,       Common, signed int,   signed int)
	TYPE_TRAITS_CHECK(unsigned int,       Common, signed int, unsigned int)
	TYPE_TRAITS_CHECK(  signed long long, Common, signed int,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, Common, signed int, unsigned long long)
	TYPE_TRAITS_CHECK(double,             Common, signed int, double)

	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned int,          char)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned int,   signed char)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned int, unsigned char)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned int,   signed short)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned int, unsigned short)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned int,   signed int)
	TYPE_TRAITS_CHECK(unsigned int,       Common, unsigned int, unsigned int)
	TYPE_TRAITS_CHECK(  signed long long, Common, unsigned int,   signed long long)
	TYPE_TRAITS_CHECK(unsigned long long, Common, unsigned int, unsigned long long)
	TYPE_TRAITS_CHECK(double,             Common, unsigned int, double)

	TYPE_TRAITS_CHECK(double, Common, double,          char)
	TYPE_TRAITS_CHECK(double, Common, double,   signed char)
	TYPE_TRAITS_CHECK(double, Common, double, unsigned char)
	TYPE_TRAITS_CHECK(double, Common, double,   signed short)
	TYPE_TRAITS_CHECK(double, Common, double, unsigned short)
	TYPE_TRAITS_CHECK(double, Common, double,   signed int)
	TYPE_TRAITS_CHECK(double, Common, double, unsigned int)
	TYPE_TRAITS_CHECK(double, Common, double,   signed long long)
	TYPE_TRAITS_CHECK(double, Common, double, unsigned long long)
	TYPE_TRAITS_CHECK(double, Common, double, double)

	TYPE_TRAITS_CHECK(double, Common, double, char, int)
	TYPE_TRAITS_CHECK(long long, Common, short, char, long long)
}