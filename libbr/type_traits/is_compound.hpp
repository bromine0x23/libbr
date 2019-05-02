/**
 * @file
 * @brief 复合类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/negation.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是复合类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsFundamental
 * @see NotCompound
 *
 * 如果 \em T 是复合类型(非基本类型，包括数组、函数、对象指针、函数指针、成员对象指针、成员函数指针、引用、类、联合、枚举及其cv变种)，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsCompound;

/**
 * @brief IsCompound 的否定
 * @tparam T 待检查类型
 * @see IsCompound
 */
template< typename T >
struct NotCompound;

/**
 * @brief IsCompound 的模板变量版本
 * @tparam T 待检查类型
 * @see IsCompound
 * @see not_compound
 */
template< typename T >
constexpr auto is_compound = boolean_constant< IsCompound<T> >;

/**
 * @brief NotCompound 的模板变量版本
 * @tparam T 待检查类型
 * @see NotCompound
 * @see is_compound
 */
template< typename T >
constexpr auto not_compound = boolean_constant< NotCompound<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
using IsCompound = Negation< IsFundamental<T> >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsCompound : public BooleanRewrapPositive< _::TypeTraits::IsCompound<T> > {};

template< typename T >
struct NotCompound : public BooleanRewrapNegative< _::TypeTraits::IsCompound<T> > {};

} // namespace TypeTraits

} // namespace BR


