#include "test.hpp"

#include <libbr/utility/implication.hpp>

using namespace BR;

TEST(Utility, Implication) {
	LOGICAL_CONNECTIVE_CHECK(true , Implication, implication, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Implication, implication, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , Implication, implication, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , Implication, implication, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , Implication, implication, true , true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, Implication, implication, true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , Implication, implication, false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , Implication, implication, false, false);
}