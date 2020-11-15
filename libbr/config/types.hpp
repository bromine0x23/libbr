/**
 * @file
 * @brief 类型定义
 * @author Bromine0x23
 */
#pragma once

#include <climits>

namespace BR {

#if UCHAR_MAX == 0xFF
using SInt8 =   signed char;
using UInt8 = unsigned char;
#elif USHRT_MAX == 0xFF
using SInt8 =   signed short;
using UInt8 = unsigned short;
#else
#  error "defaults not correct; you must hand modify libbr/typedef.hpp"
#endif

#if USHRT_MAX == 0xFFFF
using SInt16 =   signed short;
using UInt16 = unsigned short;
#elif UINT_MAX == 0xFFFF
using SInt16 =   signed int;
using UInt16 = unsigned int;
#else
#  error "defaults not correct; you must hand modify libbr/typedef.hpp"
#endif

#if UINT_MAX == 0xFFFFFFFF
using SInt32 =   signed int;
using UInt32 = unsigned int;
#elif ULONG_MAX == 0xFFFFFFFF
using SInt32 =   signed long;
using UInt32 = unsigned long;
#else
#  error "defaults not correct; you must hand modify libbr/typedef.hpp"
#endif

#if ULONG_MAX == 0xFFFFFFFFFFFFFFFFULL
using SInt64 =   signed long;
using UInt64 = unsigned long;
#elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFFULL
using SInt64 =   signed long long;
using UInt64 = unsigned long long;
#else
#  error "defaults not correct; you must hand modify libbr/typedef.hpp"
#endif


#if defined(BR_HAS_INT128) || defined(BR_DOXYGEN)

using SInt128 = BR_SINT128;

using UInt128 = BR_UINT128;

#endif // defined(BR_HAS_INT128) || defined(BR_DOXYGEN)

constexpr static auto BIT_PER_BYTE = CHAR_BIT;

constexpr static auto BIT_PER_CHAR = CHAR_BIT;

using SSize = decltype(static_cast<char *>(nullptr) - static_cast<char *>(nullptr));

using USize = decltype(sizeof(char));

/**
 * @deprecated
 */
using Size = USize;

/**
 * @deprecated
 */
using PointerDifference = SSize;

#if defined(BR_HAS_INTPTR)

using SIntPointer = BR_SINTPTR;

using UIntPointer = BR_UINTPTR;

#else

using SIntPointer = SSize;

using UIntPointer = USize;

#endif // defined(BR_HAS_INTPTR)

} // namespace BR

namespace BR {

/**
 * @brief 窄字符（ASCII字符）
 */
using NChar = char;

/**
 * @brief 宽字符
 */
using WChar = wchar_t;

/**
 * @brief 8位字符
 */
using Char8 = char;

/**
 * @brief 16位字符
 */
using Char16 = char16_t;

/**
 * @brief 32位字符
 */
using Char32 = char32_t;

/**
 * @brief 布尔值
 */
using Boolean = bool;

/**
 * @brief 有符号整数
 */
using SInt = signed int;

/**
 * @brief 无符号整数
 */
using UInt = unsigned int;

/**
 * @brief 单精度浮点数
 */
using SFloat = float;

/**
 * @brief 双精度浮点数
 */
using DFloat = double;

/**
 * @brief 四精度浮点数
 */
using QFloat = long double;

using Float32 = float;

using Float64 = double;

using Float96 = long double;

/**
 * @brief 字节
 */
using Byte  = UInt8;

/**
 * @brief 字
 */
using Word  = UInt16;

/**
 * @brief 双字
 */
using DWord = UInt32;

/**
 * @brief 四字
 */
using QWord = UInt64;

#if defined(BR_HAS_INT128) || defined(BR_DOXYGEN)

/**
 * @brief 八字
 */
using OWord = UInt128;

#endif // defined(BR_HAS_INT128) || defined(BR_DOXYGEN)

/**
 * @brief 空指针类型
 */
using NullPointer = decltype(nullptr);

/**
 * @brief C风格指针
 */
template< typename T >
using CPointer = T *;

/**
 * @brief C风格数组
 */
template< typename T, Size S >
using CArray = T[S];

/**
 * @brief 无界C风格数组
 */
template< typename T >
using CArrayUnbound = T[];

/**
 * @brief C风格字符串
 */
template< typename TChar >
using CString = TChar const *;

template< typename TResult, typename ... TArguments >
using CFunction = auto (TArguments...) -> TResult;

template<typename TClass, typename TMember>
using MemberPointer = TMember TClass::*;

struct MaxAlignType {
	alignas(alignof(long long)) long long ll;
	alignas(alignof(long double)) long double ld;
};

static_assert(BIT_PER_BYTE * sizeof(SInt8)  ==  8, "SInt8  isn't excatly  8 bits.");
static_assert(BIT_PER_BYTE * sizeof(SInt16) == 16, "SInt16 isn't excatly 16 bits.");
static_assert(BIT_PER_BYTE * sizeof(SInt32) == 32, "SInt32 isn't excatly 32 bits.");
static_assert(BIT_PER_BYTE * sizeof(SInt64) == 64, "SInt64 isn't excatly 64 bits.");

static_assert(BIT_PER_BYTE * sizeof(UInt8)  ==  8, "UInt8  isn't excatly  8 bits.");
static_assert(BIT_PER_BYTE * sizeof(UInt16) == 16, "UInt16 isn't excatly 16 bits.");
static_assert(BIT_PER_BYTE * sizeof(UInt32) == 32, "UInt32 isn't excatly 32 bits.");
static_assert(BIT_PER_BYTE * sizeof(UInt64) == 64, "UInt64 isn't excatly 64 bits.");

static_assert(BIT_PER_BYTE * sizeof(Float32) == 32, "Float32 isn't excatly 32 bits.");
static_assert(BIT_PER_BYTE * sizeof(Float64) == 64, "Float64 isn't excatly 64 bits.");

} // namespace BR