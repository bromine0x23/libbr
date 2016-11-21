/**
 * @file
 * @brief class LogicalNot<T>
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
 * Functor for operator!
 * @tparam T
 */
template< typename T = void >
struct LogicalNot;

} // namespace Functional

inline namespace Functional {

template< typename T >
struct LogicalNot : public UnaryFunctor< T > {
	constexpr auto operator() (T const & t) const -> decltype(!t) {
		return !t;
	}
};

template<>
struct LogicalNot<void> : public UnaryFunctor< void > {
	template< typename T >
	constexpr auto operator() (T && t) const -> decltype(!forward<T>(t)) {
		return !forward<T>(t);
	}
};

} // namespace Functional

} // namespace BR
