#include "test.hpp"

#include <libbr/type_traits/is_rvalue_reference.hpp>

using namespace BR;

TEST(TypeTraits, IsRValueReference) {
	IS_TRAITS_CHECK_CV(false, RValueReference, rvalue_reference, void);
}