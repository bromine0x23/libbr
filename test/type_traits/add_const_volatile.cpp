#include <libbr/type_traits/add_const_volatile.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeTraits, AddConstVolatile) {
	TYPE_TRAITS_CHECKS(AddConstVolatile, BR_EMPTY, const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const, const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, volatile, const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const volatile, const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, *, * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, * const, * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, * volatile, * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, * const volatile, * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const *, const * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, volatile *, volatile * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const * const, const * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const * volatile, const * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const * const volatile, const * const volatile)
	TYPE_TRAITS_CHECKS(AddConstVolatile, &, &)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const &, const &)
	TYPE_TRAITS_CHECKS(AddConstVolatile, volatile &, volatile &)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const volatile &, const volatile &)
	TYPE_TRAITS_CHECKS(AddConstVolatile, &&, &&)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const &&, const &&)
	TYPE_TRAITS_CHECKS(AddConstVolatile, volatile &&, volatile &&)
	TYPE_TRAITS_CHECKS(AddConstVolatile, const volatile &&, const volatile &&)
	TYPE_TRAITS_CHECKS(AddConstVolatile, [2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddConstVolatile, const[2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddConstVolatile, volatile[2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddConstVolatile, const volatile[2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddConstVolatile, [2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, const[2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, volatile[2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, const volatile[2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, [][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, const[][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, volatile[][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, const volatile[][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, (&)[2], (&)[2])
	TYPE_TRAITS_CHECKS(AddConstVolatile, (&&)[2], (&&)[2])
	TYPE_TRAITS_CHECKS(AddConstVolatile, (&)[2][3], (&)[2][3])
	TYPE_TRAITS_CHECKS(AddConstVolatile, (&&)[2][3], (&&)[2][3])
}

