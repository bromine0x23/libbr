/**
 * @file
 * @brief 可枚举模块
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/enumerate/enumerator.hpp>
#include <libbr/type_traits/is_base_of.hpp>

namespace BR {

/**
 * 可枚举模块
 * @tparam TDerived
 * @tparam TIterator
 * @tparam TConstIterator
 */
template< typename TDerived, typename TIterator, typename TConstIterator >
struct Enumerable;


namespace Detail {
namespace Enumerable {

template< typename TDerived, typename TIterator, typename TConstIterator, bool = IsBaseOf< BidirectionalTraversalTag, typename IteratorTraits<TIterator>::Category >{} >
struct Base {
private:
	using Derived = TDerived;

public:
	using Iterator = TIterator;

	using ConstIterator = TConstIterator;

public:
	BR_CONSTEXPR_AFTER_CXX11 auto each() noexcept -> BR::Enumerator<Iterator> {
		return make_enumerator(begin(), begin());
	}

	BR_CONSTEXPR_AFTER_CXX11 auto each() const noexcept -> BR::Enumerator<ConstIterator> {
		return make_enumerator(begin(), begin());
	}

	template< typename TFunctor, typename ... TArgs >
	auto each(TFunctor functor, TArgs && ... args) -> Derived & {
		for (auto iterator = begin(); iterator != end(); ++iterator) {
			invoke(functor, *iterator, forward<TArgs>(args)...);
		}
		return as_derived();
	}

	template< typename TFunctor, typename ... TArgs >
	auto each(TFunctor functor, TArgs && ... args) const -> Derived const & {
		for (auto iterator = begin(); iterator != end(); ++iterator) {
			invoke(functor, *iterator, forward<TArgs>(args)...);
		}
		return as_derived();
	}

protected:
	auto as_derived() -> Derived & {
		return *static_cast<Derived *>(this);
	}
	auto as_derived() const -> Derived const & {
		return *static_cast<Derived const *>(this);
	}

	auto begin() noexcept -> Iterator {
		return as_derived().begin();
	}

	auto end() noexcept -> Iterator {
		return as_derived().end();
	}

	auto begin() const noexcept -> ConstIterator {
		return as_derived().begin();
	}

	auto end() const noexcept -> ConstIterator {
		return as_derived().end();
	}
};

template< typename TDerived, typename TIterator, typename TConstIterator >
struct Base< TDerived, TIterator, TConstIterator, true > : public Base< TDerived, TIterator, TConstIterator, false > {
private:
	using Derived = TDerived;

public:
	using Iterator = TIterator;

	using ConstIterator = TConstIterator;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

	BR_CONSTEXPR_AFTER_CXX11 auto reverse_each() noexcept -> BR::Enumerator<ReverseIterator> {
		return make_enumerator(rbegin(), rbegin());
	}

	BR_CONSTEXPR_AFTER_CXX11 auto reverse_each() const noexcept -> BR::Enumerator<ConstReverseIterator> {
		return make_enumerator(rbegin(), rbegin());
	}

	template< typename TFunctor, typename ... TArgs >
	auto reverse_each(TFunctor functor, TArgs && ... args) -> Derived & {
		for (auto iterator = rbegin(); iterator != rend(); ++iterator) {
			invoke(functor, *iterator, forward<TArgs>(args)...);
		}
		return this->as_derived();
	}

	template< typename TFunctor, typename ... TArgs >
	auto reverse_each(TFunctor functor, TArgs && ... args) const -> Derived const & {
		for (auto iterator = rbegin(); iterator != rend(); ++iterator) {
			invoke(functor, *iterator, forward<TArgs>(args)...);
		}
		return this->as_derived();
	}

private:
	auto rbegin() noexcept -> ReverseIterator {
		return this->as_derived().rbegin();
	}

	auto rend() noexcept -> ReverseIterator {
		return this->as_derived().rend();
	}

	auto rbegin() const noexcept -> ConstReverseIterator {
		return this->as_derived().rbegin();
	}

	auto rend() const noexcept -> ConstReverseIterator {
		return this->as_derived().rend();
	}
};

} // namespace Enumerable
} // namespace Detail

template< typename TDerived, typename TIterator, typename TConstIterator >
struct Enumerable : public Detail::Enumerable::Base< TDerived, TIterator, TConstIterator > {

	template< typename TUnaryPredicate >
	auto all(TUnaryPredicate predicate) const -> bool {
		for (auto iterator = this->begin(); iterator != this->end(); ++iterator) {
			if (!invoke(predicate, *iterator)) {
				return false;
			}
		}
		return true;
	}

	template< typename TUnaryPredicate >
	auto any(TUnaryPredicate predicate) const -> bool {
		for (auto iterator = this->begin(); iterator != this->end(); ++iterator) {
			if (invoke(predicate, *iterator)) {
				return true;
			}
		}
		return false;
	}

	template< typename TUnaryPredicate >
	auto none(TUnaryPredicate predicate) const -> bool {
		for (auto iterator = this->begin(); iterator != this->end(); ++iterator) {
			if (invoke(predicate, *iterator)) {
				return false;
			}
		}
		return true;
	}

	template< typename TValue >
	auto include(TValue const & value) const -> bool {
		for (auto iterator = this->begin(); iterator != this->end(); ++iterator) {
			if (*iterator == value) {
				return true;
			}
		}
		return false;
	}

}; // struct Enumerable

} // namespace BR
