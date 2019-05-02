#include "test.hpp"

#include <libbr/type_traits/is_scalar.hpp>

using namespace BR;

TEST(TypeTraits, IsScalar) {
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, bool);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, char);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, wchar_t);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, char16_t);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, char32_t);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar,   signed char);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, unsigned char);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar,   signed short);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, unsigned short);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar,   signed int);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, unsigned int);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar,   signed long);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, unsigned long);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar,   signed long long);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, unsigned long long);
#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, SInt128);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, UInt128);
#endif
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, float);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, double);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, long double);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, NullPointer);

	IS_TRAITS_CHECK_CV(true, Scalar, scalar, void *);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, int *);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, Enum);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, EnumClass);
	IS_TRAITS_CHECK_CV(true, Scalar, scalar, NullPointer);
	IS_TRAITS_CHECK(true, Scalar, scalar, CFunction<void> *);
	IS_TRAITS_CHECK(true, Scalar, scalar, CFunction<int> *);
	IS_TRAITS_CHECK(true, Scalar, scalar, CFunction<int, int> *);
	IS_TRAITS_CHECK(true, Scalar, scalar, MemberPointer<Class, int>);
	IS_TRAITS_CHECK(true, Scalar, scalar, MemberPointer<Class, CFunction<void>>);
	IS_TRAITS_CHECK(true, Scalar, scalar, MemberPointer<Class, CFunction<int>>);
	IS_TRAITS_CHECK(true, Scalar, scalar, MemberPointer<Class, CFunction<int, int>>);

	IS_TRAITS_CHECK(false, Scalar, scalar, void);
	IS_TRAITS_CHECK(false, Scalar, scalar, int &);
	IS_TRAITS_CHECK(false, Scalar, scalar, int &&);
	IS_TRAITS_CHECK(false, Scalar, scalar, int[]);
	IS_TRAITS_CHECK(false, Scalar, scalar, int[2]);
	IS_TRAITS_CHECK_CV(false, Scalar, scalar, Class);
	IS_TRAITS_CHECK_CV(false, Scalar, scalar, Struct);
	IS_TRAITS_CHECK_CV(false, Scalar, scalar, Union);
}