#include<libbr/type_operate/common.hpp>

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

TEST(TypeOperate, Common) {
	OPERATE_CHECKS(Common, BR_EMPTY, BR_EMPTY)

	OPERATE_CHECK(C1C2, Common, C1, C1C2)
	OPERATE_CHECK(C1C2, Common, C1, C1C2, C2)
	OPERATE_CHECK(C1C2, Common, C2, C1C2)
	OPERATE_CHECK(C1C2, Common, C2, C1C2, C1)
	OPERATE_CHECK(C1C2, Common, C1C2, C1)
	OPERATE_CHECK(C1C2, Common, C1C2, C2)
	OPERATE_CHECK(C1C2, Common, C1C2, C1, C2)

	OPERATE_CHECK(C1C2, Common, C1C2 &, C1 &)
	OPERATE_CHECK(C2 *, Common, C3 *, C2 *)

	OPERATE_CHECK(int const          *, Common, int       *, int const *)
	OPERATE_CHECK(int       volatile *, Common, int       *, int volatile *)
	OPERATE_CHECK(int const volatile *, Common, int const *, int volatile *)
	OPERATE_CHECK(int const volatile *, Common, int       *, int const *, int volatile *)

	OPERATE_CHECK(         char,      Common, char,          char)
	OPERATE_CHECK(  signed int,       Common, char,   signed char)
	OPERATE_CHECK(  signed int,       Common, char, unsigned char)
	OPERATE_CHECK(  signed int,       Common, char,   signed short)
	OPERATE_CHECK(  signed int,       Common, char, unsigned short)
	OPERATE_CHECK(  signed int,       Common, char,   signed int)
	OPERATE_CHECK(unsigned int,       Common, char, unsigned int)
	OPERATE_CHECK(  signed long long, Common, char,   signed long long)
	OPERATE_CHECK(unsigned long long, Common, char, unsigned long long)
	OPERATE_CHECK(double,             Common, char, double)

	OPERATE_CHECK(  signed int,       Common, signed char,          char)
	OPERATE_CHECK(  signed char,      Common, signed char,   signed char)
	OPERATE_CHECK(  signed int,       Common, signed char, unsigned char)
	OPERATE_CHECK(  signed int,       Common, signed char,   signed short)
	OPERATE_CHECK(  signed int,       Common, signed char, unsigned short)
	OPERATE_CHECK(  signed int,       Common, signed char,   signed int)
	OPERATE_CHECK(unsigned int,       Common, signed char, unsigned int)
	OPERATE_CHECK(  signed long long, Common, signed char,   signed long long)
	OPERATE_CHECK(unsigned long long, Common, signed char, unsigned long long)
	OPERATE_CHECK(double,             Common, signed char, double)

	OPERATE_CHECK(  signed int,       Common, unsigned char,          char)
	OPERATE_CHECK(  signed int,       Common, unsigned char,   signed char)
	OPERATE_CHECK(unsigned char,      Common, unsigned char, unsigned char)
	OPERATE_CHECK(  signed int,       Common, unsigned char,   signed short)
	OPERATE_CHECK(  signed int,       Common, unsigned char, unsigned short)
	OPERATE_CHECK(  signed int,       Common, unsigned char,   signed int)
	OPERATE_CHECK(unsigned int,       Common, unsigned char, unsigned int)
	OPERATE_CHECK(  signed long long, Common, unsigned char,   signed long long)
	OPERATE_CHECK(unsigned long long, Common, unsigned char, unsigned long long)
	OPERATE_CHECK(double,             Common, unsigned char, double)

	OPERATE_CHECK(  signed int,       Common, signed short,          char)
	OPERATE_CHECK(  signed int,       Common, signed short,   signed char)
	OPERATE_CHECK(  signed int,       Common, signed short, unsigned char)
	OPERATE_CHECK(  signed short,     Common, signed short,   signed short)
	OPERATE_CHECK(  signed int,       Common, signed short, unsigned short)
	OPERATE_CHECK(  signed int,       Common, signed short,   signed int)
	OPERATE_CHECK(unsigned int,       Common, signed short, unsigned int)
	OPERATE_CHECK(  signed long long, Common, signed short,   signed long long)
	OPERATE_CHECK(unsigned long long, Common, signed short, unsigned long long)
	OPERATE_CHECK(double,             Common, signed short, double)

	OPERATE_CHECK(  signed int,       Common, unsigned short,          char)
	OPERATE_CHECK(  signed int,       Common, unsigned short,   signed char)
	OPERATE_CHECK(  signed int,       Common, unsigned short, unsigned char)
	OPERATE_CHECK(  signed int,       Common, unsigned short,   signed short)
	OPERATE_CHECK(unsigned short,     Common, unsigned short, unsigned short)
	OPERATE_CHECK(  signed int,       Common, unsigned short,   signed int)
	OPERATE_CHECK(unsigned int,       Common, unsigned short, unsigned int)
	OPERATE_CHECK(  signed long long, Common, unsigned short,   signed long long)
	OPERATE_CHECK(unsigned long long, Common, unsigned short, unsigned long long)
	OPERATE_CHECK(double,             Common, unsigned short, double)

	OPERATE_CHECK(  signed int,       Common, signed int,          char)
	OPERATE_CHECK(  signed int,       Common, signed int,   signed char)
	OPERATE_CHECK(  signed int,       Common, signed int, unsigned char)
	OPERATE_CHECK(  signed int,       Common, signed int,   signed short)
	OPERATE_CHECK(  signed int,       Common, signed int, unsigned short)
	OPERATE_CHECK(  signed int,       Common, signed int,   signed int)
	OPERATE_CHECK(unsigned int,       Common, signed int, unsigned int)
	OPERATE_CHECK(  signed long long, Common, signed int,   signed long long)
	OPERATE_CHECK(unsigned long long, Common, signed int, unsigned long long)
	OPERATE_CHECK(double,             Common, signed int, double)

	OPERATE_CHECK(unsigned int,       Common, unsigned int,          char)
	OPERATE_CHECK(unsigned int,       Common, unsigned int,   signed char)
	OPERATE_CHECK(unsigned int,       Common, unsigned int, unsigned char)
	OPERATE_CHECK(unsigned int,       Common, unsigned int,   signed short)
	OPERATE_CHECK(unsigned int,       Common, unsigned int, unsigned short)
	OPERATE_CHECK(unsigned int,       Common, unsigned int,   signed int)
	OPERATE_CHECK(unsigned int,       Common, unsigned int, unsigned int)
	OPERATE_CHECK(  signed long long, Common, unsigned int,   signed long long)
	OPERATE_CHECK(unsigned long long, Common, unsigned int, unsigned long long)
	OPERATE_CHECK(double,             Common, unsigned int, double)

	OPERATE_CHECK(double, Common, double,          char)
	OPERATE_CHECK(double, Common, double,   signed char)
	OPERATE_CHECK(double, Common, double, unsigned char)
	OPERATE_CHECK(double, Common, double,   signed short)
	OPERATE_CHECK(double, Common, double, unsigned short)
	OPERATE_CHECK(double, Common, double,   signed int)
	OPERATE_CHECK(double, Common, double, unsigned int)
	OPERATE_CHECK(double, Common, double,   signed long long)
	OPERATE_CHECK(double, Common, double, unsigned long long)
	OPERATE_CHECK(double, Common, double, double)

	OPERATE_CHECK(double, Common, double, char, int)
	OPERATE_CHECK(long long, Common, short, char, long long)
}