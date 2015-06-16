#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Math {

enum class Relation {
	LT = -1,
	EQ = 0,
	GT = 1,
	LESS_THAN = LT,
	EQUAL = EQ,
	GREATER_THAN = GT
};

} // namespace Math
} // namespace BR
