#include "test.hpp"

#include <libbr/type_traits/is_signed.hpp>

using namespace BR;

TEST(TypeTraits, IsSigned) {
	IS_TRAITS_CHECK_CV(true , Signed, signed, signed char);
	IS_TRAITS_CHECK_CV(true , Signed, signed, signed short);
	IS_TRAITS_CHECK_CV(true , Signed, signed, signed int);
	IS_TRAITS_CHECK_CV(true , Signed, signed, signed long);
	IS_TRAITS_CHECK_CV(true , Signed, signed, signed long long);

	IS_TRAITS_CHECK(false, Signed, signed, void);
	IS_TRAITS_CHECK(false, Signed, signed, unsigned char);
	IS_TRAITS_CHECK(false, Signed, signed, unsigned short);
	IS_TRAITS_CHECK(false, Signed, signed, unsigned int);
	IS_TRAITS_CHECK(false, Signed, signed, unsigned long);
	IS_TRAITS_CHECK(false, Signed, signed, unsigned long long);
}