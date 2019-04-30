#include "test.hpp"

#include <libbr/type_traits/is_volatile.hpp>

using namespace BR;

TEST(TypeTraits, IsVolatile) {
	IS_TRAITS_CHECK(true, Volatile, volatile, void volatile);
	IS_TRAITS_CHECK(true, Volatile, volatile, void const volatile);
	IS_TRAITS_CHECK(true, Volatile, volatile, int volatile);
	IS_TRAITS_CHECK(true, Volatile, volatile, int const volatile);
	IS_TRAITS_CHECK(true, Volatile, volatile, int volatile []);
	IS_TRAITS_CHECK(true, Volatile, volatile, int const volatile []);
	IS_TRAITS_CHECK(true, Volatile, volatile, int volatile [3]);
	IS_TRAITS_CHECK(true, Volatile, volatile, int const volatile [3]);

	IS_TRAITS_CHECK(false, Volatile, volatile, void);
	IS_TRAITS_CHECK(false, Volatile, volatile, int);
	IS_TRAITS_CHECK(false, Volatile, volatile, int const);
	IS_TRAITS_CHECK(false, Volatile, volatile, int volatile *);
	IS_TRAITS_CHECK(false, Volatile, volatile, int volatile &);
	IS_TRAITS_CHECK(false, Volatile, volatile, int volatile &&);
	IS_TRAITS_CHECK(false, Volatile, volatile, int []);
	IS_TRAITS_CHECK(false, Volatile, volatile, int const []);
	IS_TRAITS_CHECK(false, Volatile, volatile, int [3]);
	IS_TRAITS_CHECK(false, Volatile, volatile, int const [3]);
	IS_TRAITS_CHECK(false, Volatile, volatile, auto (int) volatile -> int);
}