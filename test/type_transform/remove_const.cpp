#include "test.hpp"

#include <libbr/type_transform/remove_const.hpp>

using namespace BR;

TEST(TypeTransform, RemoveConst) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, volatile, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const volatile, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, *, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, * const, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, * volatile, * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, * const volatile, * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const *, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, volatile *, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const * const, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const * volatile, const * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const * const volatile, const * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, [2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const[2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, volatile[2], volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveConst, const volatile[2], volatile[2])
}