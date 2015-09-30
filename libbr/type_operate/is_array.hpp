/**
 * @file
 * @brief 数组类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsArrayKnownBounds : BooleanFalse {};

template< typename T, Size S >
struct IsArrayKnownBounds< T [S] > : BooleanTrue {};

template< typename T >
struct IsArrayUnknownBounds : BooleanFalse {};

template< typename T >
struct IsArrayUnknownBounds< T [] > : BooleanTrue {};

template< typename T >
using IsArray = BooleanOr< IsArrayKnownBounds<T>, IsArrayUnknownBounds<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是约束长度的数组类型(<tt>U[S]</tt>)
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotArrayKnownBounds
 *
 * 如果 \em T 是约束长度的数组类型，那么封装的值为 true ；否则为 false
 */
template< typename T >
struct IsArrayKnownBounds : Boolean< Detail::TypeOperate::IsArrayKnownBounds<T> > {};

/**
 * @brief IsArrayKnownBounds 的否定
 * @tparam T 待检查类型
 * @see IsArrayKnownBounds
 */
template< typename T >
struct NotArrayKnownBounds : BooleanNot< Detail::TypeOperate::IsArrayKnownBounds<T> > {};

/**
 * @brief 检查 \em T 是否是不约束长度的数组类型(<tt>U[]</tt>)
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotArrayUnknownBounds
 *
 * 如果 \em T 是不约束长度的数组类型，那么封装的值为 true ；否则为 false
 */
template< typename T >
struct IsArrayUnknownBounds : Boolean< Detail::TypeOperate::IsArrayUnknownBounds<T> > {};

/**
 * @brief IsArrayUnknownBounds 的否定
 * @tparam T 待检查类型
 * @see IsArrayUnknownBounds
 */
template< typename T >
struct NotArrayUnknownBounds : BooleanNot< Detail::TypeOperate::IsArrayUnknownBounds<T> > {};

/**
 * @brief 检查 \em T 是否是数组类型(<tt>U[S]</tt>或<tt>U[]</tt>)
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsArrayKnownBounds
 * @see IsArrayUnknownBounds
 * @see NotArray
 *
 * 如果 \em T 是数组类型，那么封装的值为 true ；否则为 false
 */
template< typename T >
struct IsArray : Boolean< Detail::TypeOperate::IsArray<T> > {};

/**
 * @brief IsArray 的否定
 * @tparam T 待检查类型
 * @see IsArray
 */
template< typename T >
struct NotArray : BooleanNot< Detail::TypeOperate::IsArray<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsArrayKnownBounds 的模板变量版本
 * @tparam T 待检查类型
 * @see IsArrayKnownBounds
 * @see not_array_known_bounds
 */
template< typename T >
constexpr auto is_array_known_bounds = IsArrayKnownBounds<T>::value;

/**
 * @brief NotArrayKnownBounds 的模板变量版本
 * @tparam T 待检查类型
 * @see NotArrayKnownBounds
 * @see is_array_known_bounds
 */
template< typename T >
constexpr auto not_array_known_bounds = NotArrayKnownBounds<T>::value;

/**
 * @brief IsArrayUnknownBounds 的模板变量版本
 * @tparam T 待检查类型
 * @see IsArrayUnknownBounds
 * @see not_array_unknown_bounds
 */
template< typename T >
constexpr auto is_array_unknown_bounds = IsArrayUnknownBounds<T>::value;

/**
 * @brief NotArrayUnknownBounds 的模板变量版本
 * @tparam T 待检查类型
 * @see NotArrayUnknownBounds
 * @see is_array_unknown_bounds
 */
template< typename T >
constexpr auto not_array_unknown_bounds = NotArrayUnknownBounds<T>::value;

/**
 * @brief IsArray 的模板变量版本
 * @tparam T 待检查类型
 * @see IsArray
 * @see not_array
 */
template< typename T >
constexpr auto is_array = IsArray<T>::value;

/**
 * @brief NotArray 的模板变量版本
 * @tparam T 待检查类型
 * @see NotArray
 * @see is_array
 */
template< typename T >
constexpr auto not_array = NotArray<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
