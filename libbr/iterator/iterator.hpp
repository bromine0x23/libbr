#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>

namespace BR {
namespace Iterator {

template<
	typename TCategory,
	typename TValue,
	typename TDifference = BR::PointerDifference,
	typename TPointer = TValue *,
	typename TReference = TValue &
>
struct Iterator {
	using Difference = TDifference;
	using Value      = TValue;
	using Pointer    = TPointer;
	using Reference  = TReference;
	using Category   = TCategory;
};

} // namespace Iterator
} // namespace BR
