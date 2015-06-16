#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Iterator {

template< typename TContainer >
class AddFirstIterator : public Iterator< OutputIteratorTag, void, void, void, AddFirstIterator< TContainer > & > {
public:
	using Container = TContainer;

	explicit AddFirstIterator(Container & container) : m_container(Memory::address_of(container)) {}

	AddFirstIterator & operator=(typename TContainer::Value const & value) {
		m_container->addFirst(value);
		return *this;
	}

	AddFirstIterator & operator=(typename TContainer::Value && value) {
		m_container->addFirst(move(value));
		return *this;
	}

	AddFirstIterator & operator* ()    {return *this;}
	AddFirstIterator & operator++()    {return *this;}
	AddFirstIterator   operator++(int) {return *this;}

private:
	Container * m_container;
}; // class AddFirstIterator< TContainer >

template< typename TContainer >
inline AddFirstIterator< TContainer > makeAddFirstIterator(TContainer & container) {
	return AddFirstIterator< TContainer >(container);
}

} // namespace Iterator
} // namespace BR