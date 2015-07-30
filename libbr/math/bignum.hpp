#pragma once

#include <libbr/config.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/math/detail/bignum.hpp>
#include <libbr/exception/index_out_of_range_exception.hpp>
#include <libbr/utility/bit_math.hpp>
#include <libbr/utility/initializer_list.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/pair.hpp>
#include <libbr/memory/detail/pointer_wrapper.hpp>

namespace BR {

class Bignum {
public:
	using Digit  = Detail::Bignum::Digit;
	using DDigit = Detail::Bignum::DDigit;

	using UDigit  = Detail::Bignum::UDigit;
	using SDigit  = Detail::Bignum::SDigit;
	using UDDigit = Detail::Bignum::UDDigit;
	using SDDigit = Detail::Bignum::SDDigit;
	using Size    = Detail::Bignum::Size;
	using Index   = Detail::Bignum::Index;

private:
	struct NotAllocateTag {};

	struct Positive {};
	struct Negative {};
	struct Absolute {};
	struct Complement {};

	template< Digit value >
	struct Value {};

	template< typename TInt > struct Bits   { TInt const v; };
	template< typename TInt > struct Digits { TInt const v; };

	struct Power2 { Digit const v; };

	struct Exponent { Digit const v; };

public:
	constexpr static auto BIT_PER_DIGIT = sizeof(Digit) * BIT_PER_CHAR;

	constexpr static auto RADIX = UDDigit(1) << BIT_PER_DIGIT;

	constexpr static auto positive   = Positive();
	constexpr static auto negative   = Negative();
	constexpr static auto absolute   = Absolute();
	constexpr static auto complement = Complement();

	static Bignum const ZERO;

private:
	constexpr static auto not_allocate_tag = NotAllocateTag();

public:
	template< Digit v >
	static constexpr Value<v> value() {
		return Value<v>{};
	}

	static constexpr Bits  <UDigit> bits  (UDigit n) { return Bits  <UDigit>{n}; }
	static constexpr Bits  <SDigit> bits  (SDigit n) { return Bits  <SDigit>{n}; }
	static constexpr Digits<UDigit> digits(UDigit n) { return Digits<UDigit>{n}; }
	static constexpr Digits<SDigit> digits(SDigit n) { return Digits<SDigit>{n}; }

	static constexpr Power2 power2(Digit n) { return Power2{n}; }

	static constexpr Exponent exponent(Digit n) { return Exponent{n}; }

public:
	Bignum() : Bignum(not_allocate_tag) { Detail::Bignum::set0(m_imp); }

	Bignum(Bignum const & Y) : Bignum(not_allocate_tag) { Detail::Bignum::copy(m_imp, Y.m_imp); }
	Bignum(Bignum      && Y) : Bignum(not_allocate_tag) { Detail::Bignum::swap(m_imp, Y.m_imp); }

	explicit Bignum(  signed char      v) : Bignum(not_allocate_tag) { Detail::Bignum::set_sint(m_imp, v); }
	explicit Bignum(unsigned char      v) : Bignum(not_allocate_tag) { Detail::Bignum::set_uint(m_imp, v); }
	explicit Bignum(  signed short     v) : Bignum(not_allocate_tag) { Detail::Bignum::set_sint(m_imp, v); }
	explicit Bignum(unsigned short     v) : Bignum(not_allocate_tag) { Detail::Bignum::set_uint(m_imp, v); }
	explicit Bignum(  signed int       v) : Bignum(not_allocate_tag) { Detail::Bignum::set_sint(m_imp, v); }
	explicit Bignum(unsigned int       v) : Bignum(not_allocate_tag) { Detail::Bignum::set_uint(m_imp, v); }
	explicit Bignum(  signed long      v) : Bignum(not_allocate_tag) { Detail::Bignum::set_sint(m_imp, v); }
	explicit Bignum(unsigned long      v) : Bignum(not_allocate_tag) { Detail::Bignum::set_uint(m_imp, v); }
	explicit Bignum(  signed long long v) : Bignum(not_allocate_tag) { Detail::Bignum::set_sint(m_imp, v); }
	explicit Bignum(unsigned long long v) : Bignum(not_allocate_tag) { Detail::Bignum::set_uint(m_imp, v); }

	template< Digit v >
	explicit Bignum(Value<v>) : Bignum(not_allocate_tag) { Detail::Bignum::set_d(m_imp, v); }

	Bignum(InitializerList< Digit > L) : Bignum(not_allocate_tag) { Detail::Bignum::copy_list(m_imp, L); }

	Bignum(Power2 n) : Bignum(not_allocate_tag) { Detail::Bignum::set_power2(m_imp, n.v); }

	virtual ~Bignum() { Detail::Bignum::clear(m_imp); }

public:
	Bignum & operator=(Bignum const & Y) { Detail::Bignum::copy(m_imp, Y.m_imp); return *this; }
	Bignum & operator=(Bignum      && Y) { Detail::Bignum::swap(m_imp, Y.m_imp); return *this; }

	Bignum & operator=(  signed char      v) { Detail::Bignum::set_sint(m_imp, v); return *this; }
	Bignum & operator=(unsigned char      v) { Detail::Bignum::set_uint(m_imp, v); return *this; }
	Bignum & operator=(  signed short     v) { Detail::Bignum::set_sint(m_imp, v); return *this; }
	Bignum & operator=(unsigned short     v) { Detail::Bignum::set_uint(m_imp, v); return *this; }
	Bignum & operator=(  signed int       v) { Detail::Bignum::set_sint(m_imp, v); return *this; }
	Bignum & operator=(unsigned int       v) { Detail::Bignum::set_uint(m_imp, v); return *this; }
	Bignum & operator=(  signed long      v) { Detail::Bignum::set_sint(m_imp, v); return *this; }
	Bignum & operator=(unsigned long      v) { Detail::Bignum::set_uint(m_imp, v); return *this; }
	Bignum & operator=(  signed long long v) { Detail::Bignum::set_sint(m_imp, v); return *this; }
	Bignum & operator=(unsigned long long v) { Detail::Bignum::set_uint(m_imp, v); return *this; }

	template< Digit v >
	Bignum & operator=(Value<v>) { Detail::Bignum::set_d(m_imp, v); return *this; }

	Bignum & operator=(InitializerList< Digit > L) { Detail::Bignum::copy_list(m_imp, L); return *this; }

	Bignum & operator=(Power2 n) { Detail::Bignum::set_power2(m_imp, n.v); return *this; }

#if defined(BR_HAS_INT128)
	explicit Bignum(SInt128 v) : Bignum(not_allocate_tag) { Detail::Bignum::set_sint(m_imp, v); }
	explicit Bignum(UInt128 v) : Bignum(not_allocate_tag) { Detail::Bignum::set_uint(m_imp, v); }

	Bignum & operator=(SInt128 v) { Detail::Bignum::set_sint(m_imp, v); return *this; }
	Bignum & operator=(UInt128 v) { Detail::Bignum::set_uint(m_imp, v); return *this; }
#endif

public:
	Sign sign() const noexcept {
		return Detail::Bignum::sign(m_imp);
	}

	Size length() const noexcept {
		return Detail::Bignum::length(m_imp);
	}

	Size capacity() const noexcept {
		return Detail::Bignum::capacity(m_imp);
	}

	Digit const * digits() const noexcept {
		return Detail::Bignum::digits(m_imp);
	}

	Size digit_length() const noexcept {
		return length();
	}

	Size bit_length() const {
		return Detail::Bignum::bit_length(m_imp);
	}

	// get digit at index
	Digit operator()(Index index) const {
		return digits()[m_fix_index(index)];
	}

	Digit digit(Index index) const noexcept(false) {
		auto fixed_index = m_fix_index(index);
		if (fixed_index >= length()) {
			throw IndexOutOfRangeException("BR::Math::Bignum#digit(Index)");
		}
		return operator()(index);
	}

	// get bit at index
	Digit operator[](Index index) const {
		return Detail::Bignum::bit(m_imp, m_fix_index(index));
	}

	Digit bit(Index index) const noexcept(false) {
		auto fixed_index = m_fix_index(index);
		if (fixed_index >= bit_length()) {
			throw IndexOutOfRangeException("BR::Math::Bignum#bit(Index)");
		}
		return operator[](index);
	}

public:
	Bignum & reserve(Size size) { Detail::Bignum::reserve(m_imp, size); return *this; }

	Bignum & swap(Bignum & Y) { Detail::Bignum::swap(m_imp, Y.m_imp); return *this; }

	bool is_pos() const noexcept { return sign() == Sign::ZPOS; }
	bool is_neg() const noexcept { return sign() == Sign::NEG; }

	bool is_even() const noexcept { return operator%(Value<2>()) == 0; }
	bool is_odd () const noexcept { return operator%(Value<2>()) == 1; }

	bool operator!() const noexcept {
		return length() == 1 && digits()[0] == 0;
	}

	explicit operator bool() const noexcept {
		return !operator!();
	}

	// X <=> Y
	Relation compare(Bignum const & Y) const {
		return Detail::Bignum::cmp(m_imp, Y.m_imp);
	}

	bool operator< (Bignum const & Y) const noexcept { return compare(Y) == Relation::LT; }
	bool operator> (Bignum const & Y) const noexcept { return compare(Y) == Relation::GT; }
	bool operator<=(Bignum const & Y) const noexcept { return compare(Y) != Relation::GT; }
	bool operator>=(Bignum const & Y) const noexcept { return compare(Y) != Relation::LT; }
	bool operator==(Bignum const & Y) const noexcept { return compare(Y) == Relation::EQ; }
	bool operator!=(Bignum const & Y) const noexcept { return compare(Y) != Relation::EQ; }

public:
	Bignum & operator=(Positive) noexcept { Detail::Bignum::sign(m_imp) = +sign(); return *this; } // X = +X
	Bignum & operator=(Negative) noexcept { Detail::Bignum::sign(m_imp) = -sign(); return *this; } // X = -X
	Bignum & operator=(Absolute) noexcept { Detail::Bignum::sign(m_imp) = Sign::ZPOS; return *this; } // X = |X|

	// X = ~X
	Bignum & operator=(Complement) {
		Detail::Bignum::conj(m_imp);
		return *this;
	}

	Bignum operator+() const { Bignum Z(*this); return Z.operator=(positive); }
	Bignum operator-() const { Bignum Z(*this); return Z.operator=(negative); }
	Bignum abs      () const { Bignum Z(*this); return Z.operator=(absolute); }
	Bignum operator~() const { Bignum Z(*this); return Z.operator=(complement); }

public:
	Bignum operator+(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::add (m_imp, Y.m_imp, Z.m_imp); return Z; }
	Bignum operator-(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::sub (m_imp, Y.m_imp, Z.m_imp); return Z; }
	Bignum operator*(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::mul (m_imp, Y.m_imp, Z.m_imp); return Z; }
	Bignum operator/(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::div (m_imp, Y.m_imp, Z.m_imp); return Z; }
	Bignum operator%(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::mod (m_imp, Y.m_imp, Z.m_imp); return Z; }
	Bignum operator|(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::bor (m_imp, Y.m_imp, Z.m_imp); return Z; }
	Bignum operator&(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::band(m_imp, Y.m_imp, Z.m_imp); return Z; }
	Bignum operator^(Bignum const & Y) const { Bignum Z(not_allocate_tag); Detail::Bignum::bxor(m_imp, Y.m_imp, Z.m_imp); return Z; }

	Bignum & operator+=(Bignum const & Y) { Detail::Bignum::add (m_imp, Y.m_imp, m_imp); return *this; }
	Bignum & operator-=(Bignum const & Y) { Detail::Bignum::sub (m_imp, Y.m_imp, m_imp); return *this; }
	Bignum & operator*=(Bignum const & Y) { Detail::Bignum::mul (m_imp, Y.m_imp, m_imp); return *this; }
	Bignum & operator/=(Bignum const & Y) { Detail::Bignum::div (m_imp, Y.m_imp, m_imp); return *this; }
	Bignum & operator%=(Bignum const & Y) { Detail::Bignum::mod (m_imp, Y.m_imp, m_imp); return *this; }
	Bignum & operator|=(Bignum const & Y) { Detail::Bignum::bor (m_imp, Y.m_imp, m_imp); return *this; }
	Bignum & operator&=(Bignum const & Y) { Detail::Bignum::band(m_imp, Y.m_imp, m_imp); return *this; }
	Bignum & operator^=(Bignum const & Y) { Detail::Bignum::bxor(m_imp, Y.m_imp, m_imp); return *this; }

public:
	Bignum operator+ (       UDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::add_ud  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator- (       UDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::sub_ud  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator* (       UDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::mul_ud  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator/ (       UDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::div_ud  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator| (       UDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::bor_ud  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator& (       UDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::band_ud (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator^ (       UDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::bxor_ud (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator<<(       UDigit   n) const { Bignum Z(not_allocate_tag); Detail::Bignum::lsh_ud  (m_imp,    n, Z.m_imp); return Z; }
	Bignum operator>>(       UDigit   n) const { Bignum Z(not_allocate_tag); Detail::Bignum::rsh_ud  (m_imp,    n, Z.m_imp); return Z; }
	Bignum operator<<(Bits  <UDigit> bn) const { Bignum Z(not_allocate_tag); Detail::Bignum::lsh_b_ud(m_imp, bn.v, Z.m_imp); return Z; }
	Bignum operator>>(Bits  <UDigit> bn) const { Bignum Z(not_allocate_tag); Detail::Bignum::rsh_b_ud(m_imp, bn.v, Z.m_imp); return Z; }
	Bignum operator<<(Digits<UDigit> dn) const { Bignum Z(not_allocate_tag); Detail::Bignum::lsh_d_ud(m_imp, dn.v, Z.m_imp); return Z; }
	Bignum operator>>(Digits<UDigit> dn) const { Bignum Z(not_allocate_tag); Detail::Bignum::rsh_d_ud(m_imp, dn.v, Z.m_imp); return Z; }

	Bignum operator+ (       SDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::add_sd  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator- (       SDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::sub_sd  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator* (       SDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::mul_sd  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator/ (       SDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::div_sd  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator| (       SDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::bor_sd  (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator& (       SDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::band_sd (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator^ (       SDigit   d) const { Bignum Z(not_allocate_tag); Detail::Bignum::bxor_sd (m_imp,    d, Z.m_imp); return Z; }
	Bignum operator<<(       SDigit   n) const { Bignum Z(not_allocate_tag); Detail::Bignum::lsh_sd  (m_imp,    n, Z.m_imp); return Z; }
	Bignum operator>>(       SDigit   n) const { Bignum Z(not_allocate_tag); Detail::Bignum::rsh_sd  (m_imp,    n, Z.m_imp); return Z; }
	Bignum operator<<(Bits  <SDigit> bn) const { Bignum Z(not_allocate_tag); Detail::Bignum::lsh_b_sd(m_imp, bn.v, Z.m_imp); return Z; }
	Bignum operator>>(Bits  <SDigit> bn) const { Bignum Z(not_allocate_tag); Detail::Bignum::rsh_b_sd(m_imp, bn.v, Z.m_imp); return Z; }
	Bignum operator<<(Digits<SDigit> dn) const { Bignum Z(not_allocate_tag); Detail::Bignum::lsh_d_sd(m_imp, dn.v, Z.m_imp); return Z; }
	Bignum operator>>(Digits<SDigit> dn) const { Bignum Z(not_allocate_tag); Detail::Bignum::rsh_d_sd(m_imp, dn.v, Z.m_imp); return Z; }

	Bignum & operator +=(       UDigit   d) { Detail::Bignum::add_ud  (m_imp,    d, m_imp); return *this; }
	Bignum & operator -=(       UDigit   d) { Detail::Bignum::sub_ud  (m_imp,    d, m_imp); return *this; }
	Bignum & operator *=(       UDigit   d) { Detail::Bignum::mul_ud  (m_imp,    d, m_imp); return *this; }
	Bignum & operator /=(       UDigit   d) { Detail::Bignum::div_ud  (m_imp,    d, m_imp); return *this; }
	Bignum & operator |=(       UDigit   d) { Detail::Bignum::bor_ud  (m_imp,    d, m_imp); return *this; }
	Bignum & operator &=(       UDigit   d) { Detail::Bignum::band_ud (m_imp,    d, m_imp); return *this; }
	Bignum & operator ^=(       UDigit   d) { Detail::Bignum::bxor_ud (m_imp,    d, m_imp); return *this; }
	Bignum & operator<<=(       UDigit   n) { Detail::Bignum::lsh_ud  (m_imp,    n, m_imp); return *this; }
	Bignum & operator>>=(       UDigit   n) { Detail::Bignum::rsh_ud  (m_imp,    n, m_imp); return *this; }
	Bignum & operator<<=(Bits  <UDigit> bn) { Detail::Bignum::lsh_b_ud(m_imp, bn.v, m_imp); return *this; }
	Bignum & operator>>=(Bits  <UDigit> bn) { Detail::Bignum::rsh_b_ud(m_imp, bn.v, m_imp); return *this; }
	Bignum & operator<<=(Digits<UDigit> dn) { Detail::Bignum::lsh_d_ud(m_imp, dn.v, m_imp); return *this; }
	Bignum & operator>>=(Digits<UDigit> dn) { Detail::Bignum::rsh_d_ud(m_imp, dn.v, m_imp); return *this; }

	Bignum & operator+= (       SDigit   d) { Detail::Bignum::add_sd  (m_imp,    d, m_imp); return *this; }
	Bignum & operator-= (       SDigit   d) { Detail::Bignum::sub_sd  (m_imp,    d, m_imp); return *this; }
	Bignum & operator*= (       SDigit   d) { Detail::Bignum::mul_sd  (m_imp,    d, m_imp); return *this; }
	Bignum & operator/= (       SDigit   d) { Detail::Bignum::div_sd  (m_imp,    d, m_imp); return *this; }
	Bignum & operator|= (       SDigit   d) { Detail::Bignum::bor_sd  (m_imp,    d, m_imp); return *this; }
	Bignum & operator&= (       SDigit   d) { Detail::Bignum::band_sd (m_imp,    d, m_imp); return *this; }
	Bignum & operator^= (       SDigit   d) { Detail::Bignum::bxor_sd (m_imp,    d, m_imp); return *this; }
	Bignum & operator<<=(       SDigit   n) { Detail::Bignum::lsh_sd  (m_imp,    n, m_imp); return *this; }
	Bignum & operator>>=(       SDigit   n) { Detail::Bignum::rsh_sd  (m_imp,    n, m_imp); return *this; }
	Bignum & operator<<=(Bits  <SDigit> bn) { Detail::Bignum::lsh_b_sd(m_imp, bn.v, m_imp); return *this; }
	Bignum & operator>>=(Bits  <SDigit> bn) { Detail::Bignum::rsh_b_sd(m_imp, bn.v, m_imp); return *this; }
	Bignum & operator<<=(Digits<SDigit> dn) { Detail::Bignum::lsh_d_sd(m_imp, dn.v, m_imp); return *this; }
	Bignum & operator>>=(Digits<SDigit> dn) { Detail::Bignum::rsh_d_sd(m_imp, dn.v, m_imp); return *this; }

	UDigit operator%(UDigit d) const {
		return Detail::Bignum::mod_d(m_imp, d);
	}

	Bignum & operator%=(Digit d) {
		return operator=(operator%(d));
	}

	Bignum operator*(Value<2>) const { Bignum Z(not_allocate_tag); Detail::Bignum::mul2(m_imp, Z.m_imp); return Z; }
	Bignum operator/(Value<2>) const { Bignum Z(not_allocate_tag); Detail::Bignum::div2(m_imp, Z.m_imp); return Z; }

	Bignum & operator*=(Value<2>) { Detail::Bignum::mul2(m_imp, m_imp); return *this; }
	Bignum & operator/=(Value<2>) { Detail::Bignum::div2(m_imp, m_imp); return *this; }

	Digit operator%(Value<2>) const { return operator()(0) & Digit(1); } // X % 2

	Bignum operator^(Value<2>) const {
		Bignum Z(not_allocate_tag);
		Detail::Bignum::sqr(m_imp, Z.m_imp);
		return Z;
	}

	Bignum & operator^=(Value<2>) {
		Detail::Bignum::sqr(m_imp, m_imp);
		return *this;
	}

	Bignum operator^(Exponent n) const {
		Bignum Z(not_allocate_tag);
		Detail::Bignum::power(m_imp, n.v, Z.m_imp);
		return Z;
	}

	Bignum & operator^=(Exponent n) {
		Detail::Bignum::power(m_imp, n.v, m_imp);
		return *this;
	}

public:

	Bignum next() const { return operator+(Digit(1)); } // X + 1
	Bignum succ() const { return operator-(Digit(1)); } // X - 1

	Bignum & operator++() { return operator+=(Digit(1)); }
	Bignum & operator--() { return operator-=(Digit(1)); }

	Bignum operator++(int) { Bignum t(*this); operator++(); return t; }
	Bignum operator--(int) { Bignum t(*this); operator--(); return t; }

public:

	Pair< Bignum, Bignum > div_mod(Bignum const & Y) const {
		Bignum Q, R;
		Detail::Bignum::div_mod(m_imp, Y.m_imp, &Q.m_imp, &R.m_imp);
		return make_pair(move(Q), move(R));
	}

	Pair< Bignum, Digit > div_mod(SDigit d) const {
		Bignum Q(not_allocate_tag);
		auto r = Detail::Bignum::div_mod_sd(m_imp, d, Q.m_imp);
		return make_pair(move(Q), r);
	}

	Pair< Bignum, Digit > div_mod(UDigit d) const {
		Bignum Q(not_allocate_tag);
		auto r = Detail::Bignum::div_mod_ud(m_imp, d, Q.m_imp);
		return make_pair(move(Q), r);
	}

public:
	struct Reducer;

	Reducer to_reducer() const;

	Bignum operator/(Reducer const &) const;

	Bignum & operator/=(Reducer const &);

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
		return Detail::Bignum::inspect(m_imp);
	}

	std::string to_s(Digit base = 10, bool show_plus = false) const {
		return Detail::Bignum::to_s(m_imp, base, show_plus);
	}

	operator std::string() const {
		return to_s();
	}

private:
	Bignum(NotAllocateTag) { Detail::Bignum::init(m_imp); }

	Size m_fix_index(Index index) const noexcept { return index < 0 ? length() + index : static_cast<Size>(index); }

	Detail::Bignum::Imp m_imp;
};

inline Bignum && operator+(Bignum && X, Bignum const & Y) { return move(X += Y); }
inline Bignum && operator-(Bignum && X, Bignum const & Y) { return move(X -= Y); }
inline Bignum && operator*(Bignum && X, Bignum const & Y) { return move(X *= Y); }
inline Bignum && operator/(Bignum && X, Bignum const & Y) { return move(X /= Y); }
inline Bignum && operator%(Bignum && X, Bignum const & Y) { return move(X %= Y); }
inline Bignum && operator|(Bignum && X, Bignum const & Y) { return move(X |= Y); }
inline Bignum && operator&(Bignum && X, Bignum const & Y) { return move(X &= Y); }
inline Bignum && operator^(Bignum && X, Bignum const & Y) { return move(X ^= Y); }

template< typename TInt >
inline Bignum && operator<<(Bignum && X, TInt n) { return move(X <<= n); }

template< typename TInt >
inline Bignum && operator>>(Bignum && X, TInt n) { return move(X >>= n); }

namespace BignumHelper {

constexpr static auto positive   = Bignum::positive;
constexpr static auto negative   = Bignum::negative;
constexpr static auto absolute   = Bignum::absolute;
constexpr static auto complement = Bignum::complement;

template< Bignum::Digit v >
constexpr auto value() -> decltype(Bignum::value<v>()) {
	return Bignum::value<v>();
}

template< typename T >
constexpr auto bits(T n) -> decltype(Bignum::bits(n)) {
	return Bignum::bits(n);
}

template< typename T >
constexpr auto digits(T n) -> decltype(Bignum::digits(n)) {
	return Bignum::digits(n);
}

template< Bignum::Digit v >
constexpr auto power2(Bignum::Digit n) -> decltype(Bignum::power2(n)) {
	return Bignum::power2(n);
}

constexpr auto exponent(Bignum::Digit n) -> decltype(Bignum::exponent(n)) {
	return Bignum::exponent(n);
}

} // namespace BignumHelper

} // namespace BR
