#include "test.hpp"

#include<libbr/type_traits/is_compound.hpp>

using namespace BR;

TEST(TypeTraits, IsCompound) {
	IS_TRAITS_CHECK_CV(false, Compound, void);
	IS_TRAITS_CHECK_CV(false, Compound, bool);
	IS_TRAITS_CHECK_CV(false, Compound,   signed char);
	IS_TRAITS_CHECK_CV(false, Compound, unsigned char);
	IS_TRAITS_CHECK_CV(false, Compound,   signed short);
	IS_TRAITS_CHECK_CV(false, Compound, unsigned short);
	IS_TRAITS_CHECK_CV(false, Compound,   signed int);
	IS_TRAITS_CHECK_CV(false, Compound, unsigned int);
	IS_TRAITS_CHECK_CV(false, Compound,   signed long);
	IS_TRAITS_CHECK_CV(false, Compound, unsigned long);
	IS_TRAITS_CHECK_CV(false, Compound,   signed long long);
	IS_TRAITS_CHECK_CV(false, Compound, unsigned long long);
#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK_CV(false, Compound, SInt128);
	IS_TRAITS_CHECK_CV(false, Compound, UInt128);
#endif
	IS_TRAITS_CHECK_CV(false, Compound, float);
	IS_TRAITS_CHECK_CV(false, Compound, double);
	IS_TRAITS_CHECK_CV(false, Compound, long double);
	IS_TRAITS_CHECK_CV(false, Compound, char);
	IS_TRAITS_CHECK_CV(false, Compound, wchar_t);
	IS_TRAITS_CHECK_CV(false, Compound, char16_t);
	IS_TRAITS_CHECK_CV(false, Compound, char32_t);
	IS_TRAITS_CHECK_CV(false, Compound, NullPointer);

	IS_TRAITS_CHECK_CV(true, Compound, int *);
	IS_TRAITS_CHECK(true, Compound, int &);
	IS_TRAITS_CHECK(true, Compound, int &&);
	IS_TRAITS_CHECK(true, Compound, int[]);
	IS_TRAITS_CHECK(true, Compound, int[2]);
	IS_TRAITS_CHECK(true, Compound, int(*)[]);
	IS_TRAITS_CHECK(true, Compound, int(*)[2]);
	IS_TRAITS_CHECK(true, Compound, int(&)[]);
	IS_TRAITS_CHECK(true, Compound, int(&)[2]);
	IS_TRAITS_CHECK(true, Compound, int(&&)[]);
	IS_TRAITS_CHECK(true, Compound, int(&&)[2]);
	IS_TRAITS_CHECK(true, Compound, int(int));
	IS_TRAITS_CHECK(true, Compound, int(*)(int));
	IS_TRAITS_CHECK(true, Compound, int(&)(int));
	IS_TRAITS_CHECK(true, Compound, int(&&)(int));
	IS_TRAITS_CHECK(true, Compound, int(Class::*));
	IS_TRAITS_CHECK(true, Compound, int(Class::*)(int));
	IS_TRAITS_CHECK_CV(true, Compound, Class);
	IS_TRAITS_CHECK_CV(true, Compound, Union);
	IS_TRAITS_CHECK_CV(true, Compound, Enum);
	IS_TRAITS_CHECK_CV(true, Compound, EnumClass);
}