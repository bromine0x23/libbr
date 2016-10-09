#include <libbr/string/string_append.hpp>
#include <libbr/string/string_compare.hpp>
#include <libbr/string/string_copy.hpp>
#include <libbr/string/string_fill.hpp>
#include <libbr/string/string_find.hpp>
#include <libbr/string/string_length.hpp>
#include <libbr/string/string_move.hpp>
#include <libbr/string/string_search.hpp>
#include <cstring>
#include <cwchar>
#include <libbr/string/raw_string.hpp>
#include <libbr/string/string.hpp>

#if defined(BR_MSVC)
#pragma warning(push)
#pragma warning(disable: 4996)
#elif defined(BR_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

auto libbr_nstring_append(BR::NChar * D, BR::CString<BR::NChar> S) -> BR::NChar * {
	return std::strcat(D, S);
}

auto libbr_wstring_append(BR::WChar * D, BR::CString<BR::WChar> S) -> BR::WChar * {
	return std::wcscat(D, S);
}

auto libbr_nstring_append_n(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar * {
	return std::strncat(D, S, n);
}

auto libbr_wstring_append_n(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar * {
	return std::wcsncat(D, S, n);
}

auto libbr_nstring_compare(BR::CString<BR::NChar> X, BR::CString<BR::NChar> Y) -> BR::Relation {
	return BR::to_relation(std::strcmp(X, Y));
}

auto libbr_wstring_compare(BR::CString<BR::WChar> X, BR::CString<BR::WChar> Y) -> BR::Relation {
	return BR::to_relation(std::wcscmp(X, Y));
}

auto libbr_nstring_compare_n(BR::CString<BR::NChar> X, BR::CString<BR::NChar> Y, BR::Size n) -> BR::Relation {
	return BR::to_relation(std::strncmp(X, Y, n));
}

auto libbr_wstring_compare_n(BR::CString<BR::WChar> X, BR::CString<BR::WChar> Y, BR::Size n) -> BR::Relation {
	return BR::to_relation(std::wcsncmp(X, Y, n));
}

auto libbr_nstring_copy(BR::NChar * D, BR::CString<BR::NChar> S) -> BR::NChar * {
	return std::strcpy(D, S);
}

auto libbr_wstring_copy(BR::WChar * D, BR::CString<BR::WChar> S) -> BR::WChar * {
	return std::wcscpy(D, S);
}

auto libbr_nstring_copy_n(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar * {
	return std::strncpy(D, S, n);
}

auto libbr_wstring_copy_n(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar * {
	return std::wcsncpy(D, S, n);
}

auto libbr_nstring_find(BR::NChar * S, BR::NChar c) -> BR::NChar * {
	return std::strchr(S, c);
}

auto libbr_wstring_find(BR::WChar * S, BR::WChar c) -> BR::WChar * {
	return std::wcschr(S, c);
}

auto libbr_nstring_find_n(BR::NChar * S, BR::NChar c, BR::Size n) -> BR::NChar * {
	return reinterpret_cast<BR::NChar *>(std::memchr(S, c, n));
}

auto libbr_wstring_find_n(BR::WChar * S, BR::WChar c, BR::Size n) -> BR::WChar * {
	return std::wmemchr(S, c, n);
}

auto libbr_nstring_fill(BR::NChar * D, BR::NChar c, BR::Size n) -> BR::NChar * {
	return reinterpret_cast<BR::NChar *>(std::memset(D, c, n));
}

auto libbr_wstring_fill(BR::WChar * D, BR::WChar c, BR::Size n) -> BR::WChar * {
	return std::wmemset(D, c, n);
}

auto libbr_nstring_length(BR::CString<BR::NChar> S) -> BR::Size {
	return std::strlen(S);
}

auto libbr_wstring_length(BR::CString<BR::WChar> S) -> BR::Size {
	return std::wcslen(S);
}
auto libbr_nstring_move(BR::NChar * D, BR::CString<BR::NChar> S, BR::Size n) -> BR::NChar * {
	return reinterpret_cast<BR::NChar *>(std::memmove(D, S, n));
}

auto libbr_wstring_move(BR::WChar * D, BR::CString<BR::WChar> S, BR::Size n) -> BR::WChar * {
	return std::wmemmove(D, S, n);
}

auto libbr_nstring_search(BR::NChar * S, BR::CString<BR::NChar> K) -> BR::NChar * {
	return std::strstr(S, K);
}

auto libbr_wstring_search(BR::WChar * S, BR::CString<BR::WChar> K) -> BR::WChar * {
	return std::wcsstr(S, K);
}

namespace BR {

template class RawString<Char8>;

template class RawString<Char16>;

template class RawString<Char32>;

template class String<ASCIIEncoding>;

template class String<UTF8Encoding>;

} // namespace BR

#if defined(BR_MSVC)
#pragma warning(pop)
#elif defined(BR_CLANG)
#pragma clang diagnostic pop
#endif
