#include "test.hpp"

#include <libbr/utility/non_disjunction.hpp>

using namespace BR;

TEST(Utility, NonDisjunction) {
	LOGICAL_CONNECTIVE_CHECK(true, NonDisjunction, non_disjunction);

	LOGICAL_CONNECTIVE_CHECK(true,  NonDisjunction, non_disjunction, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonDisjunction, non_disjunction, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanTrue , BooleanTrue,  BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanTrue , BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanTrue , BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanTrue , BooleanFalse, BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanFalse, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanFalse, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, NonDisjunction, non_disjunction, BooleanFalse, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonDisjunction, non_disjunction, BooleanFalse, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true, NonDisjunction, non_disjunction);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true,  NonDisjunction, non_disjunction, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, false);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, true , true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonDisjunction, non_disjunction, false, false);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, true , true,  true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, true , true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, true , false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, true , false, false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, false, true , true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, false, true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonDisjunction, non_disjunction, false, false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonDisjunction, non_disjunction, false, false, false);
}