#pragma once

#include <libbr/config.hpp>

namespace BR {

enum class Sign {
	NEG = false,
	ZPOS = true,
	POS = ZPOS
};

inline Sign operator+(Sign sign) {
	return sign;
}

inline Sign operator-(Sign s) {
	switch (s) {
		case Sign::POS:
			return Sign::NEG;
		case Sign::NEG:
			return Sign::POS;
		default:
			BR_ASSERT(false);
	}
}

inline Sign operator~(Sign s) {
	return -s;
}

inline Sign operator*(Sign x, Sign y) {
	return (x == y) ? Sign::POS : Sign::NEG;
}

inline Sign operator|(Sign x, Sign y) {
	return (x == Sign::POS && y == Sign::POS) ? Sign::POS : Sign::NEG;
}

inline Sign operator&(Sign x, Sign y) {
	return (x != Sign::POS && y != Sign::POS) ? Sign::POS : Sign::NEG;
}

inline Sign operator^(Sign x, Sign y) {
	return x * y;
}

inline NChar sign_to_nchar(Sign s) {
	switch (s) {
		case Sign::POS:
			return '+';
		case Sign::NEG:
			return '-';
		default:
			BR_ASSERT(false);
			return '\0';
	}
}

inline WChar sign_to_wchar(Sign s) {
	switch (s) {
		case Sign::POS:
			return L'+';
		case Sign::NEG:
			return L'-';
		default:
			BR_ASSERT(false);
			return L'\0';
	}
}

} // namespace BR