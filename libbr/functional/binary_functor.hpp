/**
 * @file
 * @brief 二元函数对象基类
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/basic_functor.hpp>

namespace BR {

template< typename TX, typename TY >
struct BinaryFunctor : public BasicFunctor< TX, TY > {
};

} // namespace BR
