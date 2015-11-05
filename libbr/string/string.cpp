#include <libbr/string/cstring.hpp>
#include <cstring>
#include <cwchar>

namespace BR {

auto string_compare(CString<NChar> X, CString<NChar> Y) -> Relation {
	return to_relation(std::strcmp(X, Y));
}

auto string_compare(CString<WChar> X, CString<WChar> Y) -> Relation {
	return to_relation(std::wcscmp(X, Y));
}

auto string_compare(CString<NChar> X, CString<NChar> Y, Size n) -> Relation {
	return to_relation(std::strncmp(X, Y, n));
}

auto string_compare(CString<WChar> X, CString<WChar> Y, Size n) -> Relation {
	return to_relation(std::wcsncmp(X, Y, n));
}

auto string_concat(NChar * D, CString<NChar> S) -> NChar * {
	return std::strcat(D, S);
}

auto string_concat(WChar * D, CString<WChar> S) -> WChar * {
	return std::wcscat(D, S);
}

auto string_concat(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return std::strncat(D, S, n);
}

auto string_concat(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return std::wcsncat(D, S, n);
}

auto string_copy(NChar * D, CString<NChar> S) -> NChar * {
	return std::strcpy(D, S);
}

auto string_copy(WChar * D, CString<WChar> S) -> WChar * {
	return std::wcscpy(D, S);
}

auto string_copy(NChar * D, CString<NChar> S, Size n) -> NChar * {
	return std::strncpy(D, S, n);
}

auto string_copy(WChar * D, CString<WChar> S, Size n) -> WChar * {
	return std::wcsncpy(D, S, n);
}

auto string_find(NChar const * S, NChar c) -> NChar const * {
	return std::strchr(S, c);
}

auto string_find(WChar const * S, WChar c) -> WChar const * {
	return std::wcschr(S, c);
}

auto string_find(NChar * S, NChar c) -> NChar * {
	return std::strchr(S, c);
}

auto string_find(WChar * S, WChar c) -> WChar * {
	return std::wcschr(S, c);
}

auto string_length(CString<NChar> X) -> Size {
	return std::strlen(X);
}

auto string_length(CString<WChar> X) -> Size {
	return std::wcslen(X);
}

auto string_search(NChar const * S, CString<NChar> K) -> NChar const * {
	return std::strstr(S, K);
}

auto string_search(WChar const * S, CString<WChar> K) -> WChar const * {
	return std::wcsstr(S, K);
}

auto string_search(NChar * S, CString<NChar> K) -> NChar * {
	return std::strstr(S, K);
}

auto string_search(WChar * S, CString<WChar> K) -> WChar * {
	return std::wcsstr(S, K);
}

} // namespace BR