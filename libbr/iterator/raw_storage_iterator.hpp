/**
 * @file
 * @brief 指针类型信息
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/address_of.hpp>

namespace BR {

template< typename TIterator, typename TElement >
class RawStorageIterator : public BasicIterator {
public:
	struct Category : public IteratorTag, public WritableTag, public IncrementableTraversalTag {
	};

	using Element = void;

	using Difference = void;

	using Pointer = void;

	using Reference = RawStorageIterator &;

public:
	explicit RawStorageIterator(TIterator i) : m_i(i) {
	}

	auto operator=(TElement const & x) -> RawStorageIterator & {
		::new(address_of(*m_i)) TElement(x);
		return *this;
	}

	auto operator*() -> Reference {
		return *this;
	}

	auto operator++() -> RawStorageIterator & {
		++m_i;
		return *this;
	}

	auto operator++(int) -> RawStorageIterator & {
		RawStorageIterator t(*this);
		operator++();
		return t;
	}

	auto base() const -> TIterator {
		return m_i;
	}

private:
	TIterator m_i;
};// class RawStorageIterator< TIterator, TElement >

} // namespace BR