#pragma once

#include <libbr/assert/assert.hpp>
#include <libbr/memory/checked_delete.hpp>
#include <libbr/memory/detail/pointer_wrapper.hpp>
#include <libbr/type_operate/remove_extent.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Memory {

template< typename TValue, typename TDeleter = CheckedDeleter<TValue> >
class ScopedPointer : public Detail::PointerWrapper<TValue> {

private:
	using Self = ScopedPointer<TValue>;
	using Base = Detail::PointerWrapper<TValue>;

public:
	using Value   = typename Base::Value;
	using Element = typename Base::Element;
	using Pointer = typename Base::Pointer;
	using Deleter = TDeleter;

	ScopedPointer() : Base(nullptr), deleter_() {}

	ScopedPointer(NullPointer) : Self() {}

	explicit ScopedPointer(Element * pointer) : Base(pointer), deleter_() {}

	ScopedPointer(Element * pointer, Deleter deleter) : Base(pointer), deleter_(deleter) {}

	ScopedPointer(Self && pointer) : Base(move(pointer)), deleter_() {}

	~ScopedPointer() {
		deleter_(Base::get());
	}

private:
	Deleter deleter_;

}; // class ScopedPointer<TValue>

} // namespace Memory
} // namespace BR


