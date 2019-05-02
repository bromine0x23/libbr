#include "test.hpp"

#include <libbr/type_traits/is_union.hpp>

using namespace BR;

TEST(TypeTraits, IsUnion) {
	IS_TRAITS_CHECK_CV(false, Union, union, int);
	IS_TRAITS_CHECK_CV(false, Union, union, int *);
	IS_TRAITS_CHECK(false, Union, union, int &);
	IS_TRAITS_CHECK(false, Union, union, int &&);
	IS_TRAITS_CHECK(false, Union, union, int[2]);
	IS_TRAITS_CHECK_CV(true, Union, union, Union);
}