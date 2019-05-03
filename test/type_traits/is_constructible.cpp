#include "test.hpp"

#include<libbr/type_traits/is_constructible.hpp>

using namespace BR;

TEST(TypeTraits, IsConstructible) {
	IS_TRAITS_CHECK(false, Constructible, constructible, void);
	IS_TRAITS_CHECK(true , Constructible, constructible, int);
	IS_TRAITS_CHECK(true , Constructible, constructible, int *);
	IS_TRAITS_CHECK(false, Constructible, constructible, int[]);
	IS_TRAITS_CHECK(true , Constructible, constructible, int[2]);
	IS_TRAITS_CHECK(true , Constructible, constructible, NullPointer);
	IS_TRAITS_CHECK(true , Constructible, constructible, Enum);
	IS_TRAITS_CHECK(true , Constructible, constructible, EnumClass);

	IS_TRAITS_CHECK(false, Constructible, constructible, void, void);
	IS_TRAITS_CHECK(true , Constructible, constructible, int, int);
	IS_TRAITS_CHECK(false, Constructible, constructible, int[], int[]);
	IS_TRAITS_CHECK(false, Constructible, constructible, int[2], int[2]);
	IS_TRAITS_CHECK(true , Constructible, constructible, NullPointer, NullPointer);
	IS_TRAITS_CHECK(true , Constructible, constructible, Union, Union);
	IS_TRAITS_CHECK(true , Constructible, constructible, Enum, Enum);
	IS_TRAITS_CHECK(true , Constructible, constructible, EnumClass, EnumClass);
	IS_TRAITS_CHECK(false, Constructible, constructible, Abstract, Abstract);

	IS_TRAITS_CHECK(true , Constructible, constructible, void *, void *);
	IS_TRAITS_CHECK(true , Constructible, constructible, void *, int *);
	IS_TRAITS_CHECK(true , Constructible, constructible, int *, int *);
	IS_TRAITS_CHECK(false, Constructible, constructible, int *, void *);
	IS_TRAITS_CHECK(true , Constructible, constructible, int Class::*, int Class::*);

	IS_TRAITS_CHECK(true , Constructible, constructible, Base, Derived);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const *, Derived const *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base volatile *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base volatile *, Derived volatile *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const volatile *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const volatile *, Derived const *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const volatile *, Derived volatile *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const volatile *, Derived const volatile *);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base &, Derived &);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base &&, Derived &&);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const &, Derived &);
	IS_TRAITS_CHECK(true , Constructible, constructible, Base const &&, Derived &&);
}