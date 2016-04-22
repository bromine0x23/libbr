#include "test.hpp"

#include<libbr/type_traits/is_constructible.hpp>

using namespace BR;

TEST(TypeTraits, IsConstructible) {
	IS_TRAITS_CHECK(false, Constructible, void, void);
	IS_TRAITS_CHECK(true , Constructible, int, int);
	IS_TRAITS_CHECK(false, Constructible, int[], int[]);
	IS_TRAITS_CHECK(false, Constructible, int[2], int[2]);
	IS_TRAITS_CHECK(true , Constructible, NullPointer, NullPointer);
	IS_TRAITS_CHECK(true , Constructible, Union, Union);
	IS_TRAITS_CHECK(true , Constructible, Enum, Enum);
	IS_TRAITS_CHECK(true , Constructible, EnumClass, EnumClass);
	IS_TRAITS_CHECK(false, Constructible, Abstract, Abstract);

	IS_TRAITS_CHECK(true , Constructible, void *, void *);
	IS_TRAITS_CHECK(true , Constructible, void *, int *);
	IS_TRAITS_CHECK(true , Constructible, int *, int *);
	IS_TRAITS_CHECK(false, Constructible, int *, void *);
	IS_TRAITS_CHECK(true , Constructible, int Class::*, int Class::*);

	IS_TRAITS_CHECK(true , Constructible, Base, Derived);
	IS_TRAITS_CHECK(true , Constructible, Base *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, Base const *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, Base const *, Derived const *);
	IS_TRAITS_CHECK(true , Constructible, Base volatile *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, Base volatile *, Derived volatile *);
	IS_TRAITS_CHECK(true , Constructible, Base const volatile *, Derived *);
	IS_TRAITS_CHECK(true , Constructible, Base const volatile *, Derived const *);
	IS_TRAITS_CHECK(true , Constructible, Base const volatile *, Derived volatile *);
	IS_TRAITS_CHECK(true , Constructible, Base const volatile *, Derived const volatile *);
	IS_TRAITS_CHECK(true , Constructible, Base &, Derived &);
	IS_TRAITS_CHECK(true , Constructible, Base &&, Derived &&);
	IS_TRAITS_CHECK(true , Constructible, Base const &, Derived &);
	IS_TRAITS_CHECK(true , Constructible, Base const &&, Derived &&);

	IS_TRAITS_CHECK(true , Constructible, AnyConstructor);
	IS_TRAITS_CHECK(true , Constructible, AnyConstructor, int);
	IS_TRAITS_CHECK(true , Constructible, AnyConstructor, int, char);
	IS_TRAITS_CHECK(true , Constructible, AnyConstructor, int, char, short(*)[2]);
	IS_TRAITS_CHECK(true , Constructible, AnyConstructor, int, char, short(*)[2], bool(&&)(double));

	IS_TRAITS_CHECK(true, Constructible, ExplicitConstruct, int &);
	IS_TRAITS_CHECK(true, Constructible, ExplicitConstruct, double &);
	IS_TRAITS_CHECK(true, Constructible, ExplicitConstruct, int &, double &);
}