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
		char * buffer = (char *)raw;
		Size i = 0;
		BR_TRY {
			for (; i != N; ++i) {
				new(buffer) TElement(initializer);
				buffer += sizeof(TElement);
			}
		} BR_CATCH(...) {
			for (; i--;) {
				buffer -= sizeof(TElement);
				((TElement *)buffer)->~TElement();
			}
			BR_RETHROW;
		}
	}

	~RawArray() {
		char * buffer = (char *)raw + N * sizeof(TElement);
		for (Size i = 0; i != N; ++i) {
			buffer -= sizeof(TElement);
			((TElement *)buffer)->~TElement();
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
};


} // namespace Container
} // namespace Detail
} // namespace BR