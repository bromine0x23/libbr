/**
 * @file
 * @brief 位与运算符
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/binary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief Functor for operator&
 * @tparam TLhs,TRhs
 */
template< typename TLhs = void, typename TRhs = TLhs >
struct BitAnd;

} // namespace Functional



inline namespace Functional {

template< typename TLhs, typename TRhs >
struct BitAnd : public BinaryFunctor< TLhs, TRhs > {
	constexpr decltype(auto) operator() (TLhs const & lhs, TRhs const & rhs) const {
		return lhs & rhs;
	}
};

template< typename TLhs >
struct BitAnd< TLhs, void > : public BinaryFunctor< TLhs, void > {
	template< typename TRhs >
	constexpr decltype(auto) operator() (TLhs const & lhs, TRhs && rhs) const {
		return lhs & forward<TRhs>(rhs);
	}
};

template< typename TRhs >
struct BitAnd< void, TRhs > : public BinaryFunctor< void, TRhs > {
	template< typename TLhs >
	constexpr decltype(auto) operator() (TLhs && lhs, TRhs const & rhs) const {
		return forward<TLhs>(lhs) & rhs;
	}
};

template<>
struct BitAnd< void, void > : public BinaryFunctor< void, void > {
	template< typename TLhs, typename TRhs >
	constexpr decltype(auto) operator() (TLhs && lhs, TRhs && rhs) const {
		return forward<TLhs>(lhs) & forward<TRhs>(rhs);
	}
};

} // namespace Functional

} // namespace BR