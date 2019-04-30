#include "test.hpp"

#include<libbr/type_traits/is_const.hpp>

using namespace BR;

TEST(TypeTraits, IsConst) {
	IS_TRAITS_CHECK(true,  Const, const, void const);
	IS_TRAITS_CHECK(true,  Const, const, void const volatile);
	IS_TRAITS_CHECK(true,  Const, const, int const);
	IS_TRAITS_CHECK(true,  Const, const, int const volatile);
	IS_TRAITS_CHECK(true,  Const, const, int const []);
	IS_TRAITS_CHECK(true,  Const, const, int const volatile []);
	IS_TRAITS_CHECK(true,  Const, const, int const [3]);
	IS_TRAITS_CHECK(true,  Const, const, int const volatile [3]);

	IS_TRAITS_CHECK(false, Const, const, void);
	IS_TRAITS_CHECK(false, Const, const, int);
	IS_TRAITS_CHECK(false, Const, const, int volatile);
	IS_TRAITS_CHECK(false, Const, const, int const *);
	IS_TRAITS_CHECK(false, Const, const, int const &);
	IS_TRAITS_CHECK(false, Const, const, int const &&);
	IS_TRAITS_CHECK(false, Const, const, int []);
	IS_TRAITS_CHECK(false, Const, const, int volatile []);
	IS_TRAITS_CHECK(false, Const, const, int [3]);
	IS_TRAITS_CHECK(false, Const, const, int volatile [3]);
	IS_TRAITS_CHECK(false, Const, const, auto (int) const -> int);
}