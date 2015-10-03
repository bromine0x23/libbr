#pragma once

#include <new>

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T, T t >
struct HasOperatorNewHelper;

struct HasOperatorNewTester0 {
	template< typename T >
	static BooleanTrue test(T *, HasOperatorNewHelper< void *(*)(std::size_t), &T::operator new > * = nullptr);

	template< typename T >
	static BooleanFalse test(...);
};

struct HasOperatorNewTester1 {
	template< typename T >
	static BooleanTrue test(T *, HasOperatorNewHelper< void *(*)(std::size_t, std::nothrow_t const &), &T::operator new > * = nullptr);

	template< typename T >
	static BooleanFalse test(...);
};

struct HasOperatorNewTester2 {
	template< typename T >
	static BooleanTrue test(T *, HasOperatorNewHelper< void *(*)(std::size_t, void *), &T::operator new > * = nullptr);

	template< typename T >
	static BooleanFalse test(...);
};

struct HasOperatorNewTester3 {
	template< typename T >
	static BooleanTrue test(T *, HasOperatorNewHelper< void *(*)(std::size_t), &T::operator new [] > * = nullptr);

	template< typename T >
	static BooleanFalse test(...);
};

struct HasOperatorNewTester4 {
	template< typename T >
	static BooleanTrue test(T *, HasOperatorNewHelper< void *(*)(std::size_t, std::nothrow_t const &), &T::operator new []  > * = nullptr);

	template< typename T >
	static BooleanFalse test(...);
};

struct HasOperatorNewTester5 {
	template< typename T >
	static BooleanTrue test(T *, HasOperatorNewHelper< void *(*)(std::size_t, void *), &T::operator new []  > * = nullptr);

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T > struct HasOperatorNew0 : decltype(HasOperatorNewTester0::test<T>(nullptr)) {};
template< typename T > struct HasOperatorNew1 : decltype(HasOperatorNewTester1::test<T>(nullptr)) {};
template< typename T > struct HasOperatorNew2 : decltype(HasOperatorNewTester2::test<T>(nullptr)) {};
template< typename T > struct HasOperatorNew3 : decltype(HasOperatorNewTester3::test<T>(nullptr)) {};
template< typename T > struct HasOperatorNew4 : decltype(HasOperatorNewTester4::test<T>(nullptr)) {};
template< typename T > struct HasOperatorNew5 : decltype(HasOperatorNewTester5::test<T>(nullptr)) {};

template< typename T >
using HasOperatorNew = BooleanOr<
	HasOperatorNew0<T>,
	HasOperatorNew1<T>,
	HasOperatorNew2<T>,
	HasOperatorNew3<T>,
	HasOperatorNew4<T>,
	HasOperatorNew5<T>
>;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasOperatorNew : BooleanRewrapPositive< Detail::TypeTraits::HasOperatorNew<T> > {};

template< typename T >
struct NoOperatorNew : BooleanRewrapNegative< Detail::TypeTraits::HasOperatorNew<T> > {};

} // namespace BR
