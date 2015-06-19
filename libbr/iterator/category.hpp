#pragma once

#include <libbr/config.hpp>

namespace BR {

struct InputIteratorTag  {};

struct OutputIteratorTag {};

struct ForwardIteratorTag : InputIteratorTag {};

struct BidirectionalIteratorTag : ForwardIteratorTag {};

struct RandomAccessIteratorTag : BidirectionalIteratorTag {};

} // namespace BR