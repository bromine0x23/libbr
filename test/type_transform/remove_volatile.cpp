#include "test.hpp"

#include <libbr/type_transform/remove_volatile.hpp>

using namespace BR;

TEST(TypeTransform, RemoveVolatile) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, const, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, const volatile, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, *, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, * const, * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, * volatile, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, * const volatile, * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile *, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile *, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile * const, volatile * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile * volatile, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile * const volatile, volatile * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile &, volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile &&, volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, [2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, const[2], const[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, volatile[2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveVolatile, const volatile[2], const[2])
}