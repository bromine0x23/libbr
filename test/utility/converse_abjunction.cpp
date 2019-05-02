#include "test.hpp"

#include <libbr/utility/converse_abjunction.hpp>

using namespace BR;

TEST(Utility, ConverseAbjunction) {
	LOGICAL_CONNECTIVE_CHECK(false, ConverseAbjunction, converse_abjunction, BooleanTrue , BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, ConverseAbjunction, converse_abjunction, BooleanTrue , BooleanFalse);
	LOGICAL_CONNECTIVE_CHECK(true , ConverseAbjunction, converse_abjunction, BooleanFalse, BooleanTrue );
	LOGICAL_CONNECTIVE_CHECK(false, ConverseAbjunction, converse_abjunction, BooleanFalse, BooleanFalse);
}