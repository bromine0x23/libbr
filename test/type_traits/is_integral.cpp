#include "test.hpp"

#include<libbr/type_traits/is_integral.hpp>

using namespace BR;

TEST(TypeTraits, IsIntegral) {
	IS_TRAITS_CHECK_CV(false, Integral, integral, void);
	IS_TRAITS_CHECK_CV(true , Integral, integral, bool);
	IS_TRAITS_CHECK_CV(true , Integral, integral, char);
	IS_TRAITS_CHECK_CV(true , Integral, integral, wchar_t);
	IS_TRAITS_CHECK_CV(true , Integral, integral, char16_t);
	IS_TRAITS_CHECK_CV(true , Integral, integral, char32_t);
	IS_TRAITS_CHECK_CV(true , Integral, integral,   signed char);
	IS_TRAITS_CHECK_CV(true , Integral, integral, unsigned char);
	IS_TRAITS_CHECK_CV(true , Integral, integral,   signed short);
	IS_TRAITS_CHECK_CV(true , Integral, integral, unsigned short);
	IS_TRAITS_CHECK_CV(true , Integral, integral,   signed int);
	IS_TRAITS_CHECK_CV(true , Integral, integral, unsigned int);
	IS_TRAITS_CHECK_CV(true , Integral, integral,   signed long);
	IS_TRAITS_CHECK_CV(true , Integral, integral, unsigned long);
	IS_TRAITS_CHECK_CV(true , Integral, integral,   signed long long);
	IS_TRAITS_CHECK_CV(true , Integral, integral, unsigned long long);
#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK_CV(true, Integral, integral, SInt128);
	IS_TRAITS_CHECK_CV(true, Integral, integral, UInt128);
#endif
	IS_TRAITS_CHECK_CV(false, Integral, integral, float);
	IS_TRAITS_CHECK_CV(false, Integral, integral, double);
	IS_TRAITS_CHECK_CV(false, Integral, integral, long double);
	IS_TRAITS_CHECK_CV(false, Integral, integral, NullPointer);
	IS_TRAITS_CHECK_CV(false, Integral, integral, Class);
	IS_TRAITS_CHECK_CV(false, Integral, integral, Union);
	IS_TRAITS_CHECK_CV(false, Integral, integral, Enum);
	IS_TRAITS_CHECK_CV(false, Integral, integral, EnumClass);
	IS_TRAITS_CHECK(false, Integral, integral, int *);
	IS_TRAITS_CHECK(false, Integral, integral, int &);
	IS_TRAITS_CHECK(false, Integral, integral, int &&);
}