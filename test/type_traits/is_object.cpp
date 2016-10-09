#include "test.hpp"

#include <libbr/type_traits/is_object.hpp>

using namespace BR;

TEST(TypeTraits, IsObject) {
	IS_TRAITS_CHECK_CV(false, Object, object, void);
}