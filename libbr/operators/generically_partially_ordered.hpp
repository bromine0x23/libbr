/**
 * @file
 * @brief GenericallyPartiallyOrdered
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/_/empty.hpp>

namespace BR {

inline namespace Operators {

template< typename T, template<typename...> class Template, typename TBase = _::Operators::Empty<T> >
struct GenericallyPartiallyOrdered;

} // namespace Operators



inline namespace Operators {

template< template<typename...> class Template, typename... TArguments, typename TBase >
struct GenericallyPartiallyOrdered< Template<TArguments...>, Template, TBase > : public TBase {
	template< typename... TOtherArguments >
	friend constexpr auto operator>(Template<TArguments...> const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return y < x;
	}

	template< typename... TOtherArguments >
	friend constexpr auto operator<=(Template<TArguments...> const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(y < x);
	}

	template< typename... TOtherArguments >
	friend constexpr auto operator>=(Template<TArguments...> const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x < y);
	}
};

template< typename TX, template<typename...> class Template, typename TBase >
struct GenericallyPartiallyOrdered : public TBase {
	template< typename... TOtherArguments >
	friend constexpr auto operator<=(TX const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x > y);
	}

	template< typename... TOtherArguments >
	friend constexpr auto operator>=(TX const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x < y);
	}

	template< typename... TOtherArguments >
	friend constexpr auto operator<(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return x < y;
	}

	template< typename... TOtherArguments >
	friend constexpr auto operator>(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return x > y;
	}

	template< typename... TOtherArguments >
	friend constexpr auto operator<=(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return !static_cast<Boolean>(x < y);
	}

	template< typename... TOtherArguments >
	friend constexpr auto operator>=(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return !static_cast<Boolean>(x > y);
	}
};

} // namespace Operators

} // namespace BR

