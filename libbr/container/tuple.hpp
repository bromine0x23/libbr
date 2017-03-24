/**
 * @file
 * @brief Tuple
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/tuple_forward.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/container/detail/tuple_implement.hpp>
#include <libbr/container/detail/tuple_traits.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/has_default_constructor.hpp>
#include <libbr/type_traits/has_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/make_integral_sequence.hpp>
#include <libbr/type_traits/map_qualifier.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>
#include <libbr/type_traits/remove_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/types.hpp>

namespace BR {

inline namespace Container {

template < typename... TElements >
class Tuple;

template< typename... TElements >
struct TupleSize< Tuple<TElements...> > : public IntegralConstant< Size, sizeof...(TElements) > {};

template< Size I, typename... TElements >
struct TypeTupleElement< I, Tuple<TElements...> > : public TypeWrapper< typename Types<TElements...>::template Get<I> > {};

template< typename ... TElement >
void swap(Tuple< TElement ... > & lhs, Tuple< TElement ... > & rhs) noexcept(noexcept(lhs.swap(rhs))) {
	lhs.swap(rhs);
}

template< Size I, typename ... Tn > constexpr auto get(Tuple<Tn...>        & t) noexcept -> TupleElement< I, Tuple<Tn...> >        & { return t.template get<I>(); }
template< Size I, typename ... Tn > constexpr auto get(Tuple<Tn...> const  & t) noexcept -> TupleElement< I, Tuple<Tn...> > const  & { return t.template get<I>(); }
template< Size I, typename ... Tn > constexpr auto get(Tuple<Tn...>       && t) noexcept -> TupleElement< I, Tuple<Tn...> >       && { return move(t.template get<I>()); }
template< Size I, typename ... Tn > constexpr auto get(Tuple<Tn...> const && t) noexcept -> TupleElement< I, Tuple<Tn...> > const && { return move(t.template get<I>()); }

template< typename T, typename ... Tn > constexpr auto get(Tuple<Tn...>        & t) noexcept -> T        & { return t.template get<T>(); }
template< typename T, typename ... Tn > constexpr auto get(Tuple<Tn...> const  & t) noexcept -> T const  & { return t.template get<T>(); }
template< typename T, typename ... Tn > constexpr auto get(Tuple<Tn...>       && t) noexcept -> T       && { return move(t.template get<T>()); }
template< typename T, typename ... Tn > constexpr auto get(Tuple<Tn...> const && t) noexcept -> T const && { return move(t.template get<T>()); }

template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 >        & P) noexcept -> TupleElement< I, Pair< T0, T1 > > &;
template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 > const  & P) noexcept -> TupleElement< I, Pair< T0, T1 > > const &;
template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 >       && P) noexcept -> TupleElement< I, Pair< T0, T1 > > &&;
template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 > const && P) noexcept -> TupleElement< I, Pair< T0, T1 > > const &&;

template< typename... T0, typename... T1 > constexpr auto operator==(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean;
template< typename... T0, typename... T1 > constexpr auto operator!=(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean;
template< typename... T0, typename... T1 > constexpr auto operator< (Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean;
template< typename... T0, typename... T1 > constexpr auto operator> (Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean;
template< typename... T0, typename... T1 > constexpr auto operator<=(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean;
template< typename... T0, typename... T1 > constexpr auto operator>=(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean;

/**
 * @brief Creates a tuple of lvalue references to its arguments or instances of std::ignore.
 * @tparam TArguments Type of \p arguments.
 * @param arguments Zero or more lvalue arguments to construct the Tuple from.
 * @return A Tuple object containing lvalue references.
 */
template< typename... TArguments >
BR_CONSTEXPR_AFTER_CXX11 inline auto tie(TArguments &... arguments) noexcept -> Tuple<TArguments &...> {
	return Tuple<TArguments &...>(arguments...);
}

/**
 * @brief Creates a tuple of rvalue references.
 * @tparam TArguments Type of \p arguments.
 * @param arguments Zero or more arguments to construct the Tuple from.
 * @return A Tuple object created as if by Tuple<TArguments &&...>(std::forward<Types>(args)...)
 */
template< typename... TArguments >
BR_CONSTEXPR_AFTER_CXX11 inline auto forward_as_tuple(TArguments &&... arguments) noexcept -> Tuple<TArguments &&...> {
	return Tuple<TArguments &&...>(forward<TArguments>(arguments)...);
}

/**
 * @brief Creates a tuple object, deducing the target type from the types of arguments.
 * @tparam TArguments Type of \p arguments.
 * @param arguments Zero or more arguments to construct the Tuple from.
 * @return A Tuple object containing the given values, created as if by Tuple<VTypes...>(forward<TArguments>(arguments)...).
 */
template< typename... TArguments >
BR_CONSTEXPR_AFTER_CXX11 inline auto make_tuple(TArguments &&... arguments) -> Tuple< Detail::Container::Tuple::MakeTupleReturn<TArguments>... > {
	return Tuple< Detail::Container::Tuple::MakeTupleReturn<TArguments>... >(forward<TArguments>(arguments) ...);
}

} // namespace Container

inline namespace TypeTraits {

template< typename T, typename TAllocator >
struct IsUseAllocator;

template< typename... T, typename TAllocator >
struct IsUseAllocator< Tuple<T...>, TAllocator > : public BooleanTrue {};

template< typename T, typename TAllocator >
struct NotUseAllocator;

template< typename... T, typename TAllocator >
struct NotUseAllocator< Tuple<T...>, TAllocator > : public BooleanFalse {};

} // namespace TypeTraits




inline namespace Container {

template < typename... TElements >
class Tuple {
private:
	using Implement = Detail::Container::Tuple::Implement< MakeIndexSequence< 0, sizeof...(TElements) >, TElements ... >;

	template< typename... TValues >
	struct NotExpandableToThis : BooleanTrue {};

	template< typename TValue >
	struct NotExpandableToThis<TValue> : NotSame< RemoveConstVolatile< RemoveReference<TValue> >, Tuple > {};

	template< Boolean enable >
	using EnableDefaultConstructor = BooleanAnd< BooleanConstant<enable>, HasDefaultConstructor<TElements>... >;

	template< Boolean enable, typename Dummy = void >
	struct EnableValueConstructor {
		template< typename...TValues >
		using Explicit = BooleanFalse;
		template< typename...TValues >
		using Implicit = BooleanFalse;
	};

	template< typename Dummy >
	struct EnableValueConstructor< true, Dummy > {
		template< typename...TValues >
		using Enable = Detail::Container::Tuple::IsAllConstructible< Types<TElements...>, Types<TValues...> >;
		template< typename...TValues >
		using Explicit = BooleanAnd< Enable<TValues...>, Detail::Container::Tuple::NotAllConvertible< Types<TElements...>, Types<TValues...> > >;
		template< typename...TValues >
		using Implicit = BooleanAnd< Enable<TValues...>, Detail::Container::Tuple::IsAllConvertible< Types<TElements...>, Types<TValues...> > >;
	};

	template< Boolean enable, typename Dummy = void >
	struct EnableTupleLikeConstructor {
		template< typename...TValues >
		using Explicit = BooleanFalse;
		template< typename...TValues >
		using Implicit = BooleanFalse;
	};

	template< typename Dummy >
	struct EnableTupleLikeConstructor< true, Dummy > {
		template< typename...TValues >
		using Enable = Detail::Container::Tuple::IsAllConstructible< Types<TElements...>, Types<TValues...> >;
		template< typename...TValues >
		using Explicit = BooleanAnd< Enable<TValues...>, Detail::Container::Tuple::NotAllConvertible< Types<TElements...>, Types<TValues...> > >;
		template< typename...TValues >
		using Implicit = BooleanAnd< Enable<TValues...>, Detail::Container::Tuple::IsAllConvertible< Types<TElements...>, Types<TValues...> > >;
	};

	template< Boolean enable, typename Dummy = void >
	struct EnableAssignment {
		template< typename... TValues >
		using Enable = BooleanFalse;
	};

	template< typename Dummy >
	struct EnableAssignment< true, Dummy > {
		template< typename... TValues >
		using Enable = Detail::Container::Tuple::IsAllAssignable< Types<TElements &...>, Types<TValues...> >;
	};

public:
	/**
	 * @brief Default constructor.
	 *
	 * Value-initializes all elements.
	 */
	template<
		Boolean dummy = true,
		typename = EnableIf< EnableDefaultConstructor<dummy> >
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<TElements>... >{}
	) {
	}

	/**
	 * @brief Direct constructor.
	 *
	 * Initializes each element of the tuple with the corresponding parameter.
	 * @param elements Values used to initialize each element of the tuple.
	 */
	template<
		Boolean dummy = true,
		typename = EnableIf< typename EnableValueConstructor<dummy>::template Explicit<TElements const &...> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		TElements const &... elements
	) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<TElements>... >{}
	) : m_impl(
		Implement::direct_tag,
		elements...
	) {
	}

	/**
	 * @brief Direct constructor.
	 *
	 * Initializes each element of the tuple with the corresponding parameter.
	 * @param elements Values used to initialize each element of the tuple.
	 */
	template<
		Boolean dummy = true,
		EnableIf< typename EnableValueConstructor<dummy>::template Implicit<TElements const &...>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		TElements const &... elements
	) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<TElements>... >{}
	) : m_impl(
		Implement::direct_tag,
		elements...
	) {
	}

	/**
	 * @brief Converting constructor(explicit).
	 *
	 * Initializes each element of the tuple with the corresponding value in forward<TValues>(values).
	 * @tparam TValues Type of \p values
	 * @param values Values used to initialize each element of the tuple.
	 */
	template<
		typename ... TValues,
		typename = EnableIf< typename EnableValueConstructor<sizeof...(TValues) == sizeof...(TElements)>::template Explicit<TValues &&...> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		TValues &&... values
	) noexcept(
		IsNothrowConstructible< Implement, TValues...>{}
	) : m_impl(
		Implement::direct_tag,
		forward<TValues>(values)...
	) {
	}

	/**
	 * @brief Converting constructor(implicit).
	 *
	 * Initializes each element of the tuple with the corresponding value in forward<TValues>(values).
	 * @tparam TValues Type of \p values
	 * @param values Values used to initialize each element of the tuple.
	 */
	template<
		typename ... TValues,
		EnableIf< typename EnableValueConstructor<sizeof...(TValues) == sizeof...(TElements)>::template Implicit<TValues &&...>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		TValues &&... values
	) noexcept(
		IsNothrowConstructible< Implement, TValues...>{}
	) : m_impl(
		Implement::direct_tag,
		forward<TValues>(values)...
	) {
	}

	/**
	 * @brief Converting copy-constructor(explicit).
	 * @tparam TValues Type of elements that \p other hold.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename... TValues,
		typename = EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues) && NotExpandableToThis<TValues...>{}>::template Explicit<TValues const &...> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Tuple<TValues...> const & other
	) : m_impl(
		other
	) {
	}

	/**
	 * @brief Converting copy-constructor(implicit).
	 * @tparam TValues Type of elements that \p other hold.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename... TValues,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues) && NotExpandableToThis<TValues...>{}>::template Implicit<TValues const &...>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Tuple<TValues...> const & other
	) : m_impl(
		other
	) {
	}

	/**
	 * @brief Converting move-constructor(explicit).
	 * @tparam TValues Type of elements that \p other hold.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename... TValues,
		typename = EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues) && NotExpandableToThis<TValues...>{}>::template Explicit<TValues &&...> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Tuple<TValues...> && other
	) : m_impl(
		move(other)
	) {
	}

	/**
	 * @brief Converting move-constructor(implicit).
	 * @tparam TValues Type of elements that \p other hold.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename... TValues,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues) && NotExpandableToThis<TValues...>{}>::template Implicit<TValues &&...>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Tuple<TValues...> && other
	) : m_impl(
		move(other)
	) {
	}

	/**
	 * @brief Pair copy constructor(explicit).
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TFirst, typename TSecond,
		typename = EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Explicit<TFirst const &, TSecond const &> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Pair<TFirst, TSecond> const & pair
	) : m_impl(
		pair.first,
		pair.second
	) {
	}

	/**
	 * @brief Pair copy constructor(implicit).
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TFirst, typename TSecond,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Implicit<TFirst const &, TSecond const &>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Pair<TFirst, TSecond> const & pair
	) : m_impl(
		pair.first,
		pair.second
	) {
	}

	/**
	 * @brief Pair move constructor(explicit).
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TFirst, typename TSecond,
		typename = EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Explicit<TFirst &&, TSecond &&> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Pair<TFirst, TSecond> && pair
	) : m_impl(
		forward<TFirst>(pair.first),
		forward<TSecond>(pair.second)
	) {
	}

	/**
	 * @brief Pair move constructor(implicit).
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TFirst, typename TSecond,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Implicit<TFirst &&, TSecond &&>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		Pair<TFirst, TSecond> && pair
	) : m_impl(
		forward<TFirst>(pair.first),
		forward<TSecond>(pair.second)
	)  {
	}

	/**
	 * @brief Default constructor that uses allocator.
	 * @tparam TAllocator Type of \p allocator.
	 * @param allocator Allocator to use in uses-allocator construction.
	 */
	template<
		typename TAllocator,
		Boolean dummy = true, typename = EnableIf< EnableDefaultConstructor<dummy> >
	>
	Tuple(
		AllocatorArgumentTag, TAllocator const & allocator
	) : m_impl(
		allocator_argument_tag, allocator
	) {
	}

	/**
	 * @brief Copy constructor that uses allocator.
	 * @tparam TAllocator Type of \p allocator.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param other A tuple of values used to initialize each element of the tuple.
	 */
	template< typename TAllocator >
	Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Tuple const & other
	) : m_impl(
		allocator_argument_tag, allocator,
		other
	) {
	}

	/**
	 * @brief Move constructor that uses allocator.
	 * @tparam TAllocator Type of \p allocator.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param other A tuple of values used to initialize each element of the tuple.
	 */
	template< typename TAllocator >
	Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Tuple && other
	) : m_impl(
		allocator_argument_tag, allocator,
		move(other)
	) {
	}

	/**
	 * @brief Direct constructor that uses allocator(explicit).
	 * @tparam TAllocator Type of \p allocator
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param element Values used to initialize each element of the tuple.
	 */
	template<
		typename TAllocator,
		Boolean dummy = true,
		EnableIf< typename EnableValueConstructor<dummy>::template Explicit<TElements const &...>, Boolean > = true
	>
	explicit Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		TElements const &... element
	) : m_impl(
		allocator_argument_tag, allocator,
		Implement::direct_tag,
		element...
	) {
	}

	/**
	 * @brief Direct constructor that uses allocator(implicit).
	 * @tparam TAllocator Type of \p allocator
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param element Values used to initialize each element of the tuple.
	 */
	template<
		typename TAllocator,
		Boolean dummy = true,
		EnableIf< typename EnableValueConstructor<dummy>::template Implicit<TElements const &...>, Boolean > = true
	>
	Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		TElements const &... element
	) : m_impl(
		allocator_argument_tag, allocator,
		Implement::direct_tag,
		element...
	) {
	}

	/**
	 * @brief Converting constructor that uses allocator(explicit).
	 *
	 * Initializes each element of the tuple with the corresponding value in forward<TValues>(values).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TValues Type of \p values
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param values Values used to initialize each element of the tuple.
	 */
	template<
		typename TAllocator,
		typename ... TValues,
		EnableIf< typename EnableValueConstructor<sizeof...(TValues) == sizeof...(TElements)>::template Explicit<TValues &&...>, Boolean > = true
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		TValues &&... values
	) : m_impl(
		allocator_argument_tag, allocator,
		Implement::direct_tag,
		forward<TValues>(values)...
	) {
	}

	/**
	 * @brief Converting constructor that uses allocator(implicit).
	 *
	 * Initializes each element of the tuple with the corresponding value in forward<TValues>(values).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TValues Type of \p values
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param values Values used to initialize each element of the tuple.
	 */
	template<
		typename TAllocator,
		typename ... TValues,
		EnableIf< typename EnableValueConstructor<sizeof...(TValues) == sizeof...(TElements)>::template Implicit<TValues &&...>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		TValues &&... values
	) : m_impl(
		allocator_argument_tag, allocator,
		Implement::direct_tag,
		forward<TValues>(values)...
	) {
	}

	/**
	 * @brief Converting copy-constructor that uses allocator(explicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TValues Type of elements that \p other hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename TAllocator,
		typename... TValues,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues)>::template Explicit<TValues const &...>, Boolean > = true
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Tuple<TValues...> const & other
	) : m_impl(
		allocator_argument_tag, allocator,
		other
	) {
	}

	/**
	 * @brief Converting copy-constructor that uses allocator(implicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TValues Type of elements that \p other hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename TAllocator,
		typename... TValues,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues)>::template Implicit<TValues const &...>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Tuple<TValues...> const & other
	) : m_impl(
		allocator_argument_tag, allocator,
		other
	) {
	}

	/**
	 * @brief Converting move-constructor that uses allocator(explicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TValues Type of elements that \p other hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename TAllocator,
		typename... TValues,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues)>::template Explicit<TValues &&...>, Boolean > = true
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Tuple<TValues...> && other
	) : m_impl(
		allocator_argument_tag, allocator,
		move(other)
	) {
	}

	/**
	 * @brief Converting move-constructor that uses allocator(implicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TValues Type of elements that \p other hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param other A tuple of values used to initialize each element.
	 */
	template<
		typename TAllocator,
		typename... TValues,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == sizeof...(TValues)>::template Implicit<TValues &&...>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Tuple<TValues...> && other
	) : m_impl(
		allocator_argument_tag, allocator,
		move(other)
	) {
	}

	/**
	 * @brief Pair copy constructor that uses allocator(explicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TAllocator,
		typename TFirst, typename TSecond,
		typename = EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Explicit<TFirst const &, TSecond const &> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Pair<TFirst, TSecond> const & pair
	) : m_impl(
		allocator_argument_tag, allocator,
		pair
	) {
	}

	/**
	 * @brief Pair copy constructor that uses allocator(implicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TAllocator,
		typename TFirst, typename TSecond,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Implicit<TFirst const &, TSecond const &>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Pair<TFirst, TSecond> const & pair
	) : m_impl(
		allocator_argument_tag, allocator,
		pair
	) {
	}

	/**
	 * @brief Pair move constructor that uses allocator(explicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TAllocator,
		typename TFirst, typename TSecond,
		typename = EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Explicit<TFirst &&, TSecond &&> >
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Pair<TFirst, TSecond> && pair
	) : m_impl(
		allocator_argument_tag, allocator,
		move(pair)
	) {
	}

	/**
	 * @brief Pair move constructor that uses allocator(implicit).
	 * @tparam TAllocator Type of \p allocator
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param allocator Allocator to use in uses-allocator construction.
	 * @param pair Pair of values used to initialize both elements of this 2-tuple.
	 */
	template<
		typename TAllocator,
		typename TFirst, typename TSecond,
		EnableIf< typename EnableTupleLikeConstructor<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Implicit<TFirst &&, TSecond &&>, Boolean > = true
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		AllocatorArgumentTag, TAllocator const & allocator,
		Pair<TFirst, TSecond> && pair
	) : m_impl(
		allocator_argument_tag, allocator,
		move(pair)
	) {
	}

	/**
	 * @brief For all i, assigns other.template get<i>() to this->template get<i>().
	 * @tparam TValues
	 * @param other
	 * @return *this
	 */
	template< typename... TValues >
	auto operator=(
		Tuple<TValues...> const & other
	) noexcept(
		IsNothrowAssignable< Implement &, Tuple<TValues...> const & >{}
	) -> EnableIf< typename EnableAssignment<sizeof...(TElements) == sizeof...(TValues)>::template Enable<TValues const &...>, Tuple & > {
		m_impl.operator=(other);
		return *this;
	}

	/**
	 * @brief For all i, assigns forward<TValue_i>(other.template get<i>()) to this->template get<i>().
	 * @tparam TValues
	 * @param other
	 * @return *this
	 */
	template< typename... TValues >
	auto operator=(
		Tuple<TValues...> && other
	) noexcept(
		IsNothrowAssignable< Implement &, Tuple<TValues...> && >{}
	) -> EnableIf< typename EnableAssignment<sizeof...(TElements) == sizeof...(TValues)>::template Enable<TValues &&...>, Tuple & > {
		m_impl.operator=(move(other));
		return *this;
	}

	/**
	 * @biref Assigns pair.first to the first element of *this and pair.second to the second element of *this.
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param pair Pair to replace the contents of this 2-tuple.
	 * @return *this
	 */
	template< typename TFirst, typename TSecond, typename = EnableIf< typename EnableAssignment<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Enable<TFirst const &, TSecond const &> > >
	auto operator=(Pair<TFirst, TSecond> const & pair) noexcept(IsNothrowAssignable< Implement &, Pair<TFirst, TSecond> const & >{}) -> Tuple & {
		m_impl.operator=(pair);
		return *this;
	}

	/**
	 * @biref Assigns forward<TFirst>(pair.first) to the first element of *this and forward<TSecond>(pair.second) to the second element of *this.
	 * @tparam TFirst,TSecond Type of elements that \p pair hold.
	 * @param pair Pair to replace the contents of this 2-tuple.
	 * @return *this
	 */
	template< typename TFirst, typename TSecond, typename = EnableIf< typename EnableAssignment<sizeof...(TElements) == Types<TFirst, TSecond>::size>::template Enable<TFirst &&, TSecond &&> > >
	auto operator=(Pair<TFirst, TSecond> && pair) noexcept(IsNothrowAssignable< Implement &, Pair<TFirst, TSecond> && >{}) -> Tuple & {
		m_impl.operator=(move(pair));
		return *this;
	}

	/**
	 * swap
	 */
	void swap(Tuple & other) noexcept(BooleanAnd< IsNothrowSwappable<TElements>... >{}) {
		m_impl.swap(other.m_impl);
	}

	/**
	 *  取第 \em I 个元素
	 */
	///@{
	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TupleElement< I, Tuple >        & { return m_impl.template get<I>(); }
	template< Size I > constexpr                auto get() const  & noexcept -> TupleElement< I, Tuple > const  & { return m_impl.template get<I>(); }
	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TupleElement< I, Tuple >       && { return move(m_impl.template get<I>()); }
	template< Size I > constexpr                auto get() const && noexcept -> TupleElement< I, Tuple > const && { return move(m_impl.template get<I>()); }
	///@}

	/**
	 *  取类型 \em T 对应的元素
	 */
	///@{
	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> T        & { return m_impl.template get<T>(); }
	template< typename T > constexpr                auto get() const  & noexcept -> T const  & { return m_impl.template get<T>(); }
	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> T       && { return move(m_impl.template get<T>()); }
	template< typename T > constexpr                auto get() const && noexcept -> T const && { return move(m_impl.template get<T>()); }
	///@}

private:
	Implement m_impl;

}; // class Tuple<TElements...>

template <>
class Tuple<> {
public:
	constexpr Tuple() noexcept = default;

	template< typename TAllocator >
	constexpr Tuple(AllocatorArgumentTag, TAllocator const &) noexcept {
	}

	template< typename TAllocator >
	constexpr Tuple(AllocatorArgumentTag, TAllocator const &, Tuple const &) noexcept {
	}

	void swap(Tuple & tuple) noexcept {
	}
}; // class Tuple<>

} // namespace Container

inline namespace Container {

} // namespace Container

namespace Detail {
namespace Container {
namespace Tuple {

struct IgnoreTag {
	template< typename T >
	auto operator=(T &&) const -> IgnoreTag const & {
		return *this;
	}
};

} // namespace Tuple
} // namespace Container
} // namespace Detail

inline namespace Container {

/**
 * @brief Placeholder to skip an element when unpacking a tuple using tie.
 */
constexpr auto ignore_tag = Detail::Container::Tuple::IgnoreTag{};

} // namespace Container

namespace Detail {
namespace Container {
namespace Tuple {

template< Size I >
struct Compare {
	template< typename T0, typename T1 >
	static constexpr auto equal(T0 const & t0, T1 const & t1) -> bool {
		return Compare<I-1>::equal(t0, t1) && get<I-1>(t0) == get<I-1>(t1);
	}

	template< typename T0, typename T1 >
	static constexpr auto less(T0 const & t0, T1 const & t1) -> bool {
		return Compare< I-1 >::less(t0, t1) || (!Compare<I-1>::less(t1, t0) && get<I-1>(t0) < get<I-1>(t1));
	}
};

template<>
struct Compare<0> {
	template< typename T0, typename T1 >
	static constexpr auto equal(T0 const &, T1 const &) -> bool {
		return true;
	}

	template< typename T0, typename T1 >
	static constexpr auto less(T0 const &, T1 const &) -> bool {
		return false;
	}
};

} // namespace Tuple
} // namespace Container
} // namespace Detail

inline namespace Container {

template< typename... T0, typename... T1 >
constexpr auto operator==(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean {
	return Detail::Container::Tuple::Compare< sizeof...(T0) >::equal(t0, t1);
}

template< typename... T0, typename... T1 >
constexpr auto operator<(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean {
	return Detail::Container::Tuple::Compare< sizeof...(T0) >::less(t0, t1);
}

template< typename... T0, typename... T1 >
constexpr auto operator!=(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean {
	return !(t0 == t1);
}

template< typename... T0, typename... T1 >
constexpr auto operator>(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean {
	return t1 < t0;
}

template< typename... T0, typename... T1 >
constexpr auto operator<=(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean {
	return !(t1 < t0);
}

template< typename... T0, typename... T1 >
constexpr auto operator>=(Tuple<T0...> const & t0, Tuple<T1...> const & t1) -> Boolean {
	return !(t0 < t1);
}

} // namespace Container

namespace Detail {
namespace Container {
namespace Tuple {

template< typename T0, typename T1 >
struct TypeCatTypes;

template< typename T0, typename T1 >
using CatTypes = TypeUnwrap< TypeCatTypes<T0, T1> >;

template< typename... TTypes0, typename... TTypes1 >
struct TypeCatTypes< BR::Tuple<TTypes0...>, Types<TTypes1...> > :
	public TypeWrapper< BR::Tuple< TTypes0..., TTypes1... > > {};

template< typename TResult, bool is_tuple_like, typename... TTuples >
struct TypeCatResultBasic {};

template< typename... TTypes, typename TTuple >
struct TypeCatResultBasic< BR::Tuple<TTypes...>, true, TTuple > :
	public TypeCatTypes< BR::Tuple<TTypes...>, MakeTupleTypes< RemoveReference<TTuple> > > {};

template< typename... TTypes, typename TTuple0, typename TTuple1, typename... TTuples >
struct TypeCatResultBasic< BR::Tuple<TTypes...>, true, TTuple0, TTuple1, TTuples... > :
	public TypeCatResultBasic< CatTypes< BR::Tuple<TTypes...>, MakeTupleTypes< RemoveReference<TTuple0> > >, IsTupleLike< RemoveReference<TTuple1> >{}, TTuple1, TTuples... > {};

template< typename... TTuples >
struct TypeCatResult;

template<>
struct TypeCatResult<> : public TypeWrapper< BR::Tuple<> > {};

template< typename TTuple0, typename... TTuples >
struct TypeCatResult< TTuple0, TTuples... > : public TypeCatResultBasic< BR::Tuple<>, IsTupleLike< RemoveReference<TTuple0> >{}, TTuple0, TTuples... > {
};

template< typename ... TTuples >
using CatResult = TypeUnwrap< TypeCatResult<TTuples...> >;

template< typename TResult, typename TIndices, typename TTuple0, typename... TTuples >
struct TypeCatResultReferenceBasic;

template< typename... TTypes, Size... indices, typename TTuple >
struct TypeCatResultReferenceBasic< BR::Tuple<TTypes...>, IndexSequence<indices...>, TTuple > :
	public TypeWrapper< BR::Tuple< TTypes..., MapQualifier< TTuple, TupleElement< indices, RemoveReference<TTuple> > > &&... > > {};

template< typename... TTypes, Size... indices, typename TTuple0, typename TTuple1, typename... TTuples >
struct TypeCatResultReferenceBasic< BR::Tuple<TTypes...>, IndexSequence<indices...>, TTuple0, TTuple1, TTuples... > :
	public TypeCatResultReferenceBasic<
		BR::Tuple< TTypes..., MapQualifier< TTuple0, TupleElement< indices, RemoveReference<TTuple0> > > &&... >,
		MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple1> >{} >,
		TTuple1,
		TTuples...
	> {};

template< typename TTuple0, typename... TTuples >
struct TypeCatResultReference :
	public TypeCatResultReferenceBasic<
		BR::Tuple<>,
		MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple0> >{} >,
		TTuple0,
		TTuples...
	> {};

template< typename... TTuples >
using CatResultReference = TypeUnwrap< TypeCatResultReference<TTuples...> >;

template< typename TResult, typename TIHead, typename TITail >
struct Cat;

template< typename... TTypes, Size... head_indices, Size... tail_indices >
struct Cat< BR::Tuple<TTypes...>, IndexSequence<head_indices...>, IndexSequence<tail_indices...> > {
	template< typename TTuple >
	BR_CONSTEXPR_AFTER_CXX11 static auto cat(BR::Tuple<TTypes...> head, TTuple && tail) -> CatResultReference< BR::Tuple<TTypes...> &&, TTuple && > {
		return forward_as_tuple(forward<TTypes>(get<head_indices>(head))..., get<tail_indices>(forward<TTuple>(tail))...);
	}

	template< typename TTuple0, typename TTuple1, typename... TTuples >
	BR_CONSTEXPR_AFTER_CXX11 static auto cat(BR::Tuple<TTypes...> head, TTuple0 && tail0, TTuple1 && tail1, TTuples &&... tails) -> CatResultReference< BR::Tuple<TTypes...> &&, TTuple0 &&, TTuple1 &&, TTuples &&... > {
		using NoRefTuple0 = RemoveReference<TTuple0>;
		return Cat<
			BR::Tuple<TTypes..., MapQualifier< TTuple0, TupleElement< tail_indices, NoRefTuple0 > > &&... >,
			MakeIndexSequence< 0, sizeof...(TTypes) + TupleSize< NoRefTuple0 >{} >,
			MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple1> >{} >
		>::cat(
			forward_as_tuple(forward<TTypes>(get<head_indices>(head))..., get<tail_indices>(forward<TTuple0>(tail0))...),
			forward<TTuple1>(tail1),
			forward<TTuples>(tails)...
		);
	}
};

} // namespace Tuple
} // namespace Container
} // namespace Detail

inline namespace Container {

BR_CONSTEXPR_AFTER_CXX11 inline auto tuple_cat() -> Tuple<> {
	return Tuple<>();
}

template< typename TTuple0, typename... TTuples >
BR_CONSTEXPR_AFTER_CXX11 inline auto tuple_cat(TTuple0 && tuple0, TTuples &&... tuples) -> Detail::Container::Tuple::CatResult< TTuple0, TTuples... > {
	return Detail::Container::Tuple::Cat<
		Tuple<>, IndexSequence<>, MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple0> >{} >
	>::cat(
		Tuple<>(), forward<TTuple0>(tuple0), forward<TTuples>(tuples)...
	);
}

} // namespace Container

} // namespace BR