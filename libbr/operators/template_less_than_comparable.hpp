/**
 * @file
 * @brief TemplateLessThanComparable
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/detail/empty.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

inline namespace Operators {

template< typename TX, template<typename...> class Template, typename TBase = Detail::Operators::Empty<TX> >
struct TemplateLessThanComparable;

} // namespace Operators



inline namespace Operators {

template< template<typename...> class Template, typename... TArguments, typename TBase >
struct TemplateLessThanComparable< Template<TArguments...>, Template, TBase > : public TBase {
	template< typename... TOtherArguments >
	friend auto operator>(Template<TArguments...> const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return y < x;
	}

	template< typename... TOtherArguments >
	friend auto operator<=(Template<TArguments...> const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(y < x);
	}

	template< typename... TOtherArguments >
	friend auto operator>=(Template<TArguments...> const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x < y);
	}
};

template< typename TX, template<typename...> class Template, typename TBase >
struct TemplateLessThanComparable : public TBase {

	template< typename... TOtherArguments >
	friend auto operator<=(TX const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x > y);
	}

	template< typename... TOtherArguments >
	friend auto operator>=(TX const & x, Template<TOtherArguments...> const & y) -> Boolean {
		return !static_cast<Boolean>(x < y);
	}

	template< typename... TOtherArguments >
	friend auto operator<(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return x < y;
	}

	template< typename... TOtherArguments >
	friend auto operator>(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return x > y;
	}

	template< typename... TOtherArguments >
	friend auto operator<=(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return !static_cast<Boolean>(x < y);
	}

	template< typename... TOtherArguments >
	friend auto operator>=(Template<TOtherArguments...> const & y, TX const & x) -> Boolean {
		return !static_cast<Boolean>(x > y);
	}

};

} // namespace Operators

} // namespace BR

