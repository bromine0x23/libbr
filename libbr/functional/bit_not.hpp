/**
 * @file
 * @brief class BitNot<T>
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
 * @brief Functor for operator~
 * @tparam T
 */
template< typename T = void >
struct BitNot;

} // namespace Functional

inline namespace Functional {

template< typename T >
struct BitNot : public UnaryFunctor< T > {
	constexpr auto operator() (T const & t) const -> decltype(~t) {
		return ~t;
	}
};

template<>
struct BitNot<void> : public UnaryFunctor< void > {
	template< typename T >
	constexpr auto operator() (T && t) const -> decltype(~forward<T>(t)) {
		return ~forward<T>(t);
	}
};

} // namespace Functional

} // namespace BR
