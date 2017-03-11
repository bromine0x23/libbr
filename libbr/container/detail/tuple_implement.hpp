#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/dummy_false.hpp>
#include <libbr/container/detail/tuple_forward.hpp>
#include <libbr/container/detail/tuple_leaf.hpp>
#include <libbr/container/detail/tuple_traits.hpp>
#include <libbr/type_traits/allocator_constructor_usage.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_copy_assignment.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/integral_sequence.hpp>
#include <libbr/utility/swallow.hpp>
#include <libbr/utility/types.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace Tuple {

template< typename TIndices, typename... TTypes >
class Implement;

template< typename TTarget, typename... TElements >
struct FindLeafChecker;

template< typename TTarget >
struct FindLeafChecker<TTarget> : BooleanTrue {};

template< typename TTarget, typename... TTails >
struct FindLeafChecker< TTarget, TTarget, TTails... > : BooleanFalse {};

template< typename TTarget, typename THead, typename... TTails >
struct FindLeafChecker< TTarget, THead, TTails... > : public BooleanRewrap< FindLeafChecker< TTarget, TTails... > > {};

template< typename T, Size I, typename ... TTypes >
struct TypeFindLeafBasic;

template< typename T, Size I >
struct TypeFindLeafBasic< T, I > {
	static_assert(DummyFalse<T>{}, "Type not found in type list.");
};

template< typename TTarget, Size I, typename ... TTails >
struct TypeFindLeafBasic< TTarget, I, TTarget, TTails... > : public TypeWrapper< Leaf< I, TTarget > > {
	static_assert(FindLeafChecker< TTarget, TTails... >{}, "Type can only occur once in type list.");
};

template< typename TTarget, Size I, typename THead, typename ... TTails >
struct TypeFindLeafBasic< TTarget, I, THead, TTails... > : public TypeRewrap< TypeFindLeafBasic< TTarget, I + 1, TTails... > > {
};

template< typename TTarget, typename ... TTypes >
using FindLeaf = TypeUnwrap< TypeFindLeafBasic< TTarget, 0, TTypes... > >;

template< Size... indices, typename... TElements >
class Implement< IndexSequence<indices...>, TElements... > : public Leaf< indices, TElements >... {
	using Indices = IndexSequence<indices...>;

	template< typename... TValues >
	using EnableAssignment = IsAllAssignable< Types<TElements &...>, Types<TValues...> >;

public:
	struct DirectTag {};

	static constexpr auto direct_tag = DirectTag{};

public:
	BR_CONSTEXPR_AFTER_CXX11 Implement() noexcept(BooleanAnd< HasNothrowDefaultConstructor<TElements>... >{}) {
	}

	template< typename TAllocator >
	BR_CONSTEXPR_AFTER_CXX11 Implement(
		AllocatorArgumentTag,
		TAllocator const & allocator
	) : Leaf< indices, TElements >(
		AllocatorConstructorUsage< TElements, TAllocator >{},
		allocator
	)... {
	}

	Implement(Implement const & other) = default;

	Implement(Implement && other) = default;

	template< typename... TValues >
	BR_CONSTEXPR_AFTER_CXX11 explicit Implement(
		DirectTag,
		TValues &&... values
	) noexcept(
		BooleanAnd< IsNothrowConstructible< TElements, TValues >... >{}
	) : Leaf< indices, TElements >(forward<TValues>(values))... {
	}

	template< typename TAllocator, typename... TValues >
	BR_CONSTEXPR_AFTER_CXX11 explicit Implement(
		AllocatorArgumentTag,
		TAllocator const & allocator,
		DirectTag,
		TValues &&... values
	) : Leaf< indices, TElements >(AllocatorConstructorUsage< TElements, TAllocator, TValues && >{}, allocator, forward<TValues>(values))... {
	}

	template< typename... TValues, typename = EnableIf< IsAllConstructible< Types<TElements...>, Types<TValues const &...> > > >
	BR_CONSTEXPR_AFTER_CXX11 explicit Implement(
		BR::Tuple<TValues...> const & other
	) : Leaf< indices, TElements >(
		other.template get<indices>()
	)... {
	}

	template< typename... TValues, typename = EnableIf< IsAllConstructible< Types<TElements...>, Types<TValues &&...> > > >
	BR_CONSTEXPR_AFTER_CXX11 explicit Implement(
		BR::Tuple<TValues...> && other
	) : Leaf< indices, TElements >(
		forward<TValues>(other.template get<indices>())
	)... {
	}

	template< typename TAllocator, typename... TValues, typename = EnableIf< IsAllConstructible< Types<TElements...>, Types<TValues const &...> > > >
	BR_CONSTEXPR_AFTER_CXX11 explicit Implement(
		AllocatorArgumentTag,
		TAllocator const & allocator,
		BR::Tuple<TValues...> const & other
	) : Leaf< indices, TElements >(
		AllocatorConstructorUsage< TElements, TAllocator, TValues const & >{},
		allocator,
		other.template get<indices>()
	)... {
	}

	template< typename TAllocator, typename... TValues, typename = EnableIf< IsAllConstructible< Types<TElements...>, Types<TValues &&...> > > >
	BR_CONSTEXPR_AFTER_CXX11 explicit Implement(
		AllocatorArgumentTag,
		TAllocator const & allocator,
		BR::Tuple<TValues...> && other
	) : Leaf< indices, TElements >(
		AllocatorConstructorUsage< TElements, TAllocator, TValues && >{},
		allocator,
		forward<TValues>(other.template get<indices>())
	)... {
	}

	auto operator=(Implement const & other) noexcept(BooleanAnd< HasNothrowCopyAssignment<TElements>... >{}) -> Implement & {
		return assign(static_cast< Leaf< indices, TElements > const & >(other).get()...);
	}

	auto operator=(Implement && other) noexcept(BooleanAnd< HasNothrowMoveAssignment<TElements>... >{}) -> Implement &  {
		return assign(forward<TElements>(static_cast< Leaf< indices, TElements > && >(other).get())...);
	}

	template< typename... TValues >
	auto operator=(Implement< Indices, TValues... > const & other) noexcept(
		BooleanAnd< IsNothrowAssignable< TElements &, TValues const & >... >{}
	) -> EnableIf< EnableAssignment<TValues const &...>, Implement & > {
		static_assert(sizeof...(TElements) == sizeof...(TValues), "Number of TElements & TValues should fit.");
		return assign(other.template get<indices>()...);
	}

	template< typename... TValues >
	auto operator=(Implement< Indices, TValues... > && other) noexcept(
		BooleanAnd< IsNothrowAssignable< TElements &, TValues const & >... >{}
	) -> EnableIf< EnableAssignment<TValues &&...>, Implement & > {
		static_assert(sizeof...(TElements) == sizeof...(TValues), "Number of TElements & TValues should fit.");
		return assign(forward<TValues>(other.template get<indices>())...);
	}

	template< typename TFirst, typename TSecond >
	auto operator=(BR::Pair< TFirst, TSecond> const & pair) noexcept(
		BooleanAnd<
			IsNothrowAssignable< typename Types<TElements...>::template Get<0>, TFirst const & >,
			IsNothrowAssignable< typename Types<TElements...>::template Get<1>, TSecond const & >
		>{}
	) -> EnableIf< EnableAssignment< TFirst const &, TSecond const & >, Implement & > {
		static_assert(sizeof...(TElements) == 2, "Number of TElements should be 2.");
		return assign(pair.first, pair.second);
	}

	template< typename TFirst, typename TSecond >
	auto operator=(BR::Pair< TFirst, TSecond> && pair) noexcept(
		BooleanAnd<
			IsNothrowAssignable< typename Types<TElements...>::template Get<0>, TFirst && >,
			IsNothrowAssignable< typename Types<TElements...>::template Get<1>, TSecond && >
		>{}
	) -> EnableIf< EnableAssignment< TFirst &&, TSecond && >, Implement & > {
		static_assert(sizeof...(TElements) == 2, "Number of TElements should be 2.");
		return assign(forward<TFirst>(pair.first), forward<TSecond>(pair.second));
	}

	void swap(Implement & tuple) noexcept(BooleanAnd< IsNothrowSwappable<TElements>... >{}) {
		swallow(
			Leaf< indices, TElements >::swap(
				static_cast< Leaf< indices, TElements > & >(tuple)
			)...
		);
	}

	template< typename... TValues >
	auto assign(TValues &&... values) -> Implement & {
		swallow(Leaf< indices, TElements >::operator=(forward<TValues>(values))...);
		return *this;
	}

	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> typename Types<TElements      ...>::template Get<I>  & { return static_cast< Leaf< I, typename Types<TElements...>::template Get<I> >        & >(*this).get(); }
	template< Size I > constexpr                auto get() const  & noexcept -> typename Types<TElements const...>::template Get<I>  & { return static_cast< Leaf< I, typename Types<TElements...>::template Get<I> > const  & >(*this).get(); }
	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> typename Types<TElements      ...>::template Get<I> && { return static_cast< Leaf< I, typename Types<TElements...>::template Get<I> >       && >(*this).get(); }
	template< Size I > constexpr                auto get() const && noexcept -> typename Types<TElements const...>::template Get<I> && { return static_cast< Leaf< I, typename Types<TElements...>::template Get<I> > const && >(*this).get(); }

	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> T        & { return static_cast< FindLeaf< T, TElements... >        & >(*this).get(); }
	template< typename T > constexpr                auto get() const  & noexcept -> T const  & { return static_cast< FindLeaf< T, TElements... > const  & >(*this).get(); }
	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> T       && { return static_cast< FindLeaf< T, TElements... >       && >(*this).get(); }
	template< typename T > constexpr                auto get() const && noexcept -> T const && { return static_cast< FindLeaf< T, TElements... > const && >(*this).get(); }

}; // class Implement< IndexSequence<indices...>, TElements... >

} // namespace Tuple
} // namespace Container
} // namespace Detail
} // namespace BR
