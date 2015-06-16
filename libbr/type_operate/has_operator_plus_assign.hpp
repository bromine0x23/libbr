#pragma once

#define BR_TYPE_OPERATE_OP_NAME PlusAssign
#define BR_TYPE_OPERATE_OP +=
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == pointer && TRhs == pointer */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsPointer< TRhsNoRef > \
	>, \
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
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsFundamental< TRhsNoCV >, \
		NotInteger< TRhsNoRef > \
	>,\
	/* TRhs == pointer && TLhs == fundamental && TLhs != bool */\
	BooleanAnd<\
		IsPointer< TRhsNoRef >, \
		IsFundamental< TLhsNoCV >, \
		NotSame< TLhsNoRef, bool > \
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
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/detail/has_binary_operator.hpp>