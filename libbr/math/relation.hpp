/**
 * @file
 * @author Bromine0x23
 * @date 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 比较结果
 * @author Bromine0x23
 * @since 2015/6/16
 */
enum class Relation {
	LT = -1, ///< 小于
	EQ =  0, ///< 等于
	GT =  1, ///< 大于
};

/**
 * @brief 整形转 Relation
 *
 * (x < 0) => Relation::LT \n
 * (x = 0) => Relation::EQ \n
 * (x > 0) => Relation::GT
 */
template< typename TIntegral >
constexpr auto to_relation(TIntegral const & x) -> Relation {
	return x != TIntegral(0) ? (x < TIntegral(0) ? Relation::LT : Relation::GT) : Relation::EQ;
}

} // namespace BR
