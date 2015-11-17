#pragma once

#include <libbr/config.hpp>

namespace BR {

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

struct InputIteratorTag : public IteratorTag, public ReadableTag, public SinglePassTraversalTag {
};

struct ForwardIteratorTag : public IteratorTag, public ReadableTag, public ForwardTraversalTag {
};

struct BidirectionalIteratorTag : public IteratorTag, public ReadableTag, public BidirectionalTraversalTag {
};

struct RandomAccessIteratorTag : public IteratorTag, public ReadableTag, public RandomAccessTraversalTag {
};

struct OutputIteratorTag : public IteratorTag, public WritableTag, public IncrementableTraversalTag {
};

struct MutableForwardIteratorTag : public ForwardIteratorTag, public WritableTag {
};

struct MutableBidirectionalIteratorTag : public BidirectionalIteratorTag, public WritableTag {
};

struct MutableRandomAccessIteratorTag : public RandomAccessIteratorTag, public WritableTag {
};

/*

struct InputIteratorTag : public IteratorTag {};

struct OutputIteratorTag : public IteratorTag {};

struct ForwardIteratorTag : public InputIteratorTag {};

struct BidirectionalIteratorTag : public ForwardIteratorTag {};

struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

*/

} // namespace BR