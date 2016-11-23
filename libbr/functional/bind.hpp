/**
 * @file
 * @brief bind
 * @author Bromine0x23
 * @since 2015/11/1
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/call_result.hpp>
#include <libbr/type_traits/decay.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_callable.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/make_integral_sequence.hpp>
#include <libbr/type_traits/remove_const.hpp>
#include <libbr/type_traits/remove_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/integral_constant.hpp>
#include <libbr/utility/wrapped_reference.hpp>

namespace BR {

template< typename T >
struct IsBindExpression;

template< typename T >
struct NotBindExpression : public BooleanRewrapNegative< IsBindExpression<T> > {
};

template< typename T >
struct IsPlaceholder;

template< typename T >
struct NotPlaceholder : public BooleanRewrapNegative< IsPlaceholder<T> > {
};

template< Size I >
struct PlaceHolder : IndexConstant< I > {
};

namespace PlaceHolders {

constexpr auto _0 = PlaceHolder<0>();
constexpr auto _1 = PlaceHolder<1>();
constexpr auto _2 = PlaceHolder<2>();
constexpr auto _3 = PlaceHolder<3>();
constexpr auto _4 = PlaceHolder<4>();
constexpr auto _5 = PlaceHolder<5>();
constexpr auto _6 = PlaceHolder<6>();
constexpr auto _7 = PlaceHolder<7>();
constexpr auto _8 = PlaceHolder<8>();
constexpr auto _9 = PlaceHolder<9>();

} // namespace PlaceHolders

namespace Detail {
namespace Functional {

template< typename T >
struct IsBindExpression : public BooleanFalse {
};

template< typename T >
struct IsPlaceholder : public BooleanFalse {
};

template< Size I >
struct IsPlaceholder< PlaceHolder<I> > : public BooleanTrue {
};

template< typename T, typename TDummy >
inline auto apply_arg(WrappedReference<T> t, TDummy & _dummy) -> T & {
	return t.get();
}

template< Size I, typename TArg >
inline auto apply_arg(PlaceHolder<I> & _holder, TArg & arg) -> TupleElement< I, TArg > {
	return forward< TupleElement< I, TArg > >(get<I>(arg));
}

template< typename TCallable, typename ... TArgs, Size ... I >
inline auto apply_arg_expand(TCallable & callable, Tuple<TArgs...> & args, IndexSequence<I...> _indices) -> CallResult< TCallable &, TArgs... > {
	return callable(forward<TArgs>(get<I>(args))...);
}

template< typename TCallable, typename ... TArgs, typename _TDummy = EnableIf< IsBindExpression<TCallable> > >
inline auto apply_arg(TCallable & callable, Tuple<TArgs...> & args) -> CallResult< TCallable &, TArgs... > {
	return apply_arg_expand(callable, args, MakeIndexSequence< 0, sizeof...(TArgs) >());
}

template< typename T, typename TDummy0, typename _TDummy1 = EnableIf< NotBindExpression<T> > >
inline auto apply_arg(T & t, TDummy0 & _dummy) -> T & {
	return t;
}

template< typename T0, typename T1 >
using ApplyArgReturn = decltype(apply_arg(make_value<T0>(), make_value<T1>()));

template< typename TCallable, typename TBoundArgs, typename TArgs >
struct IsValidBindReturn : BooleanFalse {
};

template< typename TCallable, typename ... TBoundArgs, typename TArgs >
struct IsValidBindReturn< TCallable, Tuple<TBoundArgs...>, TArgs > : IsCallable< TCallable, ApplyArgReturn< TBoundArgs, TArgs >... > {
};

template< typename TCallable, typename ... TBoundArgs, typename TArgs >
struct IsValidBindReturn< TCallable, Tuple<TBoundArgs...> const, TArgs > : IsCallable< TCallable, ApplyArgReturn< TBoundArgs const, TArgs >... > {
};

template< typename TCallable, typename TBoundArgs, typename TArgs, bool = IsValidBindReturn< TCallable, TBoundArgs, TArgs >::value >
struct TypeBindReturn;

template< typename TCallable, typename ... TBoundArgs, typename TArgs >
struct TypeBindReturn< TCallable, Tuple<TBoundArgs...>, TArgs, true > : TypeCallResult< TCallable &, ApplyArgReturn< TBoundArgs, TArgs >... > {
};

template< typename TCallable, typename ... TBoundArgs, typename TArgs >
struct TypeBindReturn< TCallable, Tuple<TBoundArgs...> const, TArgs, true > : TypeCallResult< TCallable &, ApplyArgReturn< TBoundArgs const, TArgs >... > {
};

template< typename TCallable, typename TBoundArgs, typename TArgs >
using BindReturn = TypeUnwrap< TypeBindReturn< TCallable, TBoundArgs, TArgs > >;

template< typename TCallable, typename TBoundArgs, Size ... I, typename TArgs >
inline auto apply(TCallable & callable, TBoundArgs & bound_args, IndexSequence<I...> _indices, TArgs && args) -> BindReturn< TCallable, TBoundArgs, TArgs > {
	return invoke(callable, apply_arg(get<I>(bound_args), args)...);
}

template< typename TCallable, typename ... TBoundArgs >
class Bind {

protected:
	using Callable = Decay<TCallable>;

	using BoundArgs = Tuple< Decay<TBoundArgs> ... >;

	using Indices = MakeIndexSequence< 0, sizeof...(TBoundArgs) >;

public:
	Bind(Bind const & bind) = default;

	Bind(Bind && bind) = default;

	template< typename TOtherCallable, typename ...TOtherBoundArgs, typename = EnableIf< BooleanAnd< IsConvertible< TOtherCallable, Callable >, NotSame< RemoveReference<TOtherCallable>, Bind > > > >
	explicit Bind(
		TOtherCallable && callable, TOtherBoundArgs && ... bound_args
	) : m_callable(forward<TOtherCallable>(callable)), m_bound_args(forward<TOtherBoundArgs>(bound_args)...) {
	}

	auto operator=(Bind const & bind) -> Bind & = default;

	auto operator=(Bind && bind) -> Bind & = default;

	template< typename ... TArgs >
	auto operator()(TArgs && ... args) -> BindReturn< Callable, BoundArgs, Tuple< TArgs && ... > > {
		return apply(m_callable, m_bound_args, Indices(), Tuple< TArgs && ... >(forward<TArgs>(args)...));
	}

	template< typename ... TArgs >
	auto operator()(TArgs && ... args) const -> BindReturn< Callable const, BoundArgs const, Tuple< TArgs && ... > > {
		return apply(m_callable, m_bound_args, Indices(), Tuple< TArgs && ... >(forward<TArgs>(args)...));
	}

private:
	Callable m_callable;
	BoundArgs m_bound_args;

}; // class Bind< TCallable, TBoundArgs... >

template< typename TCallable, typename ... TBoundArgs >
struct IsBindExpression< Bind< TCallable, TBoundArgs... > > : public BooleanTrue {
};

template< typename TResult, typename TCallable, typename ... TBoundArgs >
class BindR : Bind< TCallable, TBoundArgs... > {
	using Base = Bind< TCallable, TBoundArgs... >;

	using Callable = typename Base::Callable;

	using BoundArgs = typename Base::BoundArgs;

public:
	using Result = TResult;

	BindR(BindR const & bind) = default;

	BindR(BindR && bind) = default;

	template< typename TOtherCallable, typename ...TOtherBoundArgs, typename = EnableIf< BooleanAnd< IsConvertible< TOtherCallable, Callable >, NotSame< RemoveReference<TOtherCallable>, BindR > > > >
	explicit BindR(
		TOtherCallable && callable, TOtherBoundArgs && ... bound_args
	) : Base(forward<TOtherCallable>(callable), forward<TOtherBoundArgs>(bound_args)...) {
	}

	auto operator=(BindR const & bind) -> BindR & = default;

	auto operator=(BindR && bind) -> BindR & = default;

	template< typename ... TArgs >
	auto operator()(TArgs && ... args) -> EnableIf< IsConvertible< BindReturn< Callable, BoundArgs, Tuple< TArgs && ... > >, Result >, Result > {
		return Base::operator()(forward<TArgs>(args)...);
	}

	template< typename ... TArgs >
	auto operator()(TArgs && ... args) const -> EnableIf< IsConvertible< BindReturn< Callable const, BoundArgs const, Tuple< TArgs && ... > >, Result >, Result > {
		return Base::operator()(forward<TArgs>(args)...);
	}

}; // class BindR< TResult, TCallable, TBoundArgs... >

template< typename TResult, typename TCallable, typename ... TBoundArgs >
struct IsBindExpression< BindR< TResult, TCallable, TBoundArgs... > > : public BooleanTrue {
};

} // namespace Functional
} // namespace Detail

template< typename T >
struct IsBindExpression : public Detail::Functional::IsBindExpression< RemoveConstVolatile<T> > {
};

template< typename T >
struct IsPlaceholder : public Detail::Functional::IsPlaceholder< RemoveConstVolatile<T> > {
};

template< typename TCallable, typename ... TBoundArgs >
inline auto bind(TCallable && callable, TBoundArgs &&... bound_args) -> Detail::Functional::Bind< TCallable, TBoundArgs... > {
	return Detail::Functional::Bind< TCallable, TBoundArgs... >(forward<TCallable>(callable), forward<TBoundArgs>(bound_args)...);
}

template< typename TResult, typename TCallable, typename ... TBoundArgs >
inline auto bind(TCallable && callable, TBoundArgs &&... bound_args) -> Detail::Functional::BindR< TResult, TCallable, TBoundArgs... > {
	return Detail::Functional::BindR< TCallable, TBoundArgs... >(forward<TCallable>(callable), forward<TBoundArgs>(bound_args)...);
}

} // namespace BR