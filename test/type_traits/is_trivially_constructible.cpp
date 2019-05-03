#include "test.hpp"

#include <libbr/type_traits/is_trivially_constructible.hpp>

using namespace BR;

TEST(TypeTraits, IsTriviallyConstructible) {
	IS_TRAITS_CHECK(false, TriviallyConstructible, trivially_constructible, void);

	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, int);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, int *);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, int[2]);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, int[2][3]);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, int, int);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, Class, Class);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, Class, Class &);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, Class, Class const &);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, Class, Class &&);
	IS_TRAITS_CHECK(true, TriviallyConstructible, trivially_constructible, Class, Class const &&);

	IS_TRAITS_CHECK(false, TriviallyConstructible, trivially_constructible, Class, Class volatile &);
	IS_TRAITS_CHECK(false, TriviallyConstructible, trivially_constructible, Class, Class const volatile &);
	IS_TRAITS_CHECK(false, TriviallyConstructible, trivially_constructible, Class, Class volatile &&);
	IS_TRAITS_CHECK(false, TriviallyConstructible, trivially_constructible, Class, Class const volatile &&);
}