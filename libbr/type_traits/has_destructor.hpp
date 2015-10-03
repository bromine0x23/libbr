/**
 * @file
 * @brief 检查是否具有析构函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_DESTRUCTOR)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_operate/remove_all_extents.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_function.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_void.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_HAS_DESTRUCTOR)

template< typename T >
using HasDestructor = BooleanConstant< BR_HAS_DESTRUCTOR(T) >;

#else

struct HasDestructorTest {
	template< typename T, typename = decltype(make_reference<T>().~T()) >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T >
using HasDestructorBasic = decltype(HasDestructorTest::test<T>(0));

template< typename T >
using HasDestructor = BooleanAnd<
	NotArrayUnknownBounds<T>,
	NotFunction<T>,
	NotVoid<T>,
	BooleanOr<
		IsReference<T>,
		HasDestructorBasic< RemoveAllExtents<T> >
	>
>;

#endif

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 具有析构函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_HAS_DESTRUCTOR
 * @see BR::NoDestructor
 *
 * 如果 \em T 具有析构函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasDestructor : BooleanRewrapPositive< Detail::TypeTraits::HasDestructor<T> > {};

/**
 * @brief HasDestructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasDestructor
 */
template< typename T >
struct NoDestructor : BooleanRewrapNegative< Detail::TypeTraits::HasDestructor<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasDestructor
 * @see BR::not_destructible
 */
template< typename T >
constexpr auto has_destructor = bool_constant< HasDestructor<T> >;

/**
 * @brief NoDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoDestructor
 * @see BR::no_destructor
 */
template< typename T >
constexpr auto no_destructor = bool_constant< NoDestructor<T> >;

#endif // defined(BR_CXX14)

} // namespace BR