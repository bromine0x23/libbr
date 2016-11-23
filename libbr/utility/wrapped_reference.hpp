#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/call_result.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

template< typename T >
class WrappedReference;

template< typename T >
inline auto reference(T & t) -> WrappedReference<T> {
	return WrappedReference<T>(t);
}

template< typename T >
inline auto reference(WrappedReference<T> r) -> WrappedReference<T> {
	return reference(r.get());
}

template< typename T >
void reference(T && t) = delete;

template< typename T >
inline auto const_reference(T const & t) -> WrappedReference< T const > {
	return WrappedReference< T const >(t);
}

template< typename T >
inline auto const_reference(WrappedReference<T> r) -> WrappedReference< T const > {
	return const_reference(r.get());
}

template< typename T >
void const_reference(T && t) = delete;

template< typename T >
struct IsWrappedReference;

template< typename T >
struct NotWrappedReference;

#if defined(BR_CXX14)

template< typename T >
constexpr auto is_wrapped_reference = boolean_constant< IsWrappedReference<T> >;

template< typename T >
constexpr auto not_wrapped_reference = boolean_constant< NotWrappedReference<T> >;

#endif // defined(BR_CXX14)

namespace Detail {
namespace Utility {

template< typename T >
struct IsWrappedReferenceBasic : BooleanFalse {
};

template< typename T >
struct IsWrappedReferenceBasic< WrappedReference<T> > : BooleanTrue {
};

template< typename T >
using IsWrappedReference = IsWrappedReferenceBasic< RemoveConstVolatile<T> >;

} // namespace Utility
} // namespace Detail

template< typename T >
struct IsWrappedReference : BooleanRewrapPositive< Detail::Utility::IsWrappedReference<T> > {};

template< typename T >
struct NotWrappedReference : BooleanRewrapNegative< Detail::Utility::IsWrappedReference<T> > {};

template< typename T >
T * get_pointer(WrappedReference<T> const & reference) {
	return reference.get_pointer();
}

template< typename T >
class WrappedReference {
public:

	using Type = T;

	explicit WrappedReference(Type & t) noexcept : m_t(address_of(t)) {
	}

	WrappedReference(WrappedReference const & t) noexcept {}

	auto get() const noexcept -> Type & {
		return *m_t;
	}

	operator Type & () const noexcept {
		return *m_t;
	}

	template< typename ... TArguments >
	auto operator()(TArguments && ... arguments) const -> CallResult< Type &, TArguments... > {
		return invoke(get(), forward<TArguments>(arguments)...);
	}

private:
	WrappedReference(Type &&) = delete;

	Type * m_t;

}; // class WrappedReference<T>

} // namespace BR
