/**
 * @file
 * @brief 检查是否具有 \em nothrow 的析构函数
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_NOTHROW_DESTRUCTOR)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_traits/has_destructor.hpp>
#  include <libbr/type_traits/is_array.hpp>
#endif

namespace BR {

/**
 * @brief 检查 \em T 具有 \em nothrow 的析构函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_HAS_NOTHROW_DESTRUCTOR
 * @see BR::HasDestructor
 * @see BR::NoNothrowDestructor
 *
 * 如果 \em T 具有 \em nothrow 的析构函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowDestructor;

/**
 * @brief HasNothrowDestructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasNothrowDestructor
 */
template< typename T >
struct NoNothrowDestructor;

#if defined(BR_CXX14)

/**
 * @brief HasNothrowDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasNothrowDestructor
 * @see BR::no_nothrow_destructor
 */
template< typename T >
constexpr auto has_nothrow_destructor = bool_constant< HasNothrowDestructor<T> >;

/**
 * @brief NoNothrowDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoNothrowDestructor
 * @see BR::has_nothrow_destructor
 */
template< typename T >
constexpr auto no_nothrow_destructor = bool_constant< NoNothrowDestructor<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

#if defined(BR_HAS_NOTHROW_DESTRUCTOR)

template< typename T >
using HasNothrowDestructor = BooleanConstant< BR_HAS_NOTHROW_DESTRUCTOR(T) >;

#else

template< typename T >
struct HasNothrowDestructorBasic : public BooleanConstant< noexcept(make_rvalue<T>().~T()) > {};

template< typename T >
struct HasNothrowDestructor : public BooleanAnd<
	HasDestructor<T>,
	HasNothrowDestructorBasic<T>
> {};

template< typename T, Size S >
struct HasNothrowDestructor<T[S]> : public HasNothrowDestructor<T> {};

template< typename T >
struct HasNothrowDestructor<T&> : public HasNothrowDestructor<T> {};

#endif // defined(BR_HAS_NOTHROW_DESTRUCTOR)

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasNothrowDestructor : public BooleanRewrapPositive< Detail::TypeTraits::HasNothrowDestructor<T> > {};

template< typename T >
struct NoNothrowDestructor : public BooleanRewrapNegative< Detail::TypeTraits::HasNothrowDestructor<T> > {};

} // namespace BR