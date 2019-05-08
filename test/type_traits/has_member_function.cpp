#include "test.hpp"

#include <libbr/type_traits/has_member_function.hpp>

using namespace BR;

struct Sample {

	void f() {}

	void f(int) {}

	void f(int, double) {}
};

BR_HAS_MEMBER_FUNCTION(f);

TEST(TypeTraits, HasMemberFunction) {
	HAS_TRAITS_CHECK(false, MemberFunction_f, member_function_f, void);
	HAS_TRAITS_CHECK(true , MemberFunction_f, member_function_f, Sample);
	HAS_TRAITS_CHECK(true , MemberFunction_f, member_function_f, Sample, int);
	HAS_TRAITS_CHECK(false, MemberFunction_f, member_function_f, Sample, int *);
	HAS_TRAITS_CHECK(true , MemberFunction_f, member_function_f, Sample, int, double);
}