/**
 * @file
 * @brief 逻辑非运算符
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief Functor for operator!
 * @tparam T
 */
template< typename T = void >
struct LogicalNot;

} // namespace Functional



inline namespace Functional {

template< typename T >
struct LogicalNot : public UnaryFunctor< T > {
	constexpr decltype(auto) operator() (T const & t) const {
		return !t;
	}
};

template<>
struct LogicalNot<void> : public UnaryFunctor< void > {
	template< typename T >
	constexpr decltype(auto) operator() (T && t) const {
		return !forward<T>(t);
	}
};

} // namespace Functional

} // namespace BR
