/**
 * @file
 * @brief class template Types
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

/**
 * @brief 包装类型列表
 * @tparam T 被包装类型
 */
template< typename ... TTypes >
struct Types;



namespace Detail {
namespace Utility {

template< Size I, typename ... Ts >
struct TypesGet;

template< Size I >
struct TypesGet<I> {
	static_assert(I == 0, "Types<T...>::Get<I> index out of range");
	static_assert(I != 0, "Types<T...>::Get<I> index out of range");
};

template< typename THead, typename ... TTails >
struct TypesGet< 0, THead, TTails ... > : TypeWrapper<THead> {
};

template< Size I, typename THead, typename ... TTails >
struct TypesGet< I, THead, TTails ... > : TypesGet< I - 1, TTails ... > {
};

} // namespace Utility
} // namespace Detail

template< typename ... TTypes >
struct Types {
	constexpr static Size size = sizeof...(TTypes);

	template< Size I >
	using Get = TypeUnwrap< Detail::Utility::TypesGet< I, TTypes ... > >;

	constexpr Types() noexcept = default;
};

} // namespace BR