#include "test.hpp"

#include <libbr/type_traits/is_polymorphic.hpp>

using namespace BR;

TEST(TypeTraits, IsPolymorphic) {
	IS_TRAITS_CHECK_CV(false, Polymorphic, polymorphic, void);
}