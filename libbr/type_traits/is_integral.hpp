/**
 * @file
 * @brief 整型类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是整型类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see NotIntegral
 *
 * 如果 \em T 是整型类型(\em bool、\em char、\em char16_t、\em char32_t、\em wchar_t、\em short、\em int、\em long、<em>long long</em>及扩展整型类型，包括 \em signed 和 \em unsigned 和带CV修饰的版本)，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsIntegral;

/**
 * @brief IsIntegral 的否定
 * @tparam T 待检查类型
 * @see IsIntegral
 */
template< typename T >
struct NotIntegral;

/**
 * @brief IsIntegral 的模板变量版本
 * @tparam T 待检查类型
 * @see IsIntegral
 * @see not_integral
 */
template< typename T >
constexpr auto is_integral = boolean_constant< IsIntegral<T> >;

/**
 * @brief NotInteger 的模板变量版本
 * @tparam T 待检查类型
 * @see NotIntegral
 * @see is_integral
 */
template< typename T >
constexpr auto not_integral = boolean_constant< NotIntegral<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsIntegralBasic : public BooleanFalse {};

template<> struct IsIntegralBasic<   signed char      > : public BooleanTrue {};
template<> struct IsIntegralBasic< unsigned char      > : public BooleanTrue {};
template<> struct IsIntegralBasic<   signed short     > : public BooleanTrue {};
template<> struct IsIntegralBasic< unsigned short     > : public BooleanTrue {};
template<> struct IsIntegralBasic<   signed int       > : public BooleanTrue {};
template<> struct IsIntegralBasic< unsigned int       > : public BooleanTrue {};
template<> struct IsIntegralBasic<   signed long      > : public BooleanTrue {};
template<> struct IsIntegralBasic< unsigned long      > : public BooleanTrue {};
template<> struct IsIntegralBasic<   signed long long > : public BooleanTrue {};
template<> struct IsIntegralBasic< unsigned long long > : public BooleanTrue {};

template<> struct IsIntegralBasic< bool     > : public BooleanTrue {};
template<> struct IsIntegralBasic< char     > : public BooleanTrue {};
template<> struct IsIntegralBasic< wchar_t  > : public BooleanTrue {};
template<> struct IsIntegralBasic< char16_t > : public BooleanTrue {};
template<> struct IsIntegralBasic< char32_t > : public BooleanTrue {};

#if defined(BR_HAS_INT128)
template<> struct IsIntegralBasic< SInt128 > : public BooleanTrue {};
template<> struct IsIntegralBasic< UInt128 > : public BooleanTrue {};
#endif // BR_HAS_INT128

template< typename T >
using IsIntegral = IsIntegralBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsIntegral : public BooleanRewrapPositive< _::TypeTraits::IsIntegral<T> > {};

template< typename T >
struct NotIntegral : public BooleanRewrapNegative< _::TypeTraits::IsIntegral<T> > {};

} // namespace TypeTraits

} // namespace BR