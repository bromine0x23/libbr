/**
 * @file
 * @brief address_of
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

#if defined(BR_CLANG)
#  if defined(__has_builtin) && __has_builtin(__builtin_addressof)
#    define BR_MEMORY_HAS_BUILTIN_ADDRESS_OF
#  endif
#elif defined(BR_GCC)
#  if BR_GCC_VER >= 700
#    define BR_MEMORY_HAS_BUILTIN_ADDRESS_OF
#  endif
#elif defined(BR_MSVC)
#  if BR_MSVC_VER >= 1910
#    define BR_MEMORY_HAS_BUILTIN_ADDRESS_OF
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
#if defined(BR_MEMORY_HAS_BUILTIN_ADDRESS_OF)
constexpr
#endif
inline auto address_of(T & t) noexcept -> T * {
#if defined(BR_MEMORY_HAS_BUILTIN_ADDRESS_OF)
	return __builtin_addressof(t);
#else
	return reinterpret_cast<T *>(const_cast<char &>(reinterpret_cast<char const volatile &>(t)));
#endif
}

template <class T>
auto address_of(T const &&) -> T * = delete;

} // namespace Memory
} // namespace BR

#undef BR_MEMORY_HAS_BUILTIN_ADDRESS_OF
