#include <libbr/type_traits/add_volatile.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, AddVolatile) {
	TYPE_TRAITS_CHECKS(AddVolatile, BR_EMPTY, volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, const, const volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, volatile, volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, const volatile, const volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, *, * volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, * const, * const volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, * volatile, * volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, * const volatile, * const volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, const *, const * volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, volatile *, volatile * volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, const * const, const * const volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, const * volatile, const * volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, const * const volatile, const * const volatile)
	TYPE_TRAITS_CHECKS(AddVolatile, &, &)
	TYPE_TRAITS_CHECKS(AddVolatile, const &, const &)
	TYPE_TRAITS_CHECKS(AddVolatile, volatile &, volatile &)
	TYPE_TRAITS_CHECKS(AddVolatile, const volatile &, const volatile &)
	TYPE_TRAITS_CHECKS(AddVolatile, &&, &&)
	TYPE_TRAITS_CHECKS(AddVolatile, const &&, const &&)
	TYPE_TRAITS_CHECKS(AddVolatile, volatile &&, volatile &&)
	TYPE_TRAITS_CHECKS(AddVolatile, const volatile &&, const volatile &&)
	TYPE_TRAITS_CHECKS(AddVolatile, [2], volatile[2])
	TYPE_TRAITS_CHECKS(AddVolatile, const[2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddVolatile, volatile[2], volatile[2])
	TYPE_TRAITS_CHECKS(AddVolatile, const volatile[2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddVolatile, [2][3], volatile[2][3])
	TYPE_TRAITS_CHECKS(AddVolatile, const[2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddVolatile, volatile[2][3], volatile[2][3])
	TYPE_TRAITS_CHECKS(AddVolatile, const volatile[2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddVolatile, [][3], volatile[][3])
	TYPE_TRAITS_CHECKS(AddVolatile, const[][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddVolatile, volatile[][3], volatile[][3])
	TYPE_TRAITS_CHECKS(AddVolatile, const volatile[][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddVolatile, (&)[2], (&)[2])
	TYPE_TRAITS_CHECKS(AddVolatile, (&&)[2], (&&)[2])
	TYPE_TRAITS_CHECKS(AddVolatile, (&)[2][3], (&)[2][3])
	TYPE_TRAITS_CHECKS(AddVolatile, (&&)[2][3], (&&)[2][3])
}

