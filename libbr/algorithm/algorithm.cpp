#include <libbr/algorithm/sort.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template void sort(NChar * first, NChar * last, Less<NChar> & comparator);

template void sort(WChar * first, WChar * last, Less<WChar> & comparator);

template void sort(SInt8 * first, SInt8 * last, Less<SInt8> & comparator);

template void sort(UInt8 * first, UInt8 * last, Less<UInt8> & comparator);

template void sort(SInt16 * first, SInt16 * last, Less<SInt16> & comparator);

template void sort(UInt16 * first, UInt16 * last, Less<UInt16> & comparator);

template void sort(SInt32 * first, SInt32 * last, Less<SInt32> & comparator);

template void sort(UInt32 * first, UInt32 * last, Less<UInt32> & comparator);

template void sort(SInt64 * first, SInt64 * last, Less<SInt64> & comparator);

template void sort(UInt64 * first, UInt64 * last, Less<UInt64> & comparator);

template void sort(SFloat * first, SFloat * last, Less<SFloat> & comparator);

template void sort(DFloat * first, DFloat * last, Less<DFloat> & comparator);

template void sort(QFloat * first, QFloat * last, Less<QFloat> & comparator);

} // namespace Algorithm
} // namespace Detail

} // namespace BR