/**
 * @file
 * @brief AlignedStorage
 * @author Bromine0x23
 * @since 2015/11/7
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/types.hpp>
#include <libbr/type_operate/max_integer.hpp>
#include <libbr/type_traits/alignment_of.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename ...TTypes >
using FindMaxAlignment = MaxInteger< AlignmentOf<TTypes>... >;

using GetMaxAlignment = FindMaxAlignment< UInt8, UInt16, UInt32, UInt64, SFloat, DFloat, QFloat, void * >;

template< Size length, Size alignment >
struct AlignedStorage {
	alignas(alignment) unsigned char data[length];
};

} // namespace TypeOperate
} // namespace Detail

template< Size length, Size alignment = Detail::TypeOperate::GetMaxAlignment::value >
struct TypeAlignedStorage : public TypeWrapper< Detail::TypeOperate::AlignedStorage< length, alignment > > {
};

template< Size length, Size alignment = Detail::TypeOperate::GetMaxAlignment::value >
using AlignedStorage = TypeUnwrap< TypeAlignedStorage< length, alignment > >;

} // namespace BR
