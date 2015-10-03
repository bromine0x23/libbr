/**
 * @file
 * @brief 模板类实例检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsTemplateInstance : BooleanFalse {};

template< template< typename ... > class TemplateClass, typename... TArgs >
struct IsTemplateInstance< TemplateClass< TArgs... > > : BooleanTrue {};

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是模板类实例
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotTemplateInstance
 *
 * 如果 \em T 是模板类实例，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsTemplateInstance : BooleanRewrapPositive< Detail::TypeTraits::IsTemplateInstance<T> > {};

/**
 * @brief IsTemplateInstance 的否定
 * @tparam T 待检查类型
 * @see IsTemplateInstance
 */
template< typename T >
struct NotTemplateInstance : BooleanRewrapNegative< Detail::TypeTraits::IsTemplateInstance<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsTemplateInstance 的模板变量版本
 * @tparam T 待检查类型
 * @see IsTemplateInstance
 * @see not_template_instance
 */
template< typename T >
constexpr auto is_template_instance = bool_constant< IsTemplateInstance<T> >;

/**
 * @brief NotTemplateInstance 的模板变量版本
 * @tparam T 待检查类型
 * @see NotTemplateInstance
 * @see is_template_instance
 */
template< typename T >
constexpr auto not_template_instance = bool_constant< NotTemplateInstance<T> >;

#endif // defined(BR_CXX14)

} // namespace BR