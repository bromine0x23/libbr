#include "test.hpp"

#include <libbr/type_transform/add_volatile.hpp>

using namespace BR;

TEST(TypeTransform, AddVolatile) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, BR_EMPTY, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, volatile, volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const volatile, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, *, * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, * const, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, * volatile, * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, * const volatile, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const *, const * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, volatile *, volatile * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const * const, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const * volatile, const * volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const * const volatile, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, volatile &, volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const volatile &, const volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, volatile &&, volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const volatile &&, const volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, [2], volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const[2], const volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, volatile[2], volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddVolatile, const volatile[2], const volatile[2])
}

