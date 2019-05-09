/**
 * @file
 * @brief transfer
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_reference.hpp>
#include <libbr/utility/conditional.hpp>
#include <libbr/utility/conjunction.hpp>

namespace BR {

/**
 * @brief 强制转换为右值引用
 * @author Bromine0x23
 */
template< typename T >
constexpr auto transfer(T && t) noexcept -> RemoveReference<T> && {
	return static_cast< RemoveReference<T> && >(t);
}

} // namespace BR
