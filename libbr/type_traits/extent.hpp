/**
 * @file
 * @brief 获取数组指定维度的大小
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T, Size I >
struct Extent : IntegerConstant< Size, 0 > {};

template< typename T, Size I >
struct Extent< T [], I > : IntegerConstant< Size, Extent< RemoveConstVolatile<T>, I - 1 >::value > {};

template< typename T >
struct Extent< T [], 0 > : IntegerConstant< Size,  0 > {};

template< typename T, Size S, Size I >
struct Extent< T [S], I > : IntegerConstant< Size, Extent< RemoveConstVolatile<T>, I - 1 >::value > {};

template< typename T, Size S >
struct Extent< T [S], 0 > : IntegerConstant< Size, S > {};

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 获取数组指定维度的大小
 * @tparam T
 * @tparam I 维度
 * @see IntegerConstant
 *
 * 如果 \em T 是至少 \em I 维的数组类型，那么封装的值第 \em I 维的大小；否则为 0
 */
template< typename T, Size I = 0 >
struct Extent : IntegerRewrap< Detail::TypeTraits::Extent< T, I > > {};

#if defined(BR_CXX14)

/**
 * @brief Rank 的模板变量版本
 * @tparam T
 * @see Rank
 */
template< typename T, Size I = 0 >
constexpr auto extent = integer_constant< Extent< T, I > >;

#endif // defined(BR_CXX14)

} // namespace BR
