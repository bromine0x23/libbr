#include "test.hpp"

#include <libbr/type_traits/is_lvalue_reference.hpp>

using namespace BR;

TEST(TypeTraits, IsLValueReference) {
	IS_TRAITS_CHECK_CV(false, LValueReference, lvalue_reference, void);
}