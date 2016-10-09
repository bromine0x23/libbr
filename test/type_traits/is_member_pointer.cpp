#include "test.hpp"

#include <libbr/type_traits/is_member_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsMemberPointer) {
	IS_TRAITS_CHECK_CV(false, MemberPointer, member_pointer, void);
}