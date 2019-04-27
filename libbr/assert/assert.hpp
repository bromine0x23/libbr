#pragma once

#include <libbr/config.hpp>

#if defined(NDEBUG) || defined(BR_DOXYGEN)

/**
 * @brief 断言宏
 */
#define BR_ASSERT(expr) ((void)0)

/**
 * @brief 断言宏（可指定消息内容）
 */
#define BR_ASSERT_MESSAGE(expr, message) ((void)0)

#else

extern "C" {

[[noreturn]] void libbr_assert(
	BR::NChar const * assertion,
	BR::NChar const * file,
	BR::Size line,
	BR::NChar const * function,
	BR::NChar const * message = nullptr
);

} // extern "C"

#define BR_ASSERT(expr) ((expr) ? (void)0 : libbr_assert(BR_STRINGIFY(expr), __FILE__, __LINE__, __func__))

#define BR_ASSERT_MESSAGE(expr, message) ((expr) ? (void)0 : libbr_assert(BR_STRINGIFY(expr), __FILE__, __LINE__, __func__, message))

#endif // NDEBUG


