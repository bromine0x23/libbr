/**
 * @file
 * @brief 引用类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_rvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/disjunction.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是引用类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsLValueReference
 * @see IsRValueReference
 * @see NotLValueReference
 *
 * 如果\em T 是引用类型，那么封装的值为 \em true ；否则为 \em false
 */
template<typename T>
struct IsReference;

/**
 * @brief IsReference 的否定
 * @tparam T 待检查类型
 * @see IsReference
 */
template<typename T>
struct NotReference;

/**
 * @brief IsReference 的模板变量版本
 * @tparam T 待检查类型
 * @see IsReference
 * @see not_reference
 */
template<typename T>
constexpr auto is_reference = boolean_constant<IsReference<T>>;

/**
 * @brief NotReference 的模板变量版本
 * @tparam T 待检查类型
 * @see NotReference
 * @see is_reference
 */
template<typename T>
constexpr auto not_reference = boolean_constant<NotReference<T>>;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template<typename T>
using IsReference = Disjunction<IsLValueReference<T>, IsRValueReference<T>>;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template<typename T>
struct IsReference : public BooleanRewrapPositive< _::TypeTraits::IsReference<T> > {};

template<typename T>
struct NotReference : public BooleanRewrapNegative< _::TypeTraits::IsReference<T> > {};

} // namespace TypeTraits

} // namespace BR
