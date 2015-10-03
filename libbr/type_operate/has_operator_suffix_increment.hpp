#pragma once

#define BR_TYPE_OPERATE_OP_NAME SuffixIncrement
#define BR_TYPE_OPERATE_OP ++
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
#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/type_operate/detail/has_suffix_operator.inc>