#include "test.hpp"

#include<libbr/type_traits/is_final.hpp>

using namespace BR;

TEST(TypeTraits, IsFinal) {
	IS_TRAITS_CHECK_CV(true, Final, final, FinalInherit);

	IS_TRAITS_CHECK(false, Final, final, void);
	IS_TRAITS_CHECK(false, Final, final, int);
	IS_TRAITS_CHECK(false, Final, final, FinalInherit *);
	IS_TRAITS_CHECK(false, Final, final, FinalInherit &);
	IS_TRAITS_CHECK(false, Final, final, FinalInherit &&);
	IS_TRAITS_CHECK(false, Final, final, FinalInherit []);
	IS_TRAITS_CHECK(false, Final, final, FinalInherit [2]);
	IS_TRAITS_CHECK(false, Final, final, CFunction<int, int>);
	IS_TRAITS_CHECK(false, Final, final, CFunction<int, int> *);
	IS_TRAITS_CHECK(false, Final, final, int Class::*);
	IS_TRAITS_CHECK(false, Final, final, CFunction<int, int> Class::*);
	IS_TRAITS_CHECK(false, Final, final, NullPointer);
	IS_TRAITS_CHECK(false, Final, final, Class);
	IS_TRAITS_CHECK(false, Final, final, Struct);
	IS_TRAITS_CHECK(false, Final, final, Enum);
	IS_TRAITS_CHECK(false, Final, final, EnumClass);
	IS_TRAITS_CHECK(false, Final, final, VirtualInherit);
}