/**
 * @file
 * @brief 抽象类类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_IS_ABSTRACT)
#  include <libbr/type_traits/is_class.hpp>
#  include <libbr/utility/conjunction.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是抽象类
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR_IS_ABSTRACT
 * @see NotAbstract
 *
 * 如果 \em T 是抽象类(含有至少一个纯虚函数声明的类)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsAbstract;

/**
 * @brief IsAbstract 的否定
 * @tparam T 待检查类型
 * @see IsAbstract
 */
template< typename T >
struct NotAbstract;

/**
 * @brief IsAbstract 的模板变量版本
 * @tparam T 待检查类型
 * @see IsAbstract
 * @see not_abstract
 */
template< typename T >
constexpr auto is_abstract = boolean_constant< IsAbstract<T> >;

/**
 * @brief NotAbstract 的模板变量版本
 * @tparam T 待检查类型
 * @see NotAbstract
 * @see is_abstract
 */
template< typename T >
constexpr auto not_abstract = boolean_constant< NotAbstract<T> >;

} // namespace TypeTraits



namespace _ {
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
struct IsAbstractBasic : public decltype(IsAbstractTest::test<T>(nullptr)) {
	static_assert(sizeof(T) != 0, "Type must be complete.");
};

template< typename T >
using IsAbstract = Conjunction< IsClass<T>, IsAbstractBasic<T> >;

#endif

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsAbstract : public BooleanRewrapPositive< _::TypeTraits::IsAbstract<T> > {};

template< typename T >
struct NotAbstract : public BooleanRewrapNegative< _::TypeTraits::IsAbstract<T> > {};

} // namespace TypeTraits

} // namespace BR