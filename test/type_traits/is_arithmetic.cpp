#include "test.hpp"

#include<libbr/type_traits/is_arithmetic.hpp>

using namespace BR;

TEST(TypeTraits, IsArithmetic) {
	IS_TRAITS_CHECK_CV(true, Arithmetic, bool);
	IS_TRAITS_CHECK_CV(true, Arithmetic,   signed char);
	IS_TRAITS_CHECK_CV(true, Arithmetic, unsigned char);
	IS_TRAITS_CHECK_CV(true, Arithmetic,   signed short);
	IS_TRAITS_CHECK_CV(true, Arithmetic, unsigned short);
	IS_TRAITS_CHECK_CV(true, Arithmetic,   signed int);
	IS_TRAITS_CHECK_CV(true, Arithmetic, unsigned int);
	IS_TRAITS_CHECK_CV(true, Arithmetic,   signed long);
	IS_TRAITS_CHECK_CV(true, Arithmetic, unsigned long);
	IS_TRAITS_CHECK_CV(true, Arithmetic,   signed long long);
	IS_TRAITS_CHECK_CV(true, Arithmetic, unsigned long long);

#if defined(BR_HAS_INT128)
	IS_TRAITS_CHECK_CV(true, Arithmetic, SInt128);
	IS_TRAITS_CHECK_CV(true, Arithmetic, UInt128);
#endif
	IS_TRAITS_CHECK_CV(true, Arithmetic, float);
	IS_TRAITS_CHECK_CV(true, Arithmetic, double);
	IS_TRAITS_CHECK_CV(true, Arithmetic, long double);

	IS_TRAITS_CHECK_CV(true, Arithmetic, char);
	IS_TRAITS_CHECK_CV(true, Arithmetic, wchar_t);
	IS_TRAITS_CHECK_CV(true, Arithmetic, char16_t);
	IS_TRAITS_CHECK_CV(true, Arithmetic, char32_t);

	IS_TRAITS_CHECK_CV(false, Arithmetic, void);

	IS_TRAITS_CHECK(false, Arithmetic, int *);
	IS_TRAITS_CHECK(false, Arithmetic, int const *);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile *);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile *);

	IS_TRAITS_CHECK(false, Arithmetic, int &);
	IS_TRAITS_CHECK(false, Arithmetic, int const &);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile &);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile &);

	IS_TRAITS_CHECK(false, Arithmetic, int &&);
	IS_TRAITS_CHECK(false, Arithmetic, int const &&);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile &&);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile &&);

	IS_TRAITS_CHECK(false, Arithmetic, int []);
	IS_TRAITS_CHECK(false, Arithmetic, int const []);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile []);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile []);

	IS_TRAITS_CHECK(false, Arithmetic, int [2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const [2]);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile [2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile [2]);
	IS_TRAITS_CHECK(false, Arithmetic, int (*)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int const (*)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile (*)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile (*)[]);

	IS_TRAITS_CHECK(false, Arithmetic, int (*)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const (*)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile (*)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile (*)[2]);

	IS_TRAITS_CHECK(false, Arithmetic, int (&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int const (&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile (&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile (&)[]);

	IS_TRAITS_CHECK(false, Arithmetic, int (&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const (&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile (&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile (&)[2]);

	IS_TRAITS_CHECK(false, Arithmetic, int (&&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int const (&&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile (&&)[]);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile (&&)[]);

	IS_TRAITS_CHECK(false, Arithmetic, int (&&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const (&&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int volatile (&&)[2]);
	IS_TRAITS_CHECK(false, Arithmetic, int const volatile (&&)[2]);

	IS_TRAITS_CHECK(false, Arithmetic, int(int));
	IS_TRAITS_CHECK(false, Arithmetic, int(*)(int));
	IS_TRAITS_CHECK(false, Arithmetic, int(&)(int));
	IS_TRAITS_CHECK(false, Arithmetic, int(&&)(int));

	IS_TRAITS_CHECK_CV(false, Arithmetic, Class);
	IS_TRAITS_CHECK_CV(false, Arithmetic, Union);
	IS_TRAITS_CHECK_CV(false, Arithmetic, Enum);
	IS_TRAITS_CHECK_CV(false, Arithmetic, EnumClass);
}