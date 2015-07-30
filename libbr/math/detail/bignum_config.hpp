#pragma once

#include <libbr/config.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/type_operate/make_signed.hpp>
#include <libbr/type_operate/make_unsigned.hpp>

namespace BR {
namespace Detail {
namespace Bignum {

using Digit   = UInt32;
using DDigit  = UInt64;
using UDigit  = MakeUnsigned<Digit>;
using SDigit  = MakeSigned  <Digit>;
using UDDigit = MakeUnsigned<DDigit>;
using SDDigit = MakeSigned  <DDigit>;
using Size    = UInt32;
using Index   = SInt32;

struct Imp {
	Sign sign;
	Size length;
	Size capacity;
	Digit * digits;
};

constexpr static auto BIT_PER_DIGIT = sizeof(Digit) * BIT_PER_CHAR;

constexpr static auto RADIX = DDigit(1) << BIT_PER_DIGIT;

constexpr static auto MUL_DOOR_KARATSUBA = 80;

constexpr static auto MUL_DOOR_TOOM      = 360;

constexpr static auto SQR_DOOR_KARATSUBA = 120;

constexpr static auto SQR_DOOR_TOOM      = 420;

constexpr static auto DIGIT_PER_BLOCK = 8;

} // namespace Bignum
} // namespace Detail
} // namespace BR