/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/bignum_config.hpp>

namespace BR {

/**
 * @brief Bignum 基类
 * @author Bromine0x23
 * @since 1.0
 */
class BignumBasic : public BignumConfig {

protected:

	struct Positive {};

	struct Negative {};

	struct Absolute {};

	struct Complement {};

	template< Digit value >
	struct Value {};

	template< typename TInt >
	struct Bits {
		TInt const v;
	};

	template< typename TInt >
	struct Digits {
		TInt const v;
	};

	struct Power2 {
		UDigit const v;
	};

	struct Exponent {
		Digit const v;
	};

public:
	/**
	 * @brief 用于表示一元+操作
	 */
	constexpr static Positive positive() {
		return Positive();
	}

	/**
	 * @brief 用于表示一元-操作
	 */
	constexpr static Negative negative() {
		return Negative();
	}

	/**
	 * @brief 用于设置 Bignum 为其绝对值
	 */
	constexpr static Absolute absolute() {
		return Absolute();
	}

	/**
	 * @brief 用于设置 Bignum 为其补数
	 */
	constexpr static Complement complement() {
		return Complement();
	}

	/**
	 * @brief 包装编译期常量 \em v 以提示 Bignum
	 */
	template< Digit v >
	constexpr static Value<v> value() {
		return Value<v>{};
	}

	//@{
	/**
	 * @brief 包装 \em n 以提示 Bignum 该值表示位宽
	 */
	constexpr static Bits<UDigit> bits(UDigit n) {
		return Bits<UDigit>{n};
	}

	constexpr static Bits<SDigit> bits(SDigit n) {
		return Bits<SDigit>{n};
	}
	//@}

	//@{
	/**
	 * @brief 包装 \em n 以提示 Bignum 该值表示数码(\em digit)宽
	 */
	constexpr static Digits<UDigit> digits(UDigit n) {
		return Digits<UDigit>{n};
	}

	constexpr static Digits<SDigit> digits(SDigit n) {
		return Digits<SDigit>{n};
	}
	//@}

	/**
	 * @brief 包装 \em n 以提示 Bignum 表示值 \f$ 2^n \f$
	 */
	constexpr static Power2 power2(Digit n) {
		return Power2{n};
	}

	/**
	 * @brief 包装 \em n 以提示 Bignum 该值表示指数
	 */
	constexpr static Exponent exponent(Digit n) {
		return Exponent{n};
	}
}; // class BignumBasic

} // namespace BR
