#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
class WrappedReference {

public:

	using Type = T;

	inline explicit WrappedReference(Type & t) noexcept : m_t(address_of(t)) {}

	operator Type & () const noexcept { return *m_t; }

	Type & get() const noexcept { return *m_t; }

	Type * get_pointer() const noexcept { return m_t; }

private:

	WrappedReference(Type &&) = delete;

	Type * m_t;

}; // class WrappedReference<T>

template< typename T >
inline WrappedReference<T> const wrap_reference(T & t) {
	return WrappedReference<T>(t);
}

template< typename T >
inline WrappedReference< T const > const wrap_const_reference(T const & t) {
	return WrappedReference< T const >(t);
}

template< typename T >
void wrap_reference(T && t) = delete;

template< typename T >
void wrap_const_reference(T && t) = delete;

namespace Detail {
namespace Utility {

template< typename T >
struct IsWrappedReferenceBasic : BooleanFalse {};

template< typename T >
struct IsWrappedReferenceBasic< WrappedReference<T> > : BooleanTrue {};

template< typename T >
using IsWrappedReference = IsWrappedReferenceBasic< RemoveConstVolatile<T> >;

template< typename T >
struct TypeUnwrapReferenceBasic : TypeWrapper<T> {};

template< typename T >
struct TypeUnwrapReferenceBasic< WrappedReference<T> > : TypeWrapper< T > {};

template< typename T >
using TypeUnwrapReference = TypeUnwrapReferenceBasic< RemoveConstVolatile<T> >;

} // namespace Utility
} // namespace Detail

template< typename T >
struct IsWrappedReference : Boolean< Detail::Utility::IsWrappedReference< T > > {};

template< typename T >
struct NotWrappedReference : BooleanNot< Detail::Utility::IsWrappedReference< T > > {};

template< typename T >
struct TypeUnwrapReference : TypeRewrap< Detail::Utility::TypeUnwrapReference<T> > {};

template< typename T >
using UnwrapReference = TypeUnwrap< TypeUnwrapReference<T> >;

template< typename T >
UnwrapReference<T> & unwrap_reference(T & t) noexcept {
	return t;
}

template< typename T >
T * get_pointer(WrappedReference<T> const & reference) {
	return reference.get_pointer();
}

} // namespace BR
