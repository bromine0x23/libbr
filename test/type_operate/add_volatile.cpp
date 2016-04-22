#include <libbr/type_operate/add_volatile.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, AddVolatile) {
	OPERATE_CHECKS(AddVolatile, BR_EMPTY, volatile)
	OPERATE_CHECKS(AddVolatile, const, const volatile)
	OPERATE_CHECKS(AddVolatile, volatile, volatile)
	OPERATE_CHECKS(AddVolatile, const volatile, const volatile)
	OPERATE_CHECKS(AddVolatile, *, * volatile)
	OPERATE_CHECKS(AddVolatile, * const, * const volatile)
	OPERATE_CHECKS(AddVolatile, * volatile, * volatile)
	OPERATE_CHECKS(AddVolatile, * const volatile, * const volatile)
	OPERATE_CHECKS(AddVolatile, const *, const * volatile)
	OPERATE_CHECKS(AddVolatile, volatile *, volatile * volatile)
	OPERATE_CHECKS(AddVolatile, const * const, const * const volatile)
	OPERATE_CHECKS(AddVolatile, const * volatile, const * volatile)
	OPERATE_CHECKS(AddVolatile, const * const volatile, const * const volatile)
	OPERATE_CHECKS(AddVolatile, &, &)
	OPERATE_CHECKS(AddVolatile, const &, const &)
	OPERATE_CHECKS(AddVolatile, volatile &, volatile &)
	OPERATE_CHECKS(AddVolatile, const volatile &, const volatile &)
	OPERATE_CHECKS(AddVolatile, &&, &&)
	OPERATE_CHECKS(AddVolatile, const &&, const &&)
	OPERATE_CHECKS(AddVolatile, volatile &&, volatile &&)
	OPERATE_CHECKS(AddVolatile, const volatile &&, const volatile &&)
	OPERATE_CHECKS(AddVolatile, [2], volatile[2])
	OPERATE_CHECKS(AddVolatile, const[2], const volatile[2])
	OPERATE_CHECKS(AddVolatile, volatile[2], volatile[2])
	OPERATE_CHECKS(AddVolatile, const volatile[2], const volatile[2])
	OPERATE_CHECKS(AddVolatile, [2][3], volatile[2][3])
	OPERATE_CHECKS(AddVolatile, const[2][3], const volatile[2][3])
	OPERATE_CHECKS(AddVolatile, volatile[2][3], volatile[2][3])
	OPERATE_CHECKS(AddVolatile, const volatile[2][3], const volatile[2][3])
	OPERATE_CHECKS(AddVolatile, [][3], volatile[][3])
	OPERATE_CHECKS(AddVolatile, const[][3], const volatile[][3])
	OPERATE_CHECKS(AddVolatile, volatile[][3], volatile[][3])
	OPERATE_CHECKS(AddVolatile, const volatile[][3], const volatile[][3])
	OPERATE_CHECKS(AddVolatile, (&)[2], (&)[2])
	OPERATE_CHECKS(AddVolatile, (&&)[2], (&&)[2])
	OPERATE_CHECKS(AddVolatile, (&)[2][3], (&)[2][3])
	OPERATE_CHECKS(AddVolatile, (&&)[2][3], (&&)[2][3])
}

