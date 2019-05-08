/**
 * @file
 * @brief 衰变类型
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_function.hpp>
#include <libbr/type_transform/add_pointer.hpp>
#include <libbr/type_transform/remove_extent.hpp>
#include <libbr/type_transform/remove_reference.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/conditional.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 获取 \em T 类型变量作为参数按值传递给函数时的类型
 * @tparam T
 * @see TypeWrapper
 * @see Decay
 *
 * 包装的类型按以下规则求得
 * - 对于数组类型，应用数组到指针的转换规则：<code>AddPointer< RemoveExtent< RemoveReference<T> > ></code>
 * - 对于函数类型，应用函数到指针的转换规则：<code>AddPointer< RemoveReference<T> ></code>
 * - 对于其他类型，应用左值至右值的转换规则：<code>RemoveConstVolatile< RemoveReference<T> ></code>
 */
template< typename T >
struct TypeDecay;

/**
 * @brief TypeDecay 的简写版本
 * @tparam T
 * @see TypeDecay
 */
template< typename T >
using Decay = TypeUnwrap< TypeDecay<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
using DecayBasic = Conditional<
	IsArray<T>,
	AddPointer< RemoveExtent<T> >,
	Conditional<
		IsFunction<T>,
		AddPointer<T>,
		RemoveConstVolatile<T>
	>
>;

template< typename T >
using Decay = DecayBasic< RemoveReference<T> >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct TypeDecay : TypeWrapper< _::TypeTraits::Decay<T> > {};

} // namespace TypeTraits

} // namespace BR
