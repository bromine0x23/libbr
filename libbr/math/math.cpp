#include <libbr/math/gcd.hpp>

namespace BR {

template auto gcd(SInt8, SInt8) -> SInt8;

template auto gcd(UInt8, UInt8) -> UInt8;

template auto gcd(SInt16, SInt16) -> SInt16;

template auto gcd(UInt16, UInt16) -> UInt16;

template auto gcd(SInt32, SInt32) -> SInt32;

template auto gcd(UInt32, UInt32) -> UInt32;

template auto gcd(SInt64, SInt64) -> SInt64;

template auto gcd(UInt64, UInt64) -> UInt64;

} // namespace BR

