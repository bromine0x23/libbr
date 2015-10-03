#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>

namespace BR {

template< typename TIterator >
struct IteratorTraits  {
	using Difference = typename TIterator::Difference;
	using Value      = typename TIterator::Value;
	using Pointer    = typename TIterator::Pointer;
	using Reference  = typename TIterator::Reference;
	using Category   = typename TIterator::Category;
};

template< typename TValue >
struct IteratorTraits< TValue * > {
	using Difference = BR::PointerDifference ;
	using Value      = TValue;
	using Pointer    = TValue *;
	using Reference  = TValue &;
	using Category   = RandomAccessIteratorTag;
};

template< typename TValue >
struct IteratorTraits< TValue const * > {
	using Difference = BR::PointerDifference ;
	using Value      = TValue;
	using Pointer    = TValue const *;
	using Reference  = TValue const &;
	using Category   = RandomAccessIteratorTag;
};

template< typename TIterator >
using IteratorDifference = typename IteratorTraits< TIterator >::Difference;

template< typename TIterator >
using IteratorValue = typename IteratorTraits< TIterator >::Value;

template< typename TIterator >
using IteratorPointer = typename IteratorTraits< TIterator >::Pointer;

template< typename TIterator >
using IteratorReference= typename IteratorTraits< TIterator >::Reference;

template< typename TIterator >
using IteratorCategory = typename IteratorTraits< TIterator >::Category;

template< typename TIterator >
using IsInputIterator = IsBaseOf< InputIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using NotInputIterator = NotBaseOf< InputIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using IsOutputIterator = IsBaseOf< OutputIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using NotOutputIterator = NotBaseOf< OutputIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using IsForwardIterator = IsBaseOf< ForwardIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using NotForwardIterator = NotBaseOf< ForwardIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using IsBidirectionalIterator = IsBaseOf< BidirectionalIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using NotBidirectionalIterator = NotBaseOf< BidirectionalIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using IsRandomAccessIterator = IsBaseOf< RandomAccessIteratorTag, IteratorTraits<TIterator>::Category >;

template< typename TIterator >
using  NotRandomAccessIterator =  NotBaseOf< RandomAccessIteratorTag, IteratorTraits<TIterator>::Category >;

} // namespace BR