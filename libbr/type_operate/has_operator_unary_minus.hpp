#pragma once

#define BR_TYPE_OPERATE_OP_NAME UnaryMinus
#define BR_TYPE_OPERATE_OP -
#define BR_TYPE_OPERATE_FORBIDDEN_IF IsPointer< TRhsNoRef >::value

#include <libbr/type_operate/detail/has_prefix_operator.inc>