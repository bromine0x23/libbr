#pragma once

#include <libbr/config.hpp>

#include <initializer_list>

namespace BR {

template< typename TElement >
class InitializerList {

private:
	using Implement = std::initializer_list<TElement>;

public:
	using Element        = typename Implement::value_type;
	using Reference      = typename Implement::reference ;
	using ConstReference = typename Implement::const_reference;
	using Size           = typename Implement::size_type;
	using Iterator       = typename Implement::iterator;
	using ConstIterator  = typename Implement::const_iterator;

public:
	InitializerList(Implement list) : m_list(list) {}

	BR_CONSTEXPR_AFTER_CXX11 InitializerList() noexcept : m_list() {}

	BR_CONSTEXPR_AFTER_CXX11 Size size() const noexcept {
		return m_list.size();
	}

	BR_CONSTEXPR_AFTER_CXX11 Iterator begin() const noexcept {
		return m_list.begin();
	}

	BR_CONSTEXPR_AFTER_CXX11 Iterator end() const noexcept {
		return m_list.end();
	}

private:
	Implement m_list;
}; // class InitializerList<TElement>

template< typename TElement >
inline BR_CONSTEXPR_AFTER_CXX11 typename InitializerList<TElement>::Iterator begin(InitializerList<TElement> list) noexcept {
	return list.begin();
}

template< typename TElement >
inline BR_CONSTEXPR_AFTER_CXX11 typename InitializerList<TElement>::Iterator end(InitializerList<TElement> list) noexcept {
	return list.end();
}

} // namespace BR