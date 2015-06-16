#pragma once

#define BR_TYPE_OPERATE_OP_NAME Greater
#define BR_TYPE_OPERATE_OP >
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* TLhs == pointer && TRhs == fundamental */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsFundamental< TRhsNoCV > \
	>, \
	/* TRhs == pointer && TLhs == fundamental */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsFundamental< TLhsNoCV > \
	>, \
	/* TLhs == pointer && TRhs == pointer && TLhs != base(TRhs) && TRhs != base(TLhs) && TLhs != void * && TRhs != void * */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsPointer< TRhsNoRef >, \
		NotBaseOf< TLhsNoPtr, TRhsNoPtr >, \
		NotBaseOf< TRhsNoPtr, TLhsNoPtr >, \
		NotSame< TLhsNoPtr, TRhsNoPtr >, \
		NotVoid< TLhsNoPtr >, \
		NotVoid< TRhsNoPtr > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_base_of.hpp>
#include <libbr/type_operate/is_fundamental.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/detail/has_binary_operator.hpp>