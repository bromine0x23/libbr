#include "test.hpp"

#include <libbr/type_transform/remove_all_extents.hpp>

using namespace BR;

TEST(TypeTransform, RemoveAllExtents) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, const, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, volatile, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, *, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, const *, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, * const, * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, [2], BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, const [2], const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, [2][3], BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, const [2][3], const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, [][3], BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, const [][3], const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, (&)[2], (&)[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, (&&)[2], (&&)[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, (&)[2][3], (&)[2][3])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveAllExtents, (&&)[2][3], (&&)[2][3])
}