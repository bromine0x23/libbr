#include "test.hpp"

#include <libbr/type_traits/is_trivial.hpp>

using namespace BR;

TEST(TypeTraits, IsTrivial) {
	IS_TRAITS_CHECK(false, Trivial, trivial, void);
}