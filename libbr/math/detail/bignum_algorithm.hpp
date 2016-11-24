/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/bignum_config.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/utility/bit_math.hpp>
#include <libbr/utility/integral_constant.hpp>
#include <libbr/utility/swap.hpp>

#include <libbr/string/string.hpp>

namespace BR {

/**
 * @brief Bignum 相关算法
 * @author Bromine0x23
 * @since 1.0
 */
class BignumAlgorithm : public BignumConfig {

protected:
	template< typename TInt >
	constexpr static TInt mul_radix(TInt x) {
		return x << BIT_PER_DIGIT;
	}

	template< typename TInt >
	constexpr static TInt div_radix(TInt x) {
		return x >> BIT_PER_DIGIT;
	}

	template< typename TInt >
	constexpr static Digit mod_radix(TInt x) {
		return Digit(x & Digit(-1));
	}

	constexpr static Size align_mask() {
		return ~(Size(DIGIT_PER_BLOCK) - 1);
	}

	constexpr static Size align_size(Size size) {
		return (size + DIGIT_PER_BLOCK - 1) & align_mask();
	}

	template< typename TInt >
	constexpr static Sign separate_sign(TInt & v) noexcept {
		return (v < 0) ? (v = -v, Sign::NEG) : Sign::ZPOS;
	}

public:
	/**
	 * @brief 返回X的符号
	 * @param[in] X
	 */
	constexpr static Sign sign(BignumData const & X) noexcept {
		return X.sign;
	}

	/**
	 * @brief 返回X的符号的引用
	 * @param[in, out] X
	 */
	constexpr static Sign & sign(BignumData & X) noexcept {
		return X.sign;
	}

	/**
	 * @brief 返回X的精度
	 * @param[in] X
	 */
	constexpr static Size length(BignumData const & X) noexcept {
		return X.length;
	}

	/**
	 * @brief 返回X的精度的引用
	 * @param[in, out] X
	 */
	constexpr static Size & length(BignumData & X) noexcept {
		return X.length;
	}

	/**
	 * @brief 返回X的容量的引用
	 * @param[in] X
	 */
	constexpr static Size capacity(BignumData const & X) noexcept {
		return X.capacity;
	}

	/**
	 * @brief 返回X的容量的引用
	 * @param[in, out] X
	 */
	constexpr static Size & capacity(BignumData & X) noexcept {
		return X.capacity;
	}

	/**
	 * @brief 返回X的 \p digits
	 * @param[in] X
	 */
	constexpr static Digit const * digits(BignumData const & X) noexcept {
		return X.digits;
	}

	/**
	 * @brief 返回X的 \p digits 的引用
	 * @param[in, out] X
	 */
	constexpr static Digit * & digits(BignumData & X) noexcept {
		return X.digits;
	}

	/**
	 * @brief 返回X的位宽
	 * @param[in] X
	 */
	constexpr static Size bit_length(BignumData const & X) noexcept {
		return length(X) * BIT_PER_DIGIT - count_leading_zeros(digits(X)[length(X) - 1]);
	}

	/**
	 * @brief 取X的特定位
	 * @param[in] X
	 * @param[in] index 位索引
	 */
	constexpr static Digit bit(BignumData const & X, Size index) noexcept {
		return (digits(X)[index / BIT_PER_DIGIT] >> (index & (BIT_PER_DIGIT - 1))) & 0x1;
	}

	/**
	 * @brief 初始化
	 * @param[out] X
	 * @post X已初始化
	 */
	static void init(BignumData & X) noexcept {
		sign(X) = Sign::ZPOS;
		length(X) = 0;
		capacity(X) = 0;
		digits(X) = nullptr;
	}

	/**
	 * @brief 清理（析构）
	 * @param[in,out] X
	 * @post X未初始化
	 */
	static void clear(BignumData & X) noexcept {
		delete [] digits(X);
		length(X) = 0;
		capacity(X) = 0;
		digits(X) = nullptr;
	}

	/**
	 * @brief 预留空间
	 * @param[in,out] X
	 * @param[in] size
	 * @post capacity(X) >= size
	 */
	static void reserve(BignumData & X, Size size);

protected:
	static void clamp(BignumData & X);

public:
	/**
	 * @brief 置0
	 * @param[out] X
	 * @pre \p X 已初始化s
	 */
	static void set_zero(BignumData & X) {
		reserve(X, 1);
		sign(X) = Sign::ZPOS;
		digits(X)[0] = 0;
		length(X)  = 1;
	}

public:
	/**
	 * @brief 以 \p digit 赋值
	 * @param[out] X
	 * @param[in] d
	 * @pre \p X 已初始化
	 */
	static void set_d(BignumData & X, Digit d) {
		reserve(X, 1);
		sign(X) = Sign::ZPOS;
		digits(X)[0] = d;
		length(X)  = 1;
	}

protected:
	template< typename TInt >
	static void set_int(BignumData & X, TInt v, IntegralConstant< Size, 1 > _dummy) {
		reserve(X, 1);
		digits(X)[0] = Digit(v);
		length(X) = 1;
	}

	template< typename TInt >
	static void set_int(BignumData & X, TInt v, IntegralConstant< Size, 2 > _dummy) {
		reserve(X, 2);
		digits(X)[0] = mod_radix(v);
		if ((v = div_radix(v)) != 0) {
			digits(X)[1] = Digit(v);
			length(X) = 2;
		} else {
			length(X) = 1;
		}
	}

	template< typename TInt, Size size >
	static void set_int(BignumData & X, TInt v, IntegralConstant< Size, size > _dummy) {
		reserve(X, size);
		for (Size i = 0; v != 0; ++i, v = div_radix(v)) {
			digits(X)[i] = mod_radix(v);
			length(X) = i;
		}
	}

	template< typename TInt >
	static void set_int(BignumData & X, TInt v) {
		set_int(X, v, IntegralConstant< Size, (sizeof(TInt) + sizeof(Digit) - 1) / sizeof(Digit) >{});
	}

public:
	/**
	 * @brief 以整型赋值
	 * @param[out] X
	 * @param[in] v
	 * @pre \p X 已初始化
	 */
	//@{
	template< typename TUInt >

	static void set_uint(BignumData & X, TUInt v) {
		sign(X) = Sign::ZPOS;
		set_int(X, v);
	}

	template< typename TSInt >
	static void set_sint(BignumData & X, TSInt v) {
		sign(X) = separate_sign(v);
		set_int(X, v);
	}
	//@}

	/**
	 * @brief 赋值为2的正整数幂
	 * @param[out] X
	 * @param[in] n
	 * @pre \p X 已初始化
	 */
	static void set_power2(BignumData & X, UDigit n);

	/**
	 * @brief 赋值
	 * @param[out] X
	 * @param[in] Y
	 * @pre \p Y 已初始化
	 */
	static void copy(BignumData & X, BignumData const & Y);

	/**
	 * @brief 以 \p ds 替代 BignumData::digits 创建伪造的 BignumData
	 * @param[out] X
	 * @param[in] ds, size
	 * @pre \p X 未初始化
	 */
	static void fake(BignumData & X, Digit const * ds, Size size) noexcept {
		sign(X) = Sign::ZPOS;
		capacity(X) = length(X) = size;
		digits(X) = const_cast<Digit *>(ds);
	}

	/**
	 * @brief 以单精度数伪造 BignumData
	 * @param[out] X
	 * @param[in] d
	 * @see fake
	 */
	//@{
	static void fake_ud(BignumData & X, UDigit & d) noexcept {
		sign(X) = Sign::ZPOS;
		capacity(X) = length(X) = 1;
		digits(X) = reinterpret_cast<Digit *>(&d);
	}

	static void fake_sd(BignumData & X, SDigit & d) noexcept {
		sign(X) = separate_sign(d);
		capacity(X) = length(X) = 1;
		digits(X) = reinterpret_cast<Digit *>(&d);
	}
	//@}

	/**
	 * @brief 交换
	 * @param[in,out] X, Y
	 */
	static void swap(BignumData & X, BignumData & Y) noexcept {
		BR::swap(X, Y);
	}

	/**
	 * @brief 是否为0(X == 0)
	 * @param[in] X
	 */
	constexpr static bool is_zero(BignumData const & X) {
		return length(X) == 1 && digits(X)[0] == 0;
	}

	/**
	 * @brief 无符号比较
	 * @param[in] X, Y
	 */
	static Relation cmp_u(BignumData const & X, BignumData const & Y);

	/**
	 * @brief 有符号比较(X <=> Y)
	 * @param[in] X, Y
	 */
	static Relation cmp(BignumData const & X, BignumData const & Y) {
		if (sign(X) == sign(Y)) {
			if (sign(X) == Sign::ZPOS) {
				return cmp_u(X, Y);
			} else {
				return cmp_u(Y, X);
			}
		} else {
			if (sign(X) == Sign::ZPOS) {
				return Relation::GT;
			} else {
				return Relation::LT;
			}
		}
	}

	/**
	 * @brief 置补（X = ~X）
	 * @param[in,out] X
	 */
	static void conj(BignumData & X);

protected:
	/**
	 * @brief 无符号大数加法
	 * @pre length(X) >= length(Y)
	 */
	static void add_u(BignumData const & X, BignumData const & Y, BignumData & Z);

	/**
	 * @brief 无符号大数减法
	 * @pre length(X) >= length(Y)
	 */
	static void sub_u(BignumData const & X, BignumData const & Y, BignumData & Z);

public:
	/**
	 * @brief 有符号大数加法
	 * @param[in] X, Y 加数
	 * @param[out] Z 和
	 * @pre \p Z 已初始化
	 */
	static void add(BignumData const & X, BignumData const & Y, BignumData & Z) {
		if (sign(X) == sign(Y)) {
			if (length(X) < length(Y)) {
				sign(Z) = sign(X);
				add_u(Y, X, Z);
			} else {
				sign(Z) = sign(X);
				add_u(X, Y, Z);
			}
		} else {
			if (cmp_u(X, Y) == Relation::LT) {
				sign(Z) = -sign(X);
				sub_u(Y, X, Z);
			} else {
				sign(Z) = +sign(X);
				sub_u(X, Y, Z);
			}
		}
	}

	/**
	 * @brief 有符号大数减法
	 * @param[in] X 被减数
	 * @param[in] Y 减数
	 * @param[out] Z 差
	 * @pre \p Z 已初始化
	 */
	static void sub(BignumData const & X, BignumData const & Y, BignumData & Z) {
		if (sign(X) != sign(Y)) {
			if (length(X) < length(Y)) {
				sign(Z) = sign(X);
				add_u(Y, X, Z);
			} else {
				sign(Z) = sign(X);
				add_u(X, Y, Z);
			}
		} else {
			if (cmp_u(X, Y) == Relation::LT) {
				sign(Z) = -sign(X);
				sub_u(Y, X, Z);
			} else {
				sign(Z) = +sign(X);
				sub_u(X, Y, Z);
			}
		}
	}

	/**
	 * @brief 大数加单精度数
	 * @param[in] X, d
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	//@{
	static void add_ud(BignumData const & X, UDigit d, BignumData & Z) {
		BignumData Y;
		fake_ud(Y, d);
		add(X, Y, Z);
	}

	static void add_sd(BignumData const & X, SDigit d, BignumData & Z) {
		BignumData Y;
		fake_sd(Y, d);
		add(X, Y, Z);
	}
	//@}

	/**
	 * @brief 大数减单精度数
	 * @param[in] X, d
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	//@{
	static void sub_ud(BignumData const & X, UDigit d, BignumData & Z) {
		BignumData Y;
		fake_ud(Y, d);
		sub(X, Y, Z);
	}

	static void sub_sd(BignumData const & X, SDigit d, BignumData & Z) {
		BignumData Y;
		fake_sd(Y, d);
		sub(X, Y, Z);
	}
	//@}

	/**
	 * @brief 大数乘法
	 * @param[in] X, Y 乘数
	 * @param[out] Z 积
	 * @pre \p Z 已初始化
	 * @see https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
	 * @see https://en.wikipedia.org/wiki/Karatsuba_algorithm
	 * @see https://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplication
	 *
	 * 根据输入值的大小来自动选择基线算法、Karatsuba算法或Toom-Cook 3算法的其中之一计算.
	 */
	static void mul(BignumData const & X, BignumData const & Y, BignumData & Z);

protected:
	static void mul_d(BignumData const & X, Digit d, BignumData & Z);

public:
	/**
	 * @brief 大数乘单精度无符号数
	 * @param[in] X, d 乘数
	 * @param[out] Z 积
	 * @pre \p Z 已初始化
	 */
	//@{
	static void mul_ud(BignumData const & X, UDigit d, BignumData & Z) {
		sign(Z) = sign(X);
		mul_d(X, static_cast<Digit>(d), Z);
	}

	static void mul_sd(BignumData const & X, SDigit d, BignumData & Z) {
		sign(Z) = sign(X) * separate_sign(d);
		mul_d(X, static_cast<Digit>(d), Z);
	}
	//@}

	/**
	 * @brief 带余数大数除法
	 * @param[in] X 被除数
	 * @param[in] Y 除数
	 * @param[out] Q 商，置 nullptr 表示不需要返回
	 * @param[out] R 余数，置 nullptr 表示不需要返回
	 * @pre Y != 0
	 * @pre \p Q 为nullptr， 或 \p *Q 已初始化
	 * @pre \p R 为nullptr， 或 \p *R 已初始化
	 * @see https://en.wikipedia.org/wiki/Division_algorithm#Fast_division_methods
	 */
	static void div_mod(BignumData const & X, BignumData const & Y, BignumData * Q, BignumData * R);

	/**
	 * @brief 大数除法
	 * @param[in] X 被除数
	 * @param[in] Y 除数
	 * @param[out] Q 余数，置 nullptr 表示不需要返回
	 * @pre Y != 0
	 * @pre \p Q 已初始化
	 * @see div_mod
	 */
	static void div(BignumData const & X, BignumData const & Y, BignumData & Q) {
		div_mod(X, Y, &Q, nullptr);
	}

	/**
	 * @brief 大数取模
	 * @param[in] X 被除数
	 * @param[in] Y 除数
	 * @param[out] R 余数，置 nullptr 表示不需要返回
	 * @pre Y != 0
	 * @pre \p R 已初始化
	 * @see div_mod
	 */
	static void mod(BignumData const & X, BignumData const & Y, BignumData & R) {
		div_mod(X, Y, nullptr, &R);
	}

protected:
	static Digit div_mod_d(BignumData const & X, Digit d, BignumData & Z);

public:
	/**
	 * @brief 带余数大数除以单精度数
	 * @param[in] X 被除数
	 * @param[in] d 除数
	 * @param[out] Z 商
	 * @return 余数
	 * @pre d != 0
	 * @pre \p Z 已初始化
	 */
	//@{
	static Digit div_mod_ud(BignumData const & X, UDigit d, BignumData & Z) {
		sign(Z) = sign(X);
		return div_mod_d(X, static_cast<Digit>(d), Z);
	}

	static Digit div_mod_sd(BignumData const & X, SDigit d, BignumData & Z) {
		sign(Z) = sign(X) / separate_sign(d);
		return div_mod_d(X, static_cast<Digit>(d), Z);
	}
	//@}

public:
	/**
	 * @brief 大数除以单精度数
	 * @param[in] X 被除数
	 * @param[in] d 除数
	 * @param[out] Z 商
	 * @pre d != 0
	 * @pre \p Z 已初始化
	 */
	//@{
	static void div_ud(BignumData const & X, UDigit d, BignumData & Z) {
		div_mod_ud(X, d, Z);
	}

	static void div_sd(BignumData const & X, SDigit d, BignumData & Z) {
		div_mod_sd(X, d, Z);
	}
	//@}

	/**
	 * @brief 大数对单精度数取模
	 * @param[in] X 被除数
	 * @param[in] d 模数
	 */
	static Digit mod_d(BignumData const & X, UDigit d);

	/**
	 * @brief 大数按位或
	 * @param[in] X, Y
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void bor(BignumData const & X, BignumData const & Y, BignumData & Z);

	/**
	 * @brief 大数按位与
	 * @param[in] X, Y
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void band(BignumData const & X, BignumData const & Y, BignumData & Z);

	/**
	 * @brief 大数按位异或
	 * @param[in] X, Y
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void bxor(BignumData const & X, BignumData const & Y, BignumData & Z);

	/**
	 * @brief 大数和单精度数按位或
	 * @see bor
	 */
	//@{
	static void bor_ud(BignumData const & X, UDigit d, BignumData & Z) {
		BignumData Y;
		fake_ud(Y, d);
		bor(X, Y, Z);
	}

	static void bor_sd(BignumData const & X, SDigit d, BignumData & Z) {
		BignumData Y;
		fake_sd(Y, d);
		bor (X, Y, Z);
	}
	//@}

	/**
	 * @brief 大数和单精度数按位与
	 * @see band
	 */
	//@{
	static void band_ud(BignumData const & X, UDigit d, BignumData & Z) {
		BignumData Y;
		fake_ud(Y, d);
		band(X, Y, Z);
	}

	static void band_sd(BignumData const & X, SDigit d, BignumData & Z) {
		BignumData Y;
		fake_sd(Y, d);
		band(X, Y, Z);
	}
	//@}

	/**
	 * @brief 大数和单精度数按位异或
	 * @see bxor
	 */
	//@{
	static void bxor_ud(BignumData const & X, UDigit d, BignumData & Z) {
		BignumData Y;
		fake_ud(Y, d);
		bxor(X, Y, Z);
	}

	static void bxor_sd(BignumData const & X, SDigit d, BignumData & Z) {
		BignumData Y;
		fake_sd(Y, d);
		bxor(X, Y, Z);
	}
	//@}

	/**
	 * @brief 平方
	 * @param[in] X
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void sqr(BignumData const & X, BignumData & Z);

	/**
	 * @brief 幂运算
	 * @param[in] X 底数
	 * @param[in] n 指数
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void power(BignumData const & X, Digit n, BignumData & Z);

	/**
	 * @brief 乘以2
	 * @param[in] X
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void mul2(BignumData const & X, BignumData & Z);

	/**
	 * @brief 除以2
	 * @param[in] X
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void div2(BignumData const & X, BignumData & Z);

	/**
	 * @brief 按位左移
	 * @param[in] X
	 * @param[in] bn 左移比特数
	 * @param[out] Z
	 * @pre \p bn 不超过一个单精度数的位宽
	 * @pre \p Z 已初始化
	 */
	static void lsh_b(BignumData const & X, Digit bn, BignumData & Z);

	/**
	 * @brief 按位右移
	 * @param[in] X
	 * @param[in] bn 右移比特数
	 * @param[out] Z
	 * @pre \p bn 不超过一个单精度数的位宽
	 * @pre \p Z 已初始化
	 */
	static void rsh_b(BignumData const & X, Digit bn, BignumData & Z);

	/**
	 * @see lsh_b
	 */
	static void lsh_b_ud(BignumData const & X, UDigit bn, BignumData & Z) {
		lsh_b(X, static_cast<Digit>(bn), Z);
	}

	/**
	 * @see rsh_b
	 */
	static void rsh_b_ud(BignumData const & X, UDigit bn, BignumData & Z) {
		rsh_b(X, static_cast<Digit>(bn), Z);
	}

	/**
	 * @see lsh_b
	 */
	static void lsh_b_sd(BignumData const & X, SDigit bn, BignumData & Z) {
		if (bn < 0) {
			rsh_b(X, static_cast<Digit>(-bn), Z);
		} else {
			lsh_b(X, static_cast<Digit>(bn), Z);
		}
	}

	/**
	 * @see rsh_b
	 */
	static void rsh_b_sd(BignumData const & X, SDigit bn, BignumData & Z) {
		if (bn < 0) {
			lsh_b(X, static_cast<Digit>(-bn), Z);
		} else {
			rsh_b(X, static_cast<Digit>(bn), Z);
		}
	}

	/**
	 * @brief 按单精度数位宽左移
	 * @param[in] X
	 * @param[in] dn 左移多少个单精度数位宽
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void lsh_d(BignumData const & X, Digit dn, BignumData & Z);

	/**
	 * @brief 单精度数位宽右移
	 * @param[in] X
	 * @param[in] dn 右移多少个单精度数位宽
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void rsh_d(BignumData const & X, Digit dn, BignumData & Z);

	/**
	 * @see lsh_d
	 */
	static void lsh_d_ud(BignumData const & X, UDigit dn, BignumData & Z) {
		lsh_d(X, static_cast<Digit>(dn), Z);
	}

	/**
	 * @see rsh_d
	 */
	static void rsh_d_ud(BignumData const & X, UDigit dn, BignumData & Z) {
		rsh_d(X, static_cast<Digit>(dn), Z);
	}

	/**
	 * @see lsh_d
	 */
	static void lsh_d_sd(BignumData const & X, SDigit dn, BignumData & Z) {
		if (dn < 0) {
			rsh_d(X, static_cast<Digit>(-dn), Z);
		} else {
			lsh_d(X, static_cast<Digit>(dn), Z);
		}
	}

	/**
	 * @see rsh_d
	 */
	static void rsh_d_sd(BignumData const & X, SDigit dn, BignumData & Z) {
		if (dn < 0) {
			lsh_d(X, static_cast<Digit>(-dn), Z);
		} else {
			rsh_d(X, static_cast<Digit>(dn), Z);
		}
	}

	/**
	 * @brief 按位左移
	 * @param[in] X
	 * @param[in] n 左移比特数
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void lsh(BignumData const & X, Digit n, BignumData & Z);

	/**
	 * @brief 按位右移
	 * @param[in] X
	 * @param[in] n 右移比特数
	 * @param[out] Z
	 * @pre \p Z 已初始化
	 */
	static void rsh(BignumData const & X, Digit n, BignumData & Z);

	/**
	 * @see lsh
	 */
	static void lsh_ud(BignumData const & X, UDigit n, BignumData & Z) {
		lsh(X, static_cast<Digit>(n), Z);
	}

	/**
	 * @see rsh
	 */
	static void rsh_ud(BignumData const & X, UDigit n, BignumData & Z) {
		rsh(X, static_cast<Digit>(n), Z);
	}

	/**
	 * @see lsh
	 */
	static void lsh_sd(BignumData const & X, SDigit n, BignumData & Z) {
		if (n < 0) {
			rsh(X, static_cast<Digit>(-n), Z);
		} else {
			lsh(X, static_cast<Digit>(n), Z);
		}
	}

	/**
	 * @see rsh
	 */
	static void rsh_sd(BignumData const & X, SDigit n, BignumData & Z) {
		if (n < 0) {
			lsh(X, static_cast<Digit>(-n), Z);
		} else {
			rsh(X, static_cast<Digit>(n), Z);
		}
	}

	static String<> inspect(BignumData const & X);

	static String<> to_s(BignumData const & X, Digit b, bool show_plus);

	static BignumData parse(String<> s);

}; // class BignumAlgorithm

} // namespace BR