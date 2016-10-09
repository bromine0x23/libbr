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

class ASCIIEncoding;

class UTF8Encoding;

class UTF16Encoding;

class UTF16LEEncoding;

class GB18030Encoding;

using DefaultEncoding = BR_JOIN(BR_ENCODING, Encoding);

} // namespace BR
