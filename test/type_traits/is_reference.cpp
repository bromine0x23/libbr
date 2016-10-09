#include "test.hpp"

#include <libbr/type_traits/is_reference.hpp>

using namespace BR;

TEST(TypeTraits, IsReference) {
	IS_TRAITS_CHECK_CV(false, Reference, reference, void);
}