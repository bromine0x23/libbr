#include "test.hpp"

#include <libbr/type_traits/is_null_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsNullPointer) {
	IS_TRAITS_CHECK_CV(true, NullPointer, null_pointer, NullPointer);

	IS_TRAITS_CHECK(false, NullPointer, null_pointer, void);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, int);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, int *);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, int &);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, int &&);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, int []);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, int [2]);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, CFunction<int, int>);
	IS_TRAITS_CHECK(false, NullPointer, null_pointer, CFunction<int, int> *);
}