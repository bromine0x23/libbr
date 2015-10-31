/**
 * @file
 * @brief 大于比较仿函数类
 * @author Bromine0x23
 * @since 2015/10/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/binary_functor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TX = void, typename TY = TX >
struct Greater;

template< typename TX, typename TY >
struct Greater : public BinaryFunctor< TX, TY > {
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX const & x, TY const & y) const -> decltype(x > y) {
		return x > y;
	}
};

template< typename TX >
struct Greater< TX, void > : public BinaryFunctor< TX, void > {
	template< typename TY >
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX const & x, TY && y) const -> decltype(x > forward<TY>(y)) {
		return x > forward<TY>(y);
	}
};

template< typename TY >
struct Greater< void, TY > : public BinaryFunctor< void, TY > {
	template< typename TX >
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX && x, TY const & y) const -> decltype(forward<TX>(x) > y) {
		return forward<TX>(x) > y;
	}
};

template<>
struct Greater< void, void > : public BinaryFunctor< void, void > {
	template< typename TX, typename TY >
	BR_CONSTEXPR_AFTER_CXX11 auto operator() (TX && x, TY && y) const -> decltype(forward<TX>(x) > forward<TY>(y)) {
		return forward<TX>(x) > forward<TY>(y);
	}
};

} // namespace BR
