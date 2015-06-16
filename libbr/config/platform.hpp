#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__)
#  define BR_PLATFORM_CONFIG <libbr/config/platform/linux.hpp>
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#  define BR_PLATFORM_CONFIG <libbr/config/platform/win32.hpp>
#else
#  error "Unknown platform."
#endif

#if 0
#include <libbr/config/platform/linux.hpp>
#include <libbr/config/platform/win32.hpp>
#endif // 0

