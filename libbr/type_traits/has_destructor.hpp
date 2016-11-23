/**
 * @file
 * @brief 检查是否具有析构函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#ifndef BR_HAS_DESTRUCTOR
#  include <libbr/type_traits/boolean.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_function.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_traits/is_void.hpp>
#  include <libbr/type_traits/remove_all_extents.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 具有析构函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR_HAS_DESTRUCTOR
 * @see NoDestructor
 *
 * 如果 \em T 具有析构函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasDestructor;

/**
 * @brief HasDestructor 的否定
 * @tparam T 待检查类型
 * @see HasDestructor
 */
template< typename T >
struct NoDestructor;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasDestructor
 * @see not_destructible
 */
template< typename T >
constexpr auto has_destructor = boolean_constant< HasDestructor<T> >;

/**
 * @brief NoDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoDestructor
 * @see no_destructor
 */
template< typename T >
constexpr auto no_destructor = boolean_constant< NoDestructor<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#ifdef BR_HAS_DESTRUCTOR

template< typename T >
using HasDestructor = BooleanConstant< BR_HAS_DESTRUCTOR(T) >;

#else

struct HasDestructorTest {
	template< typename T, typename = decltype(make_reference<T>().~T()) >
	static auto test(T *) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T >
struct HasDestructorBasic : public decltype(HasDestructorTest::test<T>(nullptr)) {};

template< typename T >
struct HasDestructor : public BooleanAnd<
	NotVoid<T>,
	NotArrayUnknownBounds<T>,
	NotFunction<T>,
	BooleanOr<
		IsReference<T>,
		IsScalar<T>,
		HasDestructorBasic< RemoveAllExtents<T> >
	>
> {};

#endif

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasDestructor : public BooleanRewrapPositive< Detail::TypeTraits::HasDestructor<T> > {};

template< typename T >
struct NoDestructor : public BooleanRewrapNegative< Detail::TypeTraits::HasDestructor<T> > {};

} // namespace TypeTraits

} // namespace BR