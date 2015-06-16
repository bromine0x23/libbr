#pragma once

#include <libbr/config.hpp>

#if defined(BR_GCC)
# define BR_CURRENT_FUNCTION __PRETTY_FUNCTION__
#else
# define BR_CURRENT_FUNCTION __func__
#endif
