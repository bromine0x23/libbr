#include "test.hpp"

#include <libbr/type_traits/is_nothrow_constructible.hpp>

using namespace BR;

TEST(TypeTraits, IsNothrowConstructible) {
	using TA = int[2];

	IS_TRAITS_CHECK(false, NothrowConstructible, nothrow_constructible, void);

	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, int);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, int *);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, int[2]);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, int[2][3]);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, int, int);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, Class, Class);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, Class, Class &);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, Class, Class const &);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, Class, Class &&);
	IS_TRAITS_CHECK(true, NothrowConstructible, nothrow_constructible, Class, Class const &&);

	IS_TRAITS_CHECK(false, NothrowConstructible, nothrow_constructible, Class, Class volatile &);
	IS_TRAITS_CHECK(false, NothrowConstructible, nothrow_constructible, Class, Class const volatile &);
	IS_TRAITS_CHECK(false, NothrowConstructible, nothrow_constructible, Class, Class volatile &&);
	IS_TRAITS_CHECK(false, NothrowConstructible, nothrow_constructible, Class, Class const volatile &&);
}