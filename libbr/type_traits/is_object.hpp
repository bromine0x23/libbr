/**
 * @file
 * @brief 对象类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_function.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_void.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是对象类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsScalar
 * @see IsArray
 * @see IsClass
 * @see IsUnion
 * @see NotObject
 *
 * 如果 \em T 是对象类型(标量、数组、类、或联合)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsObject;

/**
 * @brief IsObject 的否定
 * @tparam T 待检查类型
 * @see IsObject
 */
template< typename T >
struct NotObject;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsObject 的模板变量版本
 * @tparam T 待检查类型
 * @see IsObject
 * @see not_object
 */
template< typename T >
constexpr auto is_object = boolean_constant< IsObject<T> >;

/**
 * @brief NotObject 的模板变量版本
 * @tparam T 待检查类型
 * @see NotObject
 * @see is_object
 */
template< typename T >
constexpr auto not_object = boolean_constant< NotObject<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using IsObject = BooleanAnd< NotReference<T>, NotVoid<T>, NotFunction<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsObject : public BooleanRewrapPositive< Detail::TypeTraits::IsObject<T> > {};

template< typename T >
struct NotObject : public BooleanRewrapNegative< Detail::TypeTraits::IsObject<T> > {};

} // namespace TypeTraits

} // namespace BR

