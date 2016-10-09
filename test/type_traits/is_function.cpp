#include "test.hpp"

#include<libbr/type_traits/is_function.hpp>

using namespace BR;

TEST(TypeTraits, IsFunction) {
	IS_TRAITS_CHECK(true , Function, function, int(int));
	IS_TRAITS_CHECK(true , Function, function, int(int, int[]));
	IS_TRAITS_CHECK(true , Function, function, int(int, int[], Class));
	IS_TRAITS_CHECK(true , Function, function, int(int, int[], Class, ...));
	IS_TRAITS_CHECK(true , Function, function, int (Class) const         );
	IS_TRAITS_CHECK(true , Function, function, int (Class)       volatile);
	IS_TRAITS_CHECK(true , Function, function, int (Class) const volatile);
	IS_TRAITS_CHECK(true , Function, function, int (Class &) const          &);
	IS_TRAITS_CHECK(true , Function, function, int (Class &)       volatile &);
	IS_TRAITS_CHECK(true , Function, function, int (Class &) const volatile &);
	IS_TRAITS_CHECK(true , Function, function, int (Class &&) const          &&);
	IS_TRAITS_CHECK(true , Function, function, int (Class &&)       volatile &&);
	IS_TRAITS_CHECK(true , Function, function, int (Class &&) const volatile &&);

	IS_TRAITS_CHECK(false, Function, function, int(*)(int));
	IS_TRAITS_CHECK(false, Function, function, int(&)(int));
	IS_TRAITS_CHECK(false, Function, function, int(&&)(int));

	IS_TRAITS_CHECK_CV(false, Function, function, void);
	IS_TRAITS_CHECK_CV(false, Function, function, int);
	IS_TRAITS_CHECK_CV(false, Function, function, Class);
	IS_TRAITS_CHECK_CV(false, Function, function, Union);
	IS_TRAITS_CHECK_CV(false, Function, function, Enum);
	IS_TRAITS_CHECK_CV(false, Function, function, EnumClass);
}