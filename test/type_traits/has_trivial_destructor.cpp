#include "test.hpp"

#include <libbr/type_traits/has_trivial_destructor.hpp>

using namespace BR;

TEST(TypeTraits, HasTrivialDestructor) {
	HAS_TRAITS_CHECK(false, TrivialDestructor, trivial_destructor, void);
}