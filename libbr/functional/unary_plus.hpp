/**
 * @file
 * @brief 一元加运算符
 * @author Bromine0x23
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
	constexpr decltype(auto) operator() (T const & t) const {
		return +t;
	}
};

template<>
struct UnaryPlus<void> : public UnaryFunctor< void > {
	template< typename T >
	constexpr decltype(auto) operator() (T && t) const {
		return +forward<T>(t);
	}
};

} // namespace Functional

} // namespace BR
