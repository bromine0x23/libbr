/**
 * @file
 * @brief 获取数组类型的维度
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct Rank : IntegerConstant< Size, 0 > {};

template< typename T >
struct Rank< T [] > : IntegerConstant< Size, Rank< RemoveConstVolatile<T> >::value + 1 > {};

template< typename T, Size S >
struct Rank< T [S] > : IntegerConstant< Size, Rank< RemoveConstVolatile<T> >::value + 1 > {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 获取数组类型的维度
 * @tparam T
 * @see IntegerConstant
 * @see NotMemberObjectPointer
 *
 * 如果 \em T 是数组类型，那么封装的值为数组类型的维度；否则为 0
 */
template< typename T >
using Rank = IntegerConstant< Size, Detail::TypeOperate::Rank<T>::value >;

#if defined(BR_CXX14)

/**
 * @brief Rank 的模板变量版本
 * @tparam T
 * @see Rank
 */
template< typename T >
constexpr auto rank = Rank<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
