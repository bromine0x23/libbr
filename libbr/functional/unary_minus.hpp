/**
 * @file
 * @brief class UnaryMinus
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TX = void >
struct UnaryMinus;

template< typename TX >
struct UnaryMinus : public UnaryFunctor< TX > {
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX const & x) const -> decltype(-x) {
		return -x;
	}
};

template<>
struct UnaryMinus<void> : public UnaryFunctor< void > {
	template< typename TX >
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX && x) const -> decltype(-forward<TX>(x)) {
		return -forward<TX>(x);
	}
};

} // namespace BR
