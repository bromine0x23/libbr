#include "test.hpp"

#include <libbr/utility/disjunction.hpp>

using namespace BR;

TEST(Utility, Disjunction) {
	LOGICAL_CONNECTIVE_CHECK(false, Disjunction, disjunction);
	LOGICAL_CONNECTIVE_CHECK(true,  Disjunction, disjunction, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Disjunction, disjunction, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Disjunction, disjunction, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanTrue , BooleanTrue,  BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanTrue , BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanTrue , BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanTrue , BooleanFalse, BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanFalse, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanFalse, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , Disjunction, disjunction, BooleanFalse, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Disjunction, disjunction, BooleanFalse, BooleanFalse, BooleanFalse);
}