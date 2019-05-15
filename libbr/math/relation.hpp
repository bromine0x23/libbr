/**
 * @file
 * @brief Relation
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Math {

/**
 * @brief 比较结果
 */
enum class Relation {
	LT = -1, ///< 小于
	EQ =  0, ///< 等于
	GT =  1, ///< 大于
};

/**
 * @brief 数值转 Relation
 *
 * (x < 0) => Relation::LT \n
 * (x = 0) => Relation::EQ \n
 * (x > 0) => Relation::GT
 */
template< typename TNumeric >
constexpr auto to_relation(TNumeric const & x) -> Relation {
	return x != TNumeric(0) ? (x < TNumeric(0) ? Relation::LT : Relation::GT) : Relation::EQ;
}

} // inline namespace Math
} // namespace BR
