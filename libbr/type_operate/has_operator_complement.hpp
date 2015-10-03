#pragma once

#define BR_TYPE_OPERATE_OP_NAME Complement
#define BR_TYPE_OPERATE_OP ~
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* pointer */ \
	IsPointer< TRhsNoRef >, \
	/* fundamental non integral */ \
	BooleanAnd< \
		IsFundamental< TRhsNoRef >, \
		NotInteger< TRhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integer.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_operate/detail/has_prefix_operator.inc>