#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C BitNot
#define BR_TYPE_OPERATE_OP_NAME_V bit_not
#define BR_TYPE_OPERATE_OP ~
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* pointer */ \
	IsPointer< TRhsNoRef >, \
	/* fundamental non integral */ \
	BooleanAnd< \
		IsFundamental< TRhsNoRef >, \
		NotIntegral< TRhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/detail/has_prefix_operator.inc>