#include "test.hpp"

#include <libbr/utility/abjunction.hpp>

using namespace BR;

TEST(Utility, Abjunction) {
	LOGICAL_CONNECTIVE_CHECK(false, Abjunction, abjunction, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(true , Abjunction, abjunction, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(false, Abjunction, abjunction, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, Abjunction, abjunction, BooleanFalse, BooleanFalse);
}