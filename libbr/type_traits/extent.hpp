/**
 * @file
 * @brief 获取数组指定维度的大小
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 获取数组指定维度的大小
 * @tparam T
 * @tparam I 维度
 * @see Utility::IntegralConstant
 *
 * 如果 \em T 是至少 \em I 维的数组类型，那么封装的值第 \em I 维的大小；否则为 0
 */
template< typename T, Size I = 0 >
struct Extent;

/**
 * @brief Rank 的模板变量版本
 * @tparam T
 * @see Rank
 */
template< typename T, Size I = 0 >
constexpr auto extent = integral_constant< Extent< T, I > >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T, Size I >
struct Extent;

template< typename T, Size I >
struct Extent : public IntegralConstant< Size, 0 > {};

template< typename T, Size I >
struct Extent< T [], I > : public IntegralConstant< Size, (Extent< RemoveConstVolatile<T>, I - 1 >{})() > {};

template< typename T >
struct Extent< T [], 0 > : public IntegralConstant< Size,  0 > {};

template< typename T, Size S, Size I >
struct Extent< T [S], I > : public IntegralConstant< Size, (Extent< RemoveConstVolatile<T>, I - 1 >{})() > {};

template< typename T, Size S >
struct Extent< T [S], 0 > : public IntegralConstant< Size, S > {};

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T, Size I >
struct Extent : public IntegralRewrap< _::TypeTraits::Extent< T, I > > {};

} // namespace TypeTraits

} // namespace BR
