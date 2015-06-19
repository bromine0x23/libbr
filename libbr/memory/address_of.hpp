#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
inline static T * address_of(T & t) noexcept {
	return reinterpret_cast< T * >(&const_cast< char & >(reinterpret_cast< char const volatile & >(t)));
}

template< typename T >
struct AddressOf {
	using Result = T *;
	using Argument = T &;
	using Arguments = Types< Argument >;
	Result operator()(Argument x) const {
		return address_of(x);
	}
};

} // namespace BR

