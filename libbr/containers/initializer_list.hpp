#pragma once

#include <initializer_list>

#include <libbr/config.hpp>

namespace BR {

inline namespace Containers {

template< typename TElement >
using InitializerList = std::initializer_list<TElement>;

template< typename TElement >
constexpr auto empty(InitializerList<TElement> list) -> Boolean {
	return list.size() == 0;
}

template< typename TElement >
constexpr auto data(InitializerList<TElement> list) -> TElement * {
	return list.begin();
}

} // namespace Containers

} // namespace BR