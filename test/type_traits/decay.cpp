#include <libbr/type_traits/decay.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeTraits, Decay) {
	TYPE_TRAITS_CHECKS(Decay, BR_EMPTY, BR_EMPTY)
	TYPE_TRAITS_CHECKS(Decay, [2], *)
	TYPE_TRAITS_CHECKS(Decay, const [2], const *)
	TYPE_TRAITS_CHECKS(Decay, volatile [2], volatile *)
	TYPE_TRAITS_CHECKS(Decay, const volatile [2], const volatile *)
	TYPE_TRAITS_CHECKS(Decay, [2][3], (*)[3])
	TYPE_TRAITS_CHECKS(Decay, const [2][3], const (*)[3])
	TYPE_TRAITS_CHECKS(Decay, volatile [2][3], volatile (*)[3])
	TYPE_TRAITS_CHECKS(Decay, const volatile [2][3], const volatile (*)[3])

	TYPE_TRAITS_CHECK(int(*)(void), Decay, int(void))
	TYPE_TRAITS_CHECK(int(*)(long), Decay, int(long))
}