/**
 * @file
 * @brief TypeSequence
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 包装类型列表
 * @tparam T 被包装类型
 */
template< typename ... TTypes >
struct TypeSequence;

} // namespace Utility



namespace _ {
namespace Utility {

template< Size I, typename ... Ts >
struct TypeSequenceGet;

template< Size I >
struct TypeSequenceGet<I> {
	static_assert(I == 0, "Types<T...>::Get<I> index out of range");
	static_assert(I != 0, "Types<T...>::Get<I> index out of range");
};

template< typename THead, typename ... TTails >
struct TypeSequenceGet< 0, THead, TTails ... > : TypeWrapper<THead> {};

template< Size I, typename THead, typename ... TTails >
struct TypeSequenceGet< I, THead, TTails ... > : TypeSequenceGet< I - 1, TTails ... > {};

} // namespace Utility
} // namespace _

inline namespace Utility {

template< typename ... TTypes >
struct TypeSequence {
	constexpr static Size size = sizeof...(TTypes);

	template< Size I >
	using Get = TypeUnwrap< _::Utility::TypeSequenceGet< I, TTypes ... > >;

	constexpr TypeSequence() noexcept = default;
};
} // namespace Utility

} // namespace BR