#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_base_of.hpp>
#include <libbr/type_operate/is_lvalue_reference.hpp>
#include <libbr/type_operate/is_same.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_MSVC)
#pragma warning(push)
#pragma warning(disable : 4584 4250)
#elif defined(BR_GCC) && BR_GCC_VER >= 400
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
struct IsVirtualBaseOf : BooleanAnd<
	NotLValueReference< TBase >,
	NotLValueReference< TDerived >,
	IsBaseOf< TBase, TDerived >,
	NotSame< TBase, TDerived >,
	BooleanConstant< IsVirtualBaseOfBasic< TBase, TDerived >::value >
> {};

#ifdef BR_MSVC
#pragma warning( pop )
#endif

} // namespace Detail

template< typename TBase, typename TDerived >
struct IsVirtualBaseOf : Boolean< Detail::IsVirtualBaseOf< TBase, TDerived > > {};

template< typename TBase, typename TDerived >
struct NotVirtualBaseOf : BooleanNot< Detail::IsVirtualBaseOf< TBase, TDerived > > {};

} // namespace TypeOperate
} // namespace BR
