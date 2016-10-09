#include "test.hpp"

#include <libbr/type_traits/is_standard_layout.hpp>

using namespace BR;

TEST(TypeTraits, IsStandardLayout) {
	IS_TRAITS_CHECK(false, StandardLayout, standard_layout, void);
}