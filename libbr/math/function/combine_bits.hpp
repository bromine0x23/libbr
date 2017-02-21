/**
 * @file
 * @brief combine_bits
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * combine_bits
 * @param h
 * @param l
 * @return combined bits
 */
//@{
constexpr auto libbr_combine_bits_16(BR::UInt8 h, BR::UInt8 l) noexcept -> BR::UInt16 {
	return (BR::UInt16(h) << 8) | BR::UInt16(l);
}

constexpr auto libbr_combine_bits_32(BR::UInt16 h, BR::UInt16 l) noexcept -> BR::UInt32 {
	return (BR::UInt32(h) << 16) | BR::UInt32(l);
}

constexpr auto libbr_combine_bits_64(BR::UInt32 h, BR::UInt32 l) noexcept -> BR::UInt64 {
	return (BR::UInt64(h) << 32) | BR::UInt64(l);
}

#ifdef BR_HAS_INT128
constexpr auto libbr_combine_bits_128(BR::UInt64 h, BR::UInt64 l) noexcept -> BR::UInt128 {
	return (BR::UInt128(h) << 64) | BR::UInt128(l);
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto combine_bits(UInt8 h, UInt8 l) noexcept -> UInt16 {
	return libbr_combine_bits_16(h, l);
}

constexpr auto combine_bits(UInt16 h, UInt16 l) noexcept -> UInt32 {
	return libbr_combine_bits_32(h, l);
}

constexpr auto combine_bits(UInt32 h, UInt32 l) noexcept -> UInt64 {
	return libbr_combine_bits_64(h, l);
}

#ifdef BR_HAS_INT128
constexpr auto combine_bits(UInt64 h, UInt64 l) noexcept -> UInt128 {
	return libbr_combine_bits_128(h, l);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR