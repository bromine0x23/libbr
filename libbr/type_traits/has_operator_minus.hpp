#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C Minus
#define BR_TYPE_OPERATE_OP_NAME_V minus
#define BR_TYPE_OPERATE_OP -
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == pointer && TRhs == fundamental && TRhs != integral */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsFundamental< TRhsNoCV >, \
		NotIntegral< TRhsNoRef > \
	>, \
	/* TLhs == void * && (TRhs == fundamental || TRhs == pointer) */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsVoid< TLhsNoPtr >, \
		BooleanOr< \
			IsFundamental< TRhsNoCV >, \
			IsPointer< TRhsNoRef > \
		> \
	>, \
	/* TRhs == void * && (TLhs == fundamental || TLhs == pointer) */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsVoid< TRhsNoPtr >, \
		BooleanOr< \
			IsFundamental< TLhsNoCV >, \
			IsPointer< TLhsNoRef > \
		> \
	>, \
	/* TLhs == fundamental && TRhs == pointer */ \
	BooleanAnd< \
		IsFundamental< TLhsNoCV >, \
		IsPointer< TRhsNoRef > \
	>, \
	/* two different pointers */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsPointer< TRhsNoRef >, \
		NotSame< TLhsNoCV, TRhsNoCV > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/type_traits/detail/has_binary_operator.inc>