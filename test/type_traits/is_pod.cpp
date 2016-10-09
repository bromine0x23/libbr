#include "test.hpp"

#include <libbr/type_traits/is_pod.hpp>

using namespace BR;

TEST(TypeTraits, IsPOD) {
	IS_TRAITS_CHECK_CV(false, POD, pod, void);
}