/**
 * @file
 * @brief IntegralConstant - 整型常量包装器
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 包装指定类型的整型常量
 * @tparam TValue 整型类型
 * @tparam v 常量值
 */
template<typename TValue, TValue v>
struct IntegralConstant : public TypeWrapper<IntegralConstant<TValue, v>> {

	/**
	 * @brief 整型常量类型
	 */
	using Value = TValue;

	/**
	 * @brief 整型常量值
	 */
	constexpr static TValue value = v;

	constexpr IntegralConstant() noexcept = default;

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

/**
 * @brief 整型常量重包装
 * @tparam TConstant 包装器
 */
template<typename TConstant>
using IntegralRewrap = IntegralConstant<typename TConstant::Value, TConstant::value>;

/**
 * @brief 针对 Size 类型的特化
 */
template<Size index>
using SizeConstant = IntegralConstant<Size, index>;

/**
 * @brief 整型常量解包
 * @tparam TConstant 包装器
 */
template< typename TConstant >
constexpr typename TConstant::Value integral_constant = TConstant::value;

} // namespace Utility

} // namespace BR

