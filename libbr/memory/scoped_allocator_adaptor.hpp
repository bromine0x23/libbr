/**
 * @file
 * @brief
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/allocator_traits.hpp>
#include <libbr/type_traits/allocator_constructor_usage.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_use_allocator.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename... TAllocators >
class ScopedAllocatorAdaptor;

namespace Detail {
namespace Memory {
namespace ScopedAllocatorAdaptor {

template< typename... TAllocators >
class Storage;

template< typename TOuterAllocator, typename... TInnerAllocators >
class Storage< TOuterAllocator, TInnerAllocators... > : public TOuterAllocator {
private:
	using OuterAllocator = TOuterAllocator;

protected:
	using InnerAllocator = BR::ScopedAllocatorAdaptor< TInnerAllocators... >;

private:
	InnerAllocator m_inner;

protected:
	Storage() noexcept {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	Storage(
		TOuter && outer,  TInnerAllocators const & ... inners
	) noexcept : OuterAllocator(forward<TOuter>(outer)), m_inner(inners...) {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter const & > > >
	Storage(
		Storage< TOuter, TInnerAllocators... > const & other
	) noexcept : OuterAllocator(other.outer_allocator()), m_inner(other.inner_allocator()) {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	Storage(
		Storage< TOuter, TInnerAllocators... > && other
	) noexcept : OuterAllocator(move(other.outer_allocator())), m_inner(move(other.inner_allocator())) {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	Storage(
		TOuter && outer, InnerAllocator const & inner
	) noexcept : OuterAllocator(forward<TOuter>(outer)), m_inner(inner) {
	}

	auto outer_allocator() noexcept -> OuterAllocator & {
		return static_cast< OuterAllocator & >(*this);
	}

	auto outer_allocator() const noexcept -> OuterAllocator const & {
		return static_cast< OuterAllocator const & >(*this);
	}

	auto inner_allocator() noexcept -> InnerAllocator & {
		return m_inner;
	}

	auto inner_allocator() const noexcept -> InnerAllocator const & {
		return m_inner;
	}

	auto select_on_container_copy_construction() const noexcept -> BR::ScopedAllocatorAdaptor< OuterAllocator, TInnerAllocators... > {
		return BR::ScopedAllocatorAdaptor< OuterAllocator, TInnerAllocators... >(
			AllocatorTraits<OuterAllocator>::select_on_container_copy_construction(this->outer_allocator()),
			AllocatorTraits<InnerAllocator>::select_on_container_copy_construction(this->inner_allocator())
		);
	}

	template< typename... TAllocators >
	friend class Storage;

}; // Storage< TOuterAllocator, TInnerAllocators... >


template< typename TOuterAllocator >
class Storage<TOuterAllocator> : public TOuterAllocator {
private:
	using OuterAllocator = TOuterAllocator;

protected:
	using InnerAllocator = BR::ScopedAllocatorAdaptor<OuterAllocator>;

	Storage() noexcept {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	Storage(TOuter && outer) noexcept : OuterAllocator(forward<TOuter>(outer)) {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter const & > > >
	Storage(Storage<TOuter> const & other) noexcept : OuterAllocator(other.outer_allocator()) {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	Storage(Storage<TOuter> && other) noexcept : OuterAllocator(move(other.outer_allocator())) {
	}

	auto outer_allocator() noexcept -> OuterAllocator & {
		return static_cast< OuterAllocator & >(*this);
	}

	auto outer_allocator() const noexcept -> OuterAllocator const & {
		return static_cast< OuterAllocator const & >(*this);
	}

	auto inner_allocator() noexcept -> InnerAllocator & {
		return static_cast< InnerAllocator & >(*this);
	}

	auto inner_allocator() const noexcept -> InnerAllocator const & {
		return static_cast< InnerAllocator const & >(*this);
	}

	auto select_on_container_copy_construction() const noexcept -> BR::ScopedAllocatorAdaptor<OuterAllocator> {
		return BR::ScopedAllocatorAdaptor<OuterAllocator>(
			AllocatorTraits<OuterAllocator>::select_on_container_copy_construction(outer_allocator())
		);
	}

	Storage(OuterAllocator const & outer, InnerAllocator const & inner) noexcept;

	template< typename... TAllocators >
	friend class Storage;

}; // class Storage<TOuterAllocator>

#define BR_TYPE_OPERATE_FUNCTION_NAME outer_allocator
#include <libbr/type_traits/has_member_function.inc>

template< typename TAllocator, bool _dummy = HasMemberFunction_outer_allocator<TAllocator>::value >
struct OuterMost;

template< typename TAllocator >
struct OuterMost< TAllocator, true > {
	using OuterAllocator = RemoveReference< decltype(make_rvalue<TAllocator>().outer_allocator()) >;
	using Type = typename OuterMost<TAllocator>::Type;
	auto operator()(Type & allocator) const noexcept -> Type & {
		return OuterMost<OuterAllocator>()(allocator.outer_allocator());
	}
};

template< typename TAllocator >
struct OuterMost< TAllocator, false > {
	using Type = TAllocator;
	auto operator()(Type & allocator) const noexcept -> Type & {
		return allocator;
	}
};

} // namespace ScopedAllocatorAdaptor
} // namespace Memory
} // namespace Detail

/**
 * @brief ScopedAllocatorAdaptor
 */
template< typename TOuterAllocator, typename ... TInnerAllocators >
class ScopedAllocatorAdaptor< TOuterAllocator, TInnerAllocators... > : public Detail::Memory::ScopedAllocatorAdaptor::Storage< TOuterAllocator, TInnerAllocators... > {

	template< typename... TAllocators >
	friend class Detail::Memory::ScopedAllocatorAdaptor::Storage;

	using Base = Detail::Memory::ScopedAllocatorAdaptor::Storage< TOuterAllocator, TInnerAllocators... >;

public:
	using OuterAllocator = TOuterAllocator;

	using InnerAllocator = typename Base::InnerAllocator;

protected:
	using OuterTraits = AllocatorTraits<OuterAllocator>;

public:
	using Size = typename OuterTraits::Size;

	using Difference = typename OuterTraits::Difference;

	using Pointer = typename OuterTraits::Pointer;

	using ConstPointer = typename OuterTraits::ConstPointer;

	using VoidPointer = typename OuterTraits::VoidPointer;

	using ConstVoidPointer = typename OuterTraits::ConstVoidPointer;

	using IsPropagateOnContainerCopyAssignment = BooleanAnd<
		typename OuterTraits::IsPropagateOnContainerCopyAssignment,
		typename AllocatorTraits<TInnerAllocators>::IsPropagateOnContainerCopyAssignment ...
	>;

	using IsPropagateOnContainerMoveAssignment = BooleanAnd<
		typename OuterTraits::IsPropagateOnContainerMoveAssignment,
		typename AllocatorTraits<TInnerAllocators>::IsPropagateOnContainerMoveAssignment ...
	>;

	using IsPropagateOnContainerSwap = BooleanAnd<
		typename OuterTraits::IsPropagateOnContainerSwap,
		typename AllocatorTraits<TInnerAllocators>::IsPropagateOnContainerSwap ...
	>;

	template< typename TValue >
	using Rebind = ScopedAllocatorAdaptor< typename OuterTraits::template Rebind<TValue>, TInnerAllocators... >;

	ScopedAllocatorAdaptor() noexcept {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	ScopedAllocatorAdaptor(TOuter && outer,  TInnerAllocators const & ... inners) noexcept : Base(forward<TOuter>(outer), inners ...) {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter const & > > >
	ScopedAllocatorAdaptor(ScopedAllocatorAdaptor< TOuter, TInnerAllocators ... > const & other) noexcept : Base(other) {
	}

	template< typename TOuter, typename _TDummy = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	ScopedAllocatorAdaptor(ScopedAllocatorAdaptor< TOuter, TInnerAllocators ... > && other) noexcept : Base(move(other)) {
	}

	~ScopedAllocatorAdaptor() = default;

	auto outer_allocator() noexcept -> OuterAllocator & {
		return Base::outer_allocator();
	}

	auto outer_allocator() const noexcept -> OuterAllocator const & {
		return Base::outer_allocator();
	}

	auto inner_allocator() noexcept -> InnerAllocator & {
		return Base::inner_allocator();
	}

	auto inner_allocator() const noexcept -> InnerAllocator const & {
		return Base::inner_allocator();
	}

	auto allocate(Size n) -> Pointer {
		return OuterTraits::allocate(outer_allocator(), n);
	}

	auto allocate(Size size, ConstVoidPointer hint) -> Pointer {
		return OuterTraits::allocate(outer_allocator(), size, hint);
	}

	void deallocate(Pointer pointer, Size size) noexcept {
		OuterTraits::deallocate(outer_allocator(), pointer, size);
	}

	auto max_size() const -> Size {
		return OuterTraits::max_size(outer_allocator());
	}

	template< typename TValue, typename... TArguments>
	void construct(TValue * pointer, TArguments && ... arguments) {
		m_construct(
			AllocatorConstructorUsage< TValue, InnerAllocator, TArguments... >(), pointer, forward<TArguments>(arguments)...
		);
	}

	template< typename TValue >
	void destroy(TValue * pointer) {
		using OM = Detail::Memory::ScopedAllocatorAdaptor::OuterMost<OuterAllocator>;
		AllocatorTraits<OM>::destroy(OM(outer_allocator()), pointer);
	}

	auto select_on_container_copy_construction() const noexcept -> ScopedAllocatorAdaptor {
		return Base::select_on_container_copy_construction();
	}

	auto operator==(ScopedAllocatorAdaptor const & y) const noexcept -> bool {
		return m_equal(y, BooleanConstant< sizeof...(TInnerAllocators) == 0 >());
	}

	auto operator!=(ScopedAllocatorAdaptor const & y) const noexcept -> bool {
		return !(*this == y);
	}

private:
	template< typename TOuter, typename = EnableIf< IsConstructible< OuterAllocator, TOuter > > >
	ScopedAllocatorAdaptor(TOuter && outer, InnerAllocator const & inner) noexcept : Base(forward<TOuter>(outer), inner) {
	}

	template< typename TValue, typename... TArguments>
	void m_construct(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used > _dummy, TValue * pointer, TArguments && ... arguments) {
		using OM = Detail::Memory::ScopedAllocatorAdaptor::OuterMost<OuterAllocator>;
		AllocatorTraits<OM>::construct(OM()(outer_allocator()), pointer, forward<TArguments>(arguments)...);
	}

	template< typename TValue, typename... TArguments>
	void m_construct(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag > _dummy, TValue * pointer, TArguments && ... arguments) {
		using OM = Detail::Memory::ScopedAllocatorAdaptor::OuterMost<OuterAllocator>;
		AllocatorTraits<OM>::construct(OM()(outer_allocator()), pointer, allocator_argument_tag, inner_allocator(), forward<TArguments>(arguments)...);
	}

	template< typename TValue, typename... TArguments>
	void m_construct(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag > _dummy, TValue * pointer, TArguments && ... arguments) {
		using OM = Detail::Memory::ScopedAllocatorAdaptor::OuterMost<OuterAllocator>;
		AllocatorTraits<OM>::construct(OM()(outer_allocator()), pointer, allocator_argument_tag, forward<TArguments>(arguments)..., inner_allocator());
	}

	auto m_equal(ScopedAllocatorAdaptor const & y, BooleanTrue _dummy) const noexcept -> bool {
		return outer_allocator() == y.outer_allocator();
	}

	auto m_equal(ScopedAllocatorAdaptor const & y, BooleanFalse _dummy) const noexcept -> bool {
		return outer_allocator() == y.outer_allocator() && inner_allocator() == y.inner_allocator();
	}

}; // class ScopedAllocatorAdaptor< TOuterAllocator, TInnerAllocators... >

} // namespace BR
