/**
 * @file
 * @brief 头部添加迭代器
 * @author Bromine0x23
 * @since 2015/10/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TContainer >
class AddFirstIterator;

template< typename TContainer >
inline auto make_add_first_iterator(TContainer & container) -> AddFirstIterator<TContainer> {
	return AddFirstIterator<TContainer>(container);
}

template< typename TContainer >
class AddFirstIterator : public BasicIterator {
public:
	struct Category : public IteratorTag, public WritableTag, public IncrementableTraversalTag {
	};

	using Element = void;

	using Pointer = void;

	using Reference = AddFirstIterator &;

	using Difference = void;

	using Container = TContainer;

	explicit AddFirstIterator(Container & container) : m_container(address_of(container)) {
	}

	auto operator=(typename TContainer::Element const & element) -> AddFirstIterator & {
		m_container->add_first(element);
		return *this;
	}

	auto operator=(typename TContainer::Element && element) -> AddFirstIterator & {
		m_container->add_first(move(element));
		return *this;
	}

	auto operator*() -> AddFirstIterator & {
		return *this;
	}

	auto operator++() -> AddFirstIterator & {
		return *this;
	}

	auto operator++(int) -> AddFirstIterator {
		return *this;
	}

private:
	Container * m_container;
}; // class AddFirstIterator<TContainer>

} // namespace BR