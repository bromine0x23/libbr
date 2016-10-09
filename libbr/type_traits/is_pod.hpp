/**
 * @file
 * @brief POD检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_POD)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_traits/is_void.hpp>
#endif // !BR_IS_POD

namespace BR {

/**
 * @brief 检查 \em T 是否是 \em POD 类型
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_IS_POD
 * @see BR::NotPOD
 *
 * 如果 \em T 是 \em POD 类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsPOD;

/**
 * @brief IsPOD 的否定
 * @tparam T 待检查类型
 * @see BR::IsPOD
 */
template< typename T >
struct NotPOD;

#if defined(BR_CXX14)

/**
 * @brief IsPOD 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::IsPOD
 * @see BR::not_pod
 */
template< typename T >
constexpr auto is_pod = bool_constant< IsPOD<T> >;

/**
 * @brief NotPOD 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NotPOD
 * @see BR::is_pod
 */
template< typename T >
constexpr auto not_pod = bool_constant< NotPOD<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_POD)

template< typename T >
using IsPOD = BooleanConstant< BR_IS_POD(T) >;

#else

template< typename T >
using IsPOD = BooleanOr< IsArray<T>, IsScalar<T>, IsVoid<T> >;

#endif // BR_IS_POD

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsPOD : public BooleanRewrapPositive< Detail::TypeTraits::IsPOD<T> > {};

template< typename T >
struct NotPOD : public BooleanRewrapNegative< Detail::TypeTraits::IsPOD<T> > {};

} // namespace BR
