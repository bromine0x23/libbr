/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/20
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>

namespace BR {

/**
 * @brief 符号
 * @author Bromine0x23
 * @since 2015/6/20
 */
enum class Sign {
	NEG = false,  ///< 负
	ZPOS = true, ///< 0或正
};

/**
 * @brief Sign 取补
 *
 * \em s 为 Sign::ZPOS时返回 Sign::NEG \n 否则返回 Sign::ZPOS
 */
constexpr Sign operator~(Sign s) {
	return s == Sign::ZPOS ?  Sign::NEG : Sign::ZPOS;
}

/**
 * @brief Sign 位或
 *
 * 仅当 \em x 和 \em y 均为 Sign::ZPOS 时返回 Sign::ZPOS \n 否则返回 Sign::NEG
 */
constexpr Sign operator|(Sign x, Sign y) {
	return (x == Sign::ZPOS && y == Sign::ZPOS) ? Sign::ZPOS : Sign::NEG;
}

/**
 * @brief Sign 位与
 *
 * 仅当 \em x 和 \em y 均不为 Sign::ZPOS 时返回 Sign::ZPOS \n 否则返回 Sign::NEG
 */
constexpr Sign operator&(Sign x, Sign y) {
	return (x != Sign::ZPOS && y != Sign::ZPOS) ? Sign::ZPOS : Sign::NEG;
}

/**
 * @brief Sign 位与
 *
 * 仅当 \em x 和 \em y 相同时返回 Sign::ZPOS \n 否则返回 Sign::NEG
 */
constexpr Sign operator^(Sign x, Sign y) {
	return (x == y) ? Sign::ZPOS : Sign::NEG;
}

/**
 * @brief Sign 一元+
 *
 * 返回原值
 */
constexpr Sign operator+(Sign s) {
	return s;
}

/**
 * @brief Sign 一元-
 *
 * 返回补值
 */
constexpr Sign operator-(Sign s) {
	return ~s;
}

/**
 * @brief Sign 乘
 *
 * 返回异或结果
 */
constexpr Sign operator*(Sign x, Sign y) {
	return x ^ y;
}

/**
 * @brief Sign 除
 *
 * 返回异或结果
 */
constexpr Sign operator/(Sign x, Sign y) {
	return x ^ y;
}

/**
 * @brief Sign 转 NChar
 *
 * Sign::ZPOS 对应 '+' \n Sign::NEG 对应 '-'
 */
constexpr NChar sign_to_nchar(Sign s) {
	return s == Sign::ZPOS ? '+' : '-';
}

/**
 * @brief Sign 转 WChar
 *
 * Sign::ZPOS 对应 L'+' \n Sign::NEG 对应 L'-'
 */
constexpr WChar sign_to_wchar(Sign s) {
	return s == Sign::ZPOS ? L'+' : L'-';
}

} // namespace BR