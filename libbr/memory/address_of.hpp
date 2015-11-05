#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/type_operate/types.hpp>

namespace BR {

template< typename T >
constexpr auto address_of(T & t) noexcept -> T * {
#if defined(BR_CLANG) && defined(__has_builtin) && defined(__builtin_addressof)
	return __builtin_addressof(t);
#else
	return reinterpret_cast< T * >(&const_cast< char & >(reinterpret_cast< char const volatile & >(t)));
#endif
}

template< typename T >
struct AddressOf : public UnaryFunctor< T & > {
	using Result = T *;
	auto operator()(T & x) const -> Result {
		return address_of(x);
	}
};

} // namespace BR

