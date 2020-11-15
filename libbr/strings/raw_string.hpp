/**
 * @file
 * @brief 码元序列
 * @author Bromine0x23
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/strings/_/raw_string_basic.hpp>

namespace BR {

inline namespace Strings {

/**
 * @brief 码元序列.
 * @tparam TCodeUnit 码元类型.
 * @tparam TAllocator 分配器类型.
 */
template<typename TCodeUnit, typename TAllocator = Allocator<TCodeUnit> >
class RawString;

} // namespace Strings



inline namespace Strings {

template<typename TCodeUnit, typename TAllocator>
class RawString {
private:
	using Self = RawString;

public:
	/**
	 * @brief 分配器类类型
	 * @see BR::Allocator
	 */
	using Allocator = TAllocator;

	/**
	 * @brief 码元类型
	 */
	using CodeUnit = TCodeUnit;

public:
	RawString() noexcept(false) {
	}
};

} // namespace Strings


} // namespace BR