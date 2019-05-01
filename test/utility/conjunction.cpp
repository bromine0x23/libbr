#include "test.hpp"

#include <libbr/utility/conjunction.hpp>

using namespace BR;

TEST(Utility, Conjunction) {
	LOGICAL_CONNECTIVE_CHECK(true,  Conjunction, conjunction);
	LOGICAL_CONNECTIVE_CHECK(true,  Conjunction, conjunction, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(true , Conjunction, conjunction, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK(true , Conjunction, conjunction, BooleanTrue , BooleanTrue,  BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanTrue , BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanTrue , BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanTrue , BooleanFalse, BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanFalse, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanFalse, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanFalse, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Conjunction, conjunction, BooleanFalse, BooleanFalse, BooleanFalse);
}