#pragma once

#include <libbr/config.hpp>
#include <cstddef>


namespace BR {
namespace Detail {
namespace Container {

template< typename TElement, Size N >
class RawArray {

public:
	template< typename Initializer>
	RawArray(Initializer const & initializer) {
		Size i = 0;
		BR_TRY {
			for (; i != N; ++i) {
				new(raw + i) TElement(initializer);
			}
		} BR_CATCH(...) {
			for (; i--;) {
				((TElement *)(raw + i))->~TElement();
			}
			BR_RETHROW;
		}
	}

	~RawArray() {
		for (Size i = 0; i != N; ++i) {
			((TElement *)(raw + i))->~TElement();
		}
	}

	operator TElement * () {
		return (TElement *)(raw);
	}

	operator TElement const *() const {
		return (TElement const *)(raw);
	}

private:
	struct {
		alignas(alignof(TElement)) Byte bytes[sizeof(TElement)];
	} raw[N];
}; // class RawArray< TElement, N >


} // namespace Container
} // namespace Detail
} // namespace BR