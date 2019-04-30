/**
 * @file
 * @brief 检查两个类型是否相同
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T0 、 \em T1 是否相同
 * @tparam T0,T1 待检查类型
 * @see IntegerConstant
 * @see NotSame
 *
 * 如果 \em T0 、 \em T1 是相同，那么封装的值为 \em true ；否则为 \em false
 */
template<typename T0, typename T1>
struct IsSame;

/**
 * @brief IsSame 的否定
 * @tparam T0,T1 待检查类型
 * @see IsSame
 */
template<typename T0, typename T1>
struct NotSame;

/**
 * @brief IsSame 的模板变量版本
 * @tparam T0,T1 待检查类型
 * @see IsSame
 * @see not_same
 */
template<typename T0, typename T1>
constexpr auto is_same = boolean_constant<IsSame<T0, T1>>;

/**
 * @brief NotSame 的模板变量版本
 * @tparam T0,T1 待检查类型
 * @see NotSame
 * @see is_same
 */
template<typename T0, typename T1>
constexpr auto not_same = boolean_constant<NotSame<T0, T1>>;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template<typename T0, typename T1>
struct IsSame : public BooleanFalse {};

template<typename T>
struct IsSame<T, T> : public BooleanTrue {};

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template<typename T0, typename T1>
struct IsSame : public BooleanRewrapPositive< _::TypeTraits::IsSame<T0, T1> > {};

template<typename T0, typename T1>
struct NotSame : public BooleanRewrapNegative< _::TypeTraits::IsSame<T0, T1> > {};

} // namespace TypeTraits

} // namespace BR