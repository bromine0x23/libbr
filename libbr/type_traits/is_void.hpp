/**
 * @file
 * @brief \em void 类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是 \em void 类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotVoid
 *
 * 如果 \em T 是 \em void 类型(包括带CV修饰的版本)，那么封装的值为 \em true ；否则为 \em false
 */
template<typename T>
struct IsVoid;

/**
 * @brief IsVoid 的否定
 * @tparam T 待检查类型
 * @see IsVoid
 */
template<typename T>
struct NotVoid;

/**
 * @brief IsVoid 的模板变量版本
 * @tparam T 待检查类型
 * @see IsVoid
 * @see not_void
 */
template<typename T>
constexpr auto is_void = boolean_constant<IsVoid<T>>;

/**
 * @brief NotVoid 的模板变量版本
 * @tparam T 待检查类型
 * @see NotVoid
 * @see is_void
 */
template<typename T>
constexpr auto not_void = boolean_constant<NotVoid<T>>;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template<typename T>
struct IsVoidBasic : public BooleanFalse {};

template<>
struct IsVoidBasic<void> : public BooleanTrue {};

template<typename T>
using IsVoid = IsVoidBasic<RemoveConstVolatile<T>>;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template<typename T>
struct IsVoid : public BooleanRewrapPositive< _::TypeTraits::IsVoid<T> > {};

template<typename T>
struct NotVoid : public BooleanRewrapNegative< _::TypeTraits::IsVoid<T> > {};

} // namespace TypeTraits

} // namespace BR
