/**
 * @file
 * @brief StringView
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/encoding/encoding.hpp>
#include <libbr/string/raw_string.hpp>

namespace BR {


/**
 * @brief 字符串类
 * @tparam TEncoding 编码类型
 */
template< typename TEncoding = DefaultEncoding >
class StringView;



template< typename TEncoding >
class StringView : public RawStringView< typename TEncoding::CodeUnit > {
};

} // namespace BR