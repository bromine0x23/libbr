#include <libbr/type_traits/conditional.hpp>
#include <libbr/utility/boolean_constant.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, Conditional) {
	TYPE_TRAITS_CHECK(int, ConditionalByValue, true, int, double)
	TYPE_TRAITS_CHECK(double, ConditionalByValue, false, int, double)
	TYPE_TRAITS_CHECK(int, Conditional, BooleanTrue, int, double)
	TYPE_TRAITS_CHECK(double, Conditional, BooleanFalse, int, double)
}