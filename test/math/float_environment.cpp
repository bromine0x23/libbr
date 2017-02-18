#include "../test.hpp"
#include <libbr/math/float_environment.hpp>

using namespace BR;
using namespace BR::Floating;

TEST(Floating, GetRoundMode) {
	switch (to_i(get_round_mode())) {
		case to_i(RoundMode::nearest):
			break;
		case to_i(RoundMode::negative_infinity):
			break;
		case to_i(RoundMode::positive_infinity):
			break;
		case to_i(RoundMode::zero):
			break;
		default:
			FAIL();
	}
}

TEST(Floating, SetRoundMode) {
	ASSERT_NO_THROW(set_round_mode(RoundMode::negative_infinity));
	ASSERT_EQ(RoundMode::negative_infinity, get_round_mode());
	ASSERT_THROW(set_round_mode(RoundMode(0x0CBA)), BadRoundModeException);
}

TEST(Floating, GetEnvironment) {
	Environment environment;
	get_environment(environment);
}

TEST(Floating, SetEnvironment) {
	auto mode = get_round_mode();

	Environment environment;
	get_environment(environment);

	set_round_mode(RoundMode::negative_infinity);

	ASSERT_NO_THROW(set_environment(environment));

	ASSERT_EQ(mode, get_round_mode());

}