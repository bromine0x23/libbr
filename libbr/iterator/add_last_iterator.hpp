#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TContainer >
class AddLastIterator : public Iterator< OutputIteratorTag, void, void, void, AddLastIterator< TContainer > & > {
public:
	using Container = TContainer;

	explicit AddLastIterator(Container & container) : m_container(address_of(container)) {}

	AddLastIterator & operator=(typename TContainer::Value const & value) {
		m_container->addLast(value);
		return *this;
	}

	AddLastIterator & operator=(typename TContainer::Value && value) {
		m_container->addLast(move(value));
		return *this;
	}

	AddLastIterator & operator* ()    {return *this;}
	AddLastIterator & operator++()    {return *this;}
	AddLastIterator   operator++(int) {return *this;}

private:
	Container * m_container;
}; // class AddLastIterator< TContainer >

template< typename TContainer >
inline AddLastIterator< TContainer > make_add_last_iterator(TContainer & container) {
	return AddLastIterator< TContainer >(container);
}

} // namespace BR