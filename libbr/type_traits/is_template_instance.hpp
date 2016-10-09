/**
 * @file
 * @brief 模板类实例检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否是模板类实例
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotTemplateInstance
 *
 * 如果 \em T 是模板类实例，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsTemplateInstance;

/**
 * @brief IsTemplateInstance 的否定
 * @tparam T 待检查类型
 * @see IsTemplateInstance
 */
template< typename T >
struct NotTemplateInstance;

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



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsTemplateInstance : public BooleanFalse {};

template< template< typename ... > class TemplateClass, typename... TArgs >
struct IsTemplateInstance< TemplateClass< TArgs... > > : public BooleanTrue {};

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsTemplateInstance : public BooleanRewrapPositive< Detail::TypeTraits::IsTemplateInstance<T> > {};

template< typename T >
struct NotTemplateInstance : public BooleanRewrapNegative< Detail::TypeTraits::IsTemplateInstance<T> > {};

} // namespace BR