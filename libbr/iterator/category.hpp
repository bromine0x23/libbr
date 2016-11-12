#pragma once

#include <libbr/config.hpp>

namespace BR {

struct UnreadableTag {
};

struct ReadableTag {
};

struct WritableTag {
};

struct NoTraversalTag {
};

struct IncrementableTraversalTag : public NoTraversalTag {
};

struct SinglePassTraversalTag : public IncrementableTraversalTag {
};

struct ForwardTraversalTag : public SinglePassTraversalTag {
};

struct BidirectionalTraversalTag : public ForwardTraversalTag {
};

struct RandomAccessTraversalTag : public BidirectionalTraversalTag {
};

struct IteratorTag {
};

} // namespace BR