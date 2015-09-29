/**
 * @file
 * @author Bromine0x23
 * @since 2015/9/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/bignum_basic.hpp>
#include <libbr/math/detail/bignum_config.hpp>

namespace BR {

/**
 * @brief Bignum 相关的帮助方法和常量
 * @author Bromine0x23
 * @since 2015/9/24
 *
 * BignumBasic 的静态方法和常量被导出到该名字空间中
 */
namespace BignumHelper {

/**
 * @see BignumBasic::positive
 */
// constexpr static auto positive = BignumBasic::positive;

/**
 * @see BignumBasic::negative
 */
// constexpr static auto negative = BignumBasic::negative;

/**
 * @see BignumBasic::absolute
 */
// constexpr static auto absolute = BignumBasic::absolute;

/**
 * @see BignumBasic::complement
 */
// constexpr static auto complement = BignumBasic::complement;

/**
 * @see BignumBasic::value()
 */
template< BignumConfig::Digit v >
constexpr auto value() -> decltype(BignumBasic::value<v>()) {
	return BignumBasic::value<v>();
}

/**
 * @see BignumBasic::bits()
 */
template< typename T >
constexpr auto bits(T n) -> decltype(BignumBasic::bits(n)) {
	return BignumBasic::bits(n);
}

/**
 * @see BignumBasic::digits()
 */
template< typename T >
constexpr auto digits(T n) -> decltype(BignumBasic::digits(n)) {
	return BignumBasic::digits(n);
}

/**
 * @see BignumBasic::power2()
 */
template< BignumConfig::Digit v >
constexpr auto power2(BignumConfig::Digit n) -> decltype(BignumBasic::power2(n)) {
	return BignumBasic::power2(n);
}

/**
 * @see BignumBasic::exponent()
 */
constexpr auto exponent(BignumConfig::Digit n) -> decltype(BignumBasic::exponent(n)) {
	return BignumBasic::exponent(n);
}

} // namespace BignumHelper

} // namespace BR
