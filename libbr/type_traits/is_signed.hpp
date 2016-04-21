/**
 * @file
 * @brief 有符号整型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_traits/is_enum.hpp>
#include <libbr/type_traits/is_integral.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsSignedBasic {
	using Type = RemoveConstVolatile<T>;
	constexpr static auto value = static_cast<Type>(-1) < static_cast<Type>(0);
};

template< typename T >
using IsSigned = BooleanAnd< BooleanOr< IsIntegral<T>, IsEnum<T> >, BooleanConstant< IsSignedBasic<T>::value > >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是有符号整型类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsUnsigned
 * @see MakeSigned
 * @see NotSigned
 *
 * 如果 \em T 是有符号整型类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsSigned : BooleanRewrapPositive< Detail::TypeTraits::IsSigned<T> > {
};

/**
 * @brief IsSigned 的否定
 * @tparam T 待检查类型
 * @see IsSigned
 */
template< typename T >
struct NotSigned : BooleanRewrapNegative< Detail::TypeTraits::IsSigned<T> > {
};

#if defined(BR_CXX14)

/**
 * @brief IsSigned 的模板变量版本
 * @tparam T 待检查类型
 * @see IsSigned
 * @see not_signed
 */
template< typename T >
constexpr auto is_signed = bool_constant< IsSigned<T> >;

/**
 * @brief NotSigned 的模板变量版本
 * @tparam T 待检查类型
 * @see NotSigned
 * @see is_signed
 */
template< typename T >
constexpr auto not_signed = bool_constant< NotSigned<T> >;

#endif // defined(BR_CXX14)

} // namespace BR