/**
 * @file
 * @brief 类类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_CLASS)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_traits/is_union.hpp>
#endif

namespace BR {

/**
 * @brief 检查 \em T 是否是类
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_IS_CLASS
 * @see BR::NotClass
 *
 * 如果 \em T 是类(\em struct 或 \em class)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsClass;

/**
 * @brief IsClass 的否定
 * @tparam T 待检查类型
 * @see BR::IsClass
 */
template< typename T >
struct NotClass;

#if defined(BR_CXX14)

/**
 * @brief IsClass 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::IsClass
 * @see BR::not_class
 */
template< typename T >
constexpr auto is_class = bool_constant< IsClass<T> >;

/**
 * @brief NotClass 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NotClass
 * @see BR::is_class
 */
template< typename T >
constexpr auto not_class = bool_constant< NotClass<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_CLASS)

template< typename T >
using IsClass = BooleanConstant< BR_IS_CLASS(T) >;

#else

struct IsClassTest {
	template< typename TClass >
	static BooleanTrue test(void(TClass::*)(void));

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsClassBasic = decltype(IsClassTest::test<T>(0));

template< typename T >
using IsClass = BooleanAnd<
	NotUnion<T>,
	IsClassBasic<T>
>;

#endif

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsClass : public BooleanRewrapPositive< Detail::TypeTraits::IsClass<T> > {};

template< typename T >
struct NotClass : public BooleanRewrapNegative< Detail::TypeTraits::IsClass<T> > {};

} // namespace BR