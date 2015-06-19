#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/replace_template_argument.hpp>
#include <libbr/type_operate/template_argument.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

namespace Detail {
namespace PointerTraits {

////////////////////////////////
//
// PointerTraits::Element
//
#define BR_TYPE_OPERATE_TYPE_NAME Element
#include <libbr/type_operate/has_member_type.inc>

template< typename TPointer, bool = HasMemberTypeElement< TPointer >::value >
struct TypeElement;

template< typename TPointer >
struct TypeElement< TPointer, true > : TypeWrapper< typename TPointer::Element > {};

template< typename TPointer >
struct TypeElement< TPointer, false > : TypeFirstTemplateArgument< TPointer > {};

template< typename TPointer >
using Element = TypeUnwrap< TypeElement< TPointer > >;

////////////////////////////////
//
// PointerTraits::Difference
//
#define BR_TYPE_OPERATE_TYPE_NAME Difference
#include <libbr/type_operate/has_member_type.inc>

template< typename TPointer, bool = HasMemberTypeDifference< TPointer >::value >
struct TypeDifference;

template< typename TPointer >
struct TypeDifference< TPointer, true > : TypeWrapper< typename TPointer::Difference > {};

template< typename TPointer >
struct TypeDifference< TPointer, false > : TypeWrapper< BR::PointerDifference > {};

template< typename TPointer >
using Difference = TypeUnwrap< TypeDifference< TPointer > >;

////////////////////////////////
//
// PointerTraits::Rebind
//
#define BR_TYPE_OPERATE_TYPE_NAME Rebind
#include <libbr/type_operate/has_member_type.inc>

template< typename TPointer, typename TValue, bool = HasMemberTypeRebind< TPointer >::value >
struct TypeRebind;

template< typename TPointer, typename TValue >
struct TypeRebind< TPointer, TValue, true > : TypeWrapper< typename TPointer::template Rebind< TValue > > {};

template< typename TPointer, typename TValue >
struct TypeRebind< TPointer, TValue, false > : TypeReplaceFirstTemplateArgument< TPointer, TValue > {};

template< typename TPointer, typename TValue >
using Rebind = TypeUnwrap< TypeRebind< TPointer, TValue > >;

} // namespace PointerTraits
} // namespace Detail

template< typename TPointer >
struct PointerTraits {
	using Pointer    = TPointer;
	using Element    = Detail::PointerTraits::Element< Pointer >;
	using Difference = Detail::PointerTraits::Difference< Pointer >;

	template< typename TValue >
	using Rebind = Detail::PointerTraits::Rebind< Pointer, TValue >;

	static Pointer make_pointer(EnableIf< NotVoid< Element >, Element > & reference) {
		return Pointer::make_pointer(reference);
	}
};

template< typename TElement >
struct PointerTraits< TElement * > {
	using Element    = TElement;
	using Pointer    = Element *;
	using Difference = PointerDifference;

	template< typename TOtherValue >
	using Rebind = TOtherValue *;

	static Pointer make_pointer(EnableIf< NotVoid< Element >, Element > & reference) {
		return address_of(reference);
	}
};

} // namespace BR
