#pragma once

#include <libbr/config.hpp>

namespace BR {

enum class Relation {
	LT = -1, LESS_THAN    = LT,
	EQ =  0, EQUAL        = EQ,
	GT =  1, GREATER_THAN = GT
};

template< typename TInt >
constexpr Relation to_relation(TInt const & x) {
	return x != TInt(0) ? (x < TInt(0) ? Relation::LT : Relation::GT) : Relation::EQ;
}

} // namespace BR
