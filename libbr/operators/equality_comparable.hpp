/**
 * @file
 * @brief EqualityComparable
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/detail/empty.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

namespace Detail {
namespace Operators {

template< typename T, typename TB >
struct EqualityComparable1 : public TB {
	friend auto operator!=(T const & x, T const & y) -> bool { return !static_cast<bool>(x == y); }
};

template< typename TX, typename TY, typename TB >
struct EqualityComparable2 : public TB {
	friend auto operator==(TY const & y, TX const & x) -> bool { return x == y; }
	friend auto operator!=(TX const & x, TY const & y) -> bool { return !static_cast<bool>(x == y); }
	friend auto operator!=(TY const & y, TX const & x) -> bool { return !static_cast<bool>(y == x); }
};

} // namespace Operators
} // namespace Detail

inline namespace Operators {

template< typename TX, typename TY = TX, typename TB = Detail::Operators::Empty<TX, TY> >
using EqualityComparable = Conditional< IsSame<TX, TY>, Detail::Operators::EqualityComparable1<TX, TB>, Detail::Operators::EqualityComparable2<TX, TY, TB> >;

} // namespace Operators

} // namespace BR

