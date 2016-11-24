/**
 * @file
 * @brief 兼容类型
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/type_traits/decay.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

inline namespace TypeTraits {

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

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

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
struct TypeCommon< T0, T1, Tn... > : public TypeCommon< Common< T0, T1 >, Tn... > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename... TTypes >
struct TypeCommon : public TypeRewrap< Detail::TypeTraits::TypeCommon< TTypes... > > {};

} // namespace TypeTraits

} // namespace BR

