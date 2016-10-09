/**
 * @file
 * @brief 容器特性类
 * @author Bromine0x23
 * @since 2016/10/9
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

/**
 * 分配器特性类
 * @tparam TAllocator 分配器类型
 */
template< typename TContainer >
struct ContainerTraits;



namespace Detail {
namespace TypeTraits {
namespace ContainerTraits {

////////////////////////////////
//
// ContainerTraits::Element
//
#define BR_TYPE_OPERATE_TYPE_NAME Element
#include <libbr/type_traits/has_member_type.inc>

template< typename TContainer, bool = HasMemberTypeElement<TContainer>{} >
struct TypeElement;

template< typename TContainer >
struct TypeElement< TContainer, true > : TypeWrapper< typename TContainer::Element > {};

template< typename TContainer >
struct TypeElement< TContainer, false > : TypeFirstTemplateArgument<TContainer> {};

template< typename TContainer >
using Element = TypeUnwrap< TypeElement<TContainer> >;

////////////////////////////////
//
// ContainerTraits::Iterator
//
#define BR_TYPE_OPERATE_TYPE_NAME Iterator
#include <libbr/type_traits/has_member_type.inc>

template< typename TContainer, bool = HasMemberTypeIterator<TContainer>{} >
struct TypeIterator;

template< typename TContainer >
struct TypeIterator< TContainer, true > : TypeWrapper< typename TContainer::Iterator > {};

template< typename TContainer >
struct TypeIterator< TContainer, false > : TypeWrapper< Element<TContainer> * > {};

template< typename TContainer >
using Iterator = TypeUnwrap< TypeIterator<TContainer> >;

////////////////////////////////
//
// ContainerTraits::ConstIterator
//
#define BR_TYPE_OPERATE_TYPE_NAME ConstIterator
#include <libbr/type_traits/has_member_type.inc>

template< typename TContainer, bool = HasMemberTypeConstIterator<TContainer>{} >
struct TypeConstIterator;

template< typename TContainer >
struct TypeConstIterator< TContainer, true > : TypeWrapper< typename TContainer::ConstIterator > {};

template< typename TContainer >
struct TypeConstIterator< TContainer, false > : TypeWrapper< Element<TContainer> const * > {};

template< typename TContainer >
using ConstIterator = TypeUnwrap< TypeConstIterator<TContainer> >;

////////////////////////////////
//
// ContainerTraits::ReverseIterator
//
#define BR_TYPE_OPERATE_TYPE_NAME ReverseIterator
#include <libbr/type_traits/has_member_type.inc>

template< typename TContainer, bool = HasMemberTypeReverseIterator<TContainer>{} >
struct TypeReverseIterator;

template< typename TContainer >
struct TypeReverseIterator< TContainer, true > : TypeWrapper< typename TContainer::ReverseIterator > {};

template< typename TContainer >
struct TypeReverseIterator< TContainer, false > : TypeWrapper< ReverseIterator< Iterator<TContainer> > > {};

template< typename TContainer >
using ReverseIterator = TypeUnwrap< TypeReverseIterator<TContainer> >;

////////////////////////////////
//
// ContainerTraits::ConstReverseIterator
//
#define BR_TYPE_OPERATE_TYPE_NAME ConstReverseIterator
#include <libbr/type_traits/has_member_type.inc>

template< typename TContainer, bool = HasMemberTypeReverseIterator<TContainer>{} >
struct TypeConstReverseIterator;

template< typename TContainer >
struct TypeConstReverseIterator< TContainer, true > : TypeWrapper< typename TContainer::ConstReverseIterator > {};

template< typename TContainer >
struct TypeConstReverseIterator< TContainer, false > : TypeWrapper< ReverseIterator< ConstIterator<TContainer> > > {};

template< typename TContainer >
using ConstReverseIterator = TypeUnwrap< TypeConstReverseIterator<TContainer> >;

} // namespace ContainerTraits
} // namespace TypeTraits
} // namespace Detail


template< typename TContainer >
struct ContainerTraits {
public:
	/**
	 * @brief 容器类型，即 \em TContainer
	 */
	using Container = TContainer;

	/**
	 * @brief 元素类型
	 *
	 * 如果 <tt>Container::Element</tt> 存在则为该类型；
	 * 否则，如果 \em Container 是一个模板实例 <tt>Template< T, TArgs... ></tt>，则为类型 \em T
	 */
	using Element = Detail::TypeTraits::ContainerTraits::Element<Container>;

	using Iterator = Detail::TypeTraits::ContainerTraits::Iterator<Container>;

	using ConstIterator = Detail::TypeTraits::ContainerTraits::ConstIterator<Container>;

	using ReverseIterator = Detail::TypeTraits::ContainerTraits::ReverseIterator<Container>;

	using ConstReverseIterator = Detail::TypeTraits::ContainerTraits::ConstReverseIterator<Container>;

}; // struct ContainerTraits<TContainer>


} // namespace BR