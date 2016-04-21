/**
 * @file
 * @brief HasOperatorAddressOf
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/types.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

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
struct NoOperatorAddressOf : BooleanNot< HasOperatorAddressOf<T> > {
};

#if defined(BR_CXX14)

/**
 * @brief HasOperatorAddressOf 的模板变量版本
 * @tparam T 待检查类型
 * @see HasOperatorAddressOf
 * @see no_operator_address_of
 */
template< typename T >
constexpr auto has_operator_address_of = bool_constant< HasOperatorAddressOf<T> >;

/**
 * @brief NoOperatorAddressOf 的模板变量版本
 * @tparam T 待检查类型
 * @see NoOperatorAddressOf
 * @see has_operator_address_of
 */
template< typename T >
constexpr auto no_operator_address_of = bool_constant< NoOperatorAddressOf<T> >;

#endif // defined(BR_CXX14)

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

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasOperatorAddressOf : BooleanRewrap< BooleanOr< Detail::TypeTraits::HasOperatorAddressOfFree<T>, Detail::TypeTraits::HasOperatorAddressOfMember<T> > > {
};

} // namespace BR