#include <libbr/type_traits/add_const.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, AddConst) {
	TYPE_TRAITS_CHECKS(AddConst, BR_EMPTY, const)
	TYPE_TRAITS_CHECKS(AddConst, const, const)
	TYPE_TRAITS_CHECKS(AddConst, volatile, const volatile)
	TYPE_TRAITS_CHECKS(AddConst, const volatile, const volatile)
	TYPE_TRAITS_CHECKS(AddConst, *, * const)
	TYPE_TRAITS_CHECKS(AddConst, * const, * const)
	TYPE_TRAITS_CHECKS(AddConst, * volatile, * const volatile)
	TYPE_TRAITS_CHECKS(AddConst, * const volatile, * const volatile)
	TYPE_TRAITS_CHECKS(AddConst, const *, const * const)
	TYPE_TRAITS_CHECKS(AddConst, volatile *, volatile * const)
	TYPE_TRAITS_CHECKS(AddConst, const * const, const * const)
	TYPE_TRAITS_CHECKS(AddConst, const * volatile, const * const volatile)
	TYPE_TRAITS_CHECKS(AddConst, const * const volatile, const * const volatile)
	TYPE_TRAITS_CHECKS(AddConst, &, &)
	TYPE_TRAITS_CHECKS(AddConst, const &, const &)
	TYPE_TRAITS_CHECKS(AddConst, volatile &, volatile &)
	TYPE_TRAITS_CHECKS(AddConst, const volatile &, const volatile &)
	TYPE_TRAITS_CHECKS(AddConst, &&, &&)
	TYPE_TRAITS_CHECKS(AddConst, const &&, const &&)
	TYPE_TRAITS_CHECKS(AddConst, volatile &&, volatile &&)
	TYPE_TRAITS_CHECKS(AddConst, const volatile &&, const volatile &&)
	TYPE_TRAITS_CHECKS(AddConst, [2], const[2])
	TYPE_TRAITS_CHECKS(AddConst, const[2], const[2])
	TYPE_TRAITS_CHECKS(AddConst, volatile[2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddConst, const volatile[2], const volatile[2])
	TYPE_TRAITS_CHECKS(AddConst, [2][3], const[2][3])
	TYPE_TRAITS_CHECKS(AddConst, const[2][3], const[2][3])
	TYPE_TRAITS_CHECKS(AddConst, volatile[2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddConst, const volatile[2][3], const volatile[2][3])
	TYPE_TRAITS_CHECKS(AddConst, [][3], const[][3])
	TYPE_TRAITS_CHECKS(AddConst, const[][3], const[][3])
	TYPE_TRAITS_CHECKS(AddConst, volatile[][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddConst, const volatile[][3], const volatile[][3])
	TYPE_TRAITS_CHECKS(AddConst, (&)[2], (&)[2])
	TYPE_TRAITS_CHECKS(AddConst, (&&)[2], (&&)[2])
	TYPE_TRAITS_CHECKS(AddConst, (&)[2][3], (&)[2][3])
	TYPE_TRAITS_CHECKS(AddConst, (&&)[2][3], (&&)[2][3])
}

