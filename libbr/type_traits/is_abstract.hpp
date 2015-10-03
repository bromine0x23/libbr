/**
 * @file
 * @brief 抽象类类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_ABSTRACT)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_traits/is_class.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_ABSTRACT)

template< typename T >
using IsAbstract = BooleanConstant< BR_IS_ABSTRACT(T) >;

#else

struct IsAbstractTest {
	template< typename T >
	static auto test(T(*)[1]) -> BooleanFalse;

	template< typename T >
	static auto test(...) -> BooleanTrue;
};

template< typename T >
struct IsAbstractBasic : decltype(IsAbstractTest::test<T>(nullptr)) {
	static_assert(sizeof(T) != 0, "Type must be complete.");
};

template< typename T >
using IsAbstract = BooleanAnd< IsClass<T>, IsAbstractBasic<T> >;

#endif

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是抽象类
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_IS_ABSTRACT
 * @see BR::NotAbstract
 *
 * 如果 \em T 是抽象类(含有至少一个纯虚函数声明的类)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsAbstract : BooleanRewrapPositive< Detail::TypeTraits::IsAbstract<T> > {};

/**
 * @brief IsAbstract 的否定
 * @tparam T 待检查类型
 * @see BR::IsAbstract
 */
template< typename T >
struct NotAbstract : BooleanRewrapNegative< Detail::TypeTraits::IsAbstract<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsAbstract 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::IsAbstract
 * @see BR::not_abstract
 */
template< typename T >
constexpr auto is_abstract = bool_constant< IsAbstract<T> >;

/**
 * @brief NotAbstract 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NotAbstract
 * @see BR::is_abstract
 */
template< typename T >
constexpr auto not_abstract = bool_constant< NotAbstract<T> >;

#endif // defined(BR_CXX14)

} // namespace BR