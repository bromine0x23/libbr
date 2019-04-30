#include "test.hpp"

#include <libbr/type_transform/remove_const_volatile.hpp>

using namespace BR;

TEST(TypeTransform, RemoveConstVolatile) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const         , BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile,       volatile, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const volatile, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, *, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, * const         , *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, *       volatile, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, * const volatile, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const *, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, volatile *, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const * const, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const[2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, volatile[2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConstVolatile, const volatile[2], [2])
}