#include "test.hpp"

#include<libbr/type_traits/is_const.hpp>

using namespace BR;

TEST(TypeTraits, IsConst) {
	IS_TRAITS_CHECK(false, Const, int);
	IS_TRAITS_CHECK(true , Const, int const);
	IS_TRAITS_CHECK(false, Const, int volatile);
	IS_TRAITS_CHECK(true , Const, int const volatile);
	IS_TRAITS_CHECK(false, Const, int *);
	IS_TRAITS_CHECK(true , Const, int * const);
	IS_TRAITS_CHECK(false, Const, int * volatile);
	IS_TRAITS_CHECK(true , Const, int * const volatile);
	IS_TRAITS_CHECK(false, Const, int(*)(int));
	IS_TRAITS_CHECK(true , Const, int(* const)(int));
	IS_TRAITS_CHECK(false, Const, int(* volatile)(int));
	IS_TRAITS_CHECK(true , Const, int(* const volatile)(int));
	IS_TRAITS_CHECK(false, Const, int &);
	IS_TRAITS_CHECK(false, Const, int &&);
	IS_TRAITS_CHECK(false, Const, Class);
	IS_TRAITS_CHECK(true , Const, Class const);
	IS_TRAITS_CHECK(false, Const, Class volatile);
	IS_TRAITS_CHECK(true , Const, Class const volatile);
}