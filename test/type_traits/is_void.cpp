#include "test.hpp"

#include <libbr/type_traits/is_void.hpp>

using namespace BR;

TEST(TypeTraits, IsVoid) {
	IS_TRAITS_CHECK_CV(true, Void, void, void);
}