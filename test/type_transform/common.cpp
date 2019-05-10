#include "test.hpp"

#include <libbr/type_transform/common.hpp>

using namespace BR;

namespace {

struct C1 {};

struct C2 {};

struct C3 : C2 {};

struct C1C2 {
	C1C2() = default;
	C1C2(C1 const &) {}
	C1C2(C2 const &) {}
	auto operator=(C1C2 const &) -> C1C2 & = default;
};

}

TEST(TypeTransform, Common) {
	TRANSFORM_CHECK(Common, C1C2, C1, C1C2)
	TRANSFORM_CHECK(Common, C1C2, C1, C1C2, C2)
	TRANSFORM_CHECK(Common, C1C2, C2, C1C2)
	TRANSFORM_CHECK(Common, C1C2, C2, C1C2, C1)
	TRANSFORM_CHECK(Common, C1C2, C1C2, C1)
	TRANSFORM_CHECK(Common, C1C2, C1C2, C2)
	TRANSFORM_CHECK(Common, C1C2, C1C2, C1, C2)
	TRANSFORM_CHECK(Common, C1C2, C1C2 &, C1 &)
	TRANSFORM_CHECK(Common, C2 *, C2 *, C3 *)
	TRANSFORM_CHECK(Common, C2 *, C3 *, C2 *)

	TRANSFORM_CHECK(Common, int const *         , int *, int const *                )
	TRANSFORM_CHECK(Common, int       volatile *, int *,              int volatile *)
	TRANSFORM_CHECK(Common, int const volatile *,        int const *, int volatile *)
	TRANSFORM_CHECK(Common, int const volatile *, int *, int const *, int volatile *)

	TRANSFORM_CHECK(Common,   signed int, char,   signed char)
	TRANSFORM_CHECK(Common,   signed int, char, unsigned char)
	TRANSFORM_CHECK(Common,   signed int, char,   signed short)
	TRANSFORM_CHECK(Common,   signed int, char, unsigned short)
	TRANSFORM_CHECK(Common,   signed int, char,   signed int)
	TRANSFORM_CHECK(Common, unsigned int, char, unsigned int)

	TRANSFORM_CHECK(Common, double, char, int, double)
}