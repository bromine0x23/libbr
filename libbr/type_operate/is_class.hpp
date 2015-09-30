/**
 * @file
 * @brief 类类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_CLASS)
#  include <libbr/type_operate/is_union.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_CLASS)

template< typename T >
using IsClass = BooleanConstant< BR_IS_CLASS(T) >;

#else

namespace Detail {
namespace TypeOperate {

struct IsClassTest {
	template< typename TClass >
	static BooleanTrue test(void(TClass::*)(void));

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsClassBasic = decltype(IsClassTest::test< T >(0));

template< typename T >
using IsClass = BooleanAnd<
	NotUnion<T>,
	IsClassBasic<T>
>;

#endif

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是类
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotClass
 *
 * 如果 \em T 是类(\em struct 或 \em class)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsClass : Boolean< Detail::TypeOperate::IsClass<T> > {};

/**
 * @brief IsClass 的否定
 * @tparam T 待检查类型
 * @see IsClass
 */
template< typename T >
struct NotClass : BooleanNot< Detail::TypeOperate::IsClass<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsClass 的模板变量版本
 * @tparam T 待检查类型
 * @see IsClass
 * @see not_class
 */
template< typename T >
constexpr auto is_class = IsClass<T>::value;

/**
 * @brief NotClass 的模板变量版本
 * @tparam T 待检查类型
 * @see NotClass
 * @see is_class
 */
template< typename T >
constexpr auto not_class = NotClass<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
