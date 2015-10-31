#pragma once

#include <initializer_list>

#include <libbr/config.hpp>
#include <libbr/utility/enumerator.hpp>

namespace BR {

template< typename TElement >
class InitializerList {
private:
	using Implement = std::initializer_list<TElement>;

public:
	using Element = typename Implement::value_type;

	using Reference = typename Implement::reference ;

	using ConstReference = typename Implement::const_reference;

	using Size = typename Implement::size_type;

	using Iterator = typename Implement::iterator;

	using ConstIterator  = typename Implement::const_iterator;

public:
	InitializerList(Implement list) : m_list(list) {}

	BR_CONSTEXPR_AFTER_CXX11 InitializerList() noexcept : m_list() {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto size() const noexcept -> Size {
		return m_list.size();
	}

	BR_CONSTEXPR_AFTER_CXX11 auto is_empty() const noexcept -> bool {
		return size() == 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto begin() const noexcept -> ConstIterator {
		return m_list.begin();
	}

	BR_CONSTEXPR_AFTER_CXX11 auto end() const noexcept -> ConstIterator {
		return m_list.end();
	}

	BR_CONSTEXPR_AFTER_CXX11 auto each() const noexcept -> Enumerator<ConstIterator > {
		return make_enumerator(begin(), end());
	}

	BR_CONSTEXPR_AFTER_CXX11 auto data() const noexcept -> Element * {
		return begin();
	}

	template< typename TFunctor >
	auto each(TFunctor functor) const noexcept -> InitializerList {
		each().each(functor);
		return *this;
	}

private:
	Implement m_list;
}; // class InitializerList<TElement>

} // namespace BR