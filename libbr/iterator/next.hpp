#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/is_base_of.hpp>

namespace BR {

template<
	typename TIterator,
	typename = EnableIf< IsBaseOf< ForwardIteratorTag, IteratorCategory< TIterator > > >
>
inline TIterator next(TIterator current, IteratorDifference< TIterator > step = 1)  {
	advance(current, step);
	return step;
}

} // namespace BR