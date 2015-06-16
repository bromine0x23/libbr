#pragma once

namespace BR {
	// empty
} // namespace BR

namespace BR {

using NChar = char;

using SNChar =   signed char;
using UNChar = unsigned char;

using WChar = wchar_t;

} // namespace BR

#if defined(BR_GCC)

namespace BR {

using SInt8  = __INT8_TYPE__;
using SInt16 = __INT16_TYPE__;
using SInt32 = __INT32_TYPE__;
using SInt64 = __INT64_TYPE__;

using UInt8  = __UINT8_TYPE__;
using UInt16 = __UINT16_TYPE__;
using UInt32 = __UINT32_TYPE__;
using UInt64 = __UINT64_TYPE__;

#if defined(BR_HAS_INT128)
using SInt128 =   signed __int128;
using UInt128 = unsigned __int128;
#endif

constexpr static auto BIT_PER_CHAR = __CHAR_BIT__;

} // namespace BR

#else

#include <climits>

namespace BR {

#if UCHAR_MAX == 0xFF
using SInt8 =   signed char;
using SInt8 = unsigned char;
#elif USHRT_MAX == 0xFF
using SInt8 =   signed short;
using SInt8 = unsigned short;
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

#if defined(BR_HAS_INT128)
typedef   signed __int128 SInt128;
typedef unsigned __int128 UInt128;
#endif

constexpr static auto BIT_PER_CHAR = CHAR_BIT;

} // namespace BR

#endif

namespace BR {

using Byte  = UInt8;
using Word  = UInt16;
using DWord = UInt32;
using QWord = UInt64;

#if defined(BR_HAS_INT128)
	using OWord = UInt128;
#endif // defined

using Size = decltype(sizeof(char));
using PointerDifference = decltype(static_cast<char *>(nullptr) - static_cast<char *>(nullptr));
using NullPointer = decltype(nullptr);

template< typename T, Size S >
using CArray = T[S];

template< typename TChar >
using CString = TChar const *;

using CNString = CString< NChar>;
using CWString = CString< WChar>;

} // namespace BR

namespace BR {

BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(SInt8)  ==  8, "SInt8  isn't excatly  8 bits.");
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(SInt16) == 16, "SInt16 isn't excatly 16 bits.");
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(SInt32) == 32, "SInt32 isn't excatly 32 bits.");
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(SInt64) == 64, "SInt64 isn't excatly 64 bits.");

BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(UInt8)  ==  8, "UInt8  isn't excatly  8 bits.");
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(UInt16) == 16, "UInt16 isn't excatly 16 bits.");
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(UInt32) == 32, "UInt32 isn't excatly 32 bits.");
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(UInt64) == 64, "UInt64 isn't excatly 64 bits.");

#if defined(BR_HAS_INT128)
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(SInt128) == 128, "SInt128 isn't excatly 128 bits.");
BR_STATIC_ASSERT(BIT_PER_CHAR * sizeof(UInt128) == 128, "UInt128 isn't excatly 128 bits.");
#endif // defined

} // namespace BR
