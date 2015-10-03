/**
 * @file
 * @author Bromine0x23
 * @date 2015/9/24
 */
#pragma once

#include <libbr/config.hpp>

#include <libbr/math/detail/bignum_config.hpp>
#include <libbr/math/detail/bignum_data.hpp>
#include <libbr/math/detail/bignum_algorithm.hpp>
#include <libbr/math/detail/bignum_basic.hpp>
#include <libbr/math/detail/bignum_helper.hpp>

#include <libbr/exception/out_of_range_exception.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/utility/current_function.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/pair.hpp>
#include <libbr/utility/swap.hpp>

#include <string>

namespace BR {

/**
 * @brief 多精度整数类
 * @author Bromine0x23
 * @since 2015/9/24
 */
class Bignum : public BignumBasic {

public:
	/**
	 * @brief 常量0
	 */
	static Bignum const ZERO;

private:
	struct NotAllocate {};

	// constexpr static auto not_allocate = NotAllocate();
	static NotAllocate const not_allocate;

private:
	BignumData m_data;

public:
	/**
	 * @brief 默认构造函数，置0
	 */
	Bignum() : Bignum(not_allocate) {
		BignumAlgorithm::set_zero(m_data);
	}

	/**
	 * @brief 复制构造函数
	 */
	Bignum(Bignum const & Y) : Bignum(not_allocate) {
		BignumAlgorithm::copy(m_data, Y.m_data);
	}

	/**
	 * @brief 移动构造函数
	 */
	Bignum(Bignum && Y) : Bignum(not_allocate) {
		BignumAlgorithm::swap(m_data, Y.m_data);
	}

	/**
	 * @brief 以整型初始化
	 */
	//@{
	explicit Bignum(signed char v) : Bignum(not_allocate) {
		BignumAlgorithm::set_sint(m_data, v);
	}

	explicit Bignum(unsigned char v) : Bignum(not_allocate) {
		BignumAlgorithm::set_uint(m_data, v);
	}

	explicit Bignum(signed short v) : Bignum(not_allocate) {
		BignumAlgorithm::set_sint(m_data, v);
	}

	explicit Bignum(unsigned short v) : Bignum(not_allocate) {
		BignumAlgorithm::set_uint(m_data, v);
	}

	explicit Bignum(signed int v) : Bignum(not_allocate) {
		BignumAlgorithm::set_sint(m_data, v);
	}

	explicit Bignum(unsigned int v) : Bignum(not_allocate) {
		BignumAlgorithm::set_uint(m_data, v);
	}

	explicit Bignum(signed long v) : Bignum(not_allocate) {
		BignumAlgorithm::set_sint(m_data, v);
	}

	explicit Bignum(unsigned long v) : Bignum(not_allocate) {
		BignumAlgorithm::set_uint(m_data, v);
	}

	explicit Bignum(signed long long v) : Bignum(not_allocate) {
		BignumAlgorithm::set_sint(m_data, v);
	}

	explicit Bignum(unsigned long long v) : Bignum(not_allocate) {
		BignumAlgorithm::set_uint(m_data, v);
	}

#if defined(BR_HAS_INT128) || defined(BR_DOXYGEN)
	explicit Bignum(SInt128 v) : Bignum(not_allocate) {
		BignumAlgorithm::set_sint(m_data, v);
	}

	explicit Bignum(UInt128 v) : Bignum(not_allocate) {
		BignumAlgorithm::set_uint(m_data, v);
	}
#endif

	template< Digit v >
	explicit Bignum(Value<v> _dummy) : Bignum(not_allocate) {
		BignumAlgorithm::set_d(m_data, v);
	}
	//@}

	/**
	 * @brief 初始化为2的幂
	 */
	Bignum(Power2 p) : Bignum(not_allocate) {
		BignumAlgorithm::set_power2(m_data, p.v);
	}

	/**
	 * @brief 析构函数
	 */
	virtual ~Bignum() {
		BignumAlgorithm::clear(m_data);
	}

public:
	/**
	 * @brief 复制赋值运算符
	 */
	Bignum & operator=(Bignum const & Y) {
		BignumAlgorithm::copy(m_data, Y.m_data);
		return *this;
	}

	/**
	 * @brief 移动赋值运算符
	 */
	Bignum & operator=(Bignum && Y) {
		BignumAlgorithm::swap(m_data, Y.m_data);
		return *this;
	}

	/**
	 * @brief 整型赋值运算符
	 */
	//@{
	Bignum & operator=(signed char v) {
		BignumAlgorithm::set_sint(m_data, v);
		return *this;
	}

	Bignum & operator=(unsigned char v) {
		BignumAlgorithm::set_uint(m_data, v);
		return *this;
	}

	Bignum & operator=(signed short v) {
		BignumAlgorithm::set_sint(m_data, v);
		return *this;
	}

	Bignum & operator=(unsigned short v) {
		BignumAlgorithm::set_uint(m_data, v);
		return *this;
	}

	Bignum & operator=(signed int v) {
		BignumAlgorithm::set_sint(m_data, v);
		return *this;
	}

	Bignum & operator=(unsigned int v) {
		BignumAlgorithm::set_uint(m_data, v);
		return *this;
	}

	Bignum & operator=(signed long v) {
		BignumAlgorithm::set_sint(m_data, v);
		return *this;
	}

	Bignum & operator=(unsigned long v) {
		BignumAlgorithm::set_uint(m_data, v);
		return *this;
	}

	Bignum & operator=(signed long long v) {
		BignumAlgorithm::set_sint(m_data, v);
		return *this;
	}

	Bignum & operator=(unsigned long long v) {
		BignumAlgorithm::set_uint(m_data, v);
		return *this;
	}

#if defined(BR_HAS_INT128) || defined(BR_DOXYGEN)
	Bignum & operator=(SInt128 v) {
		BignumAlgorithm::set_sint(m_data, v); return *this;
	}

	Bignum & operator=(UInt128 v) {
		BignumAlgorithm::set_uint(m_data, v); return *this;
	}
#endif

	template< Digit v >
	Bignum & operator=(Value<v> _dummy) {
		BignumAlgorithm::set_d(m_data, v);
		return *this;
	}
	//@}

	/**
	 * @brief 赋值为2的幂
	 */
	Bignum & operator=(Power2 n) {
		BignumAlgorithm::set_power2(m_data, n.v);
		return *this;
	}

public:
	/**
	 * @brief 获取符号
	 */
	Sign sign() const noexcept {
		return BignumAlgorithm::sign(m_data);
	}

	/**
	 * @brief 获取长度（以digit计）
	 */
	Size length() const noexcept {
		return BignumAlgorithm::length(m_data);
	}

	/**
	 * @brief 获取容量
	 */
	Size capacity() const noexcept {
		return BignumAlgorithm::capacity(m_data);
	}

	/**
	 * @brief 获取二进制长度
	 */
	Size bit_length() const {
		return BignumAlgorithm::bit_length(m_data);
	}

	/**
	 * @brief 索引digit，无越界检查
	 * @param[in] index 下标；负数下标对应 \f$length() - |index|\f$
	 */
	Digit operator()(Index index) const {
		return BignumAlgorithm::digits(m_data)[m_fix_index(index)];
	}

	/**
	 * @brief 索引digit，有越界检查
	 * @param[in] index 下标；负数下标对应 \f$length() - |index|\f$
	 * @see operator()(Index index)
	 */
	Digit digit(Index index) const noexcept(false) {
		auto fixed_index = m_fix_index(index);
		if (fixed_index >= length()) {
			throw OutOfRangeException(BR_CURRENT_FUNCTION);
		}
		return operator()(index);
	}

	/**
	 * @brief 索引二进制位，无越界检查
	 * @param[in] index 下标；负数下标对应 \f$length() - |index|\f$
	 */
	Digit operator[](Index index) const {
		return BignumAlgorithm::bit(m_data, m_fix_index(index));
	}

	/**
	 * @brief 索引二进制位，有越界检查
	 * @param[in] index 下标；负数下标对应 \f$length() - |index|\f$
	 * @see operator[](Index index)
	 */
	Digit bit(Index index) const noexcept(false) {
		auto fixed_index = m_fix_index(index);
		if (fixed_index >= bit_length()) {
			throw OutOfRangeException(BR_CURRENT_FUNCTION);
		}
		return operator[](index);
	}

public:
	/**
	 * @brief 预留空间以加速计算
	 */
	Bignum & reserve(Size size) {
		BignumAlgorithm::reserve(m_data, size);
		return *this;
	}

	/**
	 * @brief 交换
	 */
	Bignum & swap(Bignum & Y) {
		BignumAlgorithm::swap(m_data, Y.m_data);
		return *this;
	}

public:
	/**
	 * @brief 是否为正数
	 */
	bool is_pos() const noexcept {
		return sign() == Sign::ZPOS;
	}

	/**
	 * @brief 是否为负数
	 */
	bool is_neg() const noexcept {
		return sign() == Sign::NEG;
	}

	/**
	 * @brief 是否为偶数
	 */
	bool is_even() const noexcept {
		return operator%(Value<2>()) == 0;
	}

	/**
	 * @brief 是否为奇数
	 */
	bool is_odd () const noexcept {
		return operator%(Value<2>()) == 1;
	}

	/**
	 * @brief 是否为0
	 */
	bool operator!() const noexcept {
		return length() == 1 && operator()(Index(0)) == 0;
	}

	/**
	 * @brief 是否不为0
	 */
	explicit operator bool() const noexcept {
		return !operator!();
	}

	/**
	 * @brief 与Y比较大小
	 */
	Relation compare(Bignum const & Y) const {
		return BignumAlgorithm::cmp(m_data, Y.m_data);
	}

	/**
	 * @brief 比较操作符
	 */
	//@{
	bool operator< (Bignum const & Y) const noexcept {
		return compare(Y) == Relation::LT;
	}

	bool operator> (Bignum const & Y) const noexcept {
		return compare(Y) == Relation::GT;
	}

	bool operator<=(Bignum const & Y) const noexcept {
		return compare(Y) != Relation::GT;
	}

	bool operator>=(Bignum const & Y) const noexcept {
		return compare(Y) != Relation::LT;
	}

	bool operator==(Bignum const & Y) const noexcept {
		return compare(Y) == Relation::EQ;
	}

	bool operator!=(Bignum const & Y) const noexcept {
		return compare(Y) != Relation::EQ;
	}
	//@}

public:
	/**
	 * @brief X = +X
	 */
	Bignum & operator=(Positive) noexcept {
		using BR::operator+;
		BignumAlgorithm::sign(m_data) = operator+(sign());
		return *this;
	}

	/**
	 * @brief X = -X
	 */
	Bignum & operator=(Negative) noexcept {
		using BR::operator-;
		BignumAlgorithm::sign(m_data) = operator-(sign());
		return *this;
	}

	/**
	 * @brief X = |X|
	 */
	Bignum & operator=(Absolute) noexcept {
		BignumAlgorithm::sign(m_data) = Sign::ZPOS;
		return *this;
	}

	/**
	 * @brief X = ~X
	 */
	Bignum & operator=(Complement) {
		BignumAlgorithm::conj(m_data);
		return *this;
	}

	/**
	 * @brief +X
	 */
	Bignum operator+() const {
		Bignum Z(*this);
		return Z.operator=(positive);
	}

	/**
	 * @brief -X
	 */
	Bignum operator-() const {
		Bignum Z(*this);
		return Z.operator=(negative);
	}

	/**
	 * @brief |X|
	 */
	Bignum abs() const {
		Bignum Z(*this);
		return Z.operator=(absolute);
	}

	/**
	 * @brief ~X
	 */
	Bignum operator~() const {
		Bignum Z(*this);
		return Z.operator=(complement);
	}

public:
	Bignum operator+(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::add(m_data, Y.m_data, Z.m_data);
		return Z;
	}

	Bignum operator-(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::sub(m_data, Y.m_data, Z.m_data);
		return Z;
	}
	Bignum operator*(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::mul(m_data, Y.m_data, Z.m_data);
		return Z;
	}

	Bignum operator/(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::div(m_data, Y.m_data, Z.m_data);
		return Z;
	}

	Bignum operator%(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::mod(m_data, Y.m_data, Z.m_data);
		return Z;
	}

	Bignum operator|(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::bor(m_data, Y.m_data, Z.m_data);
		return Z;
	}

	Bignum operator&(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::band(m_data, Y.m_data, Z.m_data);
		return Z;
	}

	Bignum operator^(Bignum const & Y) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::bxor(m_data, Y.m_data, Z.m_data);
		return Z;
	}

	Bignum & operator+=(Bignum const & Y) {
		BignumAlgorithm::add(m_data, Y.m_data, m_data);
		return *this;
	}

	Bignum & operator-=(Bignum const & Y) {
		BignumAlgorithm::sub(m_data, Y.m_data, m_data);
		return *this;
	}

	Bignum & operator*=(Bignum const & Y) {
		BignumAlgorithm::mul(m_data, Y.m_data, m_data);
		return *this;
	}

	Bignum & operator/=(Bignum const & Y) {
		BignumAlgorithm::div(m_data, Y.m_data, m_data);
		return *this;
	}

	Bignum & operator%=(Bignum const & Y) {
		BignumAlgorithm::mod(m_data, Y.m_data, m_data);
		return *this;
	}

	Bignum & operator|=(Bignum const & Y) {
		BignumAlgorithm::bor(m_data, Y.m_data, m_data);
		return *this;
	}

	Bignum & operator&=(Bignum const & Y) {
		BignumAlgorithm::band(m_data, Y.m_data, m_data);
		return *this;
	}

	Bignum & operator^=(Bignum const & Y) {
		BignumAlgorithm::bxor(m_data, Y.m_data, m_data);
		return *this;
	}

public:
	Bignum operator+(UDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::add_ud(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator+(SDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::add_sd(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator-(UDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::sub_ud(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator-(SDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::sub_sd(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator*(UDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::mul_ud(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator*(SDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::mul_sd(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator/(UDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::div_ud(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator/(SDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::div_sd(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator|(UDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::bor_ud(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator|(SDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::bor_sd(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator&(UDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::band_ud(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator&(SDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::band_sd(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator^(UDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::bxor_ud(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator^(SDigit d) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::bxor_sd(m_data, d, Z.m_data);
		return Z;
	}

	Bignum operator<<(UDigit n) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::lsh_ud(m_data, n, Z.m_data);
		return Z;
	}

	Bignum operator<<(SDigit n) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::lsh_sd(m_data, n, Z.m_data);
		return Z;
	}

	Bignum operator>>(UDigit n) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::rsh_ud(m_data, n, Z.m_data);
		return Z;
	}

	Bignum operator>>(SDigit n) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::rsh_sd(m_data, n, Z.m_data);
		return Z;
	}

	Bignum operator<<(Bits<UDigit> bn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::lsh_b_ud(m_data, bn.v, Z.m_data);
		return Z;
	}

	Bignum operator<<(Bits<SDigit> bn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::lsh_b_sd(m_data, bn.v, Z.m_data);
		return Z;
	}

	Bignum operator>>(Bits<UDigit> bn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::rsh_b_ud(m_data, bn.v, Z.m_data);
		return Z;
	}

	Bignum operator>>(Bits<SDigit> bn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::rsh_b_sd(m_data, bn.v, Z.m_data);
		return Z;
	}

	Bignum operator<<(Digits<UDigit> dn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::lsh_d_ud(m_data, dn.v, Z.m_data);
		return Z;
	}

	Bignum operator<<(Digits<SDigit> dn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::lsh_d_sd(m_data, dn.v, Z.m_data);
		return Z;
	}

	Bignum operator>>(Digits<UDigit> dn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::rsh_d_ud(m_data, dn.v, Z.m_data);
		return Z;
	}

	Bignum operator>>(Digits<SDigit> dn) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::rsh_d_sd(m_data, dn.v, Z.m_data);
		return Z;
	}

	Bignum & operator+=(UDigit d) {
		BignumAlgorithm::add_ud(m_data, d, m_data);
		return *this;
	}

	Bignum & operator+=(SDigit d) {
		BignumAlgorithm::add_sd(m_data, d, m_data);
		return *this;
	}

	Bignum & operator-=(UDigit d) {
		BignumAlgorithm::sub_ud(m_data, d, m_data);
		return *this;
	}

	Bignum & operator-=(SDigit d) {
		BignumAlgorithm::sub_sd(m_data, d, m_data);
		return *this;
	}

	Bignum & operator *=(UDigit d) {
		BignumAlgorithm::mul_ud(m_data, d, m_data);
		return *this;
	}

	Bignum & operator *=(SDigit d) {
		BignumAlgorithm::mul_sd(m_data, d, m_data);
		return *this;
	}

	Bignum & operator /=(UDigit d) {
		BignumAlgorithm::div_ud(m_data, d, m_data);
		return *this;
	}

	Bignum & operator /=(SDigit d) {
		BignumAlgorithm::div_sd(m_data, d, m_data);
		return *this;
	}

	Bignum & operator |=(UDigit d) {
		BignumAlgorithm::bor_ud(m_data, d, m_data);
		return *this;
	}

	Bignum & operator |=(SDigit d) {
		BignumAlgorithm::bor_sd(m_data, d, m_data);
		return *this;
	}

	Bignum & operator &=(UDigit d) {
		BignumAlgorithm::band_ud(m_data, d, m_data);
		return *this;
	}

	Bignum & operator &=(SDigit d) {
		BignumAlgorithm::band_sd(m_data, d, m_data);
		return *this;
	}

	Bignum & operator ^=(UDigit d) {
		BignumAlgorithm::bxor_ud(m_data, d, m_data);
		return *this;
	}

	Bignum & operator ^=(SDigit d) {
		BignumAlgorithm::bxor_sd(m_data, d, m_data);
		return *this;
	}

	Bignum & operator<<=(UDigit n) {
		BignumAlgorithm::lsh_ud(m_data, n, m_data);
		return *this;
	}

	Bignum & operator<<=(SDigit n) {
		BignumAlgorithm::lsh_sd(m_data, n, m_data);
		return *this;
	}

	Bignum & operator>>=(UDigit n) {
		BignumAlgorithm::rsh_ud(m_data, n, m_data);
		return *this;
	}

	Bignum & operator>>=(SDigit n) {
		BignumAlgorithm::rsh_sd(m_data, n, m_data);
		return *this;
	}

	Bignum & operator<<=(Bits<UDigit> bn) {
		BignumAlgorithm::lsh_b_ud(m_data, bn.v, m_data);
		return *this;
	}

	Bignum & operator<<=(Bits<SDigit> bn) {
		BignumAlgorithm::lsh_b_sd(m_data, bn.v, m_data);
		return *this;
	}

	Bignum & operator>>=(Bits<UDigit> bn) {
		BignumAlgorithm::rsh_b_ud(m_data, bn.v, m_data);
		return *this;
	}

	Bignum & operator>>=(Bits<SDigit> bn) {
		BignumAlgorithm::rsh_b_sd(m_data, bn.v, m_data);
		return *this;
	}

	Bignum & operator<<=(Digits<UDigit> dn) {
		BignumAlgorithm::lsh_d_ud(m_data, dn.v, m_data);
		return *this;
	}

	Bignum & operator<<=(Digits<SDigit> dn) {
		BignumAlgorithm::lsh_d_sd(m_data, dn.v, m_data);
		return *this;
	}

	Bignum & operator>>=(Digits<UDigit> dn) {
		BignumAlgorithm::rsh_d_ud(m_data, dn.v, m_data);
		return *this;
	}

	Bignum & operator>>=(Digits<SDigit> dn) {
		BignumAlgorithm::rsh_d_sd(m_data, dn.v, m_data);
		return *this;
	}

	UDigit operator%(UDigit d) const {
		return BignumAlgorithm::mod_d(m_data, d);
	}

	Bignum & operator%=(Digit d) {
		return operator=(operator%(d));
	}

	Bignum operator*(Value<2> _dummy) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::mul2(m_data, Z.m_data);
		return Z;
	}

	Bignum operator/(Value<2> _dummy) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::div2(m_data, Z.m_data);
		return Z;
	}

	Bignum & operator*=(Value<2> _dummy) {
		BignumAlgorithm::mul2(m_data, m_data);
		return *this;
	}

	Bignum & operator/=(Value<2> _dummy) {
		BignumAlgorithm::div2(m_data, m_data);
		return *this;
	}

	Digit operator%(Value<2> _dummy) const {
		return operator()(Index(0)) & Digit(1);
	}

	Bignum operator^(Value<2>) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::sqr(m_data, Z.m_data);
		return Z;
	}

	Bignum & operator^=(Value<2>) {
		BignumAlgorithm::sqr(m_data, m_data);
		return *this;
	}

	Bignum operator^(Exponent n) const {
		Bignum Z(not_allocate);
		BignumAlgorithm::power(m_data, n.v, Z.m_data);
		return Z;
	}

	Bignum & operator^=(Exponent n) {
		BignumAlgorithm::power(m_data, n.v, m_data);
		return *this;
	}

public:
	Pair<Bignum, Bignum> div_mod(Bignum const & Y) const {
		Bignum Q, R;
		BignumAlgorithm::div_mod(m_data, Y.m_data, &Q.m_data, &R.m_data);
		return make_pair(move(Q), move(R));
	}

	Pair<Bignum, Digit > div_mod(UDigit d) const {
		Bignum Q(not_allocate);
		auto r = BignumAlgorithm::div_mod_ud(m_data, d, Q.m_data);
		return make_pair(move(Q), r);
	}

	Pair<Bignum, Digit > div_mod(SDigit d) const {
		Bignum Q(not_allocate);
		auto r = BignumAlgorithm::div_mod_sd(m_data, d, Q.m_data);
		return make_pair(move(Q), r);
	}

public:

	Bignum next() const {
		return operator+(Digit(1));
	}

	Bignum succ() const {
		return operator-(Digit(1));
	}

	Bignum & operator++() {
		return operator+=(Digit(1));
	}

	Bignum & operator--() {
		return operator-=(Digit(1));
	}

	Bignum operator++(int) {
		Bignum t(*this);
		operator++();
		return t;
	}

	Bignum operator--(int) {
		Bignum t(*this);
		operator--();
		return t;
	}

public:
	template< typename functor_type >
	Bignum const & times(functor_type functor) const {
		for (Bignum count(ZERO); count < *this; ++count) {
			functor(count);
		}
		return *this;
	}

public:
	std::string inspect() const {
		return BignumAlgorithm::inspect(m_data);
	}

	std::string to_s(Digit base = 10, bool show_plus = false) const {
		return BignumAlgorithm::to_s(m_data, base, show_plus);
	}

	operator std::string() const {
		return to_s();
	}

private:
	Bignum(decltype(not_allocate)) {
		BignumAlgorithm::init(m_data);
	}

	Size m_fix_index(Index index) const noexcept {
		return index < 0 ? length() + index : Size(index);
	}

}; // class Bignum

inline Bignum && operator+(Bignum && X, Bignum const & Y) {
	return move(X += Y);
}

inline Bignum && operator-(Bignum && X, Bignum const & Y) {
	return move(X -= Y);
}

inline Bignum && operator*(Bignum && X, Bignum const & Y) {
	return move(X *= Y);
}

inline Bignum && operator/(Bignum && X, Bignum const & Y) {
	return move(X /= Y);
}

inline Bignum && operator%(Bignum && X, Bignum const & Y) {
	return move(X %= Y);
}

inline Bignum && operator|(Bignum && X, Bignum const & Y) {
	return move(X |= Y);
}

inline Bignum && operator&(Bignum && X, Bignum const & Y) {
	return move(X &= Y);
}

inline Bignum && operator^(Bignum && X, Bignum const & Y) {
	return move(X ^= Y);
}

template< typename TInt >
inline Bignum && operator<<(Bignum && X, TInt n) {
	return move(X <<= n);
}

template< typename TInt >
inline Bignum && operator>>(Bignum && X, TInt n) {
	return move(X >>= n);
}


} // namespace BR
