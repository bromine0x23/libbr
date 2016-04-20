#include <libbr/type_operate/remove_volatile.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, RemoveVolatile) {
	OPERATE_CHECKS(RemoveVolatile, BR_EMPTY, BR_EMPTY)
	OPERATE_CHECKS(RemoveVolatile, const, const)
	OPERATE_CHECKS(RemoveVolatile, volatile, BR_EMPTY)
	OPERATE_CHECKS(RemoveVolatile, const volatile, const)
	OPERATE_CHECKS(RemoveVolatile, *, *)
	OPERATE_CHECKS(RemoveVolatile, * const, * const)
	OPERATE_CHECKS(RemoveVolatile, * volatile, *)
	OPERATE_CHECKS(RemoveVolatile, * const volatile, * const)
	OPERATE_CHECKS(RemoveVolatile, const *, const *)
	OPERATE_CHECKS(RemoveVolatile, volatile *, volatile *)
	OPERATE_CHECKS(RemoveVolatile, const * const, const * const)
	OPERATE_CHECKS(RemoveVolatile, const * volatile, const *)
	OPERATE_CHECKS(RemoveVolatile, const * const volatile, const * const)
	OPERATE_CHECKS(RemoveVolatile, &, &)
	OPERATE_CHECKS(RemoveVolatile, const &, const &)
	OPERATE_CHECKS(RemoveVolatile, volatile &, volatile &)
	OPERATE_CHECKS(RemoveVolatile, const volatile &, const volatile &)
	OPERATE_CHECKS(RemoveVolatile, &&, &&)
	OPERATE_CHECKS(RemoveVolatile, const &&, const &&)
	OPERATE_CHECKS(RemoveVolatile, volatile &&, volatile &&)
	OPERATE_CHECKS(RemoveVolatile, const volatile &&, const volatile &&)
	OPERATE_CHECKS(RemoveVolatile, [2], [2])
	OPERATE_CHECKS(RemoveVolatile, const[2], const[2])
	OPERATE_CHECKS(RemoveVolatile, volatile[2], [2])
	OPERATE_CHECKS(RemoveVolatile, const volatile[2], const[2])
	OPERATE_CHECKS(RemoveVolatile, [2][3], [2][3])
	OPERATE_CHECKS(RemoveVolatile, const[2][3], const[2][3])
	OPERATE_CHECKS(RemoveVolatile, volatile[2][3], [2][3])
	OPERATE_CHECKS(RemoveVolatile, const volatile[2][3], const[2][3])
	OPERATE_CHECKS(RemoveVolatile, [][3], [][3])
	OPERATE_CHECKS(RemoveVolatile, const[][3], const[][3])
	OPERATE_CHECKS(RemoveVolatile, volatile[][3], [][3])
	OPERATE_CHECKS(RemoveVolatile, const volatile[][3], const[][3])
	OPERATE_CHECKS(RemoveVolatile, (&)[2], (&)[2])
	OPERATE_CHECKS(RemoveVolatile, (&&)[2], (&&)[2])
	OPERATE_CHECKS(RemoveVolatile, (&)[2][3], (&)[2][3])
	OPERATE_CHECKS(RemoveVolatile, (&&)[2][3], (&&)[2][3])
}