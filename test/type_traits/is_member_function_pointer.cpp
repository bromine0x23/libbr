#include "test.hpp"

#include <libbr/type_traits/is_member_function_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsMemberFunctionPointer) {
	IS_TRAITS_CHECK_CV(false, MemberFunctionPointer, member_function_pointer, void);
}