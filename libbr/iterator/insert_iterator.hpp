#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TContainer >
class InsertIterator : public Iterator< OutputIteratorTag, void, void, void, InsertIterator< TContainer > & > {
public:
	using Container = TContainer;

	explicit InsertIterator(
		Container & container, typename Container::Iterator iterator
	) : m_container(address_of(container)), m_iterator(iterator) {}

	InsertIterator & operator=(typename TContainer::Value const & value) {
		m_container->insert(m_iterator, value);
		++m_iterator;
		return *this;
	}

	InsertIterator & operator=(typename TContainer::Value && value) {
		m_container->insert(m_iterator, move(value));
		++m_iterator;
		return *this;
	}

	InsertIterator & operator* ()    {return *this;}
	InsertIterator & operator++()    {return *this;}
	InsertIterator   operator++(int) {return *this;}

private:
	Container * m_container;
	typename Container::Iterator m_iterator;
}; // class InsertIterator< TContainer >

template< typename TContainer >
inline InsertIterator< TContainer > make_insert_iterator(TContainer & container, typename TContainer::Iterator iterator) {
	return InsertIterator< TContainer >(container, iterator);
}

} // namespace BR