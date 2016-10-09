#pragma once

#include "../test.hpp"
#include <libbr/config.hpp>

template< typename T0, typename T1 >
struct IsSameType {
	constexpr static auto value = false;
};

template< typename T >
struct IsSameType< T, T > {
	constexpr static auto value = true;
};

#define TYPE_CHECK(expected_type, actual_type) ASSERT_TRUE((::IsSameType< expected_type, actual_type >::value))

#define OPERATE_APPLY_FULL( name, ...) Type ## name< __VA_ARGS__ >::Type
#define OPERATE_APPLY_SHORT(name, ...)         name< __VA_ARGS__ >

#define OPERATE_CHECK(expected_type, operate, ...)\
	TYPE_CHECK(expected_type, OPERATE_APPLY_FULL( operate, ##__VA_ARGS__));\
	TYPE_CHECK(expected_type, OPERATE_APPLY_SHORT(operate, ##__VA_ARGS__));

#define OPERATE_CHECKS(operate, from_suffix, to_suffix)\
	OPERATE_CHECK(         bool      to_suffix, operate,          bool      from_suffix);\
	OPERATE_CHECK(         char      to_suffix, operate,          char      from_suffix);\
	OPERATE_CHECK(  signed char      to_suffix, operate,   signed char      from_suffix);\
	OPERATE_CHECK(unsigned char      to_suffix, operate, unsigned char      from_suffix);\
	OPERATE_CHECK(         wchar_t   to_suffix, operate,          wchar_t   from_suffix);\
	OPERATE_CHECK(         char16_t  to_suffix, operate,          char16_t  from_suffix);\
	OPERATE_CHECK(         char32_t  to_suffix, operate,          char32_t  from_suffix);\
	OPERATE_CHECK(         short     to_suffix, operate,          short     from_suffix);\
	OPERATE_CHECK(unsigned short     to_suffix, operate, unsigned short     from_suffix);\
	OPERATE_CHECK(         int       to_suffix, operate,          int       from_suffix);\
	OPERATE_CHECK(unsigned int       to_suffix, operate, unsigned int       from_suffix);\
	OPERATE_CHECK(         long      to_suffix, operate,          long      from_suffix);\
	OPERATE_CHECK(unsigned long      to_suffix, operate, unsigned long      from_suffix);\
	OPERATE_CHECK(         long long to_suffix, operate,          long long from_suffix);\
	OPERATE_CHECK(unsigned long long to_suffix, operate, unsigned long long from_suffix);\
	OPERATE_CHECK(     float         to_suffix, operate,      float         from_suffix);\
	OPERATE_CHECK(     double        to_suffix, operate,      double        from_suffix);\
	OPERATE_CHECK(long double        to_suffix, operate, long double        from_suffix);\
	OPERATE_CHECK(UDT                to_suffix, operate, UDT                from_suffix);

struct UDT {
	UDT();
	~UDT();
	UDT(UDT const &);
	UDT& operator=(UDT const &);

	int i;

	void f1();
	int f2();
	int f3(int);
	int f4(int, float);
};