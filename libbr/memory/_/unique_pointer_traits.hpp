#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_transform/remove_reference.hpp>
#include <libbr/utility/conditional.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR::_::Memory::UniquePointer {

BR_HAS_MEMBER_TYPE(Pointer);

template< typename TElement, typename TDeleter, Boolean = has_member_type_Pointer<TDeleter> >
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

} // namespace BR::_::Memory::UniquePointer