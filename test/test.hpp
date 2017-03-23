#pragma once

#if defined(BR_MSVC)
#pragma warning(push)
#pragma warning(disable: 4996)
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#elif defined(BR_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wsign-compare"
#elif defined(BR_GCC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

#include <gtest/gtest.h>

#if defined(BR_MSVC)
#pragma warning(pop)
#elif defined(BR_CLANG)
#pragma clang diagnostic pop
#elif defined(BR_GCC)
#pragma GCC diagnostic pop
#endif