#include "test.hpp"

#include <libbr/type_traits/has_trivial_copy_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasTrivialCopyConstructor) {
	HAS_TRAITS_CHECK(false, TrivialCopyConstructor, trivial_copy_constructor, void);
}