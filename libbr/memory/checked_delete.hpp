#pragma once

#include <libbr/assert/type_is_complete.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/remove_extent.hpp>

namespace BR {
namespace Memory {

template< typename T >
struct CheckedScalarDeleter  {
	using Result = void;
	using Argument = T *;

	Result operator()(Argument argumrnt) const {
		Assert::type_is_complete<T>();
		delete argumrnt;
	}
}; // struct CheckedScalarDeleter

template< typename T >
struct CheckedArrayDeleter {
	using Result = void;
	using Argument = T *;

	Result operator()(Argument argumrnt) const {
		Assert::type_is_complete<T>();
		delete [] argumrnt;
	}
}; // struct CheckedArrayDeleter

template< typename T >
struct CheckedDeleter {
	using Result = void;
	using Argument = TypeOperate::RemoveExtent<T> *;

	Result operator()(Argument argumrnt) const {
		TypeOperate::Conditional< TypeOperate::IsArray<T>, CheckedArrayDeleter<T>, CheckedScalarDeleter<T> >()(argumrnt);
	}
}; // struct CheckedArrayDeleter

template< typename T >
inline void checked_scalar_delete(T * x) {
	CheckedScalarDeleter<T>()(x);
}

template< typename T >
inline void checked_array_delete(T * x)  {
	CheckedArrayDeleter<T>()(x);
}

template< typename T >
inline void checked_delete(T * x)  {
	CheckedDeleter<T>()(x);
}

} // namespace Memory
} // namespace BR
