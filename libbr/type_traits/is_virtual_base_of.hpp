/**
 * @file
 * @brief 虚拟继承检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_MSVC)
#pragma warning(push)
#pragma warning(disable : 4584 4250)
#elif defined(BR_GCC)
#pragma GCC system_header
#endif

template< typename TBase, typename TDerived >
struct IsVirtualBaseOfBasic {
	struct Tester0 : public TDerived, virtual TBase {
		Tester0();
		Tester0(Tester0 const &);
		Tester0 & operator=(Tester0 const &);
		~Tester0() noexcept;
	};
	struct Tester1 : public TDerived {
		Tester1();
		Tester1(Tester1 const &);
		Tester1& operator=(Tester1 const &);
		~Tester1() noexcept;
	};
	constexpr static auto value = (sizeof(Tester0) == sizeof(Tester1));
};

template< typename TBase, typename TDerived >
using IsVirtualBaseOf = BooleanAnd<
	NotLValueReference< TBase >,
	NotLValueReference< TDerived >,
	IsBaseOf< TBase, TDerived >,
	NotSame< TBase, TDerived >,
	BooleanConstant< IsVirtualBaseOfBasic< TBase, TDerived >::value >
>;

#ifdef BR_MSVC
#pragma warning( pop )
#endif

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em TDerived 是否虚拟继承自 \em TBase
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see IntegerConstant
 * @see NotVirtualBaseOf
 *
 * 如果 \em TDerived 虚拟继承自 \em TBase，那么封装的值为 \em true ；否则为 \em false
 */
template< typename TBase, typename TDerived >
struct IsVirtualBaseOf : BooleanRewrapPositive< Detail::TypeTraits::IsVirtualBaseOf< TBase, TDerived > > {};

/**
 * @brief IsVirtualBaseOf 的否定
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see IsVirtualBaseOf
 */
template< typename TBase, typename TDerived >
struct NotVirtualBaseOf : BooleanRewrapNegative< Detail::TypeTraits::IsVirtualBaseOf< TBase, TDerived > > {};

#if defined(BR_CXX14)

/**
 * @brief IsVirtualBaseOf 的模板变量版本
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see IsVirtualBaseOf
 * @see not_virtual_base_of
 */
template< typename TBase, typename TDerived >
constexpr auto is_virtual_base_of = bool_constant< IsVirtualBaseOf< TBase, TDerived > >;

/**
 * @brief NotVirtualBaseOf 的模板变量版本
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see NotVirtualBaseOf
 * @see is_virtual_base_of
 */
template< typename TBase, typename TDerived >
constexpr auto not_virtual_base_of = bool_constant< NotVirtualBaseOf< TBase, TDerived > >;

#endif // defined(BR_CXX14)

} // namespace BR
