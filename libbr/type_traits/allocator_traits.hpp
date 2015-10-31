#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/make_unsigned.hpp>
#include <libbr/type_operate/replace_template_argument.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {
namespace AllocatorTraits {

////////////////////////////////
//
// AllocatorTraits::Value
//
template< typename TAllocator >
using Value = typename TAllocator::Value;

////////////////////////////////
//
// AllocatorTraits::Pointer
//
#define BR_TYPE_OPERATE_TYPE_NAME Pointer
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypePointer<TAllocator>::value >
struct TypePointer;

template< typename TAllocator >
struct TypePointer< TAllocator, true > : TypeWrapper< typename TAllocator::Pointer > {
};

template< typename TAllocator >
struct TypePointer< TAllocator, false > : TypeWrapper< Value<TAllocator> * > {
};

template< typename TAllocator >
using Pointer = TypeUnwrap< TypePointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::ConstPointer
//
#define BR_TYPE_OPERATE_TYPE_NAME ConstPointer
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeConstPointer<TAllocator>::value >
struct TypeConstPointer;

template< typename TAllocator >
struct TypeConstPointer< TAllocator, true > : TypeWrapper< typename TAllocator::ConstPointer > {
};

template< typename TAllocator >
struct TypeConstPointer< TAllocator, false > : TypeWrapper< typename PointerTraits< Pointer<TAllocator> >::template Rebind< Value<TAllocator> const > > {
};

template< typename TAllocator >
using ConstPointer = TypeUnwrap< TypeConstPointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::VoidPointer
//
#define BR_TYPE_OPERATE_TYPE_NAME VoidPointer
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeVoidPointer<TAllocator>::value >
struct TypeVoidPointer;

template< typename TAllocator >
struct TypeVoidPointer< TAllocator, true > : TypeWrapper< typename TAllocator::VoidPointer > {
};

template< typename TAllocator >
struct TypeVoidPointer< TAllocator, false > : TypeWrapper< typename PointerTraits< Pointer<TAllocator> >::template Rebind< void > > {
};

template< typename TAllocator >
using VoidPointer = TypeUnwrap< TypeVoidPointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::ConstVoidPointer
//
#define BR_TYPE_OPERATE_TYPE_NAME ConstVoidPointer
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeConstVoidPointer< TAllocator >::value >
struct TypeConstVoidPointer;

template< typename TAllocator >
struct TypeConstVoidPointer< TAllocator, true > : TypeWrapper< typename TAllocator::ConstVoidPointer > {
};

template< typename TAllocator >
struct TypeConstVoidPointer< TAllocator, false > : TypeWrapper< typename PointerTraits< Pointer<TAllocator> >::template Rebind< void const > > {
};

template< typename TAllocator >
using ConstVoidPointer = TypeUnwrap< TypeVoidPointer<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::Difference
//
#define BR_TYPE_OPERATE_TYPE_NAME Difference
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeDifference<TAllocator>::value >
struct TypeDifference;

template< typename TAllocator >
struct TypeDifference< TAllocator, true > : TypeWrapper< typename TAllocator::Difference > {
};

template< typename TAllocator >
struct TypeDifference< TAllocator, false > : TypeWrapper< typename PointerTraits< Pointer<TAllocator> >::Difference > {
};

template< typename TAllocator >
using Difference = TypeUnwrap< TypeDifference<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::Size
//
#define BR_TYPE_OPERATE_TYPE_NAME Size
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeSize<TAllocator>::value >
struct TypeSize;

template< typename TAllocator >
struct TypeSize< TAllocator, true > : TypeWrapper< typename TAllocator::Size > {
};

template< typename TAllocator >
struct TypeSize< TAllocator, false > : TypeMakeUnsigned< Difference<TAllocator> > {
};

template< typename TAllocator >
using Size = TypeUnwrap< TypeSize<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::IsPropagateOnContainerCopyAssignment
//
#define BR_TYPE_OPERATE_TYPE_NAME IsPropagateOnContainerCopyAssignment
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeIsPropagateOnContainerCopyAssignment<TAllocator>::value >
struct TypeIsPropagateOnContainerCopyAssignment;

template< typename TAllocator >
struct TypeIsPropagateOnContainerCopyAssignment< TAllocator, true > : TypeWrapper< typename TAllocator::IsPropagateOnContainerCopyAssignment > {
};

template< typename TAllocator >
struct TypeIsPropagateOnContainerCopyAssignment< TAllocator, false > : TypeWrapper<BooleanFalse> {
};

template< typename TAllocator >
using IsPropagateOnContainerCopyAssignment = TypeUnwrap< TypeIsPropagateOnContainerCopyAssignment<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::IsPropagateOnContainerMoveAssignment
//
#define BR_TYPE_OPERATE_TYPE_NAME IsPropagateOnContainerMoveAssignment
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeIsPropagateOnContainerMoveAssignment<TAllocator>::value >
struct TypeIsPropagateOnContainerMoveAssignment;

template< typename TAllocator >
struct TypeIsPropagateOnContainerMoveAssignment< TAllocator, true > : TypeWrapper< typename TAllocator::IsPropagateOnContainerMoveAssignment > {
};

template< typename TAllocator >
struct TypeIsPropagateOnContainerMoveAssignment< TAllocator, false > : TypeWrapper<BooleanFalse> {
};

template< typename TAllocator >
using IsPropagateOnContainerMoveAssignment = TypeUnwrap< TypeIsPropagateOnContainerMoveAssignment<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::IsPropagateOnContainerSwap
//
#define BR_TYPE_OPERATE_TYPE_NAME IsPropagateOnContainerSwap
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, bool = HasMemberTypeIsPropagateOnContainerSwap< TAllocator >::value >
struct TypeIsPropagateOnContainerSwap;

template< typename TAllocator >
struct TypeIsPropagateOnContainerSwap< TAllocator, true > : TypeWrapper< typename TAllocator::IsPropagateOnContainerSwap > {
};

template< typename TAllocator >
struct TypeIsPropagateOnContainerSwap< TAllocator, false > : TypeWrapper<BooleanFalse> {
};

template< typename TAllocator >
using IsPropagateOnContainerSwap = TypeUnwrap< TypeIsPropagateOnContainerSwap<TAllocator> >;

////////////////////////////////
//
// AllocatorTraits::Rebind
//
#define BR_TYPE_OPERATE_TYPE_NAME Rebind
#include <libbr/type_traits/has_member_type.inc>

template< typename TAllocator, typename TValue, bool = HasMemberTypeRebind< TAllocator >::value >
struct TypeRebind;

template< typename TAllocator, typename TValue >
struct TypeRebind< TAllocator, TValue, true > : TypeWrapper< typename TAllocator::template Rebind<TValue> > {
};

template< typename TAllocator, typename TValue >
struct TypeRebind< TAllocator, TValue, false > : TypeReplaceFirstTemplateArgument< TAllocator, TValue > {
};

template< typename TAllocator, typename TValue >
using Rebind = TypeUnwrap< TypeRebind< TAllocator, TValue > >;

////////////////////////////////
//
// AllocatorTraits::allocate()
//
#define BR_TYPE_OPERATE_FUNCTION_NAME allocate
#include <libbr/type_traits/has_member_function.inc>

template< bool has_member_function, typename TAllocator, typename ... TArgs >
struct AllocateBasic;

template< typename TAllocator, typename ... TArgs >
struct Allocate : AllocateBasic< HasMemberFunction_allocate< TAllocator, TArgs ... >::value, TAllocator, TArgs ... > {
};

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
// AllocatorTraits::construct()
//
#define BR_TYPE_OPERATE_FUNCTION_NAME construct
#include <libbr/type_traits/has_member_function.inc>

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct ConstructBasic;

template< typename TAllocator, typename ... TArguments >
struct Construct : ConstructBasic< HasMemberFunction_construct< TAllocator, TArguments ... >::value, TAllocator, TArguments ... > {
};

template< typename TAllocator, typename TValue, typename ... TArguments >
struct ConstructBasic< true, TAllocator, TValue *, TArguments ... > {
	static void call(TAllocator allocator, TValue * pointer, TArguments && ... arguments) {
		allocator.construct(pointer, forward<TArguments>(arguments) ...);
	}
};

template< typename TAllocator, typename TValue, typename ... TArguments >
struct ConstructBasic< false, TAllocator, TValue *, TArguments ... > {
	static void call(TAllocator allocator, TValue * pointer, TArguments && ... arguments) {
		::new (reinterpret_cast< void * >(pointer)) TValue(forward<TArguments>(arguments) ...);
	}
};

////////////////////////////////
//
// AllocatorTraits::destroy()
//
#define BR_TYPE_OPERATE_FUNCTION_NAME destroy
#include <libbr/type_traits/has_member_function.inc>

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct DestroyBasic;

template< typename TAllocator, typename ... TArguments >
struct Destroy : DestroyBasic< HasMemberFunction_destroy< TAllocator, TArguments ... >::value, TAllocator, TArguments ... > {
};

template< typename TAllocator, typename ... TArguments >
struct DestroyBasic< true, TAllocator, TArguments ... > {
	static void call(TAllocator allocator, TArguments && ... arguments) {
		allocator.destroy(forward<TArguments>(arguments) ...);
	}
};

template< typename TAllocator, typename TValue >
struct DestroyBasic< false, TAllocator, TValue * > {
	static void call(TAllocator allocator, TValue * pointer) {
		pointer->~TValue();
	}
};

////////////////////////////////
//
// AllocatorTraits::max_size()
//
#define BR_TYPE_OPERATE_FUNCTION_NAME max_size
#include <libbr/type_traits/has_member_function.inc>

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct MaxSizeBasic;

template< typename TAllocator, typename ... TArguments >
struct MaxSize : MaxSizeBasic< HasMemberFunction_max_size< TAllocator, TArguments ... >::value, TAllocator, TArguments ... > {
};

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
#define BR_TYPE_OPERATE_FUNCTION_NAME select_on_container_copy_construction
#include <libbr/type_traits/has_member_function.inc>

template< bool has_member_function, typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstructionBasic;

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

template< typename TAllocator, typename ... TArguments >
struct SelectOnContainerCopyConstruction : SelectOnContainerCopyConstructionBasic< HasMemberFunction_select_on_container_copy_construction< TAllocator, TArguments ... >::value, TAllocator, TArguments ... > {
};

} // namespace AllocatorTraits
} // namespace TypeTraits
} // namespace Detail

template< typename TAllocator >
struct AllocatorTraits {
	using Allocator        = TAllocator;
	using Value            = Detail::TypeTraits::AllocatorTraits::Value<Allocator>;
	using Pointer          = Detail::TypeTraits::AllocatorTraits::Pointer<Allocator>;
	using ConstPointer     = Detail::TypeTraits::AllocatorTraits::ConstPointer<Allocator>;
	using VoidPointer      = Detail::TypeTraits::AllocatorTraits::VoidPointer<Allocator>;
	using ConstVoidPointer = Detail::TypeTraits::AllocatorTraits::ConstVoidPointer<Allocator>;
	using Difference       = Detail::TypeTraits::AllocatorTraits::Difference<Allocator>;
	using Size             = Detail::TypeTraits::AllocatorTraits::Size<Allocator>;

	using IsPropagateOnContainerCopyAssignment = Detail::TypeTraits::AllocatorTraits::IsPropagateOnContainerCopyAssignment<Allocator>;
	using IsPropagateOnContainerMoveAssignment = Detail::TypeTraits::AllocatorTraits::IsPropagateOnContainerMoveAssignment<Allocator>;
	using IsPropagateOnContainerSwap           = Detail::TypeTraits::AllocatorTraits::IsPropagateOnContainerSwap<Allocator>;

	template< typename TValue >
	using Rebind = Detail::TypeTraits::AllocatorTraits::Rebind< TAllocator, TValue >;

	static Pointer allocate(Allocator & allocator, Size size) {
		return allocator.allocate(size);
	}

	static Pointer allocate(Allocator & allocator, Size size, ConstVoidPointer hint) {
		return Detail::TypeTraits::AllocatorTraits::Allocate< Allocator, Size, ConstVoidPointer >::call(
			allocator, size, hint
		);
	}

	static void deallocate(Allocator & allocator, Pointer pointer, Size size) noexcept {
		allocator.deallocate(pointer, size);
	}

	template< typename TValue, typename ... TArguments >
	static void construct(Allocator & allocator, TValue * pointer, TArguments && ... arguments) {
		Detail::TypeTraits::AllocatorTraits::Construct< Allocator, TValue *, TArguments ... >::call(
			allocator, pointer, forward<TArguments>(arguments) ...
		);
	}

	template< typename TValue >
	static void destroy(Allocator & allocator, TValue * pointer) {
		Detail::TypeTraits::AllocatorTraits::Destroy< Allocator, TValue * >::call(allocator, pointer);
	}

	static Size max_size(Allocator const & allocator) noexcept {
		return Detail::TypeTraits::AllocatorTraits::MaxSize<Allocator>::call(allocator);
	}

	static Allocator select_on_container_copy_construction(Allocator const & allocator) noexcept {
		Detail::TypeTraits::AllocatorTraits::SelectOnContainerCopyConstruction<Allocator>::call(allocator);
	}
};

} // namespace BR
