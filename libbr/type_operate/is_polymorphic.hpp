#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TT_IS_POLYMORPHIC)
#  include <libbr/type_operate/remove_const_volatile.hpp>
#  include <libbr/type_operate/is_class.hpp>
#endif // !BR_TT_IS_POLYMORPHIC

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_IS_POLYMORPHIC)

template< typename T >
using IsPolymorphic = BooleanConstant< BR_TYPE_OPERATE_IS_POLYMORPHIC(T) >;

#else

template< typename T >
struct IsPolymorphicBasic {
	using TypeNoCV = RemoveConstVolatile< T >;

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
using IsPolymorphic = BooleanAnd< IsClass< T >, BooleanConstant< IsPolymorphicBasic< T >::value > >;

#endif // BR_TYPE_OPERATE_IS_POLYMORPHIC

} // namespace Detail

template< typename T >
struct IsPolymorphic : Boolean< Detail::IsPolymorphic< T > > {};

template< typename T >
struct NotPolymorphic : BooleanNot< Detail::IsPolymorphic< T > > {};

} // namespace TypeOperate
} // namespace BR
