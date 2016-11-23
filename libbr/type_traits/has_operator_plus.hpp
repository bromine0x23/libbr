#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C Plus
#define BR_TYPE_OPERATE_OP_NAME_V plus
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
		NotIntegral< TRhsNoRef > \
	>, \
	/* TRhs == pointer && TLhs == fundamental && TLhs != integral */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsFundamental< TLhsNoCV >, \
		NotIntegral< TLhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/type_traits/detail/has_binary_operator.inc>