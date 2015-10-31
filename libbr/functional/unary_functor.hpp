/**
 * @file
 * @brief 一元仿函数基类
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/basic_functor.hpp>

namespace BR {

template< typename TArgument >
struct UnaryFunctor : public BasicFunctor< TArgument > {
};

} // namespace BR
