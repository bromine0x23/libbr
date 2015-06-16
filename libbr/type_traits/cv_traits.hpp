#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/is_const.hpp>
#include <libbr/type_operate/is_volatile.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {
namespace TypeTraits {

template< typename T >
struct CVTraits {
	constexpr static auto is_const    = TypeOperate::IsConst< T >::value;
	constexpr static auto is_volatile = TypeOperate::IsVolatile< T >::value;
	using Type   = TypeOperate::RemoveConstVolatile< T >;
	using TypeC  = TypeOperate::AddConst< Type >;
	using TypeV  = TypeOperate::AddVolatile< Type >;
	using TypeCV = TypeOperate::AddConstVolatile< Type >;
};

} // namespace TypeTraits
} // namespace BR
