#include "test.hpp"

#include <libbr/type_traits/is_member_object_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsMemberObjectPointer) {
	IS_TRAITS_CHECK_CV(false, MemberObjectPointer, member_object_pointer, void);
}