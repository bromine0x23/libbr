#pragma once

#include <libbr/config.hpp>

#if defined(NDEBUG)

#define BR_ASSERT(expr) ((void)0)

#else

extern "C" {

[[noreturn]] void libbr_assert(
	BR::CString<BR::NChar>  assertion,
	BR::CString<BR::NChar>  file,
	BR::Size line,
	BR::CString<BR::NChar>  func
);

} // extern "C"

#define BR_ASSERT(expr) ((expr) ? (void)0 : libbr_assert(BR_STRINGIFY(expr), __FILE__, __LINE__, __func__))

#endif // NDEBUG


