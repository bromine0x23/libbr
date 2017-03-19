#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/remove_reference.hpp>
#include <libbr/utility/type.hpp>

namespace BR {
namespace Detail {
namespace Memory {
namespace UniquePointer {

BR_HAS_MEMBER_TYPE(Pointer);

template< typename TElement, typename TDeleter, bool = HasMemberTypePointer<TDeleter>{} >
struct TypePointer;

template< typename TElement, typename TDeleter >
using Pointer = TypeUnwrap< TypePointer< TElement, TDeleter> >;

template< typename TElement, typename TDeleter >
struct TypePointer< TElement, TDeleter, true > : TypeWrapper< typename TDeleter::Pointer > {};

template< typename TElement, typename TDeleter >
struct TypePointer< TElement, TDeleter, false > : TypeWrapper< TElement * > {};

template< typename TDeleter >
using DeleterLValue = Conditional< IsReference<TDeleter>, TDeleter, TDeleter const & >;

template< typename TDeleter >
using DeleterRValue = RemoveReference<TDeleter> &&;

} // namespace UniquePointer
} // namespace Memory
} // namespace Detail
} // namespace BR