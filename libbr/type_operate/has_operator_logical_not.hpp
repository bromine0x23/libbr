#pragma once

#if defined(BR_GCC) && (BR_GCC_FULL_VER > 40800)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

#define BR_TYPE_OPERATE_OP_NAME LogicalNot
#define BR_TYPE_OPERATE_OP !
#define BR_TYPE_OPERATE_FORBIDDEN_IF false

#include <libbr/type_operate/detail/has_prefix_operator.inc>

#if defined(BR_GCC) && (BR_GCC_FULL_VER > 40800)
#pragma GCC diagnostic pop
#endif
