/**
 * @file
 * @brief 插入迭代器
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TContainer >
class InsertIterator;

template< typename TContainer >
inline auto make_insert_iterator(TContainer & container, typename TContainer::Iterator iterator) -> InsertIterator<TContainer> {
	return InsertIterator<TContainer>(container, iterator);
}

template< typename TContainer >
class InsertIterator : public BasicIterator {
public:
	struct Category : public BasicIterator::Category, public WritableTag, public IncrementableTraversalTag {
	};

	using Element = void;

	using Pointer = void;

	using Reference = InsertIterator &;

	using Difference = void;

	using Container = TContainer;

	explicit InsertIterator(
		Container & container, typename Container::Iterator iterator
	) : m_container(address_of(container)), m_iterator(iterator) {
	}

	auto operator=(typename TContainer::Element const & element) -> InsertIterator & {
		m_iterator = m_container->insert(m_iterator, element);
		++m_iterator;
		return *this;
	}

	auto operator=(typename TContainer::Element && element) -> InsertIterator & {
		m_iterator = m_container->insert(m_iterator, move(element));
		++m_iterator;
		return *this;
	}

	auto operator*() -> Reference {
		return *this;
	}

	auto operator++() -> InsertIterator & {
		return *this;
	}

	auto operator++(int) -> InsertIterator {
		return *this;
	}

private:
	Container * m_container;

	typename Container::Iterator m_iterator;
}; // class InsertIterator< TContainer >

} // namespace BR