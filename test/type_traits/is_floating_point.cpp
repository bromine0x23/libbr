#include "test.hpp"

#include<libbr/type_traits/is_floating_point.hpp>

using namespace BR;

TEST(TypeTraits, IsFloatingPoint) {
	IS_TRAITS_CHECK_CV(true , FloatingPoint, floating_point, float);
	IS_TRAITS_CHECK_CV(true , FloatingPoint, floating_point, double);
	IS_TRAITS_CHECK_CV(true , FloatingPoint, floating_point, long double);

	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, void);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, bool);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, char);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, wchar_t);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, char16_t);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, char32_t);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point,   signed char);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, unsigned char);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point,   signed short);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, unsigned short);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point,   signed int);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, unsigned int);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point,   signed long);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, unsigned long);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point,   signed long long);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, unsigned long long);
#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, SInt128);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, UInt128);
#endif
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, void);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, float *);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, float &);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, float &&);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, float []);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, float [2]);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, CFunction<float, float>);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, CFunction<float, float> *);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, float Class::*);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, CFunction<float, float> Class::*);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, NullPointer);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, Class);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, Struct);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, Union);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, Enum);
	IS_TRAITS_CHECK(false, FloatingPoint, floating_point, EnumClass);
}