#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C RightShiftAssign
#define BR_TYPE_OPERATE_OP_NAME_V right_shift_assign
#define BR_TYPE_OPERATE_OP >>=
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == fundamental && TRhs == fundamental && (TLhs != integer || TRhs != integer) */ \
	BooleanAnd< \
		IsFundamental< TLhsNoCV >, \
		IsFundamental< TRhsNoCV >, \
		BooleanOr< \
			NotIntegral< TLhsNoRef >, \
			NotIntegral< TRhsNoRef > \
		> \
	>, \
	/* TLhs == fundamental && TRhs == pointer */ \
	BooleanAnd<\
		IsFundamental< TLhsNoCV >, \
		IsPointer< TRhsNoRef > \
	>, \
	/* TRhs == fundamental && TLhs == pointer */ \
	BooleanAnd< \
		IsFundamental< TRhsNoCV >, \
		IsPointer< TLhsNoRef > \
	>, \
	/* TLhs == pointer && TRhs == pointer */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsPointer< TRhsNoRef > \
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
#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/detail/has_binary_operator.inc>
