#include <libbr/strings.hpp>

#include <cstring>
#include <cwchar>

using namespace BR;

auto libbr_nstring_compare(BR::CString<BR::NChar> x, BR::CString<BR::NChar> y) -> BR::Relation {
	return BR::to_relation(std::strcmp(x, y));
}

auto libbr_wstring_compare(BR::CString<BR::WChar> x, BR::CString<BR::WChar> y) -> BR::Relation {
	return BR::to_relation(std::wcscmp(x, y));
}

auto libbr_nstring_compare_n(BR::CString<BR::NChar> x, BR::CString<BR::NChar> y, BR::Size count) -> BR::Relation {
	return BR::to_relation(std::strncmp(x, y, count));
}

auto libbr_wstring_compare_n(BR::CString<BR::WChar> x, BR::CString<BR::WChar> y, BR::Size count) -> BR::Relation {
	return BR::to_relation(std::wcsncmp(x, y, count));
}