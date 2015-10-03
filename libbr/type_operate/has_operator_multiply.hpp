#pragma once

#define BR_TYPE_OPERATE_OP_NAME Multiply
#define BR_TYPE_OPERATE_OP *
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
/* pointer with pointer or fundamental */ \
BooleanOr< \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		BooleanOr< \
			IsPointer< TRhsNoRef >, \
			IsFundamental< TRhsNoCV > \
		> \
	>, \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		BooleanOr< \
			IsPointer< TLhsNoRef >, \
			IsFundamental< TLhsNoCV > \
		> \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_operate/detail/has_binary_operator.inc>