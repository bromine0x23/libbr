#include "test.hpp"

#include <libbr/type_traits/is_unsigned.hpp>

using namespace BR;

TEST(TypeTraits, IsUnsigned) {
	IS_TRAITS_CHECK(false, Unsigned, unsigned, void);
	IS_TRAITS_CHECK(false, Unsigned, unsigned,   signed char);
	IS_TRAITS_CHECK(true , Unsigned, unsigned, unsigned char);
	IS_TRAITS_CHECK(false, Unsigned, unsigned,   signed short);
	IS_TRAITS_CHECK(true , Unsigned, unsigned, unsigned short);
	IS_TRAITS_CHECK(false, Unsigned, unsigned,   signed int);
	IS_TRAITS_CHECK(true , Unsigned, unsigned, unsigned int);
	IS_TRAITS_CHECK(false, Unsigned, unsigned,   signed long);
	IS_TRAITS_CHECK(true , Unsigned, unsigned, unsigned long);
	IS_TRAITS_CHECK(false, Unsigned, unsigned,   signed long long);
	IS_TRAITS_CHECK(true , Unsigned, unsigned, unsigned long long);
}