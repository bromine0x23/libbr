#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/new.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {
namespace Memory {

template< typename TValue >
class Allocator;

template<>
class Allocator< void > {
public:
	using Value        = void;
	using Pointer      = void *;
	using ConstPointer = void const *;

	template< typename TOtherValue >
	struct TypeRebind : TypeOperate::TypeWrapper< Allocator< TOtherValue > > {};

	template< typename TOtherValue >
	using Rebind = TypeOperate::TypeUnwrap< TypeRebind< TOtherValue > >;
}; // class Allocator< void >

template<>
class Allocator< void const > {
public:
	using Value        = void const;
	using Pointer      = void const *;
	using ConstPointer = void const *;

	template< typename TOtherValue >
	struct TypeRebind : TypeOperate::TypeWrapper< Allocator< TOtherValue > > {};

	template< typename TOtherValue >
	using Rebind = TypeOperate::TypeUnwrap< TypeRebind< TOtherValue > >;
}; // class Allocator< void const >

template< typename TValue >
class Allocator {
public:
	using Value          = TValue;
	using Pointer        = TValue *;
	using ConstPointer   = TValue const *;
	using Reference      = TValue &;
	using ConstReference = TValue const &;
	using Size           = BR::Size;
	using Difference     = BR::PointerDifference;

	using IsPropagateOnContainerMoveAssignment = TypeOperate::BooleanTrue;

	template< typename TOtherValue >
	struct TypeRebind : TypeOperate::TypeWrapper< Allocator< TOtherValue > > {};

	template< typename TOtherValue >
	using Rebind = TypeOperate::TypeUnwrap< TypeRebind< TOtherValue > >;

	Allocator() noexcept {}

	template< typename TOtherValue >
	Allocator(Allocator< TOtherValue > const &) noexcept {}

	Pointer address(Reference reference) noexcept {
		return address_of(reference);
	}

	ConstPointer address(ConstReference reference) const noexcept {
		return address_of(reference);
	}

	Pointer allocate(Size size, Allocator< void >::ConstPointer = nullptr) {
		return static_cast< Pointer >(Detail::allocate(size * sizeof(Value)));
	}

	void deallocate(Pointer pointer, Size) noexcept {
		return Detail::allocate((void *)pointer);
	}

	Size maxSize() const noexcept {
		return Size(~0) / sizeof(Value);
	}

	template< typename TOtherValue, typename ... TArguments >
	void construct(TOtherValue * pointer, TArguments && ... arguments) {
		::new((void *)pointer) TOtherValue(forward< TArguments >(arguments) ...);
	}

	void destroy(Pointer pointer) {
		pointer->~Value();
	}
}; // class Allocator

template< typename TValue >
class Allocator< TValue const > {
public:
	using Value          = TValue;
	using Pointer        = TValue const *;
	using ConstPointer   = TValue const *;
	using Reference      = TValue const &;
	using ConstReference = TValue const &;
	using Size           = BR::Size;
	using Difference     = BR::PointerDifference;

	using IsPropagateOnContainerMoveAssignment = TypeOperate::BooleanTrue;

	template< typename TOtherValue >
	struct TypeRebind : TypeOperate::TypeWrapper< Allocator< TOtherValue > > {};

	template< typename TOtherValue >
	using Rebind = TypeOperate::TypeUnwrap< TypeRebind< TOtherValue > >;

	Allocator() noexcept {}

	template< typename TOtherValue >
	Allocator(Allocator< TOtherValue > const &) noexcept {}

	ConstPointer address(ConstReference reference) const noexcept {
		return address_of(reference);
	}

	Pointer allocate(Size size, Allocator< void >::ConstPointer = nullptr) {
		return static_cast< Pointer >(Detail::allocate(size * sizeof(Value)));
	}

	void deallocate(Pointer pointer, Size) noexcept {
		return Detail::allocate((void *)pointer);
	}

	Size maxSize() const noexcept {
		return Size(~0) / sizeof(Value);
	}

	template< typename TOtherValue, typename ... TArguments >
	void construct(TOtherValue * pointer, TArguments && ... arguments) {
		::new((void *)pointer) TOtherValue(forward< TArguments >(arguments) ...);
	}

	void destroy(Pointer pointer) {
		pointer->~Value();
	}
}; // class Allocator< TValue const >

template< typename T0, typename T1 >
inline bool operator==(Allocator< T0 > const &, Allocator< T1 > const &) noexcept {
	return true;
}

template< typename T0, typename T1 >
inline bool operator!=(Allocator< T0 > const &, Allocator< T1 > const &) noexcept {
	return false;
}

} // namespace Memory
} // namespace BR