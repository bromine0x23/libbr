#include "test.hpp"

#include<libbr/type_traits/is_function.hpp>

using namespace BR;

TEST(TypeTraits, IsFunction) {
	IS_TRAITS_CHECK(true , Function, function, auto (int) -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (int, int[]) -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (int, int[], Class) -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (int, int[], Class, ...) -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class) const          -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class)       volatile -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class) const volatile -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class &) const          & -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class &)       volatile & -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class &) const volatile & -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class &&) const          && -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class &&)       volatile && -> int);
	IS_TRAITS_CHECK(true , Function, function, auto (Class &&) const volatile && -> int);

	IS_TRAITS_CHECK(false, Function, function, CFunction<int, int> *);
	IS_TRAITS_CHECK(false, Function, function, CFunction<int, int> &);
	IS_TRAITS_CHECK(false, Function, function, CFunction<int, int> &&);

	IS_TRAITS_CHECK(false, Function, function, void);
	IS_TRAITS_CHECK(false, Function, function, int);
	IS_TRAITS_CHECK(false, Function, function, int *);
	IS_TRAITS_CHECK(false, Function, function, int &);
	IS_TRAITS_CHECK(false, Function, function, int &&);
	IS_TRAITS_CHECK(false, Function, function, int []);
	IS_TRAITS_CHECK(false, Function, function, int [2]);
	IS_TRAITS_CHECK(false, Function, function, NullPointer);
	IS_TRAITS_CHECK(false, Function, function, Class);
	IS_TRAITS_CHECK(false, Function, function, Struct);
	IS_TRAITS_CHECK(false, Function, function, Union);
	IS_TRAITS_CHECK(false, Function, function, Enum);
	IS_TRAITS_CHECK(false, Function, function, EnumClass);
}