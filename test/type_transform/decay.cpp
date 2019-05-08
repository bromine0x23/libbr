#include "test.hpp"

#include <libbr/type_transform/decay.hpp>

using namespace BR;

TEST(TypeTransform, Decay) {


	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, BR_EMPTY, BR_EMPTY)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, [2], *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, const [2], const *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, volatile [2], volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, const volatile [2], const volatile *)
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, [2][3], (*)[3])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, const [2][3], const (*)[3])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, volatile [2][3], volatile (*)[3])
	SUFFIX_TRANSFORM_CHECK_COMMON_TYPES(Decay, const volatile [2][3], const volatile (*)[3])

	TRANSFORM_CHECK(Decay, int(*)(void), int(void))
	TRANSFORM_CHECK(Decay, int(*)(long), int(long))
}