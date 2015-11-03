/**
 * @file
 * @brief 兼容类型
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

/**
 * @brief 获取能兼容所给各个类型的类型
 * @tparam TTypes
 * @see TypeWrapper
 */
template< typename... TTypes >
struct TypeCommon;

/**
 * @brief TypeCommon 的简写版本
 * @tparam TTypes
 * @see TypeCommon
 */
template< typename... TTypes >
using Common = TypeUnwrap< TypeCommon< TTypes... > >;

namespace Detail {
namespace TypeOperate {

template< typename... TTypes >
struct TypeCommon;

template< typename T >
struct TypeCommon<T> : public TypeDecay<T> {
	static_assert(sizeof(T) > 0, "Type must be complete.");
};

template< typename T0, typename T1 >
struct TypeCommon< T0, T1 > : public TypeDecay< decltype(make_rvalue<bool>() ? make_rvalue<T0>() : make_rvalue<T1>()) > {
	static_assert(sizeof(T0) > 0, "Type must be complete.");
	static_assert(sizeof(T1) > 0, "Type must be complete.");
};

template < typename T0, typename T1, typename... Tn >
struct TypeCommon< T0, T1, Tn... > : public TypeCommon< Common< T0, T1 >, Tn... > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename... TTypes >
struct TypeCommon : public TypeRewrap< Detail::TypeOperate::TypeCommon< TTypes... > > {
};

} // namespace BR

