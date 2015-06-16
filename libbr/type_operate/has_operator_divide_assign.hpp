#pragma once

#define BR_TYPE_OPERATE_OP_NAME DivideAssign
#define BR_TYPE_OPERATE_OP /=
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == pointer && (TRhs == pointer || TRhs == fundamental) */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		BooleanOr< \
			IsPointer< TRhsNoRef >, \
			IsFundamental< TRhsNoCV > \
		> \
	>, \
	/* TRhs == pointer && (TLhs == pointer || TLhs == fundamental) */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		BooleanOr< \
			IsPointer< TLhsNoRef >, \
			IsFundamental< TLhsNoCV > \
		> \
	>, \
	/* TLhs == fundamental && TRhs == fundamental && TLhs == const */ \
	BooleanAnd< \
		IsFundamental< TLhsNoCV >, \
		IsFundamental< TRhsNoCV >, \
		IsConst< TLhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_const.hpp>
#include <libbr/type_operate/is_fundamental.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/detail/has_binary_operator.hpp>
