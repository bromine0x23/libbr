#pragma once

#include <libbr/config.hpp>

#include <libbr/assert/assert.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/exception/index_out_of_range_exception.hpp>
#include <libbr/exception/invalid_argument_exception.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/make_signed.hpp>
#include <libbr/type_operate/make_unsigned.hpp>
#include <libbr/utility/bit_math.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/pair.hpp>
#include <libbr/utility/initializer_list.hpp>
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

public:
	constexpr static auto BITS_PER_DIGIT = sizeof(Digit) * BIT_PER_CHAR;

	constexpr static auto RADIX = UDDigit(1) << BITS_PER_DIGIT;

public:
	static Bignum const ZERO;

public:
	struct Power2Tag {};

	constexpr static auto power_2_tag = Power2Tag();

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

	Bignum(Power2Tag, Size n);

	~Bignum();

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
		return digit_length() * BITS_PER_DIGIT - count_leading_zeros(digits()[digit_length() - 1]);
	}

	// get digit at index
	Digit operator()(Index index) const {
		return digits()[m_normalize_index(index)];
	}

	Digit digit(Index index) const {
		index = m_normalize_index(index);
		if (!(Size(index) < length())) {
			throw IndexOutOfRangeException("BR::Math::Bignum#digit(Index)");
		}
		return operator()(index);
	}

	// get bit at index
	Digit operator[](Index index) const {
		index = m_normalize_index(index);
		return (digit(index / BITS_PER_DIGIT) >> (index & (BITS_PER_DIGIT - 1))) & 1;
	}

	Digit bit(Index index) const {
		index = m_normalize_index(index);
		if (!(Size(index) < bit_length())) {
			throw IndexOutOfRangeException("BR::Math::Bignum#bit(Index)");
		}
		return operator[](index);
	}

public:
	Bignum & reserve(Size size);

	Bignum & swap(Bignum & Y);

	Bignum & set0();

	bool is_pos() const noexcept { return sign() == Sign::POS; }
	bool is_neg() const noexcept { return sign() == Sign::NEG; }

	bool is_even() const noexcept { return mod2() == 0; }
	bool is_odd () const noexcept { return mod2() == 1; }

	bool operator!() const noexcept {
		return length() == 1 && digits()[0] == 0;
	}

	explicit operator bool() const noexcept {
		return !*this;
	}

	Relation cmp(Bignum const & Y) const; // X <=> Y

	bool operator< (Bignum const & Y) const noexcept { return cmp(Y) == Relation::LT; }
	bool operator> (Bignum const & Y) const noexcept { return cmp(Y) == Relation::GT; }
	bool operator<=(Bignum const & Y) const noexcept { return cmp(Y) != Relation::GT; }
	bool operator>=(Bignum const & Y) const noexcept { return cmp(Y) != Relation::LT; }
	bool operator==(Bignum const & Y) const noexcept { return cmp(Y) == Relation::EQ; }
	bool operator!=(Bignum const & Y) const noexcept { return cmp(Y) != Relation::EQ; }

public:

	Bignum & set_pos () noexcept { m_imp.sign = +sign(); return *this; } // X = +X
	Bignum & set_neg () noexcept { m_imp.sign = -sign(); return *this; } // X = -X
	Bignum & set_conj();  // X = ~X
	Bignum & set_abs () noexcept { m_imp.sign = Sign::POS; return *this; } // X = |X|

	Bignum operator+() const { Bignum Z(*this); return Z.set_pos (); }
	Bignum operator-() const { Bignum Z(*this); return Z.set_neg (); }
	Bignum operator~() const { Bignum Z(*this); return Z.set_conj(); }
	Bignum abs      () const { Bignum Z(*this); return Z.set_abs (); }

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

	Bignum operator+ (UDigit d) const;
	Bignum operator- (UDigit d) const;
	Bignum operator* (UDigit d) const;
	Bignum operator/ (UDigit d) const;
	Bignum operator| (UDigit d) const;
	Bignum operator& (UDigit d) const;
	Bignum operator^ (UDigit d) const;

	Bignum operator+ (SDigit d) const;
	Bignum operator- (SDigit d) const;
	Bignum operator* (SDigit d) const;
	Bignum operator/ (SDigit d) const;
	Bignum operator| (SDigit d) const;
	Bignum operator& (SDigit d) const;
	Bignum operator^ (SDigit d) const;

	Bignum & operator+= (UDigit d);
	Bignum & operator-= (UDigit d);
	Bignum & operator*= (UDigit d);
	Bignum & operator/= (UDigit d);
	Bignum & operator|= (UDigit d);
	Bignum & operator&= (UDigit d);
	Bignum & operator^= (UDigit d);

	Bignum & operator+= (SDigit d);
	Bignum & operator-= (SDigit d);
	Bignum & operator*= (SDigit d);
	Bignum & operator/= (SDigit d);
	Bignum & operator|= (SDigit d);
	Bignum & operator&= (SDigit d);
	Bignum & operator^= (SDigit d);

	UDigit operator%(UDigit d) const;

	Bignum & operator%=(Digit d) {
		return operator=(operator%(d));
	}

public:

	Bignum operator<<(UDigit n) const;
	Bignum operator>>(UDigit n) const;

	Bignum operator<<(SDigit n) const;
	Bignum operator>>(SDigit n) const;

	Bignum & operator<<=(UDigit n);
	Bignum & operator>>=(UDigit n);

	Bignum & operator<<=(SDigit n);
	Bignum & operator>>=(SDigit n);

	template< typename TInt >
	struct BitWidth { TInt v; };

	Bignum operator<<(BitWidth<UDigit> n) const;
	Bignum operator>>(BitWidth<UDigit> n) const;

	Bignum operator<<(BitWidth<SDigit> n) const;
	Bignum operator>>(BitWidth<SDigit> n) const;

	Bignum & operator<<=(BitWidth<UDigit> n);
	Bignum & operator>>=(BitWidth<UDigit> n);

	Bignum & operator<<=(BitWidth<SDigit> n);
	Bignum & operator>>=(BitWidth<SDigit> n);

/*
	Bignum lshb(Digit bn) const; // X << n, n < BIT_PER_DIGIT
	Bignum rshb(Digit bn) const; // X << n, n < BIT_PER_DIGIT
	Bignum lshd(Digit dn) const; // X << (dn * BIT_PER_DIGIT)
	Bignum rshd(Digit dn) const; // X >> (dn * BIT_PER_DIGIT)

	Bignum & lshb_by(Digit bn); // X <<= n, n < BIT_PER_DIGIT
	Bignum & rshb_by(Digit bn); // X >>= n, n < BIT_PER_DIGIT
	Bignum & lshd_by(Digit dn); // X <<= (dn * BIT_PER_DIGIT)
	Bignum & rshd_by(Digit dn); // X >>= (dn * BIT_PER_DIGIT)
 */

public:

	Bignum next() const { return operator+(Digit(1)); } // X + 1
	Bignum succ() const { return operator-(Digit(1)); } // X - 1

	Bignum & operator++() { return operator+=(Digit(1)); }
	Bignum & operator--() { return operator-=(Digit(1)); }

	Bignum operator++(int) { Bignum t(*this); operator++(); return t; }
	Bignum operator--(int) { Bignum t(*this); operator--(); return t; }

public:

	Bignum mul2() const; // X * 2
	Bignum div2() const; // X / 2

	Bignum & mul_by2(); // X *= 2
	Bignum & div_by2(); // X /= 2

	Digit mod2() const { return operator()(0) & Digit(1); } // X % 2

public:

	Bignum sqr() const; // X^2

	Bignum & set_sqr(); // X = X^2

public:

	Pair< Bignum, Bignum > div_mod(Bignum const & Y) const;

	Pair< Bignum, Digit > div_mod(Digit d) const;

public:
	struct Reducer;

	Reducer to_reducer() const;

	Bignum reduce(Reducer const &) const;

	Bignum &reduce_by(Reducer const &);

public:
	Bignum pow(Digit d) const;

	Bignum & pow_by(Digit d);

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

public:

private:
	Index m_normalize_index(Index index) const noexcept { return index < 0 ? length() + index : index; }

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

} // namespace BR
