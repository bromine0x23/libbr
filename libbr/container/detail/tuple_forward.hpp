/**
 * @file
 * @brief Forward declaration of Tuple
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace Container {

template< typename T, Size N >
struct FixedArray;

template< typename TFirst, typename TSecond >
class Pair;

/**
 * @brief A fixed-size collection of heterogeneous values.
 * @tparam TElements The types of the elements that the tuple stores. Empty list is supported.
 */
template< typename ... TElements >
class Tuple;

/**
 * @brief Obtains the size of tuple at compile time.
 * @tparam T A tuple-like type to check.
 */
template< typename T >
struct TupleSize;

#if defined(BR_CXX14)

/**
 * @brief Variable template of TupleSize
 * @tparam T A tuple-like type to check.
 * @see TupleSize
 */
template< typename T >
constexpr auto tuple_size = integral_constant< TupleSize<T> >;

#endif // defined(BR_CXX14)

template< typename T >
struct TupleSize< T const > : public TupleSize<T> {};

template< typename T >
struct TupleSize< T volatile > : public TupleSize<T> {};

template< typename T >
struct TupleSize< T const volatile > : public TupleSize<T> {};

/**
 * @brief Provides compile-time indexed access to the types of the elements of the tuple.
 * @tparam I Index.
 * @tparam T A tuple-like type to check.
 */
template< Size I, typename T >
struct TypeTupleElement;

/**
 * @brief Shortcut of TypeTupleElement.
 * @tparam I Index.
 * @tparam T A tuple-like type to check.
 * @see TypeTupleElement
 */
template< Size I, typename T >
using TupleElement = TypeUnwrap< TypeTupleElement< I, T > >;

template< Size I, typename T >
struct TypeTupleElement< I, T const > : public TypeWrapper< TupleElement< I, T > const > {};

template< Size I, typename T >
struct TypeTupleElement< I, T volatile > : public TypeWrapper< TupleElement< I, T > volatile > {};

template< Size I, typename T >
struct TypeTupleElement< I, T const volatile > : public TypeWrapper< TupleElement< I, T > const volatile > {};

} // namespace Container

inline namespace TypeTraits {

using Container::TupleSize;

#if defined(BR_CXX14)

using Container::tuple_size;

#endif // defined(BR_CXX14)

using Container::TypeTupleElement;

using Container::TupleElement;

} // namespace TypeTraits

} // namespace BR