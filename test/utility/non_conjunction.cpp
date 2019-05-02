#include "test.hpp"

#include <libbr/utility/non_conjunction.hpp>

using namespace BR;

TEST(Utility, NonConjunction) {
	LOGICAL_CONNECTIVE_CHECK(false,  NonConjunction, non_conjunction);

	LOGICAL_CONNECTIVE_CHECK(true,  NonConjunction, non_conjunction, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, NonConjunction, non_conjunction, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(false, NonConjunction, non_conjunction, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(false, NonConjunction, non_conjunction, BooleanTrue , BooleanTrue,  BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanTrue , BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanTrue , BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanTrue , BooleanFalse, BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanFalse, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanFalse, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanFalse, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , NonConjunction, non_conjunction, BooleanFalse, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false,  NonConjunction, non_conjunction);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true,  NonConjunction, non_conjunction, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonConjunction, non_conjunction, false);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonConjunction, non_conjunction, true , true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, false, false);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, NonConjunction, non_conjunction, true , true,  true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, true , true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, true , false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, true , false, false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, false, true , true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, false, true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, false, false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , NonConjunction, non_conjunction, false, false, false);
}