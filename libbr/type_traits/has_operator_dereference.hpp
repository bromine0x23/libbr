#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C Dereference
#define BR_TYPE_OPERATE_OP_NAME_V dereference
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

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integer.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/detail/has_prefix_operator.inc>
