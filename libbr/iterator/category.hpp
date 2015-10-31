#pragma once

#include <libbr/config.hpp>

namespace BR {

struct IteratorTag {};

struct InputIteratorTag : public IteratorTag  {};

struct OutputIteratorTag : public IteratorTag {};

struct ForwardIteratorTag : public InputIteratorTag {};

struct BidirectionalIteratorTag : public ForwardIteratorTag {};

struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

struct ContiguousIteratorTag : public RandomAccessIteratorTag {};

} // namespace BR