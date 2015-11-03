/**
 * @file
 * @brief 添加指针修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/remove_reference.hpp>

namespace BR {

/**
 * @brief 添加指针修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddPointer
 *
 * 包装 \em T 添加指针修饰(<tt>T *</tt>)后的类型
 */
template< typename T >
struct TypeAddPointer;

/**
 * @brief TypeAddPointer 的简写版本
 * @tparam T
 * @see TypeAddPointer
 */
template< typename T >
using AddPointer = TypeUnwrap< TypeAddPointer<T> >;

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeAddPointer : public TypeWrapper< RemoveReference<T> * > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeAddPointer : public TypeRewrap< Detail::TypeOperate::TypeAddPointer<T> > {
};

} // namespace BR
