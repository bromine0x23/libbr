/**
 * @file
 * @brief Encoding
 * @author Bromine0x23
 * @since 16/9/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/encoding/ascii_encoding.hpp>
#include <libbr/encoding/gb18030_encoding.hpp>
#include <libbr/encoding/utf8_encoding.hpp>
#include <libbr/encoding/utf16_encoding.hpp>
#include <libbr/encoding/utf16_le_encoding.hpp>

namespace BR {

struct ASCIIEncoding;

struct UTF8Encoding;

struct UTF16Encoding;

struct UTF16LEEncoding;

struct GB18030Encoding;

using DefaultEncoding = BR_JOIN(BR_ENCODING, Encoding);

} // namespace BR
