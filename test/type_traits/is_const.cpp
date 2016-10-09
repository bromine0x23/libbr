#include "test.hpp"

#include<libbr/type_traits/is_const.hpp>

using namespace BR;

TEST(TypeTraits, IsConst) {
	IS_TRAITS_CHECK(false, Const, const, int);
	IS_TRAITS_CHECK(true , Const, const, int const);
	IS_TRAITS_CHECK(false, Const, const, int volatile);
	IS_TRAITS_CHECK(true , Const, const, int const volatile);
	IS_TRAITS_CHECK(false, Const, const, int *);
	IS_TRAITS_CHECK(true , Const, const, int * const);
	IS_TRAITS_CHECK(false, Const, const, int * volatile);
	IS_TRAITS_CHECK(true , Const, const, int * const volatile);
	IS_TRAITS_CHECK(false, Const, const, int(*)(int));
	IS_TRAITS_CHECK(true , Const, const, int(* const)(int));
	IS_TRAITS_CHECK(false, Const, const, int(* volatile)(int));
	IS_TRAITS_CHECK(true , Const, const, int(* const volatile)(int));
	IS_TRAITS_CHECK(false, Const, const, int &);
	IS_TRAITS_CHECK(false, Const, const, int &&);
	IS_TRAITS_CHECK(false, Const, const, Class);
	IS_TRAITS_CHECK(true , Const, const, Class const);
	IS_TRAITS_CHECK(false, Const, const, Class volatile);
	IS_TRAITS_CHECK(true , Const, const, Class const volatile);
}