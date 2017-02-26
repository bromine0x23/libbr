/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#if defined(BR_DOXYGEN)

namespace BR {

/**
 * @brief 有符号8位整形
 * @post 类型位宽为8
 */
using SInt8 = signed_integer_with_8bits;

/**
 * @brief 有符号16位整形
 * @post 类型位宽为16
 */
using SInt16 = signed_integer_with_16bits;

/**
 * @brief 有符号32位整形
 * @post 类型位宽为32
 */
using SInt32 = signed_integer_with_32bits;

/**
 * @brief 有符号64位整形
 * @post 类型位宽为64
 */
using SInt64 = signed_integer_with_64bits;

/**
 * @brief 无符号8位整形
 * @post 类型位宽为8
 */
using UInt8 = unsigned_integer_with_8bits;

/**
 * @brief 无符号16位整形
 * @post 类型位宽为16
 */
using UInt16 = unsigned_integer_with_16bits;

/**
 * @brief 无符号32位整形
 * @post 类型位宽为32
 */
using UInt32 = unsigned_integer_with_32bits;

/**
 * @brief 无符号64位整形
 * @post 类型位宽为64
 */
using UInt64 = unsigned_integer_with_64bits;

/**
 * @brief 单个字节的位宽
 */
constexpr static auto BIT_PER_BYTE = bit_per_byte;

/**
 * @brief sizeof结果的类型
 */
using Size = type_for_sizeof_result;

/**
 * @brief 指针求差结果的类型
 */
using PointerDifference = type_of_difference_between_pointers;

} // namespace BR

#elif defined(BR_GCC) // defined(BR_DOXYGEN)

namespace BR {

using SInt8  = __INT8_TYPE__;

using SInt16 = __INT16_TYPE__;

using SInt32 = __INT32_TYPE__;

using SInt64 = __INT64_TYPE__;

using UInt8  = __UINT8_TYPE__;

using UInt16 = __UINT16_TYPE__;

using UInt32 = __UINT32_TYPE__;

using UInt64 = __UINT64_TYPE__;

constexpr static auto BIT_PER_BYTE = __CHAR_BIT__;

constexpr static auto BIT_PER_CHAR = __CHAR_BIT__;

using Size = __SIZE_TYPE__;

using PointerDifference = __PTRDIFF_TYPE__;

} // namespace BR

#else // defined(BR_DOXYGEN)

#include <climits>

namespace BR {

#  if UCHAR_MAX == 0xFF
using SInt8 =   signed char;
using UInt8 = unsigned char;
#  elif USHRT_MAX == 0xFF
using SInt8 =   signed short;
using UInt8 = unsigned short;
#  else
#    error "defaults not correct; you must hand modify libbr/typedef.hpp"
#  endif

#  if USHRT_MAX == 0xFFFF
using SInt16 =   signed short;
using UInt16 = unsigned short;
#  elif UINT_MAX == 0xFFFF
using SInt16 =   signed int;
using UInt16 = unsigned int;
#  else
#    error "defaults not correct; you must hand modify libbr/typedef.hpp"
#  endif

#  if UINT_MAX == 0xFFFFFFFF
using SInt32 =   signed int;
using UInt32 = unsigned int;
#  elif ULONG_MAX == 0xFFFFFFFF
using SInt32 =   signed long;
using UInt32 = unsigned long;
#  else
#    error "defaults not correct; you must hand modify libbr/typedef.hpp"
#  endif

#  if ULONG_MAX == 0xFFFFFFFFFFFFFFFFULL
using SInt64 =   signed long;
using UInt64 = unsigned long;
#  elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFFULL
using SInt64 =   signed long long;
using UInt64 = unsigned long long;
#  else
#    error "defaults not correct; you must hand modify libbr/typedef.hpp"
#  endif

constexpr static auto BIT_PER_BYTE = CHAR_BIT;

constexpr static auto BIT_PER_CHAR = CHAR_BIT;

using Size = decltype(sizeof(char));

using PointerDifference = decltype(static_cast<char *>(nullptr) - static_cast<char *>(nullptr));

} // namespace BR

#endif // defined(BR_DOXYGEN)

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

using Boolean = bool;

using SInt = signed int;

using UInt = unsigned int;

using SFloat = float;

using DFloat = double;

using QFloat = long double;

using Float32 = float;

using Float64 = double;

using Float96 = long double;

} // namespace BR

namespace BR {

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

/**
 * @brief 空指针类型
 */
using NullPointer = decltype(nullptr);

/**
 * @brief C风格数组
 */
template< typename T, Size S >
using CArray = T[S];

/**
 * @brief C风格字符串
 */
template< typename TChar >
using CString = TChar const *;

struct MaxAlignType {
	alignas(alignof(long long)) long long ll;
	alignas(alignof(long double)) long double ld;
};

} // namespace BR

namespace BR {

#if defined(BR_HAS_INT128) || defined(BR_DOXYGEN)

/**
 * @brief 有符号128位整形，可能未定义
 * @post 若有定义，类型位宽为128
 */
using SInt128 = BR_SINT128;

/**
 * @brief 无符号128位整形，可能未定义
 * @post 若有定义，类型位宽为128
 */
using UInt128 = BR_UINT128;

/**
 * @brief 八字
 */
using OWord = UInt128;

#endif // defined(BR_HAS_INT128) || defined(BR_DOXYGEN)

} // namespace BR

namespace BR {

static_assert(BIT_PER_BYTE * sizeof(SInt8)  ==  8, "SInt8  isn't excatly  8 bits.");
static_assert(BIT_PER_BYTE * sizeof(SInt16) == 16, "SInt16 isn't excatly 16 bits.");
static_assert(BIT_PER_BYTE * sizeof(SInt32) == 32, "SInt32 isn't excatly 32 bits.");
static_assert(BIT_PER_BYTE * sizeof(SInt64) == 64, "SInt64 isn't excatly 64 bits.");

static_assert(BIT_PER_BYTE * sizeof(UInt8)  ==  8, "UInt8  isn't excatly  8 bits.");
static_assert(BIT_PER_BYTE * sizeof(UInt16) == 16, "UInt16 isn't excatly 16 bits.");
static_assert(BIT_PER_BYTE * sizeof(UInt32) == 32, "UInt32 isn't excatly 32 bits.");
static_assert(BIT_PER_BYTE * sizeof(UInt64) == 64, "UInt64 isn't excatly 64 bits.");

#if defined(BR_HAS_INT128)
static_assert(BIT_PER_BYTE * sizeof(SInt128) == 128, "SInt128 isn't excatly 128 bits.");
static_assert(BIT_PER_BYTE * sizeof(UInt128) == 128, "UInt128 isn't excatly 128 bits.");
#endif // defined

static_assert(BIT_PER_BYTE * sizeof(Float32) == 32, "Float32 isn't excatly 32 bits.");
static_assert(BIT_PER_BYTE * sizeof(Float64) == 64, "Float64 isn't excatly 64 bits.");

} // namespace BR
