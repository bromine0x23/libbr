#include "test.hpp"

#include <libbr/utility/converse_implication.hpp>

using namespace BR;

TEST(Utility, ConverseImplication) {
	LOGICAL_CONNECTIVE_CHECK(true , ConverseImplication, converse_implication, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , ConverseImplication, converse_implication, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, ConverseImplication, converse_implication, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , ConverseImplication, converse_implication, BooleanFalse, BooleanFalse);
}