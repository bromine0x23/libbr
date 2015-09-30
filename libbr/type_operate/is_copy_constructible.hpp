/**
 * @file
 * @brief 检查类型是否可被拷贝构造
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once
#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/is_constructible.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsCopyConstructible = BooleanAnd<
	IsReferenceable<T>,
	IsConstructible< T, AddLValueReference< AddConst<T> > >
>;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被拷贝构造
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotCopyConstructible
 *
 * 如果 \em T 可被拷贝构造，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsCopyConstructible : Boolean< Detail::TypeOperate::IsCopyConstructible<T> > {};

/**
 * @brief IsCopyConstructible 的否定
 * @tparam T 待检查类型
 * @see IsCopyConstructible
 */
template< typename T >
struct NotCopyConstructible : BooleanNot< Detail::TypeOperate::IsCopyConstructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsCopyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see IsCopyConstructible
 * @see not_copy_constructible
 */
template< typename T >
constexpr auto is_copy_constructible = IsCopyConstructible<T>::value;

/**
 * @brief NotCopyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotCopyConstructible
 * @see is_copy_constructible
 */
template< typename T >
constexpr auto not_copy_constructible = NotCopyConstructible<T>::value;

#endif // defined(BR_CXX14)


} // namespace BR