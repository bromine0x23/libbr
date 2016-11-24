/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/math/sign.hpp>

namespace BR {

/**
 * @brief Bignum 的数据
 * @author Bromine0x23
 * @since 1.0
 */
struct BignumData : public BignumConfig  {
	/**
	 * @brief Bignum 的符号
	 */
	Sign sign;

	/**
	 * @brief 分配给 Bignum 的 \em digit 空间大小（以 \em digit 数计）
	 */
	Size capacity;

	/**
	 * @brief Bignum 使用的 \em digit 空间大小（以 \em digit 数计）
	 */
	Size length;

	/**
	 * @brief 分配给 Bignum 的 \em digit 空间
	 */
	Digit * digits;
};

} // namespace BR