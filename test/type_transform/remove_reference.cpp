#include "test.hpp"

#include <libbr/type_transform/remove_reference.hpp>

using namespace BR;

TEST(TypeTransform, RemoveReference) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, const, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, volatile, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, *, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, * const, * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, const *, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, &, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, const &, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, volatile &, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, const volatile &, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, &&, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, const &&, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, volatile &&, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, const volatile &&, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, [2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, const[2], const[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, (&)[2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemoveReference, (&&)[2], [2])
}