/**
 * @file
 * @brief address_of
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Memory {

/**
 * @brief address_of
 * @tparam T
 * @param t
 * @return
 */
template< typename T >
constexpr auto address_of(T & t) noexcept -> T * {
	return reinterpret_cast<T *>(&const_cast<char &>(reinterpret_cast<char const volatile &>(t)));
}

template <class T>
auto address_of(T const &&) -> T * = delete;

} // namespace Memory
} // namespace BR

