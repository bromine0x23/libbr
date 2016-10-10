/**
 * @file
 * @brief 容器特性类
 * @author Bromine0x23
 * @since 2016/10/9
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/type_traits/has_member_type.hpp>

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
BR_HAS_MEMBER_TYPE(Element)

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
BR_HAS_MEMBER_TYPE(Iterator)

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
BR_HAS_MEMBER_TYPE(ConstIterator)

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
BR_HAS_MEMBER_TYPE(ReverseIterator)

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
BR_HAS_MEMBER_TYPE(ConstReverseIterator)

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