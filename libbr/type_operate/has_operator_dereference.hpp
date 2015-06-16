#pragma once

#define BR_TYPE_OPERATE_OP_NAME Dereference
#define BR_TYPE_OPERATE_OP *
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
/* void* or fundamental */ \
BooleanOr< \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsVoid< TRhsNoPtr > \
	>, \
	IsFundamental< TRhsNoCV > \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/is_fundamental.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/detail/has_prefix_operator.hpp>
