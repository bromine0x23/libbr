#include "test.hpp"

#include <libbr/type_transform/add_pointer.hpp>

using namespace BR;

TEST(TypeTransform, AddPointer) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, BR_EMPTY, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, volatile, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const volatile, const volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, *, * *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, * const, * const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, * volatile, * volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, * const volatile, * const volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const *, const * *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, volatile *, volatile * *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const * const, const * const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const * volatile, const * volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const * const volatile, const * const volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, &, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const &, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, volatile &, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const volatile &, const volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, &&, *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const &&, const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, volatile &&, volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const volatile &&, const volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, [2], (*)[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const[2], const(*)[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, volatile[2], volatile(*)[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddPointer, const volatile[2], const volatile(*)[2])
}