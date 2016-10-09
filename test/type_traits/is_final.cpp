#include "test.hpp"

#include<libbr/type_traits/is_final.hpp>

using namespace BR;

TEST(TypeTraits, IsFinal) {
	IS_TRAITS_CHECK_CV(false, Final, final, Class);
	IS_TRAITS_CHECK_CV(false, Final, final, Base);
	IS_TRAITS_CHECK_CV(false, Final, final, Derived);
	IS_TRAITS_CHECK_CV(true, Final, final, FinalInherit);
}