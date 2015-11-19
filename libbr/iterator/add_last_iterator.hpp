/**
 * @file
 * @brief 尾部添加迭代器
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
class AddLastIterator;

template< typename TContainer >
inline auto make_add_first_iterator(TContainer & container) -> AddLastIterator<TContainer> {
	return AddLastIterator<TContainer>(container);
}

template< typename TContainer >
class AddLastIterator : public BasicIterator {
public:
	struct Category : public IteratorTag, public WritableTag, public IncrementableTraversalTag {
	};

	using Element = void;

	using Pointer = void;

	using Reference = AddLastIterator &;

	using Difference = void;

	using Container = TContainer;

	explicit AddLastIterator(Container & container) : m_container(address_of(container)) {
	}

	auto operator=(typename TContainer::Element const & element) -> AddLastIterator & {
		m_container->add_last(element);
		return *this;
	}

	auto operator=(typename TContainer::Element && element) -> AddLastIterator & {
		m_container->add_last(move(element));
		return *this;
	}

	auto operator* () -> AddLastIterator & {
		return *this;
	}

	auto operator++() -> AddLastIterator & {
		return *this;
	}

	auto operator++(int) -> AddLastIterator {
		return *this;
	}

private:
	Container * m_container;
}; // class AddLastIterator<TContainer>

} // namespace BR