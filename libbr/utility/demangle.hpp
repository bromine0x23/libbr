#pragma once

#include <libbr/config.hpp>
#include <libbr/string/string.hpp>

namespace BR {

auto demangle(CString<NChar> name) -> String<NChar>;

} // namespace BR