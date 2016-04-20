#include <libbr/type_operate/conditional.hpp>
#include <libbr/utility/bool_constant.hpp>

#include "test.hpp"

using namespace BR;

TEST(TestTypeOperate, Conditional) {
	OPERATE_CHECK(int, ConditionalByValue, true, int, double)
	OPERATE_CHECK(double, ConditionalByValue, false, int, double)
	OPERATE_CHECK(int, Conditional, BooleanTrue, int, double)
	OPERATE_CHECK(double, Conditional, BooleanFalse, int, double)
}