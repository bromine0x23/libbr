#include <libbr/type_operate/add_const.hpp>

#include "test.hpp"

using namespace BR;

TEST(TypeOperate, AddConst) {
	OPERATE_CHECKS(AddConst, BR_EMPTY, const)
	OPERATE_CHECKS(AddConst, const, const)
	OPERATE_CHECKS(AddConst, volatile, const volatile)
	OPERATE_CHECKS(AddConst, const volatile, const volatile)
	OPERATE_CHECKS(AddConst, *, * const)
	OPERATE_CHECKS(AddConst, * const, * const)
	OPERATE_CHECKS(AddConst, * volatile, * const volatile)
	OPERATE_CHECKS(AddConst, * const volatile, * const volatile)
	OPERATE_CHECKS(AddConst, const *, const * const)
	OPERATE_CHECKS(AddConst, volatile *, volatile * const)
	OPERATE_CHECKS(AddConst, const * const, const * const)
	OPERATE_CHECKS(AddConst, const * volatile, const * const volatile)
	OPERATE_CHECKS(AddConst, const * const volatile, const * const volatile)
	OPERATE_CHECKS(AddConst, &, &)
	OPERATE_CHECKS(AddConst, const &, const &)
	OPERATE_CHECKS(AddConst, volatile &, volatile &)
	OPERATE_CHECKS(AddConst, const volatile &, const volatile &)
	OPERATE_CHECKS(AddConst, &&, &&)
	OPERATE_CHECKS(AddConst, const &&, const &&)
	OPERATE_CHECKS(AddConst, volatile &&, volatile &&)
	OPERATE_CHECKS(AddConst, const volatile &&, const volatile &&)
	OPERATE_CHECKS(AddConst, [2], const[2])
	OPERATE_CHECKS(AddConst, const[2], const[2])
	OPERATE_CHECKS(AddConst, volatile[2], const volatile[2])
	OPERATE_CHECKS(AddConst, const volatile[2], const volatile[2])
	OPERATE_CHECKS(AddConst, [2][3], const[2][3])
	OPERATE_CHECKS(AddConst, const[2][3], const[2][3])
	OPERATE_CHECKS(AddConst, volatile[2][3], const volatile[2][3])
	OPERATE_CHECKS(AddConst, const volatile[2][3], const volatile[2][3])
	OPERATE_CHECKS(AddConst, [][3], const[][3])
	OPERATE_CHECKS(AddConst, const[][3], const[][3])
	OPERATE_CHECKS(AddConst, volatile[][3], const volatile[][3])
	OPERATE_CHECKS(AddConst, const volatile[][3], const volatile[][3])
	OPERATE_CHECKS(AddConst, (&)[2], (&)[2])
	OPERATE_CHECKS(AddConst, (&&)[2], (&&)[2])
	OPERATE_CHECKS(AddConst, (&)[2][3], (&)[2][3])
	OPERATE_CHECKS(AddConst, (&&)[2][3], (&&)[2][3])
}

