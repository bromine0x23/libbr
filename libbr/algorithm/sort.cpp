#include <libbr/algorithm/sort.hpp>

namespace BR {

inline namespace Algorithm {

template void sort(NChar * first, NChar * last, Less<NChar> && comparator);

template void sort(WChar * first, WChar * last, Less<WChar> && comparator);

template void sort(SInt8 * first, SInt8 * last, Less<SInt8> && comparator);

template void sort(UInt8 * first, UInt8 * last, Less<UInt8> && comparator);

template void sort(SInt16 * first, SInt16 * last, Less<SInt16> && comparator);

template void sort(UInt16 * first, UInt16 * last, Less<UInt16> && comparator);

template void sort(SInt32 * first, SInt32 * last, Less<SInt32> && comparator);

template void sort(UInt32 * first, UInt32 * last, Less<UInt32> && comparator);

template void sort(SInt64 * first, SInt64 * last, Less<SInt64> && comparator);

template void sort(UInt64 * first, UInt64 * last, Less<UInt64> && comparator);

template void sort(Float32 * first, Float32 * last, Less<Float32> && comparator);

template void sort(Float64 * first, Float64 * last, Less<Float64> && comparator);

} // namespace Algorithm

} // namespace BR