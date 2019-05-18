/**
 * @file
 * @brief address_of
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

#if defined(BR_CLANG)
#  if defined(__has_builtin) && __has_builtin(__builtin_addressof)
#    define _HAS_BUILTIN
#  endif
#elif defined(BR_GCC)
#  if BR_GCC_VER >= 700
#    define _HAS_BUILTIN
#  endif
#elif defined(BR_MSVC)
#  if BR_MSVC_VER >= 1910
#    define _HAS_BUILTIN
#  endif
#endif

namespace BR {
inline namespace Memory {

/**
 * @brief address_of
 * @tparam T
 * @param t
 * @return
 */
template< typename T >
#if defined(_HAS_BUILTIN)
constexpr
#endif
inline auto address_of(T & t) noexcept -> T * {
#if defined(_HAS_BUILTIN)
	return __builtin_addressof(t);
#else
	return reinterpret_cast<T *>(const_cast<char &>(reinterpret_cast<char const volatile &>(t)));
#endif
}

template <class T>
auto address_of(T const &&) -> T * = delete;

} // namespace Memory
} // namespace BR

