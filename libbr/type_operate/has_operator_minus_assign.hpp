#pragma once

#define BR_TYPE_OPERATE_OP_NAME MinusAssign
#define BR_TYPE_OPERATE_OP -=
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == pointer && TRhs == fundamental && TRhs != integral */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsFundamental< TRhsNoCV >, \
		NotInteger< TRhsNoRef > \
	>, \
	/* TLhs == void * && TRhs == fundamental */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsVoid< TLhsNoPtr >, \
		IsFundamental< TRhsNoCV > \
	>, \
	/* TRhs == void * && TLhs == fundamental */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsVoid< TRhsNoPtr >, \
		IsFundamental< TLhsNoCV > \
	>, \
	/* TLhs == fundamental && TRhs == pointer */ \
	BooleanAnd< \
		IsFundamental< TLhsNoCV >, \
		IsPointer< TRhsNoRef > \
	>, \
	/* two pointers */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsPointer< TRhsNoRef > \
	>, \
	/* (TLhs == fundamental || TLhs == pointer) && (TRhs == fundamental || TRhs == pointer) && (TLhs == const) */ \
	BooleanAnd< \
		BooleanOr< \
			IsFundamental< TLhsNoCV >, \
			IsPointer< TLhsNoRef > \
		>, \
		BooleanOr< \
			IsFundamental< TRhsNoCV >, \
			IsPointer< TRhsNoRef > \
		>, \
		IsConst< TLhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_fundamental.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/detail/has_binary_operator.hpp>