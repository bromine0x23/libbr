#include <libbr/algorithms.hpp>

namespace BR {

namespace _::Algorithms {

template void introsort(NChar  * first, NChar  * last, Less<> && comparator);
template void introsort(WChar  * first, WChar  * last, Less<> && comparator);
template void introsort(SInt8  * first, SInt8  * last, Less<> && comparator);
template void introsort(UInt8  * first, UInt8  * last, Less<> && comparator);
template void introsort(UInt16 * first, UInt16 * last, Less<> && comparator);
template void introsort(SInt16 * first, SInt16 * last, Less<> && comparator);
template void introsort(SInt32 * first, SInt32 * last, Less<> && comparator);
template void introsort(UInt32 * first, UInt32 * last, Less<> && comparator);
template void introsort(SInt64 * first, SInt64 * last, Less<> && comparator);
template void introsort(UInt64 * first, UInt64 * last, Less<> && comparator);
template void introsort(SFloat * first, SFloat * last, Less<> && comparator);
template void introsort(DFloat * first, DFloat * last, Less<> && comparator);
template void introsort(QFloat * first, QFloat * last, Less<> && comparator);

} // namespace _::Algorithms

inline namespace Algorithms {
} // namespace Algorithms

} // namespace BR