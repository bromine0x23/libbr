/**
 * @file
 * @brief 函数调用结果
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_callable.hpp>
#include <libbr/type_traits/member_pointer_traits.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

/**
 * @brief 获取调用结果类型
 * @tparam T 可调用对象
 * @tparam TArgs 调用参数
 * @see TypeWrapper
 *
 * 包装调用 \em T 类型变量的的返回值类型
 */
template< typename T, typename... TArgs >
struct TypeCallResult;

/**
 * @brief TypeCallResult 的简写版本
 * @tparam T 可调用对象
 * @tparam TArgs 调用参数
 * @see TypeCallResult
 */
template< typename T, typename... TArgs >
using CallResult = TypeUnwrap< TypeCallResult< T, TArgs... > >;

namespace Detail {
namespace TypeOperate {

template< typename TCallable, typename... TArgs >
struct TypeCallResultBasic : public TypeWrapper< decltype(invoke(make_rvalue<TCallable>(), make_rvalue<TArgs>()...)) > {
};

template< typename T, typename... TArgs >
struct TypeCallResultEmpty {
};

template< typename T, typename... TArgs >
using TypeCallResult = Conditional<  IsCallable< T, TArgs... >, TypeCallResultBasic< T, TArgs... > , TypeCallResultEmpty< T, TArgs... > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T, typename... TArgs >
struct TypeCallResult : public TypeRewrap< Detail::TypeOperate::TypeCallResult< T, TArgs... > > {
};

} // namespace BR