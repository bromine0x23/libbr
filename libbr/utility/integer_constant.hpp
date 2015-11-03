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
struct IntegerConstant : public TypeWrapper< IntegerConstant< TValue, v > > {

	/**
	 * @brief 整型常量类型
	 */
	using Value = TValue;

	/**
	 * @brief 整型常量值
	 */
	constexpr static TValue value = v;

	constexpr IntegerConstant() noexcept = default;

	/**
	 * @brief 返回整型常量值
	 */
	constexpr operator TValue() const noexcept {
		return value;
	}

	/**
	 * @brief 返回整型常量值
	 */
	constexpr auto operator()() const noexcept -> TValue {
		return value;
	}
};

template< typename TI >
using IntegerRewrap = IntegerConstant< typename TI::Value, TI::value >;

template< Size index >
using IndexConstant = IntegerConstant< Size, index >;

#if defined(BR_CXX14)

template< typename TI >
constexpr static typename TI::Value integer_constant = TI::value;

#endif // defined(BR_CXX14)

} // namespace BR

