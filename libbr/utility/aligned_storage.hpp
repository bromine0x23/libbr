/**
 * @file
 * @brief AlignedStorage
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/max_integer.hpp>
#include <libbr/type_traits/alignment_of.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/utility/types.hpp>

namespace BR {

namespace Detail {
namespace Utility {

template< typename ...TTypes >
using FindMaxAlignment = MaxInteger< AlignmentOf<TTypes>... >;

using GetMaxAlignment = FindMaxAlignment< UInt8, UInt16, UInt32, UInt64, SFloat, DFloat, QFloat, void * >;

template< Size length, Size alignment >
struct AlignedStorage {
	alignas(alignment) unsigned char data[length];
};

} // namespace Utility
} // namespace Detail

template< Size length, Size alignment = Detail::Utility::GetMaxAlignment::value >
struct TypeAlignedStorage : public TypeWrapper< Detail::Utility::AlignedStorage< length, alignment > > {
};

template< Size length, Size alignment = Detail::Utility::GetMaxAlignment::value >
using AlignedStorage = TypeUnwrap< TypeAlignedStorage< length, alignment > >;

} // namespace BR
