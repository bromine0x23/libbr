#include "test.hpp"

#include <libbr/utility/abjunction.hpp>

using namespace BR;

TEST(Utility, Abjunction) {
	LOGICAL_CONNECTIVE_CHECK(false, Abjunction, abjunction, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , Abjunction, abjunction, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, Abjunction, abjunction, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Abjunction, abjunction, BooleanFalse, BooleanFalse);

	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, Abjunction, abjunction, true , true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(true , Abjunction, abjunction, true , false);
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, Abjunction, abjunction, false, true );
	LOGICAL_CONNECTIVE_CHECK_BY_VALUE(false, Abjunction, abjunction, false, false);
}