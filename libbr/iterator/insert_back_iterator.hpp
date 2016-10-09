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
class InsertBackIterator;

template< typename TContainer >
inline auto make_insert_back_iterator(TContainer & container) -> InsertBackIterator<TContainer> {
	return InsertBackIterator<TContainer>(container);
}

template< typename TContainer >
class InsertBackIterator : public BasicIterator {
public:
	struct Category : public BasicIterator::Category, public WritableTag, public IncrementableTraversalTag {
	};

	using Element = void;

	using Pointer = void;

	using Reference = InsertBackIterator &;

	using Difference = void;

	using Container = TContainer;

	explicit InsertBackIterator(Container & container) : m_container(address_of(container)) {
	}

	auto operator=(typename TContainer::Element const & element) -> InsertBackIterator & {
		m_container->insert_back(element);
		return *this;
	}

	auto operator=(typename TContainer::Element && element) -> InsertBackIterator & {
		m_container->insert_back(move(element));
		return *this;
	}

	auto operator* () -> InsertBackIterator & {
		return *this;
	}

	auto operator++() -> InsertBackIterator & {
		return *this;
	}

	auto operator++(int) -> InsertBackIterator {
		return *this;
	}

private:
	Container * m_container;
}; // class InsertBackIterator<TContainer>

} // namespace BR