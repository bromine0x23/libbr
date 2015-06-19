#pragma once

#define BR_TYPE_OPERATE_OP_NAME PrefixIncrement
#define BR_TYPE_OPERATE_OP ++
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* bool */ \
	IsSame< TRhsNoCV, bool >, \
	/* void * */ \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsVoid< TRhsNoPtr > \
	>, \
	/* (fundamental || pointer) && const */ \
	BooleanAnd< \
		BooleanOr< \
			IsFundamental< TRhsNoCV >, \
			IsPointer< TRhsNoRef > \
		>, \
		IsConst< TRhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_const.hpp>
#include <libbr/type_operate/is_fundamental.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/detail/has_prefix_operator.inc>
