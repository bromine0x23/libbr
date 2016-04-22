#include <libbr/type_operate/decay.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, Decay) {
	OPERATE_CHECKS(Decay, BR_EMPTY, BR_EMPTY)
	OPERATE_CHECKS(Decay, [2], *)
	OPERATE_CHECKS(Decay, const [2], const *)
	OPERATE_CHECKS(Decay, volatile [2], volatile *)
	OPERATE_CHECKS(Decay, const volatile [2], const volatile *)
	OPERATE_CHECKS(Decay, [2][3], (*)[3])
	OPERATE_CHECKS(Decay, const [2][3], const (*)[3])
	OPERATE_CHECKS(Decay, volatile [2][3], volatile (*)[3])
	OPERATE_CHECKS(Decay, const volatile [2][3], const volatile (*)[3])

	using F0 = int(void);
	using F1 = int(long);

	OPERATE_CHECK(int(*)(void), Decay, F0)
	OPERATE_CHECK(int(*)(long), Decay, F1)
}