/**
 * @file
 * @brief 检查是否具有 \em nothrow 的析构函数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_HAS_NOTHROW_DESTRUCTOR)
#  include <libbr/type_traits/has_destructor.hpp>
#  include <libbr/utility/conjunction.hpp>
#  include <libbr/utility/declare_value.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 具有 \em nothrow 的析构函数
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see BR_HAS_NOTHROW_DESTRUCTOR
 * @see HasDestructor
 * @see NoNothrowDestructor
 *
 * 如果 \em T 具有 \em nothrow 的析构函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowDestructor;

/**
 * @brief HasNothrowDestructor 的否定
 * @tparam T 待检查类型
 * @see HasNothrowDestructor
 */
template< typename T >
struct NoNothrowDestructor;

/**
 * @brief HasNothrowDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasNothrowDestructor
 * @see BR::no_nothrow_destructor
 */
template< typename T >
constexpr auto has_nothrow_destructor = boolean_constant< HasNothrowDestructor<T> >;

/**
 * @brief NoNothrowDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoNothrowDestructor
 * @see BR::has_nothrow_destructor
 */
template< typename T >
constexpr auto no_nothrow_destructor = boolean_constant< NoNothrowDestructor<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

#if defined(BR_HAS_NOTHROW_DESTRUCTOR)

template< typename T >
using HasNothrowDestructor = BooleanConstant< BR_HAS_NOTHROW_DESTRUCTOR(T) >;

#else

template< typename T >
struct HasNothrowDestructorBasic : public BooleanConstant< noexcept(declare_value<T>().~T()) > {};

template< typename T >
struct HasNothrowDestructor : public Conjunction<
	HasDestructor<T>,
	HasNothrowDestructorBasic<T>
> {};

template< typename T, Size S >
struct HasNothrowDestructor<T[S]> : public HasNothrowDestructor<T> {};

template< typename T >
struct HasNothrowDestructor<T&> : public HasNothrowDestructor<T> {};

#endif // defined(BR_HAS_NOTHROW_DESTRUCTOR)

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct HasNothrowDestructor : public BooleanRewrapPositive< _::TypeTraits::HasNothrowDestructor<T> > {};

template< typename T >
struct NoNothrowDestructor : public BooleanRewrapNegative< _::TypeTraits::HasNothrowDestructor<T> > {};

} // namespace TypeTraits

} // namespace BR