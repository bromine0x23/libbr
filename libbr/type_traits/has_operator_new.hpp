/**
 * @file
 * @brief 检查是否重载了 \em new 操作符
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <new>

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否重载了 \em new 操作符
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::NoOperatorNew
 *
 * 如果 \em T 重载了 \em new 操作符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasOperatorNew;

/**
 * @brief HasOperatorNew 的否定
 * @tparam T 待检查类型
 * @see BR::HasOperatorNew
 */
template< typename T >
struct NoOperatorNew;

#if defined(BR_CXX14)

/**
 * @brief HasOperatorNew 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasOperatorNew
 * @see BR::no_operator_new
 */
template< typename T >
constexpr auto has_operator_new = bool_constant< HasOperatorNew<T> >;

/**
 * @brief NoOperatorNew 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoOperatorNew
 * @see BR::has_operator_new
 */
template< typename T >
constexpr auto no_operator_new = bool_constant< NoOperatorNew<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T, T t >
struct HasOperatorNewHelper;

struct HasOperatorNewTester0 {
	template< typename T, typename = HasOperatorNewHelper< void *(*)(std::size_t), &T::operator new > >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

struct HasOperatorNewTester1 {
	template< typename T, typename = HasOperatorNewHelper< void *(*)(std::size_t, std::nothrow_t const &), &T::operator new > >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

struct HasOperatorNewTester2 {
	template< typename T, typename = HasOperatorNewHelper< void *(*)(std::size_t, void *), &T::operator new > >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

struct HasOperatorNewTester3 {
	template< typename T, typename = HasOperatorNewHelper< void *(*)(std::size_t), &T::operator new [] > >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

struct HasOperatorNewTester4 {
	template< typename T, typename = HasOperatorNewHelper< void *(*)(std::size_t, std::nothrow_t const &), &T::operator new []  > >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

struct HasOperatorNewTester5 {
	template< typename T, typename = HasOperatorNewHelper< void *(*)(std::size_t, void *), &T::operator new []  > >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T >
struct HasOperatorNew : BooleanOr<
	decltype(HasOperatorNewTester0::test<T>(0)),
	decltype(HasOperatorNewTester1::test<T>(0)),
	decltype(HasOperatorNewTester2::test<T>(0)),
	decltype(HasOperatorNewTester3::test<T>(0)),
	decltype(HasOperatorNewTester4::test<T>(0)),
	decltype(HasOperatorNewTester5::test<T>(0))
> {};

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasOperatorNew : BooleanRewrapPositive< Detail::TypeTraits::HasOperatorNew<T> > {};

template< typename T >
struct NoOperatorNew : BooleanRewrapNegative< Detail::TypeTraits::HasOperatorNew<T> > {};

} // namespace BR
