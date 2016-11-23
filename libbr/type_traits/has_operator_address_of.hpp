/**
 * @file
 * @brief HasOperatorAddressOf
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/types.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief HasOperatorAddressOf
 * @tparam T 待检查类型
 * @see IntegerConstant
 */
template< typename T >
struct HasOperatorAddressOf;

/**
 * @brief HasOperatorAddressOf 的否定
 * @tparam T 待检查类型
 * @see HasOperatorAddressOf
 */
template< typename T >
struct NoOperatorAddressOf;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasOperatorAddressOf 的模板变量版本
 * @tparam T 待检查类型
 * @see HasOperatorAddressOf
 * @see no_operator_address_of
 */
template< typename T >
constexpr auto has_operator_address_of = boolean_constant< HasOperatorAddressOf<T> >;

/**
 * @brief NoOperatorAddressOf 的模板变量版本
 * @tparam T 待检查类型
 * @see NoOperatorAddressOf
 * @see has_operator_address_of
 */
template< typename T >
constexpr auto no_operator_address_of = boolean_constant< NoOperatorAddressOf<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

struct HasOperatorAddressOfFreeTest {
	template< typename T >
	static auto test(int) -> typename Types< decltype(operator&(make_value<T>())), BooleanTrue >::template Get<1>;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T >
using HasOperatorAddressOfFree = decltype(HasOperatorAddressOfFreeTest::test<T>(0));

struct HasOperatorAddressOfMemberTest {
	template< typename T >
	static auto test(int) -> typename Types< decltype(make_value<T>().operator&()), BooleanTrue >::template Get<1>;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T >
using HasOperatorAddressOfMember = decltype(HasOperatorAddressOfMemberTest::test<T>(0));

template< typename T >
struct HasOperatorAddressOf : public BooleanOr< HasOperatorAddressOfFree<T>, HasOperatorAddressOfMember<T> > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasOperatorAddressOf : public BooleanRewrapPositive< Detail::TypeTraits::HasOperatorAddressOf<T> > {};

template< typename T >
struct NoOperatorAddressOf : public BooleanRewrapNegative< Detail::TypeTraits::HasOperatorAddressOf<T> > {};

} // namespace TypeTraits

} // namespace BR