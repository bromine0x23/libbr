#pragma once

#if defined(BR_MSVC)
#pragma warning(push)
#pragma warning(disable: 4996)
#elif defined(BR_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#include <gtest/gtest.h>

#if defined(BR_MSVC)
#pragma warning(pop)
#elif defined(BR_CLANG)
#pragma clang diagnostic pop
#endif