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

auto libbr_nstring_copy_unsafely(BR::CString<BR::NChar> source, BR::NChar * destination) -> BR::NChar * {
	return std::strcpy(destination, source);
}

auto libbr_wstring_copy_unsafely(BR::CString<BR::WChar> source, BR::WChar * destination) -> BR::WChar * {
	return std::wcscpy(destination, source);
}

auto libbr_nstring_copy_unsafely_n(BR::CString<BR::NChar> source, BR::NChar * destination, BR::Size count) -> BR::NChar * {
	return std::strncpy(destination, source, count);
}

auto libbr_wstring_copy_unsafely_n(BR::CString<BR::WChar> source, BR::WChar * destination, BR::Size count) -> BR::WChar * {
	return std::wcsncpy(destination, source, count);
}

auto libbr_nstring_fill(BR::NChar * destination, BR::Size count, BR::NChar value) -> BR::NChar * {
	return reinterpret_cast<BR::NChar *>(std::memset(destination, value, count));
}

auto libbr_wstring_fill(BR::WChar * destination, BR::Size count, BR::WChar value) -> BR::WChar * {
	return std::wmemset(destination, value, count);
}

auto libbr_nstring_length(BR::CString<BR::NChar> string) -> BR::Size {
	return std::strlen(string);
}

auto libbr_wstring_length(BR::CString<BR::WChar> string) -> BR::Size {
	return std::wcslen(string);
}