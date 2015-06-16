#pragma once

#include <libbr/config.hpp>

#include <libbr/assert/assert.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/exception/index_out_of_range_exception.hpp>
#include <libbr/exception/invalid_argument_exception.hpp>
#include <libbr/type_operate/make_signed.hpp>
#include <libbr/type_operate/make_unsigned.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/pair.hpp>
#include <string>

namespace BR {
namespace Math {

class Bignum {
public:
	enum class Sign {
		NEG = false,
		POS = true,
	};

	friend inline Sign operator+(Sign sign) {
		return sign;
	}

	friend inline Sign operator-(Sign sign) {
		switch (sign) {
			case Sign::POS:
				return Sign::NEG;
			case Sign::NEG:
				return Sign::POS;
		}
	}

	friend inline Sign operator~(Sign sign) {
		return -sign;
	}

	friend inline Sign operator*(Sign x, Sign y) {
		return (x == y) ? Sign::POS : Sign::NEG;
	}

	friend inline char to_c(Sign s) {
		switch (s) {
			case Sign::POS:
				return '+';
			case Sign::NEG:
				return '-';
		}
	}

public:

	constexpr static auto BITS_PER_DIGIT = Size(32);

	using Digit  = UInt32;
	using DDigit = UInt64;

	using UDigit  = TypeOperate::MakeUnsigned<Digit>;
	using SDigit  = TypeOperate::MakeSigned  <Digit>;
	using UDDigit = TypeOperate::MakeUnsigned<DDigit>;
	using SDDigit = TypeOperate::MakeSigned  <DDigit>;
	using UIndex  = TypeOperate::MakeUnsigned<Size>;
	using SIndex  = TypeOperate::MakeSigned  <Size>;

public:
	constexpr static auto RADIX = UDDigit(1) << BITS_PER_DIGIT;

public:
	static Bignum const ZERO;

public:
	struct Power2Tag {};

	constexpr static auto power_2_tag = Power2Tag();

public:
	Bignum();

	Bignum(Bignum const & Y);

	Bignum(Bignum && Y);

	explicit Bignum(UDigit ud);

	explicit Bignum(SDigit sd);

	Bignum(std::initializer_list< Digit >);

	Bignum(Power2Tag, Size n);

	~Bignum();

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

	Size bit_length() const;

	Digit digit(UIndex index) const {
		if (index < length()) {
			return operator()(index);
		} else {
			throw Exception::IndexOutOfRangeException("BR::Math::Bignum#digit(UIndex)");
		}
	}

	Digit digit(SIndex index) const {
		return digit(static_cast<UIndex>(index < 0 ? ~index : index));
	}

	Digit bit(UIndex index) const {
		if (index < bit_length()) {
			return operator[](index);
		} else {
			throw Exception::IndexOutOfRangeException("BR::Math::Bignum#bit(UIndex)");
		}
	}

	Digit bit(SIndex index) const {
		return bit(static_cast<UIndex>(index < 0 ? ~index : index));
	}

public:
	Bignum & reserve(Size size);

	Bignum & swap(Bignum & Y);

	Bignum & assign(Bignum const & Y);

	Bignum & assign(Bignum && Y);

	Bignum & assign(UDigit ud);

	Bignum & assign(SDigit sd);

	Bignum & assign(std::initializer_list< Digit >);

	Bignum & set0();

	bool is_pos() const { return sign() == Sign::POS; }

	bool is_neg() const { return sign() == Sign::NEG; }

	bool is0() const;

	bool is_even() const { return mod2() == 0; }

	bool is_odd() const { return mod2() == 1; }

	Relation cmp(Bignum const & Y) const; // X <=> Y

	bool is_lt(Bignum const & Y) const { return cmp(Y) == Relation::LT; } // X <  Y
	bool is_gt(Bignum const & Y) const { return cmp(Y) == Relation::GT; } // X >  Y
	bool is_le(Bignum const & Y) const { return cmp(Y) != Relation::GT; } // X <= Y
	bool is_ge(Bignum const & Y) const { return cmp(Y) != Relation::LT; } // X >= Y
	bool is_eq(Bignum const & Y) const { return cmp(Y) == Relation::EQ; } // X == Y
	bool is_ne(Bignum const & Y) const { return cmp(Y) != Relation::EQ; } // X != Y

	Bignum & set_pos(); // X = +X
	Bignum & set_neg(); // X = -X
	Bignum & set_abs(); // X = |X|
	Bignum & set_conj(); // X = ~X

	Bignum pos() const {
		Bignum Z(*this);
		return Z.set_pos();
	} // +X
	Bignum neg() const {
		Bignum Z(*this);
		return Z.set_neg();
	} // -X
	Bignum abs() const {
		Bignum Z(*this);
		return Z.set_abs();
	} // |X|
	Bignum conj() const {
		Bignum Z(*this);
		return Z.set_conj();
	} // ~X

	Bignum add(Bignum const &Y) const; // X + Y
	Bignum sub(Bignum const &Y) const; // X - Y
	Bignum mul(Bignum const &Y) const; // X * Y
	Bignum div(Bignum const &Y) const; // X / Y
	Bignum mod(Bignum const &Y) const; // X % Y
	Bignum bor(Bignum const &Y) const; // X | Y
	Bignum band(Bignum const &Y) const; // X & Y
	Bignum bxor(Bignum const &Y) const; // X ^ Y

	Bignum & add_by(Bignum const &Y); // X += Y
	Bignum & sub_by(Bignum const &Y); // X -= Y
	Bignum & mul_by(Bignum const &Y); // X *= Y
	Bignum & div_by(Bignum const &Y); // X /= Y
	Bignum & mod_by(Bignum const &Y); // X %= Y
	Bignum & bor_by(Bignum const &Y); // X |= Y
	Bignum & band_by(Bignum const &Y); // X &= Y
	Bignum & bxor_by(Bignum const &Y); // X ^= Y

	Bignum add(Digit d) const; // X + d
	Bignum sub(Digit d) const; // X - d
	Bignum mul(Digit d) const; // X * d
	Bignum div(Digit d) const; // X / d
	Bignum mod(Digit d) const; // X % d
	Bignum bor(Digit d) const; // X | d
	Bignum band(Digit d) const; // X & d
	Bignum bxor(Digit d) const; // X ^ d
	Bignum lsh(Digit n) const; // X << n
	Bignum rsh(Digit n) const; // X >> n
	Bignum lshb(Digit bn) const; // X << n, n < BIT_PER_DIGIT
	Bignum rshb(Digit bn) const; // X << n, n < BIT_PER_DIGIT
	Bignum lshd(Digit dn) const; // X << (dn * BIT_PER_DIGIT)
	Bignum rshd(Digit dn) const; // X >> (dn * BIT_PER_DIGIT)

	Bignum & add_by(Digit d); // X += d
	Bignum & sub_by(Digit d); // X -= d
	Bignum & mul_by(Digit d); // X *= d
	Bignum & div_by(Digit d); // X /= d
	Bignum & bor_by(Digit d); // X |= d
	Bignum & band_by(Digit d); // X &= d
	Bignum & bxor_by(Digit d); // X ^= d
	Bignum & lsh_by(Digit n); // X <<= n
	Bignum & rsh_by(Digit n); // X >>= n
	Bignum & lshb_by(Digit bn); // X <<= n, n < BIT_PER_DIGIT
	Bignum & rshb_by(Digit bn); // X >>= n, n < BIT_PER_DIGIT
	Bignum & lshd_by(Digit dn); // X <<= (dn * BIT_PER_DIGIT)
	Bignum & rshd_by(Digit dn); // X >>= (dn * BIT_PER_DIGIT)

	// X %= d
	Bignum & mod_by(Digit d) {
		return assign(mod(d));
	}

	Bignum add1() const { return add(1); } // X + 1
	Bignum sub1() const { return sub(1); } // X - 1

	Bignum mul2() const; // X * 2
	Bignum div2() const; // X / 2

	Bignum & add_by1() { return add_by(1); } // X += 1
	Bignum & sub_by1() { return sub_by(1); } // X -= 1

	Bignum & mul_by2(); // X *= 2
	Bignum & div_by2(); // X /= 2

	Bignum sqr() const; // X^2

	Bignum & set_sqr(); // X = X^2

	Digit mod2() const { return digit(0) & Digit(1); } // X % 2

	Bignum next() const { return add1(); }

	Bignum succ() const { return sub1(); }

	Bignum inc() const { return add1(); }

	Bignum dec() const { return sub1(); }

	Bignum & set_inc() { return add_by1(); }

	Bignum & set_dec() { return sub_by1(); }

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
		for (Bignum count(ZERO); count < *this; count.set_inc()) {
			functor(count);
		}
		return *this;
	}


public:
	std::string inspect() const;

	std::string to_s(Digit base = 10, bool show_plus = false) const;

public:
	Bignum & operator=(Bignum const & Y) { return assign(Y); }

	Bignum & operator=(Bignum && Y) { return assign(move(Y)); }

	Bignum & operator=(UDigit ud) { return assign(ud); }

	Bignum & operator=(SDigit sd) { return assign(sd); }

	Bignum & operator=(std::initializer_list< Digit > L) { return assign(L); }

	bool operator<(Bignum const & Y) const { return is_lt(Y); }

	bool operator>(Bignum const & Y) const { return is_gt(Y); }

	bool operator<=(Bignum const & Y) const { return is_le(Y); }

	bool operator>=(Bignum const & Y) const { return is_ge(Y); }

	bool operator==(Bignum const & Y) const { return is_eq(Y); }

	bool operator!=(Bignum const & Y) const { return is_ne(Y); }

	// get bit at index
	Digit operator[](UIndex index) const { return (digit(index / BITS_PER_DIGIT) >> (index & (BITS_PER_DIGIT - 1))) & 1; }

	// get digit at index
	Digit operator()(UIndex index) const { return digits()[index]; }

	Digit operator[](SIndex index) const { return operator[](static_cast<UIndex>(index < 0 ? ~index : index)); }

	Digit operator()(SIndex index) const { return operator()(static_cast<UIndex>(index < 0 ? ~index : index)); }

	Bignum operator+() const { return pos(); }

	Bignum operator-() const { return neg(); }

	Bignum operator~() const { return conj(); }

	Bignum operator+(Bignum const & Y) const { return add(Y); }

	Bignum operator-(Bignum const & Y) const { return sub(Y); }

	Bignum operator*(Bignum const & Y) const { return mul(Y); }

	Bignum operator/(Bignum const & Y) const { return div(Y); }

	Bignum operator%(Bignum const & Y) const { return mod(Y); }

	Bignum operator|(Bignum const &  Y) const { return bor(Y); }

	Bignum operator&(Bignum const & Y) const { return band(Y); }

	Bignum operator^(Bignum const & Y) const { return bxor(Y); }

	Bignum &operator+=(Bignum const & Y) { return add_by(Y); }

	Bignum &operator-=(Bignum const & Y) { return sub_by(Y); }

	Bignum &operator*=(Bignum const & Y) { return mul_by(Y); }

	Bignum &operator/=(Bignum const & Y) { return div_by(Y); }

	Bignum &operator%=(Bignum const & Y) { return mod_by(Y); }

	Bignum &operator|=(Bignum const & Y) { return bor_by(Y); }

	Bignum &operator&=(Bignum const & Y) { return band_by(Y); }

	Bignum &operator^=(Bignum const & Y) { return bxor_by(Y); }

	Bignum operator+(Digit d) const { return add(d); }

	Bignum operator-(Digit d) const { return sub(d); }

	Bignum operator*(Digit d) const { return mul(d); }

	Bignum operator/(Digit d) const { return div(d); }

	Bignum operator%(Digit d) const { return mod(d); }

	Bignum operator<<(Digit n) const { return lsh(n); }

	Bignum operator>>(Digit n) const { return rsh(n); }

	Bignum & operator+=(Digit d) { return add_by(d); }

	Bignum & operator-=(Digit d) { return sub_by(d); }

	Bignum & operator*=(Digit d) { return mul_by(d); }

	Bignum & operator/=(Digit d) { return div_by(d); }

	Bignum & operator%=(Digit d) { return mod_by(d); }

	Bignum & operator<<=(Digit n) { return lsh_by(n); }

	Bignum & operator>>=(Digit n) { return rsh_by(n); }

	explicit operator bool() const { return !is0(); }

public:
	Bignum && operator+(Bignum && Y) const { return move(Y += *this); }

	Bignum && operator-(Bignum && Y) const { return move(Y -= *this); }

	Bignum && operator*(Bignum && Y) const { return move(Y *= *this); }

	Bignum && operator/(Bignum && Y) const { return move(Y /= *this); }

	Bignum && operator%(Bignum && Y) const { return move(Y %= *this); }

	Bignum && operator|(Bignum && Y) const { return move(Y |= *this); }

	Bignum && operator&(Bignum && Y) const { return move(Y &= *this); }

	Bignum && operator^(Bignum && Y) const { return move(Y ^= *this); }

	Bignum && add(Bignum && Y) const { return move(Y += *this); }

	Bignum && sub(Bignum && Y) const { return move(Y -= *this); }

	Bignum && mul(Bignum && Y) const { return move(Y *= *this); }

	Bignum && div(Bignum && Y) const { return move(Y /= *this); }

	Bignum && mod(Bignum && Y) const { return move(Y %= *this); }

	Bignum && bor(Bignum && Y) const { return move(Y |= *this); }

	Bignum && band(Bignum && Y) const { return move(Y &= *this); }

	Bignum && bxor(Bignum && Y) const { return move(Y ^= *this); }

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

} // namespace Math
} // namespace BR
