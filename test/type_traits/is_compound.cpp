#include "test.hpp"

#include<libbr/type_traits/is_compound.hpp>

using namespace BR;

TEST(TypeTraits, IsCompound) {
	IS_TRAITS_CHECK(false, Compound, compound, void);
	IS_TRAITS_CHECK(false, Compound, compound, bool);
	IS_TRAITS_CHECK(false, Compound, compound,   signed char);
	IS_TRAITS_CHECK(false, Compound, compound, unsigned char);
	IS_TRAITS_CHECK(false, Compound, compound,   signed short);
	IS_TRAITS_CHECK(false, Compound, compound, unsigned short);
	IS_TRAITS_CHECK(false, Compound, compound,   signed int);
	IS_TRAITS_CHECK(false, Compound, compound, unsigned int);
	IS_TRAITS_CHECK(false, Compound, compound,   signed long);
	IS_TRAITS_CHECK(false, Compound, compound, unsigned long);
	IS_TRAITS_CHECK(false, Compound, compound,   signed long long);
	IS_TRAITS_CHECK(false, Compound, compound, unsigned long long);
#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK(false, Compound, compound, SInt128);
	IS_TRAITS_CHECK(false, Compound, compound, UInt128);
#endif
	IS_TRAITS_CHECK(false, Compound, compound, float);
	IS_TRAITS_CHECK(false, Compound, compound, double);
	IS_TRAITS_CHECK(false, Compound, compound, long double);
	IS_TRAITS_CHECK(false, Compound, compound, char);
	IS_TRAITS_CHECK(false, Compound, compound, wchar_t);
	IS_TRAITS_CHECK(false, Compound, compound, char16_t);
	IS_TRAITS_CHECK(false, Compound, compound, char32_t);
	IS_TRAITS_CHECK(false, Compound, compound, NullPointer);

	IS_TRAITS_CHECK(true, Compound, compound, int *);
	IS_TRAITS_CHECK(true, Compound, compound, int &);
	IS_TRAITS_CHECK(true, Compound, compound, int &&);
	IS_TRAITS_CHECK(true, Compound, compound, int[]);
	IS_TRAITS_CHECK(true, Compound, compound, int[2]);
	IS_TRAITS_CHECK(true, Compound, compound, CFunction<int, int>);
	IS_TRAITS_CHECK(true, Compound, compound, CFunction<int, int> *);
	IS_TRAITS_CHECK(true, Compound, compound, int Class::*);
	IS_TRAITS_CHECK(true, Compound, compound, CFunction<int, int> Class::*);
	IS_TRAITS_CHECK_CV(true, Compound, compound, Class);
	IS_TRAITS_CHECK_CV(true, Compound, compound, Struct);
	IS_TRAITS_CHECK_CV(true, Compound, compound, Union);
	IS_TRAITS_CHECK_CV(true, Compound, compound, Enum);
	IS_TRAITS_CHECK_CV(true, Compound, compound, EnumClass);
}