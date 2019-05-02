#include "test.hpp"

#include <libbr/type_traits/is_convertible.hpp>

using namespace BR;

TEST(TypeTraits, IsConvertible) {
	IS_TRAITS_CHECK(true, Convertible, convertible, void, void);

	IS_TRAITS_CHECK(true, Convertible, convertible, Base, Base);
	IS_TRAITS_CHECK(true, Convertible, convertible, Derived, Base);
	IS_TRAITS_CHECK(true, Convertible, convertible, Derived, Derived);
	IS_TRAITS_CHECK(false, Convertible, convertible, Base, Derived);
	IS_TRAITS_CHECK(true, Convertible, convertible, Derived *, Base *);
	IS_TRAITS_CHECK(false, Convertible, convertible, Base *, Derived *);
	IS_TRAITS_CHECK(true, Convertible, convertible, Derived &, Base &);
	IS_TRAITS_CHECK(false, Convertible, convertible, Base &, Derived &);

	IS_TRAITS_CHECK(true, Convertible, convertible, double, int);
	IS_TRAITS_CHECK(true, Convertible, convertible, int const &, int);
	IS_TRAITS_CHECK(true, Convertible, convertible, int &&, int const &);
	IS_TRAITS_CHECK(true, Convertible, convertible, int[], int *);
	IS_TRAITS_CHECK(true, Convertible, convertible, int[2], int *);
}