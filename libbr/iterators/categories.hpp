/**
 * @file
 * @brief 迭代器类别
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Iterators {

template< typename ... TTags >
struct CategoryWithTags : public TTags... {};

struct IteratorTag {};

struct ReadableTag {};

struct WritableTag {};

struct NoTraversalTag {};

struct IncrementableTraversalTag : public NoTraversalTag {};

struct SinglePassTraversalTag : public IncrementableTraversalTag {};

struct ForwardTraversalTag : public SinglePassTraversalTag {};

struct BidirectionalTraversalTag : public ForwardTraversalTag {};

struct RandomAccessTraversalTag : public BidirectionalTraversalTag {};

struct ContiguousStorageTag {};

} // namespace Iterators
} // namespace BR