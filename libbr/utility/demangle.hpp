#pragma once

#include <libbr/config.hpp>

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
#include <string>

namespace BR {

inline char const * demangle_allocate(char const * name) noexcept;

inline void demangle_free(char const * name) noexcept;

inline std::string demangle(char const * name);

class ScopedDemangledName {
public:
	explicit ScopedDemangledName(char const * name) noexcept : m_name(demangle_allocate(name)) {
	}

	~ScopedDemangledName() noexcept {
		demangle_free(m_name);
	}

	char const * get() const noexcept {
		return m_name;
	}
private:
	ScopedDemangledName(ScopedDemangledName const&) = delete;

	ScopedDemangledName & operator=(ScopedDemangledName const &) = delete;

private:
	char const * m_name;
};

#if defined(BR_HAS_CXXABI_H)

inline char const * demangle_allocate(char const * name) noexcept {
	int status = 0;
	Size size = 0;
	return abi::__cxa_demangle(name, nullptr, &size, &status);
}

inline void demangle_free(char const * name) noexcept {
	std::free(const_cast<char *>(name));
}

inline std::string demangle(char const * name) {
	ScopedDemangledName demangled_name(name);
	char const * const p = demangled_name.get();
	return p != nullptr ? p : name;
}

#else

inline char const * demangle_allocate(char const * name) noexcept {
	return name;
}

inline void demangle_free(char const * name) noexcept {}

inline std::string demangle(char const * name) {
	return name;
}

#endif

} // namespace BR

#undef BR_HAS_CXXABI_H