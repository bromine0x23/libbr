#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/type_traits/is_integral.hpp>

namespace BR {
namespace Detail {
namespace Math {

template< typename T, bool = IsIntegral<T>{} >
struct TypeFloatPromote;

template< typename T >
using FloatPromote = TypeUnwrap< TypeFloatPromote<T> >;

template< typename T, bool >
struct TypeFloatPromote : public TypeWrapper<Float64> {};

template< typename T >
struct TypeFloatPromote<T, false> {};

template<>
struct TypeFloatPromote<Float32> : public TypeWrapper<Float32> {};

template<>
struct TypeFloatPromote<Float64> : public TypeWrapper<Float64> {};

template< typename TX, typename TY>
using FloatPromote2 = decltype(FloatPromote<TX>() + FloatPromote<TY>());

} // namespace Math
} // namespace Detail
} // namespace BR
