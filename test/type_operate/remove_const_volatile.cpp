#include <libbr/type_operate/remove_const_volatile.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, RemoveConstVolatile) {
	OPERATE_CHECKS(RemoveConstVolatile, BR_EMPTY, BR_EMPTY)
	OPERATE_CHECKS(RemoveConstVolatile, const, BR_EMPTY)
	OPERATE_CHECKS(RemoveConstVolatile, volatile, BR_EMPTY)
	OPERATE_CHECKS(RemoveConstVolatile, const volatile, BR_EMPTY)
	OPERATE_CHECKS(RemoveConstVolatile, *, *)
	OPERATE_CHECKS(RemoveConstVolatile, * const, *)
	OPERATE_CHECKS(RemoveConstVolatile, * volatile, *)
	OPERATE_CHECKS(RemoveConstVolatile, * const volatile, *)
	OPERATE_CHECKS(RemoveConstVolatile, const *, const *)
	OPERATE_CHECKS(RemoveConstVolatile, volatile *, volatile *)
	OPERATE_CHECKS(RemoveConstVolatile, const * const, const *)
	OPERATE_CHECKS(RemoveConstVolatile, const * volatile, const *)
	OPERATE_CHECKS(RemoveConstVolatile, const * const volatile, const *)
	OPERATE_CHECKS(RemoveConstVolatile, &, &)
	OPERATE_CHECKS(RemoveConstVolatile, const &, const &)
	OPERATE_CHECKS(RemoveConstVolatile, volatile &, volatile &)
	OPERATE_CHECKS(RemoveConstVolatile, const volatile &, const volatile &)
	OPERATE_CHECKS(RemoveConstVolatile, &&, &&)
	OPERATE_CHECKS(RemoveConstVolatile, const &&, const &&)
	OPERATE_CHECKS(RemoveConstVolatile, volatile &&, volatile &&)
	OPERATE_CHECKS(RemoveConstVolatile, const volatile &&, const volatile &&)
	OPERATE_CHECKS(RemoveConstVolatile, [2], [2])
	OPERATE_CHECKS(RemoveConstVolatile, const[2], [2])
	OPERATE_CHECKS(RemoveConstVolatile, volatile[2], [2])
	OPERATE_CHECKS(RemoveConstVolatile, const volatile[2], [2])
	OPERATE_CHECKS(RemoveConstVolatile, [2][3], [2][3])
	OPERATE_CHECKS(RemoveConstVolatile, const[2][3], [2][3])
	OPERATE_CHECKS(RemoveConstVolatile, volatile[2][3], [2][3])
	OPERATE_CHECKS(RemoveConstVolatile, const volatile[2][3], [2][3])
	OPERATE_CHECKS(RemoveConstVolatile, [][3], [][3])
	OPERATE_CHECKS(RemoveConstVolatile, const[][3], [][3])
	OPERATE_CHECKS(RemoveConstVolatile, volatile[][3], [][3])
	OPERATE_CHECKS(RemoveConstVolatile, const volatile[][3], [][3])
	OPERATE_CHECKS(RemoveConstVolatile, (&)[2], (&)[2])
	OPERATE_CHECKS(RemoveConstVolatile, (&&)[2], (&&)[2])
	OPERATE_CHECKS(RemoveConstVolatile, (&)[2][3], (&)[2][3])
	OPERATE_CHECKS(RemoveConstVolatile, (&&)[2][3], (&&)[2][3])
}