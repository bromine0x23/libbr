/**
 * @file
 * @brief 函数对象
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/compressed_pair.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/functional/bad_call_exception.hpp>
#include <libbr/functional/basic_functor.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/memory/allocator_destructor.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_traits/allocator_traits.hpp>
#include <libbr/type_traits/decay.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_callable.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/piecewise_construct_tag.hpp>
#include <libbr/utility/swap.hpp>
#include <libbr/utility/type_info.hpp>

namespace BR {

inline namespace Functional {

template< typename TFunction >
class Function;

} // inline namespace Functional


namespace Detail {
namespace Functional {

template< typename TFunction >
class BasicFunction;

template< typename TResult, typename ... TArguments >
class BasicFunction< TResult(TArguments ...) > {
public:
	constexpr BasicFunction() noexcept = default;

	virtual ~BasicFunction() = default;

	virtual auto clone() const -> BasicFunction<TResult(TArguments ...)> * = 0;

	virtual void clone(BasicFunction<TResult(TArguments ...)> * function) const = 0;

	virtual void destroy() noexcept = 0;

	virtual void destroy_deallocate() noexcept = 0;

	virtual auto operator()(TArguments && ... arguments) -> TResult = 0;

	virtual auto target(TypeInfo const & info) const noexcept -> void const * = 0;

	virtual auto target_type() const noexcept -> TypeInfo const & = 0;

private:
	BasicFunction(BasicFunction const & functor) = delete;

	auto operator=(BasicFunction const & functor) -> BasicFunction & = delete;
};

template< typename TDerivedFunction, typename TAllocator, typename TBaseFunction >
class Function;

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
class Function< TDerivedFunction, TAllocator, TResult(TArguments ...) > : public BasicFunction<TResult(TArguments ...)> {
public:
	explicit Function(TDerivedFunction && function) : m_impl(piecewise_construct_tag, forward_as_tuple(move(function)), forward_as_tuple()) {
	}

	explicit Function(
		TDerivedFunction const & function, TAllocator const & allocator
	) : m_impl(piecewise_construct_tag, forward_as_tuple(function), forward_as_tuple(allocator)) {
	}

	explicit Function(
		TDerivedFunction const & function, TAllocator && allocator
	) : m_impl(piecewise_construct_tag, forward_as_tuple(function), forward_as_tuple(move(allocator))) {
	}

	explicit Function(
		TDerivedFunction && function, TAllocator && allocator
	) : m_impl(piecewise_construct_tag, forward_as_tuple(move(function)), forward_as_tuple(move(allocator))) {
	}

	virtual auto clone() const -> BasicFunction<TResult(TArguments ...)> * override;

	virtual void clone(BasicFunction<TResult(TArguments ...)> * function) const override;

	virtual void destroy() noexcept override;

	virtual void destroy_deallocate() noexcept override;

	virtual auto operator()(TArguments && ... arguments) -> TResult override;

	virtual auto target(TypeInfo const & info) const noexcept -> void const * override;

	virtual auto target_type() const noexcept -> TypeInfo const & override;

private:
	CompressedPair< TDerivedFunction, TAllocator > m_impl;
}; // Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
auto Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >::clone() const -> BasicFunction<TResult(TArguments ...)> * {
	using Allocator = typename AllocatorTraits<TAllocator>::template Rebind<Function>;
	using Destructor = AllocatorDestructor<Allocator>;
	Allocator allocator(m_impl.second());
	UniquePointer< Function, Destructor > hold(allocator.allocate(1), Destructor(allocator, 1));
	new (hold.get()) Function(m_impl.first(), TAllocator(allocator));
	return hold.release();
};

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
void Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >::clone(BasicFunction<TResult(TArguments ...)> * function) const {
	new (function) Function(m_impl.first(), m_impl.second());
}

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
void Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >::destroy() noexcept {
	m_impl.~CompressedPair< TDerivedFunction, TAllocator >();
}

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
void Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >::destroy_deallocate() noexcept {
	using Allocator = typename AllocatorTraits<TAllocator>::template Rebind<Function>;
	Allocator allocator(m_impl.second());
	m_impl.~CompressedPair< TDerivedFunction, TAllocator >();
	allocator.deallocate(this, 1);
}

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
auto Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >::operator()(TArguments && ... arguments) -> TResult {
	return invoke(m_impl.first(), forward<TArguments>(arguments)...);
};

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
auto Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >::target(TypeInfo const & info) const noexcept -> void const * {
	if (info == BR_TYPE_ID(TDerivedFunction)) {
		return &m_impl.first();
	}
	return static_cast< void const * >(nullptr);
};

template< typename TDerivedFunction, typename TAllocator, typename TResult, typename ... TArguments >
auto Function< TDerivedFunction, TAllocator, TResult(TArguments ...) >::target_type() const noexcept -> TypeInfo const & {
	return BR_TYPE_ID(Function);
};

} // namespace Functional
} // namespace Detail

inline namespace Functional {

template< typename TResult, typename ... TArguments >
class Function<TResult(TArguments ...)> : BasicFunctor< TArguments ... > {
	using Basic = Detail::Functional::BasicFunction<TResult(TArguments ...)>;

	template< typename TFunction >
	static auto not_null(TFunction const & _f) -> bool {
		return true;
	}

	template< typename TOtherResult, typename ...TOtherArguments >
	static auto not_null(TOtherResult(*p)(TOtherArguments...)) -> bool {
		return p != nullptr;
	}

	template< typename TOtherResult, typename TClass, typename ...TOtherArguments >
	static auto not_null(TOtherResult (TClass::*p)(TOtherArguments...)) -> bool {
		return p != nullptr;
	}

	template< typename TOtherResult, typename TClass, typename ...TOtherArguments >
	static auto not_null(TOtherResult (TClass::*p)(TOtherArguments...) const) -> bool {
		return p != nullptr;
	}
	template< typename TOtherResult, typename TClass, typename ...TOtherArguments >
	static auto not_null(TOtherResult (TClass::*p)(TOtherArguments...) volatile) -> bool {
		return p != nullptr;
	}
	template< typename TOtherResult, typename TClass, typename ...TOtherArguments >
	static auto not_null(TOtherResult (TClass::*p)(TOtherArguments...) const volatile) -> bool {
		return p != nullptr;
	}

	template< typename TOtherResult, typename ...TOtherArguments >
	static auto not_null(Function<TOtherResult(TOtherArguments...)> const & f) -> bool {
		return static_cast<bool>(f);
	}

	template< typename TFunction, bool _dummy = BooleanAnd< NotSame< TFunction, Function >, BR::IsCallable< TFunction &, TArguments... > >::value >
	struct IsCallable;

	template< typename TFunction >
	struct IsCallable< TFunction, true > : IsConvertible< decltype(invoke(make_rvalue< TFunction & >(), make_rvalue<TArguments>() ...)), TResult > {
	};

	template< typename TFunction >
	struct IsCallable< TFunction, false > : BooleanFalse {
	};

public:
	Function() noexcept : m_impl(nullptr) {
	}

	Function(NullPointer _null) noexcept : Function() {
	}

	Function(Function const & function) {
		if (function.m_impl != nullptr) {
			m_impl = function.m_impl->clone();
		} else {
			m_impl = nullptr;
		}
	}

	Function(Function && function) noexcept {
		if (function.m_impl != nullptr) {
			m_impl = function.m_impl;
			function.m_impl = nullptr;
		} else {
			m_impl = nullptr;
		}
	}

	template< typename TFunction, typename _TDummy = EnableIf< BooleanAnd< IsCallable<TFunction>, NotSame< TFunction, Function > > > >
	Function(TFunction function) : m_impl(nullptr) {
		if (not_null(function)) {
			using F = Detail::Functional::Function< TFunction, Allocator<TFunction>, TResult(TArguments...) >;
			using A = Allocator<F>;
			using D = AllocatorDestructor<A>;
			A a;
			UniquePointer< Basic, D > hold(a.allocate(1), D(a, 1));
			new (hold.get()) F(move(function), Allocator<TFunction>(a));
			m_impl = hold.release();
		}
	};

	template< typename TAllocator >
	Function(AllocatorArgumentTag _tag, TAllocator const & _allocator) noexcept : m_impl(nullptr) {
	}

	template< typename TAllocator >
	Function(AllocatorArgumentTag _tag, TAllocator const & _allocator, NullPointer _null) noexcept : m_impl(nullptr) {
	}

	template< typename TAllocator >
	Function(AllocatorArgumentTag _tag, TAllocator const & _allocator, Function const & function) : Function(function) {
	}

	template< typename TAllocator >
	Function(AllocatorArgumentTag _tag, TAllocator const & _allocator, Function && function) : Function(move(function)) {
	}

	template< typename TAllocator, typename TFunction, typename _TDummy = EnableIf< IsCallable<TFunction> > >
	Function(AllocatorArgumentTag _tag, TAllocator const & _allocator, Function function) : m_impl(nullptr) {
		if (not_null(function)) {
			using F = Detail::Functional::Function< TFunction, TAllocator, TResult(TArguments...) >;
			using A = typename AllocatorTraits<TAllocator>::template Rebind<F>;
			using D = AllocatorDestructor<A>;
			A a;
			UniquePointer< Basic, D > hold(a.allocate(1), D(a, 1));
			new (hold.get()) F(move(function), Allocator<TFunction>(a));
			m_impl = hold.release();
		}
	}

	~Function() {
		if (m_impl != nullptr) {
			m_impl->destroy_deallocate();
		}
		m_impl = nullptr;
	}

	auto operator=(Function const & function) -> Function const & {
		Function(function).swap(*this);
		return *this;
	}

	auto operator=(Function && function) noexcept -> Function const & {
		if (m_impl != nullptr) {
			m_impl->destroy_deallocate();
		}
		m_impl = nullptr;
		if (function.m_impl == nullptr) {
			m_impl = nullptr;
		} else {
			m_impl = function.m_impl;
			function.m_impl = nullptr;
		}
		return *this;
	}

	auto operator=(NullPointer _null) noexcept -> Function const & {
		if (m_impl != nullptr) {
			m_impl->destroy_deallocate();
		}
		m_impl = nullptr;
		return *this;
	}

	template< typename TFunction, typename _TDummy = EnableIf< BooleanAnd< IsCallable< Decay<TFunction> >, NotSame< RemoveReference<TFunction>, Function > > > >
	auto operator=(TFunction && function) noexcept -> Function const & {
		Function(forward<TFunction>(function)).swap(*this);
		return *this;
	};

	void swap(Function & function) noexcept {
		swap(m_impl, function.m_impl);
	}

	explicit operator bool() const noexcept {
		return m_impl != nullptr;
	}

	auto operator()(TArguments... arguments) const -> TResult {
		if (m_impl == 0) {
			throw BadCallException();
		}
		return (*m_impl)(forward<TArguments>(arguments)...);
	}

	auto target_type() const noexcept -> TypeInfo const & {
		if (m_impl == nullptr) {
			return BR_TYPE_ID(void);
		}
		return m_impl->target_type();
	}

	template< typename TInfo >
	auto target() noexcept -> TInfo * {
		if (m_impl == nullptr) {
			return nullptr;
		}
		return static_cast< TInfo * >(m_impl->target(BR_TYPE_ID(TInfo)));
	}

	template< typename TInfo >
	auto target() const noexcept -> TInfo const * {
		if (m_impl == nullptr) {
			return nullptr;
		}
		return static_cast< TInfo const * >(m_impl->target(BR_TYPE_ID(TInfo)));
	}

	template <class _Rp, class... _ArgTypes>
	inline auto operator==(NullPointer _null) const noexcept -> bool {
		return !(*this);
	}

	template <class _Rp, class... _ArgTypes>
	inline auto operator!=(NullPointer _null) const noexcept -> bool {
		return static_cast<bool>(*this);
	}

private:
	template< typename TOtherResult, typename... TOtherArguments >
	auto operator==(Function<TOtherResult(TOtherArguments...)> const &) const -> bool = delete;

	template< typename TOtherResult, typename... TOtherArguments >
	auto operator!=(Function<TOtherResult(TOtherArguments...)> const &) const -> bool = delete;

private:
	Basic * m_impl;
}; // class Function<TResult(TArguments ...)>

template< typename TResult, typename ... TArguments >
inline void swap(Function<TResult(TArguments ...)> & x, Function<TResult(TArguments ...)> & y) noexcept {
	return x.swap(y);
}

} // inline namespace Functional

} // namespace BR
