#pragma once

#include <libbr/config.hpp>

#if defined(NDEBUG)

#define BR_ASSERT(expr) ((void)0)

#define BR_ASSERT_MESSAGE(expr, message) ((void)0)

#else

extern "C" {

[[noreturn]] void libbr_assert(
	BR::CString<BR::NChar> assertion,
	BR::CString<BR::NChar> file,
	BR::Size line,
	BR::CString<BR::NChar> function,
	BR::CString<BR::NChar> message = nullptr
);

} // extern "C"

#define BR_ASSERT(expr) ((expr) ? (void)0 : libbr_assert(BR_STRINGIFY(expr), __FILE__, __LINE__, __func__))

#define BR_ASSERT_MESSAGE(expr, message) ((expr) ? (void)0 : libbr_assert(BR_STRINGIFY(expr), __FILE__, __LINE__, __func__, message))

#endif // NDEBUG


