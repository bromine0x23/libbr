#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename TValue >
struct BasicIntegerConstant {
	using Value = TValue;
};

template< typename TValue, TValue v >
struct IntegerConstant : BasicIntegerConstant< TValue >, TypeWrapper< IntegerConstant< TValue, v > > {
	constexpr static auto value = v;
	constexpr operator TValue() const { return value; }
	constexpr TValue operator()() const { return value; }
};

template< typename TValue, TValue ... values >
struct Integers {};

template< typename TValue, TValue value >
constexpr IntegerConstant< TValue, value > integer_constant() {
	return IntegerConstant< TValue, value >();
}

} // namespace BR

