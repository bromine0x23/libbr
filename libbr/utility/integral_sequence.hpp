/**
 * @file
 * @brief 整型常量类型
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 封装整型常量列表
 * @tparam TValue 整型类型
 * @tparam values 常量值
 */
template< typename TValue, TValue... values >
struct IntegralSequence {
	constexpr static Size size = sizeof...(values);

	constexpr operator Size() const noexcept {
		return size;
	}

	constexpr auto operator()() const noexcept -> TValue {
		return size;
	}
};

template< Size ... indices >
using IndexSequence = IntegralSequence< Size, indices ... >;

} // namespace BR

