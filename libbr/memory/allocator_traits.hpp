/**
 * @file
 * @brief 分配器特性类
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_construct.hpp>
#include <libbr/memory/allocator_destroy.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/has_member_function.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/has_trivial_move_constructor.hpp>
#include <libbr/type_transform/make_unsigned.hpp>
#include <libbr/type_transform/replace_first_template_argument.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/declare_value.hpp>
#include <libbr/utility/disjunction.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/negation.hpp>
#include <libbr/utility/transfer.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace Memory {

/**
 * 分配器特性类
 * @tparam TAllocator 分配器类型
 */
template< typename TAllocator >
struct AllocatorTraits;

} // namespace Memory



namespace _ {
namespace Memory {
namespace AllocatorTraits {

//--------------------------------
// AllocatorTraits::Element
//--------------------------------
template<typename TAllocator>
using Element = typename TAllocator::Element;

//--------------------------------
// AllocatorTraits::Pointer
//--------------------------------
BR_HAS_MEMBER_TYPE(Pointer)

template<typename TAllocator, Boolean = has_member_type_Pointer<TAllocator> >
struct TypePointer;

template<typename TAllocator>
struct TypePointer<TAllocator, true> : TypeWrapper< typename TAllocator::Pointer > {};

template<typename TAllocator>
struct TypePointer<TAllocator, false> : TypeWrapper< Element<TAllocator> * > {};

template<typename TAllocator>
using Pointer = TypeUnwrap<TypePointer<TAllocator>>;

//--------------------------------
// AllocatorTraits::ConstPointer
//--------------------------------
BR_HAS_MEMBER_TYPE(ConstPointer)

template<typename TAllocator, Boolean = has_member_type_ConstPointer<TAllocator> >
struct TypeConstPointer;

template<typename TAllocator>
struct TypeConstPointer<TAllocator, true> : TypeWrapper< typename TAllocator::ConstPointer > {};

template<typename TAllocator>
struct TypeConstPointer<TAllocator, false> : TypeWrapper< typename BR::PointerTraits<Pointer<TAllocator>>::template Rebind<Element<TAllocator> const> > {};

template<typename TAllocator>
using ConstPointer = TypeUnwrap< TypeConstPointer<TAllocator> >;

//--------------------------------
// AllocatorTraits::VoidPointer
//--------------------------------
BR_HAS_MEMBER_TYPE(VoidPointer)

template< typename TAllocator, Boolean = has_member_type_VoidPointer<TAllocator> >
struct TypeVoidPointer;

template< typename TAllocator >
struct TypeVoidPointer< TAllocator, true > : TypeWrapper< typename TAllocator::VoidPointer > {};

template< typename TAllocator >
struct TypeVoidPointer< TAllocator, false > : TypeWrapper< typename BR::PointerTraits< Pointer<TAllocator> >::template Rebind< void > > {};

template< typename TAllocator >
using VoidPointer = TypeUnwrap< TypeVoidPointer<TAllocator> >;

//--------------------------------
// AllocatorTraits::ConstVoidPointer
//--------------------------------
BR_HAS_MEMBER_TYPE(ConstVoidPointer)

template< typename TAllocator, Boolean = has_member_type_ConstVoidPointer<TAllocator> >
struct TypeConstVoidPointer;

template< typename TAllocator >
struct TypeConstVoidPointer< TAllocator, true > : TypeWrapper< typename TAllocator::ConstVoidPointer > {};

template< typename TAllocator >
struct TypeConstVoidPointer< TAllocator, false > : TypeWrapper< typename BR::PointerTraits< Pointer<TAllocator> >::template Rebind< void const > > {};

template< typename TAllocator >
using ConstVoidPointer = TypeUnwrap< TypeConstVoidPointer<TAllocator> >;

//--------------------------------
// AllocatorTraits::Difference
//--------------------------------
BR_HAS_MEMBER_TYPE(Difference)

template< typename TAllocator, Boolean = has_member_type_Difference<TAllocator> >
struct TypeDifference;

template< typename TAllocator >
struct TypeDifference< TAllocator, true > : TypeWrapper< typename TAllocator::Difference > {};

template< typename TAllocator >
struct TypeDifference< TAllocator, false > : TypeWrapper< typename BR::PointerTraits< Pointer<TAllocator> >::Difference > {};

template< typename TAllocator >
using Difference = TypeUnwrap< TypeDifference<TAllocator> >;

//--------------------------------
// AllocatorTraits::Size
//--------------------------------
BR_HAS_MEMBER_TYPE(Size)

template< typename TAllocator, Boolean = has_member_type_Size<TAllocator> >
struct TypeSize;

template< typename TAllocator >
struct TypeSize< TAllocator, true > : TypeWrapper< typename TAllocator::Size > {};

template< typename TAllocator >
struct TypeSize< TAllocator, false > : TypeMakeUnsigned< Difference<TAllocator> > {};

template< typename TAllocator >
using Size = TypeUnwrap< TypeSize<TAllocator> >;

//--------------------------------
// AllocatorTraits::IsPropagateOnContainerCopyAssignment
//--------------------------------
struct HasStaticField_IS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT {
	template< typename T >
	static auto test(int) -> decltype(BooleanConstant< T::IS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT >{});

	template< typename T, typename ... >
	static auto test(...) -> BooleanFalse;
};

template< typename TAllocator >
using IsPropagateOnContainerCopyAssignment = decltype(HasStaticField_IS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT::test<TAllocator>(0));

//--------------------------------
// AllocatorTraits::IsPropagateOnContainerMoveAssignment
//--------------------------------
struct HasStaticField_IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT {
	template< typename T >
	static auto test(int) -> decltype(BooleanConstant< T::IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT >{});

	template< typename T, typename ... >
	static auto test(...) -> BooleanFalse;
};

template< typename TAllocator >
using IsPropagateOnContainerMoveAssignment = decltype(HasStaticField_IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT::test<TAllocator>(0));

//--------------------------------
// AllocatorTraits::IsPropagateOnContainerSwap
//--------------------------------
struct HasStaticField_IS_PROPAGATE_ON_CONTAINER_SWAP {
	template< typename T >
	static auto test(int) -> decltype(BooleanConstant< T::IS_PROPAGATE_ON_CONTAINER_SWAP >{});

	template< typename T, typename ... >
	static auto test(...) -> BooleanFalse;
};

template< typename TAllocator >
using IsPropagateOnContainerSwap = decltype(HasStaticField_IS_PROPAGATE_ON_CONTAINER_SWAP::test<TAllocator>(0));

//--------------------------------
// AllocatorTraits::IsAlwaysEqual
//--------------------------------
struct HasStaticField_IS_ALWAYS_EQUAL {
	template< typename T >
	static auto test(int) -> decltype(BooleanConstant< T::IS_ALWAYS_EQUAL >{});

	template< typename T, typename ... >
	static auto test(...) -> BooleanFalse;
};

template< typename TAllocator >
using IsAlwaysEqual = decltype(HasStaticField_IS_ALWAYS_EQUAL::test<TAllocator>(0));

//--------------------------------
// AllocatorTraits::Rebind
//--------------------------------
struct HasMemberTemplateRebindTest {
	template< typename T, template< typename > class TR = T::template Rebind >
	static auto test(int) -> BooleanTrue;

	template< typename T, typename ... >
	static auto test(...) -> BooleanFalse;
};

template < typename TAllocator >
using HasMemberTemplateRebind = decltype(HasMemberTemplateRebindTest::test<TAllocator>(0));

template< typename TAllocator, typename TElement, Boolean = HasMemberTemplateRebind< TAllocator>{} >
struct TypeRebind;

template< typename TAllocator, typename TElement >
struct TypeRebind< TAllocator, TElement, true > : TypeWrapper< typename TAllocator::template Rebind<TElement> > {};

template< typename TAllocator, typename TElement >
struct TypeRebind< TAllocator, TElement, false > : TypeReplaceFirstTemplateArgument< TAllocator, TElement > {};

template< typename TAllocator, typename TElement >
using Rebind = TypeUnwrap< TypeRebind< TAllocator, TElement > >;

//--------------------------------
// AllocatorTraits::allocate()
//--------------------------------
BR_HAS_MEMBER_FUNCTION(allocate)

template< Boolean has_member_function, typename TAllocator, typename ... TArgs >
struct AllocateBasic;

template< typename TAllocator, typename ... TArgs >
struct Allocate : AllocateBasic< has_member_function_allocate< TAllocator, TArgs ... >, TAllocator, TArgs ... > {};

template< typename TAllocator, typename ... TArgs >
struct AllocateBasic< true, TAllocator, TArgs ... > {
	static auto call(TAllocator allocator, TArgs && ... args) -> Pointer<TAllocator> {
		return allocator.allocate(forward<TArgs>(args) ...);
	}
};

template< typename TAllocator, typename TSize, typename TConstVoidPointer >
struct AllocateBasic< false, TAllocator, TSize, TConstVoidPointer > {
	static auto call(TAllocator allocator, TSize size, TConstVoidPointer hint) -> Pointer<TAllocator> {
		return Allocate< TAllocator, TSize >::call(allocator, size);
	}
};

//--------------------------------
// AllocatorTraits::max_size()
//--------------------------------
BR_HAS_MEMBER_FUNCTION(max_size)

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct MaxSizeBasic;

template< typename TAllocator, typename ... TArguments >
struct MaxSize : MaxSizeBasic< has_member_function_max_size< TAllocator, TArguments ... >, TAllocator, TArguments ... > {};

template< typename TAllocator, typename ... TArguments >
struct MaxSizeBasic< true, TAllocator, TArguments ... > {
	static auto call(TAllocator allocator, TArguments && ... arguments) -> Size<TAllocator> {
		return allocator.max_size(forward<TArguments>(arguments) ...);
	}
};

template< typename TAllocator >
struct MaxSizeBasic< false, TAllocator > {
	constexpr static auto call(TAllocator allocator) -> Size<TAllocator> {
		return BR::IntegerTraits< Size<TAllocator> >::max() / sizeof(Element<TAllocator>);
	}
};

//--------------------------------
// AllocatorTraits::select_on_container_copy_construction()
//--------------------------------
BR_HAS_MEMBER_FUNCTION(select_on_container_copy_construction)

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstructionBasic;

template< typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstruction : SelectOnContainerCopyConstructionBasic<
	has_member_function_select_on_container_copy_construction< TAllocator, TArguments ... >,
	TAllocator,
	TArguments...
> {};

template< typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstructionBasic< true, TAllocator, TArguments ... > {
	static auto call(TAllocator allocator, TArguments && ... arguments) noexcept -> TAllocator {
		return allocator.select_on_container_copy_construction(forward<TArguments>(arguments) ...);
	}
};

template< typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstructionBasic< false, TAllocator, TArguments ... > {
	static auto call(TAllocator allocator) noexcept -> TAllocator {
		return allocator;
	}
};

} // namespace AllocatorTraits
} // namespace Memory
} // namespace _

inline namespace Memory {

template<typename TAllocator>
struct AllocatorTraits {
	using Allocator        = TAllocator;
	using Element          = _::Memory::AllocatorTraits::Element<Allocator>;
	using Pointer          = _::Memory::AllocatorTraits::Pointer<Allocator>;
	using ConstPointer     = _::Memory::AllocatorTraits::ConstPointer<Allocator>;
	using VoidPointer      = _::Memory::AllocatorTraits::VoidPointer<Allocator>;
	using ConstVoidPointer = _::Memory::AllocatorTraits::ConstVoidPointer<Allocator>;
	using Difference       = _::Memory::AllocatorTraits::Difference<Allocator>;
	using Size             = _::Memory::AllocatorTraits::Size<Allocator>;

	constexpr static Boolean IS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT = boolean_constant< _::Memory::AllocatorTraits::IsPropagateOnContainerCopyAssignment<Allocator> >;
	constexpr static Boolean IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT = boolean_constant< _::Memory::AllocatorTraits::IsPropagateOnContainerMoveAssignment<Allocator> >;
	constexpr static Boolean IS_PROPAGATE_ON_CONTAINER_SWAP            = boolean_constant< _::Memory::AllocatorTraits::IsPropagateOnContainerSwap<Allocator> >;
	constexpr static Boolean IS_ALWAYS_EQUAL                           = boolean_constant< _::Memory::AllocatorTraits::IsAlwaysEqual<Allocator> >;

	template<typename TElement>
	using Rebind = _::Memory::AllocatorTraits::Rebind<TAllocator, TElement>;

	static auto allocate(Allocator & allocator, Size size) -> Pointer {
		return allocator.allocate(size);
	}

	static auto allocate(Allocator & allocator, Size size, ConstVoidPointer hint) -> Pointer {
		return _::Memory::AllocatorTraits::Allocate<Allocator, Size, ConstVoidPointer>::call(allocator, size, hint);
	}

	static void deallocate(Allocator & allocator, Pointer pointer, Size size) noexcept {
		allocator.deallocate(pointer, size);
	}

	template<typename TElement, typename ... TArguments>
	static void construct(Allocator & allocator, TElement * pointer, TArguments &&... arguments) {
		allocator_construct(allocator, pointer, forward<TArguments>(arguments) ...);
	}

	template<typename TElement>
	static void destroy(Allocator &allocator, TElement * pointer) {
		allocator_destroy(allocator, pointer);
	}

	static auto max_size(Allocator const & allocator) noexcept -> Size {
		return _::Memory::AllocatorTraits::MaxSize<Allocator>::call(allocator);
	}

	static auto select_on_container_copy_construction(Allocator const & allocator) noexcept -> Allocator {
		return _::Memory::AllocatorTraits::SelectOnContainerCopyConstruction<Allocator>::call(allocator);
	}
}; // AllocatorTraits<TAllocator>

} // namespace Memory

} // namespace BR
