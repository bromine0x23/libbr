#include <libbr/utility/demangle.hpp>
#include <libbr/container/optional.hpp>

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
#endif

namespace BR {

namespace {

static inline auto demangle_implement(CString<NChar> name) -> RawString<NChar>;

#if defined(BR_HAS_CXXABI_H)

static inline auto demangle_allocate(CString<NChar> name) noexcept -> CString<NChar> {
	int status = 0;
	Size size = 0;
	return abi::__cxa_demangle(name, nullptr, &size, &status);
}

static inline void demangle_free(CString<NChar> name) noexcept {
	std::free(const_cast< NChar * >(name));
}

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

static inline auto demangle_implement(CString<NChar> name) -> RawString<NChar> {
	ScopedDemangledName demangled_name(name);
	CString<NChar> p = demangled_name.get();
	return p != nullptr ? p : name;
}

#else

static inline auto demangle_implement(CString<NChar> name) -> RawString<NChar> {
	return name;
}

#endif

} // namespace [anonymous]

auto demangle(CString<NChar> name) -> RawString<NChar> {
	return demangle_implement(name);
}

} // namespace BR

#undef BR_HAS_CXXABI_H