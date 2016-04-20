#include <libbr/type_operate/add_lvalue_reference.hpp>

#include "test.hpp"

using namespace BR;

TEST(TestTypeOperate, AddLValueReference) {
	OPERATE_CHECKS(AddLValueReference, BR_EMPTY, &)
	OPERATE_CHECKS(AddLValueReference, const, const &)
	OPERATE_CHECKS(AddLValueReference, volatile, volatile &)
	OPERATE_CHECKS(AddLValueReference, const volatile, const volatile &)
	OPERATE_CHECKS(AddLValueReference, *, * &)
	OPERATE_CHECKS(AddLValueReference, * const, * const &)
	OPERATE_CHECKS(AddLValueReference, * volatile, * volatile &)
	OPERATE_CHECKS(AddLValueReference, * const volatile, * const volatile &)
	OPERATE_CHECKS(AddLValueReference, const *, const * &)
	OPERATE_CHECKS(AddLValueReference, volatile *, volatile * &)
	OPERATE_CHECKS(AddLValueReference, const * const, const * const &)
	OPERATE_CHECKS(AddLValueReference, const * volatile, const * volatile &)
	OPERATE_CHECKS(AddLValueReference, const * const volatile, const * const volatile &)
	OPERATE_CHECKS(AddLValueReference, &, &)
	OPERATE_CHECKS(AddLValueReference, const &, const &)
	OPERATE_CHECKS(AddLValueReference, volatile &, volatile &)
	OPERATE_CHECKS(AddLValueReference, const volatile &, const volatile &)
	OPERATE_CHECKS(AddLValueReference, &&, &)
	OPERATE_CHECKS(AddLValueReference, const &&, const &)
	OPERATE_CHECKS(AddLValueReference, volatile &&, volatile &)
	OPERATE_CHECKS(AddLValueReference, const volatile &&, const volatile &)
	OPERATE_CHECKS(AddLValueReference, [2], (&)[2])
	OPERATE_CHECKS(AddLValueReference, const[2], const(&)[2])
	OPERATE_CHECKS(AddLValueReference, volatile[2], volatile(&)[2])
	OPERATE_CHECKS(AddLValueReference, const volatile[2], const volatile(&)[2])
	OPERATE_CHECKS(AddLValueReference, [2][3], (&)[2][3])
	OPERATE_CHECKS(AddLValueReference, const[2][3], const(&)[2][3])
	OPERATE_CHECKS(AddLValueReference, volatile[2][3], volatile(&)[2][3])
	OPERATE_CHECKS(AddLValueReference, const volatile[2][3], const volatile(&)[2][3])
	OPERATE_CHECKS(AddLValueReference, [][3], (&)[][3])
	OPERATE_CHECKS(AddLValueReference, const[][3], const(&)[][3])
	OPERATE_CHECKS(AddLValueReference, volatile[][3], volatile(&)[][3])
	OPERATE_CHECKS(AddLValueReference, const volatile[][3], const volatile(&)[][3])
	OPERATE_CHECKS(AddLValueReference, (&)[2], (&)[2])
	OPERATE_CHECKS(AddLValueReference, (&&)[2], (&)[2])
	OPERATE_CHECKS(AddLValueReference, (&)[2][3], (&)[2][3])
	OPERATE_CHECKS(AddLValueReference, (&&)[2][3], (&)[2][3])
}