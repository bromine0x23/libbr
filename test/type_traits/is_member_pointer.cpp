#include "test.hpp"

#include <libbr/type_traits/is_member_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsMemberPointer) {
	IS_TRAITS_CHECK(true, MemberPointer, member_pointer, MemberPointer<Class, int>);
	IS_TRAITS_CHECK(true, MemberPointer, member_pointer, MemberPointer<Class, CFunction<void> >);

	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, void);
	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, int);
	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, int *);
	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, int &);
	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, int &&);
	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, int []);
	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, int [2]);
	IS_TRAITS_CHECK(false, MemberPointer, member_pointer, CFunction<void> *);
}