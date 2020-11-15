/**
 * @file
 * @brief 位右移运算符
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/binary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief 包装运算符&gt;&gt;的函数对象
 * @tparam TLhs,TRhs
 */
template< typename TLhs = void, typename TRhs = TLhs >
struct BitRShift;

} // namespace Functional



inline namespace Functional {

template< typename TLhs, typename TRhs >
struct BitRShift : public BinaryFunctor< TLhs, TRhs > {
	constexpr decltype(auto) operator() (TLhs const & lhs, TRhs const & rhs) const {
		return lhs >> rhs;
	}
};

template< typename TLhs >
struct BitRShift< TLhs, void > : public BinaryFunctor< TLhs, void > {
	template< typename TRhs >
	constexpr decltype(auto) operator() (TLhs const & lhs, TRhs && rhs) const {
		return lhs >> forward<TRhs>(rhs);
	}
};

template< typename TRhs >
struct BitRShift< void, TRhs > : public BinaryFunctor< void, TRhs > {
	template< typename TLhs >
	constexpr decltype(auto) operator() (TLhs && lhs, TRhs const & rhs) const {
		return forward<TLhs>(lhs) >> rhs;
	}
};

template<>
struct BitRShift< void, void > : public BinaryFunctor< void, void > {
	template< typename TLhs, typename TRhs >
	constexpr decltype(auto) operator() (TLhs && lhs, TRhs && rhs) const {
		return forward<TLhs>(lhs) >> forward<TRhs>(rhs);
	}
};

} // namespace Functional

} // namespace BR