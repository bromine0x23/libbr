#include "test.hpp"

#include <libbr/type_transform/remove_pointer.hpp>

using namespace BR;

TEST(TypeTransform, RemovePointer) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, volatile, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const volatile, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, *, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, * const, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, * volatile, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, * const volatile, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const *, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, volatile *, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const * const, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const * volatile, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const * const volatile, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, volatile &, volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const volatile &, const volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, volatile &&, volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const volatile &&, const volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, [2], [2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const[2], const[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, volatile[2], volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(RemovePointer, const volatile[2], const volatile[2])
}