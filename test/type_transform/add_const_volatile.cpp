#include "test.hpp"

#include <libbr/type_transform/add_const_volatile.hpp>

using namespace BR;

TEST(TypeTransform, AddConstVolatile) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, BR_EMPTY, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, volatile, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const volatile, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, *, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, * const, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, * volatile, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, * const volatile, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const *, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, volatile *, volatile * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const * const, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const * volatile, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const * const volatile, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, volatile &, volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const volatile &, const volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, volatile &&, volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const volatile &&, const volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, [2], const volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const[2], const volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, volatile[2], const volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConstVolatile, const volatile[2], const volatile[2])
}

