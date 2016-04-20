#include <libbr/type_operate/remove_extent.hpp>

#include "test.hpp"

using namespace BR;

TEST(TestTypeOperate, RemoveExtent) {
	OPERATE_CHECKS(RemoveExtent, BR_EMPTY, BR_EMPTY)
	OPERATE_CHECKS(RemoveExtent, const, const)
	OPERATE_CHECKS(RemoveExtent, volatile, volatile)
	OPERATE_CHECKS(RemoveExtent, const volatile, const volatile)
	OPERATE_CHECKS(RemoveExtent, *, *)
	OPERATE_CHECKS(RemoveExtent, * const, * const)
	OPERATE_CHECKS(RemoveExtent, * volatile, * volatile)
	OPERATE_CHECKS(RemoveExtent, * const volatile, * const volatile)
	OPERATE_CHECKS(RemoveExtent, const *, const *)
	OPERATE_CHECKS(RemoveExtent, volatile *, volatile *)
	OPERATE_CHECKS(RemoveExtent, const * const, const * const)
	OPERATE_CHECKS(RemoveExtent, const * volatile, const * volatile)
	OPERATE_CHECKS(RemoveExtent, const * const volatile, const * const volatile)
	OPERATE_CHECKS(RemoveExtent, &, &)
	OPERATE_CHECKS(RemoveExtent, const &, const &)
	OPERATE_CHECKS(RemoveExtent, volatile &, volatile &)
	OPERATE_CHECKS(RemoveExtent, const volatile &, const volatile &)
	OPERATE_CHECKS(RemoveExtent, &&, &&)
	OPERATE_CHECKS(RemoveExtent, const &&, const &&)
	OPERATE_CHECKS(RemoveExtent, volatile &&, volatile &&)
	OPERATE_CHECKS(RemoveExtent, const volatile &&, const volatile &&)
	OPERATE_CHECKS(RemoveExtent, [2], BR_EMPTY)
	OPERATE_CHECKS(RemoveExtent, const[2], const)
	OPERATE_CHECKS(RemoveExtent, volatile[2], volatile)
	OPERATE_CHECKS(RemoveExtent, const volatile[2], const volatile)
	OPERATE_CHECKS(RemoveExtent, [2][3], [3])
	OPERATE_CHECKS(RemoveExtent, const[2][3], const[3])
	OPERATE_CHECKS(RemoveExtent, volatile[2][3], volatile[3])
	OPERATE_CHECKS(RemoveExtent, const volatile[2][3], const volatile[3])
	OPERATE_CHECKS(RemoveExtent, [][3], [3])
	OPERATE_CHECKS(RemoveExtent, const[][3], const[3])
	OPERATE_CHECKS(RemoveExtent, volatile[][3], volatile[3])
	OPERATE_CHECKS(RemoveExtent, const volatile[][3], const volatile[3])
	OPERATE_CHECKS(RemoveExtent, (&)[2], (&)[2])
	OPERATE_CHECKS(RemoveExtent, (&&)[2], (&&)[2])
	OPERATE_CHECKS(RemoveExtent, (&)[2][3], (&)[2][3])
	OPERATE_CHECKS(RemoveExtent, (&&)[2][3], (&&)[2][3])
}