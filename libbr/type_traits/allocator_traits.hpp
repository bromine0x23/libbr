/**
 * @file
 * @brief 分配器特性类
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/construct.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/has_member_function.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/has_trivial_move_constructor.hpp>
#include <libbr/type_traits/make_unsigned.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/type_traits/replace_template_argument.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * 分配器特性类
 * @tparam TAllocator 分配器类型
 */
template< typename TAllocator >
struct AllocatorTraits;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {
namespace AllocatorTraits {

////////////////////////////////
//
// AllocatorTraits::Element
//
template< typename TAllocator >
using Element = typename TAllocator::Element;

////////////////////////////////
//
// AllocatorTraits::Pointer
//
BR_HAS_MEMBER_TYPE(Pointer)

template< typename TAllocator, bool = HasMemberTypePointer<TAllocator>{} >
struct TypePointer;

template< typename TAllocator >
struct TypePointer< TAllocator, true > : TypeWrapper< typename TAllocator::Pointer > {};

template< typename TAllocator >
struct TypePointer< TAllocator, false > : TypeWrapper< Element<TAllocator> * > {};

template< typename TAllocator >
using Pointer = TypeUnwrap< TypePointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::ConstPointer
//
BR_HAS_MEMBER_TYPE(ConstPointer)

template< typename TAllocator, bool = HasMemberTypeConstPointer<TAllocator>{} >
struct TypeConstPointer;

template< typename TAllocator >
struct TypeConstPointer< TAllocator, true > : TypeWrapper< typename TAllocator::ConstPointer > {};

template< typename TAllocator >
struct TypeConstPointer< TAllocator, false > : TypeWrapper< typename BR::PointerTraits< Pointer<TAllocator> >::template Rebind< Element<TAllocator> const > > {};

template< typename TAllocator >
using ConstPointer = TypeUnwrap< TypeConstPointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::VoidPointer
//
BR_HAS_MEMBER_TYPE(VoidPointer)

template< typename TAllocator, bool = HasMemberTypeVoidPointer<TAllocator>{} >
struct TypeVoidPointer;

template< typename TAllocator >
struct TypeVoidPointer< TAllocator, true > : TypeWrapper< typename TAllocator::VoidPointer > {};

template< typename TAllocator >
struct TypeVoidPointer< TAllocator, false > : TypeWrapper< typename BR::PointerTraits< Pointer<TAllocator> >::template Rebind< void > > {};

template< typename TAllocator >
using VoidPointer = TypeUnwrap< TypeVoidPointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::ConstVoidPointer
//
BR_HAS_MEMBER_TYPE(ConstVoidPointer)

template< typename TAllocator, bool = HasMemberTypeConstVoidPointer<TAllocator>{} >
struct TypeConstVoidPointer;

template< typename TAllocator >
struct TypeConstVoidPointer< TAllocator, true > : TypeWrapper< typename TAllocator::ConstVoidPointer > {};

template< typename TAllocator >
struct TypeConstVoidPointer< TAllocator, false > : TypeWrapper< typename BR::PointerTraits< Pointer<TAllocator> >::template Rebind< void const > > {};

template< typename TAllocator >
using ConstVoidPointer = TypeUnwrap< TypeVoidPointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::Difference
//
BR_HAS_MEMBER_TYPE(Difference)

template< typename TAllocator, bool = HasMemberTypeDifference<TAllocator>{} >
struct TypeDifference;

template< typename TAllocator >
struct TypeDifference< TAllocator, true > : TypeWrapper< typename TAllocator::Difference > {};

template< typename TAllocator >
struct TypeDifference< TAllocator, false > : TypeWrapper< typename BR::PointerTraits< Pointer<TAllocator> >::Difference > {};

template< typename TAllocator >
using Difference = TypeUnwrap< TypeDifference<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::Size
//
BR_HAS_MEMBER_TYPE(Size)

template< typename TAllocator, bool = HasMemberTypeSize<TAllocator>{} >
struct TypeSize;

template< typename TAllocator >
struct TypeSize< TAllocator, true > : TypeWrapper< typename TAllocator::Size > {};

template< typename TAllocator >
struct TypeSize< TAllocator, false > : TypeMakeUnsigned< Difference<TAllocator> > {};

template< typename TAllocator >
using Size = TypeUnwrap< TypeSize<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::IsPropagateOnContainerCopyAssignment
//
BR_HAS_MEMBER_TYPE(IsPropagateOnContainerCopyAssignment)

template< typename TAllocator, bool = HasMemberTypeIsPropagateOnContainerCopyAssignment<TAllocator>{} >
struct TypeIsPropagateOnContainerCopyAssignment;

template< typename TAllocator >
struct TypeIsPropagateOnContainerCopyAssignment< TAllocator, true > : TypeWrapper< typename TAllocator::IsPropagateOnContainerCopyAssignment > {};

template< typename TAllocator >
struct TypeIsPropagateOnContainerCopyAssignment< TAllocator, false > : TypeWrapper<BooleanFalse> {};

template< typename TAllocator >
using IsPropagateOnContainerCopyAssignment = TypeUnwrap< TypeIsPropagateOnContainerCopyAssignment<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::IsPropagateOnContainerMoveAssignment
//
BR_HAS_MEMBER_TYPE(IsPropagateOnContainerMoveAssignment)

template< typename TAllocator, bool = HasMemberTypeIsPropagateOnContainerMoveAssignment<TAllocator>{} >
struct TypeIsPropagateOnContainerMoveAssignment;

template< typename TAllocator >
struct TypeIsPropagateOnContainerMoveAssignment< TAllocator, true > : TypeWrapper< typename TAllocator::IsPropagateOnContainerMoveAssignment > {};

template< typename TAllocator >
struct TypeIsPropagateOnContainerMoveAssignment< TAllocator, false > : TypeWrapper<BooleanFalse> {};

template< typename TAllocator >
using IsPropagateOnContainerMoveAssignment = TypeUnwrap< TypeIsPropagateOnContainerMoveAssignment<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::IsPropagateOnContainerSwap
//
BR_HAS_MEMBER_TYPE(IsPropagateOnContainerSwap)

template< typename TAllocator, bool = HasMemberTypeIsPropagateOnContainerSwap<TAllocator>{} >
struct TypeIsPropagateOnContainerSwap;

template< typename TAllocator >
struct TypeIsPropagateOnContainerSwap< TAllocator, true > : TypeWrapper< typename TAllocator::IsPropagateOnContainerSwap > {};

template< typename TAllocator >
struct TypeIsPropagateOnContainerSwap< TAllocator, false > : TypeWrapper<BooleanFalse> {};

template< typename TAllocator >
using IsPropagateOnContainerSwap = TypeUnwrap< TypeIsPropagateOnContainerSwap<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::IsAlwaysEqual
//
BR_HAS_MEMBER_TYPE(IsAlwaysEqual)

template< typename TAllocator, bool = HasMemberTypeIsAlwaysEqual<TAllocator>{} >
struct TypeIsAlwaysEqual;

template< typename TAllocator >
struct TypeIsAlwaysEqual< TAllocator, true > : TypeWrapper< typename TAllocator::IsAlwaysEqual > {};

template< typename TAllocator >
struct TypeIsAlwaysEqual< TAllocator, false > : TypeWrapper< IsEmpty<TAllocator> > {};

template< typename TAllocator >
using IsAlwaysEqual = TypeUnwrap< TypeIsAlwaysEqual<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::Rebind
//
struct HasMemberTemplateRebindTest {
	template< typename T, template< typename > class TR = T::template Rebind >
	static auto test(int) -> BooleanTrue;

	template< typename T, typename ... >
	static auto test(...) -> BooleanFalse;
};

template < typename TAllocator >
using HasMemberTemplateRebind = decltype(HasMemberTemplateRebindTest::test<TAllocator>(0));

template< typename TAllocator, typename TElement, bool = HasMemberTemplateRebind<TAllocator>{} >
struct TypeRebind;

template< typename TAllocator, typename TElement >
struct TypeRebind< TAllocator, TElement, true > : TypeWrapper< typename TAllocator::template Rebind<TElement> > {};

template< typename TAllocator, typename TElement >
struct TypeRebind< TAllocator, TElement, false > : TypeReplaceFirstTemplateArgument< TAllocator, TElement > {};

template< typename TAllocator, typename TElement >
using Rebind = TypeUnwrap< TypeRebind< TAllocator, TElement > >;

////////////////////////////////
//
// AllocatorTraits::allocate()
//
BR_HAS_MEMBER_FUNCTION(allocate)

template< bool has_member_function, typename TAllocator, typename ... TArgs >
struct AllocateBasic;

template< typename TAllocator, typename ... TArgs >
struct Allocate : AllocateBasic< HasMemberFunction_allocate< TAllocator, TArgs ... >{}, TAllocator, TArgs ... > {};

template< typename TAllocator, typename ... TArgs >
struct AllocateBasic< true, TAllocator, TArgs ... > {
	static Pointer< TAllocator > call(TAllocator allocator, TArgs && ... args) {
		return allocator.allocate(forward<TArgs>(args) ...);
	}
};

template< typename TAllocator, typename TSize, typename TConstVoidPointer >
struct AllocateBasic< false, TAllocator, TSize, TConstVoidPointer > {
	static Pointer< TAllocator > call(TAllocator allocator, TSize size, TConstVoidPointer hint) {
		return Allocate< TAllocator, TSize >::call(allocator, size);
	}
};

////////////////////////////////
//
// AllocatorTraits::max_size()
//
BR_HAS_MEMBER_FUNCTION(max_size)

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct MaxSizeBasic;

template< typename TAllocator, typename ... TArguments >
struct MaxSize : MaxSizeBasic< HasMemberFunction_max_size< TAllocator, TArguments ... >{}, TAllocator, TArguments ... > {};

template< typename TAllocator, typename ... TArguments >
struct MaxSizeBasic< true, TAllocator, TArguments ... > {
	static Size< TAllocator > call(TAllocator allocator, TArguments && ... arguments) {
		return allocator.max_size(forward<TArguments>(arguments) ...);
	}
};

template< typename TAllocator >
struct MaxSizeBasic< false, TAllocator > {
	static Size< TAllocator > call(TAllocator allocator) {
		return BR::IntegerTraits< Size< TAllocator > >::max();
	}
};

////////////////////////////////
//
// AllocatorTraits::select_on_container_copy_construction()
//
BR_HAS_MEMBER_FUNCTION(select_on_container_copy_construction)

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstructionBasic;

template< typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstruction : SelectOnContainerCopyConstructionBasic< HasMemberFunction_select_on_container_copy_construction< TAllocator, TArguments ... >{}, TAllocator, TArguments ... > {};

template< typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstructionBasic< true, TAllocator, TArguments ... > {
	static TAllocator call(TAllocator allocator, TArguments && ... arguments) noexcept {
		return allocator.select_on_container_copy_construction(forward<TArguments>(arguments) ...);
	}
};

template< typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstructionBasic< false, TAllocator, TArguments ... > {
	static TAllocator call(TAllocator allocator) noexcept {
		return allocator;
	}
};

} // namespace AllocatorTraits
} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template<typename TAllocator>
struct AllocatorTraits {
	using Allocator        = TAllocator;
	using Element          = Detail::TypeTraits::AllocatorTraits::Element<Allocator>;
	using Pointer          = Detail::TypeTraits::AllocatorTraits::Pointer<Allocator>;
	using ConstPointer     = Detail::TypeTraits::AllocatorTraits::ConstPointer<Allocator>;
	using VoidPointer      = Detail::TypeTraits::AllocatorTraits::VoidPointer<Allocator>;
	using ConstVoidPointer = Detail::TypeTraits::AllocatorTraits::ConstVoidPointer<Allocator>;
	using Difference       = Detail::TypeTraits::AllocatorTraits::Difference<Allocator>;
	using Size             = Detail::TypeTraits::AllocatorTraits::Size<Allocator>;

	using IsPropagateOnContainerCopyAssignment = Detail::TypeTraits::AllocatorTraits::IsPropagateOnContainerCopyAssignment<Allocator>;
	using IsPropagateOnContainerMoveAssignment = Detail::TypeTraits::AllocatorTraits::IsPropagateOnContainerMoveAssignment<Allocator>;
	using IsPropagateOnContainerSwap           = Detail::TypeTraits::AllocatorTraits::IsPropagateOnContainerSwap<Allocator>;
	using IsAlwaysEqual                        = Detail::TypeTraits::AllocatorTraits::IsAlwaysEqual<Allocator>;

	template<typename TElement>
	using Rebind = Detail::TypeTraits::AllocatorTraits::Rebind<TAllocator, TElement>;

	static Pointer allocate(Allocator & allocator, Size size) {
		return allocator.allocate(size);
	}

	static Pointer allocate(Allocator & allocator, Size size, ConstVoidPointer hint) {
		return Detail::TypeTraits::AllocatorTraits::Allocate<Allocator, Size, ConstVoidPointer>::call(allocator, size,
		                                                                                              hint);
	}

	static void deallocate(Allocator & allocator, Pointer pointer, Size size) noexcept {
		allocator.deallocate(pointer, size);
	}

	template<typename TElement, typename ... TArguments>
	static void construct(Allocator & allocator, TElement * pointer, TArguments &&... arguments) {
		BR::construct(allocator, pointer, forward<TArguments>(arguments) ...);
	}

	template<typename TElement>
	static void destroy(Allocator &allocator, TElement *pointer) {
		BR::destroy(allocator, pointer);
	}

	static Size max_size(Allocator const & allocator) noexcept {
		return Detail::TypeTraits::AllocatorTraits::MaxSize<Allocator>::call(allocator);
	}

	static Allocator select_on_container_copy_construction(Allocator const & allocator) noexcept {
		return Detail::TypeTraits::AllocatorTraits::SelectOnContainerCopyConstruction<Allocator>::call(allocator);
	}
};

} // namespace TypeTraits

} // namespace BR
