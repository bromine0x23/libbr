/**
 * @file
 * @brief 多态类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_IS_POLYMORPHIC)
#  include <libbr/type_traits/is_class.hpp>
#  include <libbr/type_transform/remove_const_volatile.hpp>
#  include <libbr/utility/conjunction.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是多态类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see BR_IS_POLYMORPHIC
 * @see IsClass
 * @see IsAbstract
 * @see NotPolymorphic
 *
 * 如果 \em T 是多态类(声明或继承了至少一个虚函数的类)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsPolymorphic;

/**
 * @brief IsPolymorphic 的否定
 * @tparam T 待检查类型
 * @see IsPolymorphic
 */
template< typename T >
struct NotPolymorphic;

/**
 * @brief IsPolymorphic 的模板变量版本
 * @tparam T 待检查类型
 * @see IsPolymorphic
 * @see not_polymorphic
 */
template< typename T >
constexpr auto is_polymorphic = boolean_constant< IsPolymorphic<T> >;

/**
 * @brief NotPolymorphic 的模板变量版本
 * @tparam T 待检查类型
 * @see NotPolymorphic
 * @see is_polymorphic
 */
template< typename T >
constexpr auto not_polymorphic = boolean_constant< NotPolymorphic<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

#if defined(BR_IS_POLYMORPHIC)

template< typename T >
using IsPolymorphic = BooleanConstant< BR_IS_POLYMORPHIC(T) >;

#else

template< typename T >
struct IsPolymorphicBasic {
	using TypeNoCV = RemoveConstVolatile<T>;

	struct Derived1 : public TypeNoCV {
		Derived1();
#  if !defined(BR_GCC)
		~Derived1() noexcept;
#  endif // !BR_GCC
		char padding[0x100];
		Derived1(Derived1 const &) = delete;
		Derived1 & operator=(Derived1 const &) = delete;
	};

	struct Derived2 : public TypeNoCV {
		Derived2();
		virtual ~Derived2() noexcept;
#  if !defined(BR_MSVC)
		struct Unique{};
		virtual void unique(Unique *);
#  endif // !BR_MSVC
		char padding[0x100];
		Derived2(Derived2 const &) = delete;
		Derived2 & operator=(Derived2 const &) = delete;
	};

	constexpr static auto value = sizeof(Derived1) == sizeof(Derived2);
};

template< typename T >
using IsPolymorphic = Conjunction< IsClass<T>, BooleanConstant< IsPolymorphicBasic<T>::value > >;

#endif // BR_IS_POLYMORPHIC

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsPolymorphic : public BooleanRewrapPositive< _::TypeTraits::IsPolymorphic<T> > {};

template< typename T >
struct NotPolymorphic : public BooleanRewrapNegative< _::TypeTraits::IsPolymorphic<T> > {};

} // namespace TypeTraits

} // namespace BR
