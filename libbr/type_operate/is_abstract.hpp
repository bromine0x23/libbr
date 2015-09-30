/**
 * @file
 * @brief 抽象类类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_ABSTRACT)
#  include <libbr/type_operate/is_class.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_ABSTRACT)

template< typename T >
using IsAbstract = BooleanConstant< BR_IS_ABSTRACT(T) >;

#else

struct IsAbstractTest {
	template< typename T >
	static BooleanFalse test(T(*)[1]);

	template< typename T >
	static BooleanTrue test(...);
};

template< typename T >
struct IsAbstractBasic : decltype(IsAbstractTest::test< T >(nullptr)) {
	static_assert(sizeof(T) != 0, "Type must be complete.");
};

template< typename T >
using IsAbstract = BooleanAnd< IsClass<T>, IsAbstractBasic<T> >;

#endif

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是抽象类
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotAbstract
 *
 * 如果 \em T 是抽象类(含有至少一个纯虚函数声明的类)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsAbstract : Boolean< Detail::TypeOperate::IsAbstract<T> > {};

/**
 * @brief IsAbstract 的否定
 * @tparam T 待检查类型
 * @see IsAbstract
 */
template< typename T >
struct NotAbstract : BooleanNot< Detail::TypeOperate::IsAbstract<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsAbstract 的模板变量版本
 * @tparam T 待检查类型
 * @see IsAbstract
 * @see not_abstract
 */
template< typename T >
constexpr auto is_abstract = IsAbstract<T>::value;

/**
 * @brief NotAbstract 的模板变量版本
 * @tparam T 待检查类型
 * @see NotAbstract
 * @see is_abstract
 */
template< typename T >
constexpr auto not_abstract = NotAbstract<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR