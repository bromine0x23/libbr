/**
 * @file
 * @brief 整型类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsIntegralBasic : BooleanFalse {
};

template<> struct IsIntegralBasic<   signed char      > : BooleanTrue {};
template<> struct IsIntegralBasic< unsigned char      > : BooleanTrue {};
template<> struct IsIntegralBasic<   signed short     > : BooleanTrue {};
template<> struct IsIntegralBasic< unsigned short     > : BooleanTrue {};
template<> struct IsIntegralBasic<   signed int       > : BooleanTrue {};
template<> struct IsIntegralBasic< unsigned int       > : BooleanTrue {};
template<> struct IsIntegralBasic<   signed long      > : BooleanTrue {};
template<> struct IsIntegralBasic< unsigned long      > : BooleanTrue {};
template<> struct IsIntegralBasic<   signed long long > : BooleanTrue {};
template<> struct IsIntegralBasic< unsigned long long > : BooleanTrue {};

template<> struct IsIntegralBasic< bool     > : BooleanTrue {};
template<> struct IsIntegralBasic< char     > : BooleanTrue {};
template<> struct IsIntegralBasic< wchar_t  > : BooleanTrue {};
template<> struct IsIntegralBasic< char16_t > : BooleanTrue {};
template<> struct IsIntegralBasic< char32_t > : BooleanTrue {};

#if defined(BR_HAS_INT128)
template<> struct IsIntegralBasic< SInt128 > : BooleanTrue {};
template<> struct IsIntegralBasic< UInt128 > : BooleanTrue {};
#endif // BR_HAS_INT128

template< typename T >
struct IsIntegral : IsIntegralBasic< RemoveConstVolatile<T> > {
};

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是整型类型
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::NotIntegral
 *
 * 如果 \em T 是整型类型(\em bool、\em char、\em char16_t、\em char32_t、\em wchar_t、\em short、\em int、\em long、<em>long long</em>及扩展整型类型，包括 \em signed 和 \em unsigned 和带CV修饰的版本)，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsIntegral : BooleanRewrapPositive< Detail::TypeTraits::IsIntegral<T> > {
};

/**
 * @brief IsIntegral 的否定
 * @tparam T 待检查类型
 * @see BR::IsIntegral
 */
template< typename T >
struct NotIntegral : BooleanRewrapNegative< Detail::TypeTraits::IsIntegral<T> > {
};

#if defined(BR_CXX14)

/**
 * @brief IsIntegral 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::IsIntegral
 * @see BR::not_integral
 */
template< typename T >
constexpr auto is_integral = bool_constant< IsIntegral<T> >;

/**
 * @brief NotInteger 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NotIntegral
 * @see BR::is_integral
 */
template< typename T >
constexpr auto not_integral = bool_constant< NotIntegral<T> >;

#endif // defined(BR_CXX14)

} // namespace BR