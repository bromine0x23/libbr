/**
 * @file
 * @brief 除法运算符/
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/binary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief Functor for operator/
 * @tparam TLhs,TRhs
 */
template< typename TLhs = void, typename TRhs = TLhs >
struct Divide;

} // namespace Functional



inline namespace Functional {

template< typename TLhs, typename TRhs >
struct Divide : public BinaryFunctor< TLhs, TRhs > {
	constexpr decltype(auto) operator() (TLhs const & lhs, TRhs const & rhs) const {
		return lhs / rhs;
	}
};

template< typename TLhs >
struct Divide< TLhs, void > : public BinaryFunctor< TLhs, void > {
	template< typename TRhs >
	constexpr decltype(auto) operator() (TLhs const & lhs, TRhs && rhs) const {
		return lhs / forward<TRhs>(rhs);
	}
};

template< typename TRhs >
struct Divide< void, TRhs > : public BinaryFunctor< void, TRhs > {
	template< typename TLhs >
	constexpr decltype(auto) operator() (TLhs && lhs, TRhs const & rhs) const {
		return forward<TLhs>(lhs) / rhs;
	}
};

template<>
struct Divide< void, void > : public BinaryFunctor< void, void > {
	template< typename TLhs, typename TRhs >
	constexpr decltype(auto) operator() (TLhs && lhs, TRhs && rhs) const {
		return forward<TLhs>(lhs) / forward<TRhs>(rhs);
	}
};

} // namespace Functional

} // namespace BR