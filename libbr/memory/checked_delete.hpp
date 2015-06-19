#pragma once

#include <libbr/assert/assert_type_completeness.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/remove_extent.hpp>

namespace BR {

template< typename T >
struct CheckedScalarDeleter  {
	using Result = void;
	using Argument = T *;

	Result operator()(Argument argumrnt) const {
		assert_type_completeness<T>();
		delete argumrnt;
	}
}; // struct CheckedScalarDeleter

template< typename T >
struct CheckedArrayDeleter {
	using Result = void;
	using Argument = T *;

	Result operator()(Argument argumrnt) const {
		assert_type_completeness<T>();
		delete [] argumrnt;
	}
}; // struct CheckedArrayDeleter

template< typename T >
struct CheckedDeleter {
	using Result = void;
	using Argument = RemoveExtent<T> *;

	Result operator()(Argument argumrnt) const {
		Conditional< IsArray<T>, CheckedArrayDeleter<T>, CheckedScalarDeleter<T> >()(argumrnt);
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

} // namespace BR
