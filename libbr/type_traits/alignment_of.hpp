/**
 * @file
 * @brief 获取类型的对齐长度
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 获取类型的对齐长度
 * @tparam T
 * @see IntegerConstant
 *
 * <tt>alignof(T)</tt>
 */
template< typename T >
struct AlignmentOf;

/**
 * @brief AlignmentOf 的模板变量版本
 * @tparam T
 * @see AlignmentOf
 */
template< typename T >
constexpr auto alignment_of = integral_constant< AlignmentOf<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
struct AlignmentOf : IntegralConstant< Size, alignof(T) > {};

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct AlignmentOf : public IntegralRewrap< _::TypeTraits::AlignmentOf<T> > {};

} // namespace TypeTraits

} // namespace BR