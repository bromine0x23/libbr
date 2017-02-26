#include <libbr/type_traits/add_pointer.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeTraits, AddPointer) {
	TYPE_TRAITS_CHECKS(AddPointer, BR_EMPTY, *)
	TYPE_TRAITS_CHECKS(AddPointer, const, const *)
	TYPE_TRAITS_CHECKS(AddPointer, volatile, volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, const volatile, const volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, *, * *)
	TYPE_TRAITS_CHECKS(AddPointer, * const, * const *)
	TYPE_TRAITS_CHECKS(AddPointer, * volatile, * volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, * const volatile, * const volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, const *, const * *)
	TYPE_TRAITS_CHECKS(AddPointer, volatile *, volatile * *)
	TYPE_TRAITS_CHECKS(AddPointer, const * const, const * const *)
	TYPE_TRAITS_CHECKS(AddPointer, const * volatile, const * volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, const * const volatile, const * const volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, &, *)
	TYPE_TRAITS_CHECKS(AddPointer, const &, const *)
	TYPE_TRAITS_CHECKS(AddPointer, volatile &, volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, const volatile &, const volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, &&, *)
	TYPE_TRAITS_CHECKS(AddPointer, const &&, const *)
	TYPE_TRAITS_CHECKS(AddPointer, volatile &&, volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, const volatile &&, const volatile *)
	TYPE_TRAITS_CHECKS(AddPointer, [2], (*)[2])
	TYPE_TRAITS_CHECKS(AddPointer, const[2], const(*)[2])
	TYPE_TRAITS_CHECKS(AddPointer, volatile[2], volatile(*)[2])
	TYPE_TRAITS_CHECKS(AddPointer, const volatile[2], const volatile(*)[2])
	TYPE_TRAITS_CHECKS(AddPointer, [2][3], (*)[2][3])
	TYPE_TRAITS_CHECKS(AddPointer, const[2][3], const(*)[2][3])
	TYPE_TRAITS_CHECKS(AddPointer, volatile[2][3], volatile(*)[2][3])
	TYPE_TRAITS_CHECKS(AddPointer, const volatile[2][3], const volatile(*)[2][3])
	TYPE_TRAITS_CHECKS(AddPointer, [][3], (*)[][3])
	TYPE_TRAITS_CHECKS(AddPointer, const[][3], const(*)[][3])
	TYPE_TRAITS_CHECKS(AddPointer, volatile[][3], volatile(*)[][3])
	TYPE_TRAITS_CHECKS(AddPointer, const volatile[][3], const volatile(*)[][3])
	TYPE_TRAITS_CHECKS(AddPointer, (&)[2], (*)[2])
	TYPE_TRAITS_CHECKS(AddPointer, (&&)[2], (*)[2])
	TYPE_TRAITS_CHECKS(AddPointer, (&)[2][3], (*)[2][3])
	TYPE_TRAITS_CHECKS(AddPointer, (&&)[2][3], (*)[2][3])
}