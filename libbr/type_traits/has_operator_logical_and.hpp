#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C LogicalAnd
#define BR_TYPE_OPERATE_OP_NAME_V logical_and
#define BR_TYPE_OPERATE_OP &&
#define BR_TYPE_OPERATE_FORBIDDEN_IF \
/* pointer with fundamental non convertible to bool */ \
BooleanOr< \
	BooleanAnd< \
		IsPointer< TLhsNoRef >, \
		IsFundamental< TRhsNoCV >, \
		NotConvertible< TRhsNoCV, bool > \
	>, \
	BooleanAnd< \
		IsPointer< TRhsNoRef >, \
		IsFundamental< TLhsNoCV >, \
		NotConvertible< TLhsNoCV, bool > \
	> \
>::value \
/* BR_TYPE_OPERATE_FORBIDDEN_IF */

#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/detail/has_binary_operator.inc>