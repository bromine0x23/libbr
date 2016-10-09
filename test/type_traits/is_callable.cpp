#include "test.hpp"

#include <libbr/type_traits/is_callable.hpp>

using namespace BR;

TEST(TypeTraits, IsCallable) {
	IS_TRAITS_CHECK(false, Callable, callable, void);
	IS_TRAITS_CHECK(true , Callable, callable, void());
	IS_TRAITS_CHECK(false, Callable, callable, void(int));
	IS_TRAITS_CHECK(true , Callable, callable, void(int), int);
	IS_TRAITS_CHECK(false, Callable, callable, int);
	IS_TRAITS_CHECK(true , Callable, callable, int());
	IS_TRAITS_CHECK(false, Callable, callable, int(int));
	IS_TRAITS_CHECK(true , Callable, callable, int(int), int);
	IS_TRAITS_CHECK(true , Callable, callable, int(*)());
	IS_TRAITS_CHECK(false, Callable, callable, int(*)(int));
	IS_TRAITS_CHECK(true , Callable, callable, int(*)(int), int);
	IS_TRAITS_CHECK(true , Callable, callable, int(&)());
	IS_TRAITS_CHECK(false, Callable, callable, int(&)(int));
	IS_TRAITS_CHECK(true , Callable, callable, int(&)(int), int);
	IS_TRAITS_CHECK(true , Callable, callable, int(&&)());
	IS_TRAITS_CHECK(false, Callable, callable, int(&&)(int));
	IS_TRAITS_CHECK(true , Callable, callable, int(&&)(int), int);
	IS_TRAITS_CHECK(true , Callable, callable, int(Class::*)(), Class);
	IS_TRAITS_CHECK(true , Callable, callable, int(Class::*)(), Class *);
	IS_TRAITS_CHECK(false, Callable, callable, int(Class::*)(int), Class);
	IS_TRAITS_CHECK(false, Callable, callable, int(Class::*)(int), Class *);
	IS_TRAITS_CHECK(true , Callable, callable, int(Class::*)(int), Class, int);
	IS_TRAITS_CHECK(true , Callable, callable, int(Class::*)(int), Class *, int);
}