#include <libbr/type_operate/add_pointer.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, AddPointer) {
	OPERATE_CHECKS(AddPointer, BR_EMPTY, *)
	OPERATE_CHECKS(AddPointer, const, const *)
	OPERATE_CHECKS(AddPointer, volatile, volatile *)
	OPERATE_CHECKS(AddPointer, const volatile, const volatile *)
	OPERATE_CHECKS(AddPointer, *, * *)
	OPERATE_CHECKS(AddPointer, * const, * const *)
	OPERATE_CHECKS(AddPointer, * volatile, * volatile *)
	OPERATE_CHECKS(AddPointer, * const volatile, * const volatile *)
	OPERATE_CHECKS(AddPointer, const *, const * *)
	OPERATE_CHECKS(AddPointer, volatile *, volatile * *)
	OPERATE_CHECKS(AddPointer, const * const, const * const *)
	OPERATE_CHECKS(AddPointer, const * volatile, const * volatile *)
	OPERATE_CHECKS(AddPointer, const * const volatile, const * const volatile *)
	OPERATE_CHECKS(AddPointer, &, *)
	OPERATE_CHECKS(AddPointer, const &, const *)
	OPERATE_CHECKS(AddPointer, volatile &, volatile *)
	OPERATE_CHECKS(AddPointer, const volatile &, const volatile *)
	OPERATE_CHECKS(AddPointer, &&, *)
	OPERATE_CHECKS(AddPointer, const &&, const *)
	OPERATE_CHECKS(AddPointer, volatile &&, volatile *)
	OPERATE_CHECKS(AddPointer, const volatile &&, const volatile *)
	OPERATE_CHECKS(AddPointer, [2], (*)[2])
	OPERATE_CHECKS(AddPointer, const[2], const(*)[2])
	OPERATE_CHECKS(AddPointer, volatile[2], volatile(*)[2])
	OPERATE_CHECKS(AddPointer, const volatile[2], const volatile(*)[2])
	OPERATE_CHECKS(AddPointer, [2][3], (*)[2][3])
	OPERATE_CHECKS(AddPointer, const[2][3], const(*)[2][3])
	OPERATE_CHECKS(AddPointer, volatile[2][3], volatile(*)[2][3])
	OPERATE_CHECKS(AddPointer, const volatile[2][3], const volatile(*)[2][3])
	OPERATE_CHECKS(AddPointer, [][3], (*)[][3])
	OPERATE_CHECKS(AddPointer, const[][3], const(*)[][3])
	OPERATE_CHECKS(AddPointer, volatile[][3], volatile(*)[][3])
	OPERATE_CHECKS(AddPointer, const volatile[][3], const volatile(*)[][3])
	OPERATE_CHECKS(AddPointer, (&)[2], (*)[2])
	OPERATE_CHECKS(AddPointer, (&&)[2], (*)[2])
	OPERATE_CHECKS(AddPointer, (&)[2][3], (*)[2][3])
	OPERATE_CHECKS(AddPointer, (&&)[2][3], (*)[2][3])
}