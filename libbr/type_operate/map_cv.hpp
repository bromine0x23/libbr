/**
 * @file
 * @brief 映射 \em cv 修饰符
 * @author Bromine0x23
 * @since 2016/4/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename TTemplate, typename TParam >
struct TypeMapCV;

/**
 * @brief TypeMapCV 的简写版本
 * @tparam T
 * @see TypeMapCV
 */
template< typename TTemplate, typename TParam >
using MapCV = TypeUnwrap< TypeMapCV< TTemplate, TParam > >;

namespace Detail {
namespace TypeOperate {

template< typename TTemplate, typename TParam >
struct TypeMapCV : public TypeWrapper<TParam> {
};

template< typename TTemplate, typename TParam >
struct TypeMapCV< TTemplate const, TParam > : public TypeWrapper< TParam const > {
};

template< typename TTemplate, typename TParam >
struct TypeMapCV< TTemplate volatile, TParam > : public TypeWrapper< TParam volatile > {
};

template< typename TTemplate, typename TParam >
struct TypeMapCV< TTemplate const volatile, TParam > : public TypeWrapper< TParam const volatile > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename TTemplate, typename TParam >
struct TypeMapCV : public TypeRewrap< Detail::TypeOperate::TypeMapCV< TTemplate, TParam > > {
};

} // namespace BR
