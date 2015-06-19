#pragma once

#define BR_TYPE_OPERATE_OP_NAME Plus
#define BR_TYPE_OPERATE_OP +
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == pointer && TRhs == pointer */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsFundamental< TRhsNoRef > \
	>,\
	/* TLhs == void * && TRhs == fundamental */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsVoid< TLhsNoRef >, \
		IsFundamental< TRhsNoCV > \
	>, \
	/* TRhs == void * && TLhs == fundamental */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsVoid< TRhsNoPtr >, \
		IsFundamental< TLhsNoCV > \
	>, \
	/* TLhs == pointer && TRhs == fundamental && TRhs != integral */ \
	BooleanAnd<\
		IsPointer< TLhsNoRef >, \
		IsFundamental< TRhsNoCV >, \
		NotInteger< TRhsNoRef > \
	>, \
	/* TRhs == pointer && TLhs == fundamental && TLhs != integral */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsFundamental< TLhsNoCV >, \
		NotInteger< TLhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_fundamental.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/detail/has_binary_operator.inc>