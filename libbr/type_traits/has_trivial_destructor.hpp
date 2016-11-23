/**
 * @file
 * @brief 检查是否具有平凡的析构函数
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_DESTRUCTOR)
#  include <libbr/type_traits/boolean.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_traits/remove_all_extents.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有平凡的析构函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR_HAS_TRIVIAL_DESTRUCTOR
 * @see HasDestructor
 * @see NoTrivialDestructor
 *
 * 如果 \em T 具有平凡的析构函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialDestructor;

/**
 * @brief HasTrivialDestructor 的否定
 * @tparam T 待检查类型
 * @see HasTrivialDestructor
 */
template< typename T >
struct NoTrivialDestructor;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasTrivialDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasTrivialDestructor
 * @see no_trivial_destructor
 */
template< typename T >
constexpr auto has_trivial_destructor = boolean_constant< HasTrivialDestructor<T> >;

/**
 * @brief NoTrivialDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoTrivialDestructor
 * @see has_trivial_destructor
 */
template< typename T >
constexpr auto no_trivial_destructor = boolean_constant< NoTrivialDestructor<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#if defined(BR_HAS_TRIVIAL_DESTRUCTOR)

template< typename T >
using HasTrivialDestructor = BooleanConstant< BR_HAS_TRIVIAL_DESTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialDestructorBasic = BooleanOr< IsReference<T>, IsScalar<T> >;

template< typename T >
using HasTrivialDestructor = HasTrivialDestructorBasic< RemoveAllExtents<T> >;

#endif // defined(BR_HAS_TRIVIAL_DESTRUCTOR)

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasTrivialDestructor : public BooleanRewrapPositive< Detail::TypeTraits::HasTrivialDestructor<T> > {};

template< typename T >
struct NoTrivialDestructor : public BooleanRewrapNegative< Detail::TypeTraits::HasTrivialDestructor<T> > {};

} // namespace TypeTraits

} // namespace BR