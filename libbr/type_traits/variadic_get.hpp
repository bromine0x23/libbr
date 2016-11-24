/**
 * @file
 * @brief VariadicGet
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 从类型列表中取出指定位置的类型
 * @tparam index 索引
 * @tparam TTypes 类型列表
 * @see TypeWrapper
 * @see VariadicGet
 */
template< Size index, typename ... TTypes >
struct TypeVariadicGet;

/**
 * @brief TypeVariadicGet 的简写版本
 * @tparam index 索引
 * @tparam TTypes 类型列表
 * @see TypeVariadicGet
 */
template< Size index, typename ... TTypes >
using VariadicGet = TypeUnwrap< TypeVariadicGet< index, TTypes ... > >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< Size index, typename ... TTypes >
struct TypeVariadicGet;

template< Size index >
struct TypeVariadicGet<index> {
	static_assert(sizeof(index) == sizeof(Size), "Index out of range.");
};

template< typename THead, typename ... TTail >
struct TypeVariadicGet< 0, THead, TTail ... > : public TypeWrapper<THead> {};

template< Size index, typename THead, typename ... TTail >
struct TypeVariadicGet< index, THead, TTail ... > : public TypeVariadicGet< index - 1, TTail ... > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< Size index, typename ... TTypes >
struct TypeVariadicGet : public TypeRewrap< Detail::TypeTraits::TypeVariadicGet< index, TTypes... > > {};

} // namespace TypeTraits

} // namespace BR

