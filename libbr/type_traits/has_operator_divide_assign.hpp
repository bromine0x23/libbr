#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C DivideAssign
#define BR_TYPE_OPERATE_OP_NAME_V divide_assign
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

#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/detail/has_binary_operator.inc>
