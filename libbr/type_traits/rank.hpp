/**
 * @file
 * @brief 获取数组类型的维度
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 获取数组类型的维度
 * @tparam T
 * @see IntegerConstant
 * @see NotMemberObjectPointer
 *
 * 如果 \em T 是数组类型，那么封装的值为数组类型的维度；否则为 0
 */
template< typename T >
struct Rank;

#if defined(BR_AFTER_CXX11)

/**
 * @brief Rank 的模板变量版本
 * @tparam T
 * @see Rank
 */
template< typename T >
constexpr auto rank = integral_constant< Rank<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct Rank : public IntegralConstant< Size, 0 > {};

template< typename T >
struct Rank< T [] > : public IntegralConstant< Size, (Rank< RemoveConstVolatile<T> >{})() + 1 > {};

template< typename T, Size S >
struct Rank< T [S] > : public IntegralConstant< Size, (Rank< RemoveConstVolatile<T> >{})() + 1 > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct Rank : public IntegralRewrap< Detail::TypeTraits::Rank<T> > {};

} // namespace TypeTraits

} // namespace BR
