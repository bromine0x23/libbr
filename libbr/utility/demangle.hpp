#pragma once

#include <libbr/config.hpp>

#include <string>

#if defined(BR_CLANG) && defined(__has_include)
#  if __has_include(<cxxabi.h>)
#    define BR_HAS_CXXABI_H
#  endif
#elif defined(__GLIBCXX__) || defined(__GLIBCPP__)
#   define BR_HAS_CXXABI_H
#endif

#if defined(BR_HAS_CXXABI_H)
#  include<cxxabi.h>
#  include<cstdlib>
#  include<cstddef>
#endif

namespace BR {

inline auto demangle_allocate(CString<NChar> name) noexcept -> CString<NChar>;

inline void demangle_free(CString<NChar> name) noexcept;

inline auto demangle(CString<NChar> name) -> std::string;

class ScopedDemangledName {
public:
	explicit ScopedDemangledName(CString<NChar> name) noexcept : m_name(demangle_allocate(name)) {
	}

	~ScopedDemangledName() noexcept {
		demangle_free(m_name);
	}

	auto get() const noexcept -> CString<NChar> {
		return m_name;
	}

private:
	ScopedDemangledName(ScopedDemangledName const & name) = delete;

	auto operator=(ScopedDemangledName const & name) -> ScopedDemangledName & = delete;

private:
	CString<NChar> m_name;
};

#if defined(BR_HAS_CXXABI_H)

inline auto demangle_allocate(CString<NChar> name) noexcept -> CString<NChar> {
	int status = 0;
	Size size = 0;
	return abi::__cxa_demangle(name, nullptr, &size, &status);
}

inline void demangle_free(CString<NChar> name) noexcept {
	std::free(const_cast< NChar * >(name));
}

inline auto demangle(CString<NChar> name) -> std::string {
	ScopedDemangledName demangled_name(name);
	CString<NChar> const p = demangled_name.get();
	return p != nullptr ? p : name;
}

#else

inline auto demangle_allocate(CString<NChar> name) noexcept -> CString<NChar> {
	return name;
}

inline void demangle_free(CString<NChar> name) noexcept {}

inline auto demangle(CString<NChar> name) -> std::string {
	return name;
}

#endif

} // namespace BR

#undef BR_HAS_CXXABI_H