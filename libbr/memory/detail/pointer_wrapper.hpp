#pragma once

#include <libbr/assert/assert.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_pointer.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/extent.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/remove_extent.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {

template< typename TValue >
class BasicPointerWrapper {

private:
	using Self = BasicPointerWrapper;

public:
	using Value = TValue;
	using Pointer = AddPointer< Value >;

	BasicPointerWrapper() : pointer_(nullptr) { }

	BasicPointerWrapper(NullPointer) : Self() { }

	explicit BasicPointerWrapper(Pointer pointer) : pointer_(pointer) { }

	BasicPointerWrapper(Self && pointer) : pointer_(pointer) {
		pointer.pointer_ = nullptr;
	}

	Pointer get() const noexcept {
		return pointer_;
	}

private:
	Pointer pointer_;

}; // class BasicPointerWrapper<TPointer>

template< typename TValue >
class ScalarPointerWrapper : public BasicPointerWrapper< TValue > {

public:
	using Element = TValue;

private:
	using Self = ScalarPointerWrapper;
	using Base = BasicPointerWrapper< Element >;

public:
	AddLValueReference< Element > operator*() const noexcept {
		BR_ASSERT(Base::get() != nullptr);
		return *Base::get();
	}

	typename Base::Pointer operator->() const noexcept {
		BR_ASSERT(Base::get() != nullptr);
		return Base::get();
	}
}; // ScalarPointerWrapper<TValue>

template< typename TValue >
class ArrayPointerWrapper : public BasicPointerWrapper< RemoveExtent< TValue > > {

public:
	using Element = RemoveExtent< TValue >;

private:
	using Self = ArrayPointerWrapper;
	using Base = BasicPointerWrapper< Element >;

public:
	using Value   = TValue;

	Element operator[](Size index) const noexcept {
		BR_ASSERT(Base::get() != nullptr);
		BR_ASSERT(index >= 0 && (index < Extent< Value >::value || Extent< Value >::value == 0));
		return Base::get()[index];
	}
}; // class ArrayPointerWrapper<TValue>

template< typename TValue >
class PointerWrapper : public Conditional<
	IsArray< TValue >,
	ArrayPointerWrapper< TValue >,
	ScalarPointerWrapper< TValue >
> {
private:
	using Base = Conditional<
		IsArray< TValue >,
		ArrayPointerWrapper< TValue >,
		ScalarPointerWrapper< TValue >
	>;

public:
	using Value   = typename Base::Value;
	using Element = typename Base::Element;
	using Pointer = typename Base::Pointer;

};
} // namespace Detail
} // namespace BR
