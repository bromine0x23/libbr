/**
 * @file
 * @brief TemplateEqualityComparable
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/detail/empty.hpp>

namespace BR {

inline namespace Operators {

template< typename TX, template<typename...> class Template, typename TBase = Detail::Operators::Empty<TX> >
struct TemplateEqualityComparable;

} // namespace Operators



inline namespace Operators {

template< template<typename...> class Template, typename... TArguments, typename TBase >
struct TemplateEqualityComparable< Template<TArguments...>, Template, TBase > : public TBase {
	template< typename... TOtherArguments >
	friend auto operator!=(Template<TArguments...> const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x == y);
	}
};

template< typename TX, template<typename...> class Template, typename TBase >
struct TemplateEqualityComparable : public TBase {

	template< typename... TOtherArguments >
	friend auto operator!=(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return x == y;
	}

	template< typename... TOtherArguments >
	friend auto operator!=(TX const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x == y);
	}

	template< typename... TOtherArguments >
	friend auto operator!=(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return !static_cast<Boolean>(y == x);
	}
};

} // namespace Operators

} // namespace BR

