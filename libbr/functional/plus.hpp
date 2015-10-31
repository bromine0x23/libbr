/**
 * @file
 * @brief class Plus
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/binary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TX = void, typename TY = TX >
struct Plus;

template< typename TX, typename TY >
struct Plus : public BinaryFunctor< TX, TY > {
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX const & x, TY const & y) const -> decltype(x + y) {
		return x + y;
	}
};

template< typename TX >
struct Plus< TX, void > : public BinaryFunctor< TX, void > {
	template< typename TY >
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX const & x, TY && y) const -> decltype(x + forward<TY>(y)) {
		return x + forward<TY>(y);
	}
};

template< typename TY >
struct Plus< void, TY > : public BinaryFunctor< void, TY > {
	template< typename TX >
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX && x, TY const & y) const -> decltype(forward<TX>(x) + y) {
		return forward<TX>(x) + y;
	}
};

template<>
struct Plus< void, void > : public BinaryFunctor< void, void > {
	template< typename TX, typename TY >
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX && x, TY && y) const -> decltype(forward<TX>(x) + forward<TY>(y)) {
		return forward<TX>(x) + forward<TY>(y);
	}
};

} // namespace BR