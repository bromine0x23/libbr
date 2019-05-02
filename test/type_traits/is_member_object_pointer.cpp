#include "test.hpp"

#include <libbr/type_traits/is_member_object_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsMemberObjectPointer) {
	IS_TRAITS_CHECK(true, MemberObjectPointer, member_object_pointer, MemberPointer<Class, int>);

	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, void);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, int);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, int *);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, int &);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, int &&);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, int []);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, int [2]);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, CFunction<void> *);
	IS_TRAITS_CHECK(false, MemberObjectPointer, member_object_pointer, MemberPointer<Class, auto () -> int >);
}