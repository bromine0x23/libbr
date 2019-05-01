#include "test.hpp"

#include <libbr/type_transform/add_const.hpp>

using namespace BR;

TEST(TypeTransform, AddConst) {
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, BR_EMPTY, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const, const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, volatile, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const volatile, const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, *, * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, * const, * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, * volatile, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, * const volatile, * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const *, const * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, volatile *, volatile * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const * const, const * const)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const * volatile, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const * const volatile, const * const volatile)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, &, &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const &, const &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, volatile &, volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const volatile &, const volatile &)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, &&, &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const &&, const &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, volatile &&, volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const volatile &&, const volatile &&)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, [2], const[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const[2], const[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, volatile[2], const volatile[2])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(AddConst, const volatile[2], const volatile[2])
}

