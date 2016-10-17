/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/20
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/float.hpp>

namespace BR {

/**
 * @brief 符号
 */
enum class Sign : bool {
	NEG = false,  ///< 负
	POS = true, ///< 0或正
	ZPOS = POS
};

/**
 * @brief Sign 取补
 *
 * \em s 为 Sign::ZPOS时返回 Sign::NEG \n 否则返回 Sign::ZPOS
 */
constexpr auto operator~(Sign s) -> Sign {
	return s == Sign::POS ?  Sign::NEG : Sign::POS;
}

/**
 * @brief Sign 位或
 *
 * 仅当 \em x 和 \em y 均为 Sign::ZPOS 时返回 Sign::ZPOS \n 否则返回 Sign::NEG
 */
constexpr auto operator|(Sign x, Sign y) -> Sign {
	return (x == Sign::POS && y == Sign::POS) ? Sign::POS : Sign::NEG;
}

/**
 * @brief Sign 位与
 *
 * 仅当 \em x 和 \em y 均不为 Sign::ZPOS 时返回 Sign::ZPOS \n 否则返回 Sign::NEG
 */
constexpr auto operator&(Sign x, Sign y) -> Sign {
	return (x != Sign::POS && y != Sign::POS) ? Sign::POS : Sign::NEG;
}

/**
 * @brief Sign 位与
 *
 * 仅当 \em x 和 \em y 相同时返回 Sign::ZPOS \n 否则返回 Sign::NEG
 */
constexpr auto operator^(Sign x, Sign y) -> Sign {
	return (x == y) ? Sign::POS : Sign::NEG;
}

/**
 * @brief Sign 一元+
 *
 * 返回原值
 */
constexpr auto operator+(Sign s) -> Sign {
	return s;
}

/**
 * @brief Sign 一元-
 *
 * 返回补值
 */
constexpr auto operator-(Sign s) -> Sign {
	return ~s;
}

/**
 * @brief Sign 乘
 *
 * 返回异或结果
 */
constexpr auto operator*(Sign x, Sign y) -> Sign {
	return x ^ y;
}

/**
 * @brief Sign 除
 *
 * 返回异或结果
 */
constexpr auto operator/(Sign x, Sign y) -> Sign {
	return x ^ y;
}

/**
 * @brief Sign 转 NChar
 *
 * Sign::ZPOS 对应 '+' \n Sign::NEG 对应 '-'
 */
constexpr auto sign_to_nchar(Sign s) -> NChar {
	return s == Sign::POS ? '+' : '-';
}

/**
 * @brief Sign 转 WChar
 *
 * Sign::ZPOS 对应 L'+' \n Sign::NEG 对应 L'-'
 */
constexpr auto sign_to_wchar(Sign s) -> WChar {
	return s == Sign::POS ? L'+' : L'-';
}

constexpr auto sign(Float32 f) -> Sign {
	return Detail::Float::to_raw(f) < 0x80000000U ? Sign::POS : Sign::NEG;
}

constexpr auto sign(Float64 f) -> Sign {
	return Detail::Float::to_raw_high(f) < 0x80000000U ? Sign::POS : Sign::NEG;
}

} // namespace BR