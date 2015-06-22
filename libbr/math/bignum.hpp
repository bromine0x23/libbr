#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/exception/index_out_of_range_exception.hpp>
#include <libbr/type_operate/make_signed.hpp>
#include <libbr/type_operate/make_unsigned.hpp>
#include <libbr/utility/bit_math.hpp>
#include <libbr/utility/initializer_list.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/pair.hpp>
#include <libbr/utility/swap.hpp>
#include <string>

namespace BR {

class Bignum {
public:
	using Digit  = UInt32;
	using DDigit = UInt64;

	using UDigit  = MakeUnsigned<Digit>;
	using SDigit  = MakeSigned  <Digit>;
	using UDDigit = MakeUnsigned<DDigit>;
	using SDDigit = MakeSigned  <DDigit>;
	using Index   = MakeSigned  <Size>;

private:
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
	Bignum();

	Bignum(Bignum const & Y);
	Bignum(Bignum      && Y);

	explicit Bignum(  signed char      v);
	explicit Bignum(unsigned char      v);
	explicit Bignum(  signed short     v);
	explicit Bignum(unsigned short     v);
	explicit Bignum(  signed int       v);
	explicit Bignum(unsigned int       v);
	explicit Bignum(  signed long      v);
	explicit Bignum(unsigned long      v);
	explicit Bignum(  signed long long v);
	explicit Bignum(unsigned long long v);

	Bignum(InitializerList< Digit >);

	Bignum(Power2 n);

	virtual ~Bignum();

public:
	Bignum & operator=(Bignum const & Y);
	Bignum & operator=(Bignum      && Y);

	Bignum & operator=(  signed char      v);
	Bignum & operator=(unsigned char      v);
	Bignum & operator=(  signed short     v);
	Bignum & operator=(unsigned short     v);
	Bignum & operator=(  signed int       v);
	Bignum & operator=(unsigned int       v);
	Bignum & operator=(  signed long      v);
	Bignum & operator=(unsigned long      v);
	Bignum & operator=(  signed long long v);
	Bignum & operator=(unsigned long long v);

	Bignum & operator=(InitializerList< Digit >);

	Bignum & operator=(Power2 n);

#if defined(BR_HAS_INT128)
	explicit Bignum(UInt128 v);
	explicit Bignum(SInt128 v);

	Bignum & operator=(UInt128 v);
	Bignum & operator=(SInt128 v);
#endif

public:
	Sign sign() const noexcept {
		return m_imp.sign;
	}

	Size length() const noexcept {
		return m_imp.length;
	}

	Size capacity() const noexcept {
		return m_imp.capacity;
	}

	Digit const * digits() const noexcept {
		return m_imp.digits;
	}

	Size digit_length() const noexcept {
		return length();
	}

	Size bit_length() const noexcept {
		return digit_length() * BIT_PER_DIGIT - count_leading_zeros(digits()[digit_length() - 1]);
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
		auto fixed_index = m_fix_index(index);
		return (digit(fixed_index / BIT_PER_DIGIT) >> (fixed_index & (BIT_PER_DIGIT - 1))) & 1;
	}

	Digit bit(Index index) const noexcept(false) {
		auto fixed_index = m_fix_index(index);
		if (fixed_index >= bit_length()) {
			throw IndexOutOfRangeException("BR::Math::Bignum#bit(Index)");
		}
		return operator[](index);
	}

public:
	Bignum & reserve(Size size);

	Bignum & swap(Bignum & Y);

	Bignum & operator=(Value<0>);

	bool is_pos() const noexcept { return sign() == Sign::POS; }
	bool is_neg() const noexcept { return sign() == Sign::NEG; }

	bool is_even() const noexcept { return operator%(Value<2>()) == 0; }
	bool is_odd () const noexcept { return operator%(Value<2>()) == 1; }

	bool operator!() const noexcept {
		return length() == 1 && digits()[0] == 0;
	}

	explicit operator bool() const noexcept {
		return !operator!();
	}

	Relation compare(Bignum const & Y) const; // X <=> Y

	bool operator< (Bignum const & Y) const noexcept { return compare(Y) == Relation::LT; }
	bool operator> (Bignum const & Y) const noexcept { return compare(Y) == Relation::GT; }
	bool operator<=(Bignum const & Y) const noexcept { return compare(Y) != Relation::GT; }
	bool operator>=(Bignum const & Y) const noexcept { return compare(Y) != Relation::LT; }
	bool operator==(Bignum const & Y) const noexcept { return compare(Y) == Relation::EQ; }
	bool operator!=(Bignum const & Y) const noexcept { return compare(Y) != Relation::EQ; }

public:
	Bignum & operator=(Positive) noexcept { m_imp.sign = +sign(); return *this; } // X = +X
	Bignum & operator=(Negative) noexcept { m_imp.sign = -sign(); return *this; } // X = -X
	Bignum & operator=(Absolute) noexcept { m_imp.sign = Sign::POS; return *this; } // X = |X|
	Bignum & operator=(Complement);  // X = ~X

	Bignum operator+() const { Bignum Z(*this); return Z.operator=(positive); }
	Bignum operator-() const { Bignum Z(*this); return Z.operator=(negative); }
	Bignum abs      () const { Bignum Z(*this); return Z.operator=(absolute); }
	Bignum operator~() const { Bignum Z(*this); return Z.operator=(complement); }

public:
	Bignum operator+(Bignum const & Y) const;
	Bignum operator-(Bignum const & Y) const;
	Bignum operator*(Bignum const & Y) const;
	Bignum operator/(Bignum const & Y) const;
	Bignum operator%(Bignum const & Y) const;
	Bignum operator|(Bignum const & Y) const;
	Bignum operator&(Bignum const & Y) const;
	Bignum operator^(Bignum const & Y) const;

	Bignum & operator+=(Bignum const & Y);
	Bignum & operator-=(Bignum const & Y);
	Bignum & operator*=(Bignum const & Y);
	Bignum & operator/=(Bignum const & Y);
	Bignum & operator%=(Bignum const & Y);
	Bignum & operator|=(Bignum const & Y);
	Bignum & operator&=(Bignum const & Y);
	Bignum & operator^=(Bignum const & Y);

public:
	Bignum operator+ (       UDigit   d) const;
	Bignum operator- (       UDigit   d) const;
	Bignum operator* (       UDigit   d) const;
	Bignum operator/ (       UDigit   d) const;
	Bignum operator| (       UDigit   d) const;
	Bignum operator& (       UDigit   d) const;
	Bignum operator^ (       UDigit   d) const;
	Bignum operator<<(       UDigit   n) const;
	Bignum operator>>(       UDigit   n) const;
	Bignum operator<<(Bits  <UDigit> bn) const;
	Bignum operator>>(Bits  <UDigit> bn) const;
	Bignum operator<<(Digits<UDigit> dn) const;
	Bignum operator>>(Digits<UDigit> dn) const;

	Bignum operator+ (       SDigit   d) const;
	Bignum operator- (       SDigit   d) const;
	Bignum operator* (       SDigit   d) const;
	Bignum operator/ (       SDigit   d) const;
	Bignum operator| (       SDigit   d) const;
	Bignum operator& (       SDigit   d) const;
	Bignum operator^ (       SDigit   d) const;
	Bignum operator<<(       SDigit   n) const;
	Bignum operator>>(       SDigit   n) const;
	Bignum operator<<(Bits  <SDigit> bn) const;
	Bignum operator>>(Bits  <SDigit> bn) const;
	Bignum operator<<(Digits<SDigit> dn) const;
	Bignum operator>>(Digits<SDigit> dn) const;

	Bignum & operator +=(       UDigit   d);
	Bignum & operator -=(       UDigit   d);
	Bignum & operator *=(       UDigit   d);
	Bignum & operator /=(       UDigit   d);
	Bignum & operator |=(       UDigit   d);
	Bignum & operator &=(       UDigit   d);
	Bignum & operator ^=(       UDigit   d);
	Bignum & operator<<=(       UDigit   n);
	Bignum & operator>>=(       UDigit   n);
	Bignum & operator<<=(Bits  <UDigit> bn);
	Bignum & operator>>=(Bits  <UDigit> bn);
	Bignum & operator<<=(Digits<UDigit> dn);
	Bignum & operator>>=(Digits<UDigit> dn);

	Bignum & operator +=(       SDigit   d);
	Bignum & operator -=(       SDigit   d);
	Bignum & operator *=(       SDigit   d);
	Bignum & operator /=(       SDigit   d);
	Bignum & operator |=(       SDigit   d);
	Bignum & operator &=(       SDigit   d);
	Bignum & operator ^=(       SDigit   d);
	Bignum & operator<<=(       SDigit   n);
	Bignum & operator>>=(       SDigit   n);
	Bignum & operator<<=(Bits  <SDigit> bn);
	Bignum & operator>>=(Bits  <SDigit> bn);
	Bignum & operator<<=(Digits<SDigit> dn);
	Bignum & operator>>=(Digits<SDigit> dn);

	UDigit operator%(UDigit d) const;

	Bignum & operator%=(Digit d) {
		return operator=(operator%(d));
	}

	Bignum operator*(Value<2>) const; // X * 2
	Bignum operator/(Value<2>) const; // X / 2

	Bignum & operator*=(Value<2>); // X *= 2
	Bignum & operator/=(Value<2>); // X /= 2

	Digit operator%(Value<2>) const { return operator()(0) & Digit(1); } // X % 2

	Bignum operator^(Value<2>) const; // X ^ 2 === X * X

	Bignum & operator^=(Value<2>); // X = X ^ 2

	Bignum operator^(Exponent n) const; // X ^ n

	Bignum & operator^=(Exponent n); // X = X ^ n

public:

	Bignum next() const { return operator+(Digit(1)); } // X + 1
	Bignum succ() const { return operator-(Digit(1)); } // X - 1

	Bignum & operator++() { return operator+=(Digit(1)); }
	Bignum & operator--() { return operator-=(Digit(1)); }

	Bignum operator++(int) { Bignum t(*this); operator++(); return t; }
	Bignum operator--(int) { Bignum t(*this); operator--(); return t; }

public:

	Pair< Bignum, Bignum > div_mod(Bignum const & Y) const;

	Pair< Bignum, Digit > div_mod(Digit d) const;

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
	std::string inspect() const;

	std::string to_s(Digit base = 10, bool show_plus = false) const;

	operator std::string() const {
		return to_s();
	}

private:
	Size m_fix_index(Index index) const noexcept { return index < 0 ? length() + index : static_cast<Size>(index); }

private:
	struct NotAllocateTag {};

	constexpr static auto not_allocate_tag = NotAllocateTag();

	Bignum(NotAllocateTag);

	struct {
		Sign sign;
		Size length;
		Size capacity;
		Digit *digits;
	} m_imp;
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
