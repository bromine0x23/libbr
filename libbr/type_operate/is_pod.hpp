/**
 * @file
 * @brief POD检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_POD)
#  include <libbr/type_operate/is_scalar.hpp>
#  include <libbr/type_operate/is_void.hpp>
#endif // !BR_IS_POD

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_POD)

template< typename T >
using IsPOD = BooleanConstant< BR_IS_POD(T) >;

#else

template< typename T >
struct IsPOD : BooleanOr< IsScalar<T>, IsVoid<T> > {};

template< typename T >
struct IsPOD< T [] > : IsPOD<T> {};

template< typename T, Size S >
struct IsPOD< T [S] > : IsPOD<T> {};

#endif // BR_IS_POD

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是 \em POD 类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotPOD
 *
 * 如果 \em T 是 \em POD 类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsPOD : Boolean< Detail::TypeOperate::IsPOD<T> > {};

/**
 * @brief IsPOD 的否定
 * @tparam T 待检查类型
 * @see IsPOD
 */
template< typename T >
struct NotPOD : BooleanNot< Detail::TypeOperate::IsPOD<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsPOD 的模板变量版本
 * @tparam T 待检查类型
 * @see IsPOD
 * @see not_pod
 */
template< typename T >
constexpr auto is_pod = IsPOD<T>::value;

/**
 * @brief NotPOD 的模板变量版本
 * @tparam T 待检查类型
 * @see NotPOD
 * @see is_pod
 */
template< typename T >
constexpr auto not_pod = NotPOD<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
