#include <libbr/type_operate/add_const_volatile.hpp>

#include "test.hpp"

using namespace BR;

TEST(TestTypeOperate, AddConstVolatile) {
	OPERATE_CHECKS(AddConstVolatile, BR_EMPTY, const volatile)
	OPERATE_CHECKS(AddConstVolatile, const, const volatile)
	OPERATE_CHECKS(AddConstVolatile, volatile, const volatile)
	OPERATE_CHECKS(AddConstVolatile, const volatile, const volatile)
	OPERATE_CHECKS(AddConstVolatile, *, * const volatile)
	OPERATE_CHECKS(AddConstVolatile, * const, * const volatile)
	OPERATE_CHECKS(AddConstVolatile, * volatile, * const volatile)
	OPERATE_CHECKS(AddConstVolatile, * const volatile, * const volatile)
	OPERATE_CHECKS(AddConstVolatile, const *, const * const volatile)
	OPERATE_CHECKS(AddConstVolatile, volatile *, volatile * const volatile)
	OPERATE_CHECKS(AddConstVolatile, const * const, const * const volatile)
	OPERATE_CHECKS(AddConstVolatile, const * volatile, const * const volatile)
	OPERATE_CHECKS(AddConstVolatile, const * const volatile, const * const volatile)
	OPERATE_CHECKS(AddConstVolatile, &, &)
	OPERATE_CHECKS(AddConstVolatile, const &, const &)
	OPERATE_CHECKS(AddConstVolatile, volatile &, volatile &)
	OPERATE_CHECKS(AddConstVolatile, const volatile &, const volatile &)
	OPERATE_CHECKS(AddConstVolatile, &&, &&)
	OPERATE_CHECKS(AddConstVolatile, const &&, const &&)
	OPERATE_CHECKS(AddConstVolatile, volatile &&, volatile &&)
	OPERATE_CHECKS(AddConstVolatile, const volatile &&, const volatile &&)
	OPERATE_CHECKS(AddConstVolatile, [2], const volatile[2])
	OPERATE_CHECKS(AddConstVolatile, const[2], const volatile[2])
	OPERATE_CHECKS(AddConstVolatile, volatile[2], const volatile[2])
	OPERATE_CHECKS(AddConstVolatile, const volatile[2], const volatile[2])
	OPERATE_CHECKS(AddConstVolatile, [2][3], const volatile[2][3])
	OPERATE_CHECKS(AddConstVolatile, const[2][3], const volatile[2][3])
	OPERATE_CHECKS(AddConstVolatile, volatile[2][3], const volatile[2][3])
	OPERATE_CHECKS(AddConstVolatile, const volatile[2][3], const volatile[2][3])
	OPERATE_CHECKS(AddConstVolatile, [][3], const volatile[][3])
	OPERATE_CHECKS(AddConstVolatile, const[][3], const volatile[][3])
	OPERATE_CHECKS(AddConstVolatile, volatile[][3], const volatile[][3])
	OPERATE_CHECKS(AddConstVolatile, const volatile[][3], const volatile[][3])
	OPERATE_CHECKS(AddConstVolatile, (&)[2], (&)[2])
	OPERATE_CHECKS(AddConstVolatile, (&&)[2], (&&)[2])
	OPERATE_CHECKS(AddConstVolatile, (&)[2][3], (&)[2][3])
	OPERATE_CHECKS(AddConstVolatile, (&&)[2][3], (&&)[2][3])
}

