/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

/**
 * @brief 主名字空间
 * @author Bromine0x23
 * @since 2015/6/16
 */
namespace BR {

} // namespace BR

#if defined(BR_DOXYGEN)

/**
 *  @brief 是否以debug模式编译
 */
#define BR_DEBUG

/**
 * @brief 用于用户指定配置文件
 */
#define BR_USER_CONFIG

/**
 * @brief 编译器配置文件路径
 */
#define BR_COMPILER_CONFIG

/**
 * @brief 平台配置文件路径
 */
#define BR_PLATFORM_CONFIG

/**
 * @brief 编译器
 */
#define BR_COMPILER "Compiler"

/**
 * @brief 使用GCC编译器
 */
#define BR_GCC

/**
 * @brief GCC版本号（无补丁号）
 */
#define BR_GCC_VER

/**
 * @brief GCC版本号（有补丁号）
 */
#define BR_GCC_FULL_VER

/**
 * @brief 使用Clang编译器
 */
#define BR_CLANG

/**
 * @brief Clang版本号（无补丁号）
 */
#define BR_CLANG_VER

/**
 * @brief 使用MSVC编译器
 */
#define BR_MSVC

/**
 * @brief MSVC版本号（短）
 */
#define BR_MSVC_VER

/**
 * @brief MSVC版本号（长）
 */
#define BR_MSVC_FULL_VER

/**
 * @brief 目标平台信息
 */
#define BR_PLATFORM "Platform"

/**
 * @brief 目标平台Linux
 */
#define BR_LINUX

/**
 * @brief 目标平台Cygwin
 */
#define BR_CYGWIN

/**
 * @brief 目标平台Win32
 */
#define BR_Win32

/**
 * @brief 使用C++11及之后的C++标准时定义
 */
#define BR_CXX11

/**
 * @brief 使用C++11之后的C++标准时定义
 */
#define BR_AFTER_CXX11

/**
 * @brief 使用C++14及之后的C++标准时定义
 */
#define BR_CXX14

/**
 * @brief 使用C++11之后的C++标准时为转换为 constexpr
 *
 * 由于C++14开始放宽了对 constexpr 函数的限制，一些函数得以用 constexpr 修饰.
 * 该宏用于修饰这些能够在C++14中提升的函数.
 */
#define BR_CONSTEXPR_AFTER_CXX11

/**
 * @brief 导出符号
 */
#define BR_SYMBOL_EXPORT

/**
 * @brief 导入符号
 */
#define BR_SYMBOL_IMPORT

/**
 * @brief 可见符号
 */
#define BR_SYMBOL_VISIBLE

/**
 * @brief 强制内联
 *
 * 当编译器不支持强制内联时定义为 inline
 */
#define BR_FORCEINLINE

/**
 * @brief 当编译器不支持强制内联时定义
 */
#define BR_NO_FORCEINLINE

/**
 * @brief 禁止内联
 */
#define BR_NOINLINE

/**
 * @brief 当编译器不支持禁止内联时定义
 */
#define BR_NO_NOINLINE

/**
 * @brief 很可能为真的表达式
 */
#define BR_LIKELY(x)

/**
 * @brief 很可能为假的表达式
 */
#define BR_UNLIKELY(x)

/**
 * @brief 将X转化为字符串表示
 */
#define BR_STRINGIZE(X)

/**
 * @brief 链接X和Y
 */
#define BR_JOIN(X, Y)

/**
 * @brief 空
 */
#define BR_EMPTY_ARG

/**
 * @brief fallthrough
 */
#define BR_FALLTHROUGH

/**
 * @brief 是否具有128位整形
 */
#define BR_HAS_INT128

/**
 * @brief 无符号128位整形
 */
#define BR_UINT128

/**
 * @brief 有符号128位整形
 */
#define BR_SINT128

#else

#include <libbr/config/config.hpp>

#endif
