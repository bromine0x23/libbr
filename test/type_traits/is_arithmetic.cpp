#include "test.hpp"

#include<libbr/type_traits/is_arithmetic.hpp>

using namespace BR;

TEST(TypeTraits, IsArithmetic) {
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, bool);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic,   signed char);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, unsigned char);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic,   signed short);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, unsigned short);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic,   signed int);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, unsigned int);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic,   signed long);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, unsigned long);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic,   signed long long);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, unsigned long long);

#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, SInt128);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, UInt128);
#endif
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, float);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, double);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, long double);

	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, char);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, wchar_t);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, char16_t);
	IS_TRAITS_CHECK_CV(true, Arithmetic, arithmetic, char32_t);

	IS_TRAITS_CHECK_CV(false, Arithmetic, arithmetic, NullPointer);

	IS_TRAITS_CHECK_CV(false, Arithmetic, arithmetic, void);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int *);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const *);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile *);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile *);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int &);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const &);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile &);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile &);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int &&);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const &&);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile &&);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile &&);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int []);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const []);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile []);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile []);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int [2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const [2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile [2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile [2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int (*)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const (*)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile (*)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile (*)[]);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int (*)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const (*)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile (*)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile (*)[2]);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int (&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const (&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile (&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile (&)[]);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int (&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const (&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile (&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile (&)[2]);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int (&&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const (&&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile (&&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile (&&)[]);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int (&&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const (&&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int volatile (&&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int const volatile (&&)[2]);

	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int(int));
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int(*)(int));
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int(&)(int));
	IS_TRAITS_CHECK(false, Arithmetic, arithmetic, int(&&)(int));

	IS_TRAITS_CHECK_CV(false, Arithmetic, arithmetic, Class);
	IS_TRAITS_CHECK_CV(false, Arithmetic, arithmetic, Union);
	IS_TRAITS_CHECK_CV(false, Arithmetic, arithmetic, Enum);
	IS_TRAITS_CHECK_CV(false, Arithmetic, arithmetic, EnumClass);
}