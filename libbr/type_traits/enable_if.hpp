/**
 * @file
 * @brief 根据布尔常量启用或禁用一种函数重载或模板特化
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 选择性启用一种函数重载或模板特化
 * @tparam condition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeWrapper
 * @see TypeDisableIfValue
 *
 * 如果 \em condition为 \em true，则该类包装有类型 \em T ；否则该类为空类
 */
template< bool condition, typename T = void >
struct TypeEnableIfByValue;

/**
 * @brief 选择性禁用一种函数重载或模板特化
 * @tparam condition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeWrapper
 * @see TypeEnableIfByValue
 *
 * 如果 \em condition为 \em false，则该类包装有类型 \em T ；否则该类为空类
 */
template< bool condition, typename T = void >
struct TypeDisableIfValue;

/**
 * @brief TypeEnableIfByValue 使用布尔常量包装类的版本
 * @tparam TCondition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeEnableIfByValue
 */
template< typename TCondition, typename T = void >
using TypeEnableIf = TypeEnableIfByValue< TCondition{}, T >;

/**
 * @brief TypeDisableIfValue 使用布尔常量包装类的版本
 * @tparam TCondition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeDisableIfValue
 */
template< typename TCondition, typename T = void >
using TypeDisableIf = TypeDisableIfValue< TCondition{}, T >;

/**
 * @brief TypeEnableIfByValue 的简写版本
 * @tparam condition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeEnableIfByValue
 */
template< bool condition, typename T = void >
using EnableIfByValue = TypeUnwrap< TypeEnableIfByValue< condition, T > >;

/**
 * @brief TypeDisableIfValue 的简写版本
 * @tparam condition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeDisableIfValue
 */
template< bool condition, typename T = void >
using DisableIfValue = TypeUnwrap< TypeDisableIfValue< condition, T > >;

/**
 * @brief TypeEnableIf 的简写版本
 * @tparam condition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeEnableIf
 */
template< typename TCondition, typename T = void >
using EnableIf = TypeUnwrap< TypeEnableIf< TCondition, T > >;

/**
 * @brief TypeDisableIf 的简写版本
 * @tparam condition 开关布尔常量
 * @tparam T 包装类型
 * @see TypeDisableIf
 */
template< typename TCondition, typename T = void >
using DisableIf = TypeUnwrap< TypeDisableIf< TCondition, T > >;

} // namespace TypeTraits



inline namespace TypeTraits {

template< typename T >
struct TypeEnableIfByValue< true, T > : public TypeWrapper<T> {};

template< typename T >
struct TypeEnableIfByValue< false, T > {};

template< typename T >
struct TypeDisableIfValue< true, T > {};

template< typename T >
struct TypeDisableIfValue< false, T > : public TypeWrapper<T> {};

} // namespace TypeTraits

} // namespace BR