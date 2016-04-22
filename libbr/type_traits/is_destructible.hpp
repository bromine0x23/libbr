/**
 * @file
 * @brief 检查类型是否可被析构
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_destructor.hpp>

namespace BR {

/**
 * @see HasDestructor
 *
 * 如果 \em T 可被析构，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
using IsDestructible = HasDestructor<T>;

/**
 * @see NoDestructor
 */
template< typename T >
using NotDestructible = NoDestructor<T>;

#if defined(BR_CXX14)

/**
 * @see has_destructor
 */
template< typename T >
constexpr auto is_destructible = has_destructor<T>;

/**
 * @see no_destructor
 */
template< typename T >
constexpr auto not_destructible = no_destructor<T>;

#endif // defined(BR_CXX14)

} // namespace BR