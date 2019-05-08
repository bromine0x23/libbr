#include "test.hpp"

#include <libbr/type_traits/has_member_type.hpp>

using namespace BR;

namespace {

BR_HAS_MEMBER_TYPE(Type);

} // namespace [anonymous]

TEST(TypeTraits, HasMemberType) {

	typename IntegralConstant<int, 0>::Type a;
	HAS_TRAITS_CHECK(false, MemberTypeType, member_type_Type, void);
	HAS_TRAITS_CHECK(false, MemberTypeType, member_type_Type, int);
	HAS_TRAITS_CHECK(true , MemberTypeType, member_type_Type, TypeWrapper<void>);
	HAS_TRAITS_CHECK(true , MemberTypeType, member_type_Type, TypeWrapper<int>);
	HAS_TRAITS_CHECK(false, MemberTypeType, member_type_Type, Class);
}