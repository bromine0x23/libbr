#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Iterator {

struct InputIteratorTag  {};

struct OutputIteratorTag {};

struct ForwardIteratorTag : InputIteratorTag {};

struct BidirectionalIteratorTag : ForwardIteratorTag {};

struct RandomAccessIteratorTag : BidirectionalIteratorTag {};


} // namespace Iterator
} // namespace BR