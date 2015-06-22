#pragma once

#include <libbr/config.hpp>

namespace BR {

enum class Relation {
	LT = -1,
	EQ = 0,
	GT = 1,
	LESS_THAN = LT,
	EQUAL = EQ,
	GREATER_THAN = GT
};

template< typename TInt >
constexpr Relation to_relation(TInt const & x) {
	return x != TInt(0) ? (x < TInt(0) ? Relation::LT : Relation::GT) : Relation::EQ;
}

} // namespace BR
