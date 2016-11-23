/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 布尔常量封装类否定
 * @tparam TB
 * @see boolean_not
 */
template< typename TB >
using BooleanNot = BooleanRewrapNegative<TB>;

/**
 * @brief alias of BooleanNot
 * @tparam TB
 * @see negation
 */
template< typename TB >
using Negation = BooleanNot<TB>;

#if defined(BR_AFTER_CXX11)

/**
 * @brief boolean_not
 * @tparam TB
 * @see BooleanNot
 */
template< typename TB >
constexpr auto boolean_not = boolean_constant< BooleanNot<TB> >;

/**
 * @brief negation
 * @tparam TB
 * @see Negation
 */
template< typename TB >
constexpr auto negation = boolean_constant< Negation<TB> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits

} // namespace BR
