/**
 * @file
 * @brief default_delete
 * @author Bromine0x23
 * @since 2015/10/25
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_void.hpp>

namespace BR {
inline namespace Memory {

template< typename TElement >
struct DefaultDeleter : public UnaryFunctor<TElement *> {
	constexpr DefaultDeleter() noexcept = default;

	template< typename TOtherElement, typename = EnableIf< IsConvertible<TOtherElement *, TElement *> > >
	DefaultDeleter(DefaultDeleter<TOtherElement> const & deleter) noexcept {
	}

	void operator()(TElement * pointer) const noexcept {
		static_assert(sizeof(TElement) > 0 || NotVoid<TElement>(), "DefaultDeleter can not delete incomplete type");
		delete pointer;
	}
};

template< typename TElement >
struct DefaultDeleter<TElement[]> : public UnaryFunctor<void> {
	constexpr DefaultDeleter() noexcept = default;

	template< typename TOtherElement, typename = EnableIf< IsConvertible<TOtherElement *, TElement *> > >
	DefaultDeleter(DefaultDeleter<TOtherElement> const & deleter) noexcept {
	}

	template< typename TOtherElement, typename = EnableIf< IsConvertible<TOtherElement *, TElement *> > >
	void operator()(TOtherElement * pointer) const noexcept {
		static_assert(sizeof(TElement) > 0 || NotVoid<TElement>(), "DefaultDeleter can not delete incomplete type");
		delete[] pointer;
	}
};

} // namespace Memory
} // namespace BR
