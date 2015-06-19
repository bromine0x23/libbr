#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename TValue >
struct IntegerConstantBase {
	using Value = TValue;
};

template< typename TValue, TValue v >
struct IntegerConstant : IntegerConstantBase< TValue >, TypeWrapper< IntegerConstant< TValue, v > > {
	constexpr static auto value = v;
	constexpr operator TValue() const { return value; }
	constexpr TValue operator()() const { return value; }
};

template< typename TValue, TValue ... values >
struct Integers {};

} // namespace BR

