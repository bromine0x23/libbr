#include "test.hpp"

#include <libbr/type_traits/is_same.hpp>

using namespace BR;

TEST(TypeTraits, IsSame) {
	IS_TRAITS_CHECK(true, Same, same, void, void);
	IS_TRAITS_CHECK(true, Same, same, int, int);
	IS_TRAITS_CHECK(true, Same, same, int *, int *);
	IS_TRAITS_CHECK(true, Same, same, int &, int &);
	IS_TRAITS_CHECK(true, Same, same, int &&, int &&);
	IS_TRAITS_CHECK(true, Same, same, int [], int []);
	IS_TRAITS_CHECK(true, Same, same, int [2], int [2]);

	IS_TRAITS_CHECK(false, Same, same, int const, int);
	IS_TRAITS_CHECK(false, Same, same, int const, int volatile);
	IS_TRAITS_CHECK(false, Same, same, int const, int const volatile);
	IS_TRAITS_CHECK(false, Same, same, int &, int &&);

	IS_TRAITS_CHECK(true, Same, same, CArrayUnbound<int>, int []);
	IS_TRAITS_CHECK(true, Same, same, CArray<int, 2>, int [2]);
	IS_TRAITS_CHECK(true, Same, same, CFunction<int, int>, auto (int) -> int);
}