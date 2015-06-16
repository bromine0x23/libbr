#pragma once

#define BR_TYPE_OPERATE_OP_NAME SuffixDecrement
#define BR_TYPE_OPERATE_OP --
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
BooleanOr< \
	/* bool */ \
	IsSame< TLhsNoCV, bool >, \
	/* void * */ \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsVoid< TLhsNoPtr > \
	>, \
	/* (fundamental || pointer) && const */ \
	BooleanAnd< \
		BooleanOr< \
			IsFundamental< TLhsNoCV >, \
			IsPointer< TLhsNoRef > \
		>, \
		IsConst< TLhsNoRef > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_const.hpp>
#include <libbr/type_operate/is_fundamental.hpp>
#include <libbr/type_operate/is_pointer.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/detail/has_suffix_operator.hpp>