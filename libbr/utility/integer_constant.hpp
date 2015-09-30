/**
 * @file
 * @brief 整型常量类型
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 包装指定类型的整型静态常量
 * @tparam TValue 整型类型
 * @tparam v 常量值
 */
template< typename TValue, TValue v >
struct IntegerConstant : TypeWrapper< IntegerConstant< TValue, v > > {

	/**
	 * @brief 整型常量类型
	 */
	using Value = TValue;

	/**
	 * @brief 整型常量值
	 */
	constexpr static auto value = v;

	/**
	 * @brief 返回整型常量值
	 */
	constexpr operator TValue() const {
		return value;
	}

	/**
	 * @brief 返回整型常量值
	 */
	constexpr TValue operator()() const {
		return value;
	}
};

/**
 * @brief 封装整型常量列表
 * @tparam TValue 整型类型
 * @tparam values 常量值
 */
template< typename TValue, TValue... values >
struct Integers {};

#if defined(BR_CXX14)

template< typename TI >
constexpr static typename TI::Value integer_constant = TI::value;

#endif // defined(BR_CXX14)

} // namespace BR

