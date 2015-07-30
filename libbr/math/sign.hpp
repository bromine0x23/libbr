#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>

namespace BR {

enum class Sign {
	NEG = false,
	ZPOS = true
};

constexpr Sign operator~(Sign s) {
	return s == Sign::ZPOS ?  Sign::NEG : Sign::ZPOS;
}

constexpr Sign operator|(Sign x, Sign y) {
	return (x == Sign::ZPOS && y == Sign::ZPOS) ? Sign::ZPOS : Sign::NEG;
}

constexpr Sign operator&(Sign x, Sign y) {
	return (x != Sign::ZPOS && y != Sign::ZPOS) ? Sign::ZPOS : Sign::NEG;
}

constexpr Sign operator^(Sign x, Sign y) {
	return (x == y) ? Sign::ZPOS : Sign::NEG;
}

constexpr Sign operator+(Sign s) {
	return s;
}

constexpr Sign operator-(Sign s) {
	return ~s;
}

constexpr Sign operator*(Sign x, Sign y) {
	return x ^ y;
}

constexpr Sign operator/(Sign x, Sign y) {
	return x * y;
}

constexpr NChar sign_to_nchar(Sign s) {
	return s == Sign::ZPOS ? '+' : '-';
}

constexpr WChar sign_to_wchar(Sign s) {
	return s == Sign::ZPOS ? L'+' : L'-';
}

} // namespace BR