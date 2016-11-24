/**
 * @file
 * @brief 头部添加迭代器
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
class InsertFrontIterator;

template< typename TContainer >
inline auto make_insert_front_iterator(TContainer & container) -> InsertFrontIterator<TContainer> {
	return InsertFrontIterator<TContainer>(container);
}

template< typename TContainer >
class InsertFrontIterator : public BasicIterator {
public:
	struct Category : public BasicIterator::Category, public WritableTag, public IncrementableTraversalTag {
	};

	using Element = void;

	using Pointer = void;

	using Reference = InsertFrontIterator &;

	using Difference = void;

	using Container = TContainer;

	explicit InsertFrontIterator(Container & container) : m_container(address_of(container)) {
	}

	auto operator=(typename TContainer::Element const & element) -> InsertFrontIterator & {
		m_container->insert_front(element);
		return *this;
	}

	auto operator=(typename TContainer::Element && element) -> InsertFrontIterator & {
		m_container->insert_front(move(element));
		return *this;
	}

	auto operator*() -> InsertFrontIterator & {
		return *this;
	}

	auto operator++() -> InsertFrontIterator & {
		return *this;
	}

	auto operator++(int) -> InsertFrontIterator {
		return *this;
	}

private:
	Container * m_container;
}; // class InsertFrontIterator<TContainer>

} // namespace BR