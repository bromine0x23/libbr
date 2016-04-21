/**
 * @file
 * @brief AlignedUnion
 * @author Bromine0x23
 * @since 2015/11/7
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/types.hpp>
#include <libbr/type_operate/max_integer.hpp>
#include <libbr/type_traits/alignment_of.hpp>
#include <libbr/type_traits/size_of.hpp>
#include <libbr/utility/aligned_storage.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

template< Size length, typename ...TTypes >
struct TypeAlignedUnion : public TypeWrapper< AlignedStorage< MaxInteger< IntegralConstant< Size, length >, SizeOf<TTypes>... >::value, MaxInteger< AlignmentOf<TTypes>... >::value > > {
};

template< Size length, typename ...TTypes >
using AlignedUnion = TypeUnwrap< TypeAlignedUnion< length, TTypes... > >;

} // namespace BR
