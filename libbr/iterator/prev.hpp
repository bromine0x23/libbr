#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/is_base_of.hpp>

namespace BR {
namespace Iterator {

template<
	typename TIterator,
	typename = TypeOperate::EnableIf<
		TypeOperate::IsBaseOf< BidirectionalIteratorTag, IteratorCategory< TIterator > >
	>
>
inline TIterator prev(TIterator current, IteratorDifference< TIterator > step = 1)  {
	advance(current, -step);
	return step;
}

} // namespace Iterator
} // namespace BR