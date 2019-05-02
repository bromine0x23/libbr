/**
 * @file
 * @brief 数组类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/disjunction.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是约束长度的数组类型(<tt>U[S]</tt>)
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotBoundedArray
 *
 * 如果 \em T 是约束长度的数组类型，那么封装的值为 true ；否则为 false
 */
template< typename T >
struct IsBoundedArray;

/**
 * @brief IsBoundedArray 的否定
 * @tparam T 待检查类型
 * @see IsBoundedArray
 */
template< typename T >
struct NotBoundedArray;

/**
 * @brief 检查 \em T 是否是不约束长度的数组类型(<tt>U[]</tt>)
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotUnboundedArray
 *
 * 如果 \em T 是不约束长度的数组类型，那么封装的值为 true ；否则为 false
 */
template< typename T >
struct IsUnboundedArray;

/**
 * @brief IsUnboundedArray 的否定
 * @tparam T 待检查类型
 * @see IsUnboundedArray
 */
template< typename T >
struct NotUnboundedArray;

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
struct IsArray;

/**
 * @brief IsArray 的否定
 * @tparam T 待检查类型
 * @see IsArray
 */
template< typename T >
struct NotArray;

/**
 * @brief IsBoundedArray 的模板变量版本
 * @tparam T 待检查类型
 * @see IsBoundedArray
 * @see not_bounded_array
 */
template< typename T >
constexpr auto is_bounded_array = boolean_constant< IsBoundedArray<T> >;

/**
 * @brief NotBoundedArray 的模板变量版本
 * @tparam T 待检查类型
 * @see NotBoundedArray
 * @see is_bounded_array
 */
template< typename T >
constexpr auto not_bounded_array = boolean_constant< NotBoundedArray<T> >;

/**
 * @brief IsUnboundedArray 的模板变量版本
 * @tparam T 待检查类型
 * @see IsUnboundedArray
 * @see not_unbounded_array
 */
template< typename T >
constexpr auto is_unbounded_array = boolean_constant< IsUnboundedArray<T> >;

/**
 * @brief NotUnboundedArray 的模板变量版本
 * @tparam T 待检查类型
 * @see NotUnboundedArray
 * @see is_unbounded_array
 */
template< typename T >
constexpr auto not_unbounded_array = boolean_constant< NotUnboundedArray<T> >;

/**
 * @brief IsArray 的模板变量版本
 * @tparam T 待检查类型
 * @see IsArray
 * @see not_array
 */
template< typename T >
constexpr auto is_array = boolean_constant< IsArray<T> >;

/**
 * @brief NotArray 的模板变量版本
 * @tparam T 待检查类型
 * @see NotArray
 * @see is_array
 */
template< typename T >
constexpr auto not_array = boolean_constant< NotArray<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsBoundedArray : public BooleanFalse {};

template< typename T, Size S >
struct IsBoundedArray< T [S] > : public BooleanTrue {};

template< typename T >
struct IsUnboundedArray : public BooleanFalse {};

template< typename T >
struct IsUnboundedArray< T [] > : public BooleanTrue {};

template< typename T >
using IsArray = Disjunction< IsBoundedArray<T>, IsUnboundedArray<T> >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsBoundedArray : public BooleanRewrapPositive< _::TypeTraits::IsBoundedArray<T> > {};

template< typename T >
struct NotBoundedArray : public BooleanRewrapNegative< _::TypeTraits::IsBoundedArray<T> > {};

template< typename T >
struct IsUnboundedArray : public BooleanRewrapPositive< _::TypeTraits::IsUnboundedArray<T> > {};

template< typename T >
struct NotUnboundedArray : public BooleanRewrapNegative< _::TypeTraits::IsUnboundedArray<T> > {};

template< typename T >
struct IsArray : public BooleanRewrapPositive< _::TypeTraits::IsArray<T> > {};

template< typename T >
struct NotArray : public BooleanRewrapNegative< _::TypeTraits::IsArray<T> > {};

} // namespace TypeTraits

} // namespace BR
