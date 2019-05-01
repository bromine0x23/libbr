#include "test.hpp"

#include <libbr/type_transform/remove_extent.hpp>

using namespace BR;

TEST(TypeTransform, RemoveExtent) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, volatile, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const volatile, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, *, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, * const, * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, * volatile, * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, * const volatile, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const *, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, volatile *, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const * const, const * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const * volatile, const * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const * const volatile, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, volatile &, volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const volatile &, const volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, volatile &&, volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const volatile &&, const volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, [2], BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const[2], const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, volatile[2], volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveExtent, const volatile[2], const volatile)
}