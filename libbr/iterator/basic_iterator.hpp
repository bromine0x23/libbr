/**
 * @file
 * @brief 迭代器基类
 * @author Bromine0x23
 * @since 2015/10/22
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>

namespace BR {

/**
 * @brief 作为所有迭代器类的基类，空类
 */
class BasicIterator {
public:
	struct Category : public IteratorTag {
	};
};

} // namespace BR
