/**
 * @file
 * @brief class EqualTo<T>
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief Functor for x == ?
 * @tparam TLhs,TRhs
 */
template< typename TLhs = void, typename TRhs = TLhs >
struct EqualTo;

} // namespace Functional



inline namespace Functional {

template< typename TLhs, typename TRhs >
struct EqualTo : public UnaryFunctor< TRhs > {
	EqualTo(TLhs const & lhs) : lhs(lhs) {}

	constexpr auto operator() (TRhs const & rhs) const -> decltype(make_reference<TLhs>() == rhs) {
		return lhs == rhs;
	}

private:
	TLhs const & lhs;
};

template< typename TLhs >
struct EqualTo< TLhs, void > : public UnaryFunctor< void > {
	EqualTo(TLhs const & lhs) : lhs(lhs) {}

	template< typename TRhs >
	constexpr auto operator() (TRhs && rhs) const -> decltype(make_reference<TLhs>() == forward<TRhs>(rhs)) {
		return lhs == forward<TRhs>(rhs);
	}

private:
	TLhs const & lhs;
};

} // namespace Functional

} // namespace BR
