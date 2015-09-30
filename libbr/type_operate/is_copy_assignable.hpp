/**
 * @file
 * @brief 检查类型是否可被拷贝赋值
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once
#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/is_assignable.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsCopyAssignable = BooleanAnd<
	IsReferenceable<T>,
	IsAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >
>;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被拷贝赋值
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotCopyAssignable
 *
 * 如果 \em T 可被拷贝赋值，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsCopyAssignable : Boolean< Detail::TypeOperate::IsCopyAssignable<T> > {};

/**
 * @brief IsCopyAssignable 的否定
 * @tparam T 待检查类型
 * @see IsCopyAssignable
 */
template< typename T >
struct NotCopyAssignable : BooleanNot< Detail::TypeOperate::IsCopyAssignable<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsCopyAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsCopyAssignable
 * @see not_copy_assignable
 */
template< typename T >
constexpr auto is_copy_assignable = IsCopyAssignable<T>::value;

/**
 * @brief NotCopyAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotCopyAssignable
 * @see is_copy_assignable
 */
template< typename T >
constexpr auto not_copy_assignable = NotCopyAssignable<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR