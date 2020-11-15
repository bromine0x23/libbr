/**
 * @file
 * @brief 兼容类型
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/decay.hpp>
#include <libbr/utility/declare_value.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

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

} // namespace TypeTransform



namespace _::TypeTransform {

template< typename... TTypes >
struct TypeCommon;

template< typename T >
struct TypeCommon<T> : public TypeDecay<T> {
	static_assert(sizeof(T) > 0, "Type must be complete.");
};

template< typename T0, typename T1 >
struct TypeCommon< T0, T1 > : public TypeDecay< decltype(declare_value<bool>() ? declare_value<T0>() : declare_value<T1>()) > {
	static_assert(sizeof(T0) > 0, "Type must be complete.");
	static_assert(sizeof(T1) > 0, "Type must be complete.");
};

template < typename T0, typename T1, typename... Tn >
struct TypeCommon< T0, T1, Tn... > : public TypeCommon< Common< T0, T1 >, Tn... > {};

} // namespace _::TypeTransform

inline namespace TypeTransform {

template< typename... TTypes >
struct TypeCommon : public TypeRewrap< _::TypeTransform::TypeCommon< TTypes... > > {};

} // namespace TypeTransform

} // namespace BR

