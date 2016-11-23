/**
 * @file
 * @brief class UnaryPlus<T>
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief Functor for unary operator+
 * @tparam T
 */
template< typename T = void >
struct UnaryPlus;

} // namespace Functional

inline namespace Functional {

template< typename T >
struct UnaryPlus : public UnaryFunctor< T > {
	constexpr auto operator() (T const & t) const -> decltype(+t) {
		return +t;
	}
};

template<>
struct UnaryPlus<void> : public UnaryFunctor< void > {
	template< typename T >
	constexpr auto operator() (T && t) const -> decltype(+forward<T>(t)) {
		return +forward<T>(t);
	}
};

} // namespace Functional

} // namespace BR
