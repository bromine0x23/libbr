/**
 * @file
 * @author Bromine0x23
 * @since 2015/9/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/make_signed.hpp>
#include <libbr/type_operate/make_unsigned.hpp>

namespace BR {

/**
 * @brief Bignum 相关的配置
 * @author Bromine0x23
 * @since 2015/9/24
 */
class BignumConfig {

public:
	/**
	 * @brief 用于表示和存储一个 \em digit 的整型
	 */
	using Digit   = UInt32;

	/**
	 * @brief 能存储至少两个 \em digit 的整型
	 */
	using DDigit  = UInt64;

	/**
	 * @brief 无符号的 #Digit
	 */
	using UDigit  = MakeUnsigned<Digit>;

	/**
	 * @brief 有符号的 #Digit
	 */
	using SDigit  = MakeSigned<Digit>;

	/**
	 * @brief 无符号的 #DDigit
	 */
	using UDDigit = MakeUnsigned<DDigit>;

	/**
	 * @brief 有符号的 #DDigit
	 */
	using SDDigit = MakeSigned<DDigit>;

	/**
	 * @brief 表示 \em digit 数量的整型
	 */
	using Size = UInt32;

	/**
	 * @brief 用于索引 \em digit 的整型
	 */
	using Index = SInt32;

	/**
	 * @brief \em digit 的位宽
	 */
	constexpr static auto BIT_PER_DIGIT = sizeof(Digit) * BIT_PER_BYTE;

	/**
	 * @brief Bignum 的基数
	 */
	constexpr static auto RADIX = DDigit(1) << BIT_PER_DIGIT;

protected:

	constexpr static auto MUL_DOOR_KARATSUBA = 80;

	constexpr static auto MUL_DOOR_TOOM      = 360;

	constexpr static auto SQR_DOOR_KARATSUBA = 120;

	constexpr static auto SQR_DOOR_TOOM      = 420;

	constexpr static auto DIGIT_PER_BLOCK = 8;

}; // class BignumConfig

} // namespace BR