#pragma once

#include <libbr/config.hpp>
#include <libbr/string/raw_string.hpp>

namespace BR {

auto demangle(CString<NChar> name) -> RawString<NChar>;

} // namespace BR