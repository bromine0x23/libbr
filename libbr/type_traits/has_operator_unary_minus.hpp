#pragma once

#define BR_TYPE_OPERATE_OP_NAME_C UnaryMinus
#define BR_TYPE_OPERATE_OP_NAME_V unary_minus
#define BR_TYPE_OPERATE_OP -
#define BR_TYPE_OPERATE_FORBIDDEN_IF IsPointer< TRhsNoRef >::value

#include <libbr/type_traits/detail/has_prefix_operator.inc>