#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C LeftShift
#define BR_TYPE_OPERATE_OP_NAME_V left_shift
#define BR_TYPE_OPERATE_OP <<
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == fundamental && TRhs == fundamental && (TLhs != integral || TRhs != integral) */ \
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
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/detail/has_binary_operator.inc>