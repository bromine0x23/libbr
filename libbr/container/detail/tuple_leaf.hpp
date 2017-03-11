#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/allocator_constructor_usage.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>
#include <libbr/utility/wrapped_reference.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace Tuple {

template< Size I, typename TElement, Boolean derive = BooleanAnd< IsEmpty<TElement>, NotFinal<TElement> >{}  >
class Leaf;

template< Size I, typename T, Boolean B >
inline void swap(Leaf< I, T, B > & x, Leaf< I, T, B > & y) noexcept(noexcept(swap(x.get(), y.get()))) {
	using BR::swap;
	swap(x.get(), y.get());
}

template< Size I, typename TElement >
class Leaf< I, TElement, false > {
public:
	BR_CONSTEXPR_AFTER_CXX11 Leaf() noexcept(HasNothrowDefaultConstructor<TElement>{}) : m_element() {
		static_assert(NotReference<TElement>{}, "Attempted to default construct a reference element in a Tuple");
	}

	Leaf(Leaf const & other) = default;

	Leaf(Leaf && other) = default;

	template< typename TAllocator >
	Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const &) : m_element() {
		static_assert(NotReference<TElement>{}, "Attempted to default construct a reference element in a Tuple");
	}

	template< typename TAllocator >
	Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator) : m_element(allocator_argument_tag, allocator) {
		static_assert(NotReference<TElement>{}, "Attempted to default construct a reference element in a Tuple");
	}

	template< typename TAllocator >
	Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator) : m_element(allocator) {
		static_assert(NotReference<TElement>{}, "Attempted to default construct a reference element in a Tuple");
	}

	template< typename TValue, typename = EnableIf< BooleanAnd< NotSame< Decay<TValue>, Leaf >, IsConstructible< TElement, TValue > > > >
	explicit BR_CONSTEXPR_AFTER_CXX11 Leaf(TValue && value) noexcept(IsNothrowConstructible< TElement, TValue >{}) : m_element(forward<TValue>(value)) {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame< RemoveReference<TValue>, WrappedReference< RemoveReference<TElement> >
					>
				>
			>,
			BooleanAnd< IsRValueReference<TElement>, NotLValueReference<TValue> >
			>{},
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

	template< typename TValue, typename TAllocator >
	explicit Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const &, TValue && value) : m_element(forward<TValue>(value)) {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame< RemoveReference<TValue>, WrappedReference< RemoveReference<TElement> > >
					>
				>
			>{},
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

	template< typename TValue, typename TAllocator >
	explicit Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator, TValue && value) : m_element(allocator_argument_tag, allocator, forward<TValue>(value)) {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame< RemoveReference<TValue>, WrappedReference< RemoveReference<TElement> > >
					>
				>
			>{},
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

	template< typename TValue, typename TAllocator >
	explicit Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator, TValue && value) : m_element(forward<TValue>(value), allocator) {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame< RemoveReference<TValue>, WrappedReference< RemoveReference<TElement> > >
					>
				>
			>{},
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

	template< typename TValue >
	auto operator=(TValue && value) noexcept(IsNothrowAssignable< AddLValueReference<TElement>, TValue >()) -> Leaf & {
		m_element = forward<TValue>(value);
		return *this;
	}

	auto swap(Leaf & other) noexcept(IsNothrowSwappable<Leaf>{}) -> SInt {
		using BR::swap;
		swap(*this, other);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TElement        & { return m_element; }
	constexpr                auto get() const  & noexcept -> TElement const  & { return m_element; }
	BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TElement       && { return static_cast< TElement       && >(m_element); }
	constexpr                auto get() const && noexcept -> TElement const && { return static_cast< TElement const && >(m_element); }

private:
	auto operator=(Leaf const & other) -> Leaf & = delete;

private:
	TElement m_element;
}; // class Leaf< I, TElement, false >

template< Size I, typename TElement >
class Leaf< I, TElement, true > : private TElement {
public:
	BR_CONSTEXPR_AFTER_CXX11 Leaf() noexcept(HasNothrowDefaultConstructor<TElement>{}) {
	}

	Leaf(Leaf const & other) = default;

	Leaf(Leaf && other) = default;

	template< typename TAllocator >
	Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const &) {
	}

	template< typename TAllocator >
	Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator) : TElement(allocator_argument_tag, allocator) {
	}

	template< typename TAllocator >
	Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator) : TElement(allocator) {
	}

	template< typename TValue, typename = EnableIf< BooleanAnd< NotSame< Decay<TValue>, Leaf >, IsConstructible< TElement, TValue > > > >
	explicit BR_CONSTEXPR_AFTER_CXX11 Leaf(TValue && value) noexcept(IsNothrowConstructible< TElement, TValue >{}) : TElement(forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const & _allocator, TValue && value) : TElement(forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator, TValue && value) : TElement(allocator_argument_tag, allocator, forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit Leaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator, TValue && value) : TElement(forward<TValue>(value), allocator) {
	}

	template< typename TValue >
	auto operator=(TValue && value) noexcept(IsNothrowAssignable< TElement &, TValue >{}) -> Leaf & {
		TElement::operator=(forward<TValue>(value));
		return *this;
	}

	auto swap(Leaf & other) noexcept(IsNothrowSwappable<Leaf>()) -> int {
		using BR::swap;
		swap(*this, other);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TElement        & { return static_cast< TElement        & >(*this); }
	constexpr                auto get() const  & noexcept -> TElement const  & { return static_cast< TElement const  & >(*this); }
	BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TElement       && { return static_cast< TElement       && >(*this); }
	constexpr                auto get() const && noexcept -> TElement const && { return static_cast< TElement const && >(*this); }

private:
	auto operator=(Leaf const & other) -> Leaf & = delete;

}; // class Leaf< I, TElement, true >

} // namespace Tuple
} // namespace Container
} // namespace Detail
} // namespace BR
