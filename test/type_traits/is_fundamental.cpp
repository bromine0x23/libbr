#include "test.hpp"

#include<libbr/type_traits/is_fundamental.hpp>

using namespace BR;

TEST(TypeTraits, IsFundamental) {
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, void);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, bool);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, char);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, wchar_t);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, char16_t);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, char32_t);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental,   signed char);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, unsigned char);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental,   signed short);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, unsigned short);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental,   signed int);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, unsigned int);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental,   signed long);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, unsigned long);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental,   signed long long);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, unsigned long long);
#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK_CV(true, Fundamental, fundamental, SInt128);
	IS_TRAITS_CHECK_CV(true, Fundamental, fundamental, UInt128);
#endif
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, float);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, double);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, long double);
	IS_TRAITS_CHECK_CV(true , Fundamental, fundamental, NullPointer);

	IS_TRAITS_CHECK(false, Fundamental, fundamental, int *);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int &);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int &&);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int []);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (*)[]);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (&)[]);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (&&)[]);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int [2]);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (*)[2]);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (&)[2]);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (&&)[2]);
	IS_TRAITS_CHECK_CV(false, Fundamental, fundamental, Class);
	IS_TRAITS_CHECK_CV(false, Fundamental, fundamental, Union);
	IS_TRAITS_CHECK_CV(false, Fundamental, fundamental, Enum);
	IS_TRAITS_CHECK_CV(false, Fundamental, fundamental, EnumClass);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (Class));
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (*)(Class));
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (&)(Class));
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (&&)(Class));
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int Class::*);
	IS_TRAITS_CHECK(false, Fundamental, fundamental, int (Class::*)());
}