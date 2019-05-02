#include "test.hpp"

#include <libbr/type_traits/is_polymorphic.hpp>

using namespace BR;

TEST(TypeTraits, IsPolymorphic) {
	IS_TRAITS_CHECK_CV(true, Polymorphic, polymorphic, Polymorphic);
	IS_TRAITS_CHECK_CV(true, Polymorphic, polymorphic, PolymorphicDerived);

	IS_TRAITS_CHECK_CV(false, Polymorphic, polymorphic, void);
	IS_TRAITS_CHECK_CV(false, Polymorphic, polymorphic, Class);
	IS_TRAITS_CHECK_CV(false, Polymorphic, polymorphic, Struct);
}