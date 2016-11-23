/**
 * @file
 * @brief class LessEqual<TLhs, TRhs>
 * @author Bromine0x23
 * @since 2015/10/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/binary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief Functor for operator<=
 * @tparam TLhs,TRhs
 */
template< typename TLhs = void, typename TRhs = TLhs >
struct LessEqual;

} // namespace Functional

inline namespace Functional {

template< typename TLhs, typename TRhs >
struct LessEqual : public BinaryFunctor< TLhs, TRhs > {
	constexpr auto operator() (TLhs const & lhs, TRhs const & rhs) const -> decltype(lhs <= rhs) {
		return lhs <= rhs;
	}
};

template< typename TLhs >
struct LessEqual< TLhs, void > : public BinaryFunctor< TLhs, void > {
	template< typename TRhs >
	constexpr auto operator() (TLhs const & lhs, TRhs && rhs) const -> decltype(lhs <= forward<TRhs>(rhs)) {
		return lhs <= forward<TRhs>(rhs);
	}
};

template< typename TRhs >
struct LessEqual< void, TRhs > : public BinaryFunctor< void, TRhs > {
	template< typename TLhs >
	constexpr auto operator() (TLhs && lhs, TRhs const & rhs) const -> decltype(forward<TLhs>(lhs) <= rhs) {
		return forward<TLhs>(lhs) <= rhs;
	}
};

template<>
struct LessEqual< void, void > : public BinaryFunctor< void, void > {
	template< typename TLhs, typename TRhs >
	constexpr auto operator() (TLhs && lhs, TRhs && rhs) const -> decltype(forward<TLhs>(lhs) <= forward<TRhs>(rhs)) {
		return forward<TLhs>(lhs) <= forward<TRhs>(rhs);
	}
};

} // namespace Functional

} // namespace BR
