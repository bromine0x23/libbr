#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/add_const.hpp>
#include <libbr/type_traits/add_volatile.hpp>
#include <libbr/type_traits/add_const_volatile.hpp>
#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_volatile.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief CVTraits
 * @tparam T
 */
template< typename T >
struct CVTraits {
	constexpr static auto is_const    = IsConst   < T >::value;
	constexpr static auto is_volatile = IsVolatile< T >::value;
	using Type   = RemoveConstVolatile< T >;
	using TypeC  = AddConst        < Type >;
	using TypeV  = AddVolatile     < Type >;
	using TypeCV = AddConstVolatile< Type >;
};

} // namespace TypeTraits

} // namespace BR
