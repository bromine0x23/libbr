#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_operate/is_unsigned.hpp>

namespace BR {

namespace Detail {
namespace Math {

template< typename TStorage >
class BitReference {
private:
	using Self = BitReference;
	using Storage = TStorage;

public:
	BitReference(Self const &) = default;

	BitReference(Storage & storage, Size index) : m_reference(storage), m_index(index) {}

	Self & operator=(Self const &) = default;

	Self & operator=(bool bit) {
		m_reference |= (bit & 1) << m_index;
		return *this;
	}

	operator Storage() const {
		return (m_reference >> m_index) & 1;
	}

private:
	Storage & m_reference;
	Size m_index;
};

template< Size bit_width, typename TStorage >
class WithScalar {
	static_assert(bit_width > 0, "'bit_width' should be greater than 0.");

private:
	using Self = WithScalar;
	using Storage = TStorage;

	static_assert(IsUnsigned<Storage>::value, "Implement exception, 'Storage' should be unsigned.");

public:
	constexpr static auto BIT_WIDTH = bit_width;

public:
	WithScalar() = default;

	WithScalar(Self const &) = default;

	WithScalar(TStorage value) : WithScalar() { m_value = value; }

	~WithScalar() = default;

	Self & operator=(Self const &) = default;

	Self & operator=(TStorage value) {
		m_value = value;
		return *this;
	}

	Self & operator +=(Self const & y) { m_value  += y.m_value; return *this; }
	Self & operator -=(Self const & y) { m_value  -= y.m_value; return *this; }
	Self & operator *=(Self const & y) { m_value  *= y.m_value; return *this; }
	Self & operator /=(Self const & y) { m_value  /= y.m_value; return *this; }
	Self & operator %=(Self const & y) { m_value  %= y.m_value; return *this; }
	Self & operator ^=(Self const & y) { m_value  ^= y.m_value; return *this; }
	Self & operator &=(Self const & y) { m_value  &= y.m_value; return *this; }
	Self & operator |=(Self const & y) { m_value  |= y.m_value; return *this; }
	Self & operator<<=(Self const & y) { m_value <<= y.m_value; return *this; }
	Self & operator>>=(Self const & y) { m_value >>= y.m_value; return *this; }

	bool operator< (Self const & y) const { return m_value <  y.m_value; }
	bool operator> (Self const & y) const { return m_value >  y.m_value; }
	bool operator<=(Self const & y) const { return m_value <= y.m_value; }
	bool operator>=(Self const & y) const { return m_value >= y.m_value; }
	bool operator==(Self const & y) const { return m_value == y.m_value; }
	bool operator!=(Self const & y) const { return m_value != y.m_value; }

	bool operator!() const { return !m_value; }

	Self & operator++() { ++m_value; return *this; }
	Self & operator--() { --m_value; return *this; }

	Self operator++(int) { Self nrv(*this); ++m_value; return nrv; }
	Self operator--(int) { Self nrv(*this); --m_value; return nrv; }

	Self operator+ (Self const & y) const { Self nrv(*this); nrv  += y; return nrv; }
	Self operator- (Self const & y) const { Self nrv(*this); nrv  -= y; return nrv; }
	Self operator* (Self const & y) const { Self nrv(*this); nrv  *= y; return nrv; }
	Self operator/ (Self const & y) const { Self nrv(*this); nrv  /= y; return nrv; }
	Self operator% (Self const & y) const { Self nrv(*this); nrv  %= y; return nrv; }
	Self operator^ (Self const & y) const { Self nrv(*this); nrv  ^= y; return nrv; }
	Self operator& (Self const & y) const { Self nrv(*this); nrv  &= y; return nrv; }
	Self operator| (Self const & y) const { Self nrv(*this); nrv  |= y; return nrv; }
	Self operator<<(Self const & y) const { Self nrv(*this); nrv <<= y; return nrv; }
	Self operator>>(Self const & y) const { Self nrv(*this); nrv >>= y; return nrv; }

	BitReference<Storage> operator[](Size index) {
		BitReference<Storage> reference(m_storage, index);
		return reference;
	}

	Storage operator[](Size index) const {
		return (m_storage >> index) & 1;
	}

	operator Storage() const {
		return m_storage;
	}

private:
	union {
		Storage m_storage;
		Storage m_value : bit_width;
	};
};

template< Size bit_width, typename TStorage >
class WithCompound {

private:
	using Self = WithCompound;
	using Storage = TStorage;

	static_assert(IsUnsigned<Storage>::value, "Implement exception, 'Storage' should be unsigned.");

public:
	constexpr static auto BIT_WIDTH = bit_width;

private:
	constexpr static auto BIT_PER_STORAGE = sizeof(Storage) * BIT_PER_CHAR;
	constexpr static auto HEAD_BITS = (BIT_WIDTH + BIT_PER_STORAGE - 1) % BIT_PER_STORAGE + 1;
	constexpr static auto TAIL_SIZE = (BIT_WIDTH - 1) / BIT_PER_STORAGE;
	constexpr static auto TAIL_BITS = TAIL_SIZE * BIT_PER_STORAGE;

	using DStorage = ConditionalByValue<
		(bit_width <= 8),
		UInt16,
		ConditionalByValue<
			(bit_width <= 16),
			UInt32,
			UInt64
		>
	>;

	static_assert(BIT_PER_STORAGE * 2 <= sizeof(DStorage) * BIT_PER_CHAR, "Implement exception, 'DStorage' is too short.");

public:
	WithCompound() = default;

	WithCompound(Self const &) = default;

	~WithCompound() = default;

	Self & operator=(Self const &) = default;

	Self & operator+=(Self const & y) {
		DStorage t = 0;
		for (auto i = 0; i < TAIL_SIZE; ++i) {
			t += m_tail[i];
			t += y.m_tail[i];
			m_tail[i] = t & Storage(-1);
			t >> BIT_PER_STORAGE;
		}
		t += m_head;
		t += y.m_head;
		m_head = t & Storage(-1);
		return *this;
	}

	Self & operator-=(Self const & y) {

		return *this;
	}

	Self & operator^=(Self const & y) {
		m_head  ^= y.m_head;
		for (auto i = 0; i < TAIL_SIZE; ++i) {
			m_tail[i] ^= y.m_tail[i];
		}
		return *this;
	}

	Self & operator&=(Self const & y) {
		m_head &= y.m_head;
		for (auto i = 0; i < TAIL_SIZE; ++i) {
			m_tail[i] &= y.m_tail[i];
		}
		return *this;
	}

	Self & operator|=(Self const & y) {
		m_head |= y.m_head;
		for (auto i = 0; i < TAIL_SIZE; ++i) {
			m_tail[i] |= y.m_tail[i];
		}
		return *this;
	}

	Self operator+ (Self const & y) const { Self nrv(*this); nrv  += y; return nrv; }
	Self operator^ (Self const & y) const { Self nrv(*this); nrv  ^= y; return nrv; }
	Self operator& (Self const & y) const { Self nrv(*this); nrv  &= y; return nrv; }
	Self operator| (Self const & y) const { Self nrv(*this); nrv  |= y; return nrv; }

	BitReference<Storage> operator[](Size index) {
		if (index < TAIL_BITS) {
			return BitReference<Storage>(m_storage[index / BIT_PER_STORAGE], index % BIT_PER_STORAGE);
		} else {
			return BitReference<Storage>(m_storage[TAIL_SIZE], index - TAIL_BITS);
		}
	}

	Storage operator[](Size index) const {
		if (index < TAIL_BITS) {
			return (m_storage[index / BIT_PER_STORAGE] >> (index % BIT_PER_STORAGE)) & 1;
		} else {
			return (m_storage >> (index - TAIL_BITS)) & 1;
		}
	}

private:

	union {
		Storage m_storage[TAIL_SIZE + 1];
		struct {
			Storage m_head : HEAD_BITS, m_tail[TAIL_SIZE];
		};
	};
};

template< Size bit_width >
using SelectScalarStorage = ConditionalByValue<
	(bit_width <= 8),
	UInt8,
	ConditionalByValue<
		(bit_width <= 16),
		UInt16,
		ConditionalByValue<
			(bit_width <= 32),
			UInt32,
			UInt64
		>
	>
>;

template< Size bit_width >
using SelectImplement = ConditionalByValue<
	(bit_width > 64),
	WithCompound< bit_width, UInt16 >,
	WithScalar< bit_width, SelectScalarStorage< bit_width > >
>;

} // namespace Math
} // namespace Detail

template< Size bit_width >
using UInt = Detail::Math::SelectImplement<bit_width>;

} // namespace BR