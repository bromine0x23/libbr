#include "test.hpp"

#include <libbr/type_traits/is_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsPointer) {
	IS_TRAITS_CHECK_CV(true, Pointer, pointer, void *);
	IS_TRAITS_CHECK_CV(true, Pointer, pointer, int *);
	IS_TRAITS_CHECK_CV(true, Pointer, pointer, Class *);
	IS_TRAITS_CHECK_CV(true, Pointer, pointer, Struct *);
	IS_TRAITS_CHECK_CV(true, Pointer, pointer, Union *);
	IS_TRAITS_CHECK_CV(true, Pointer, pointer, Enum *);
	IS_TRAITS_CHECK_CV(true, Pointer, pointer, EnumClass *);
	IS_TRAITS_CHECK(true, Pointer, pointer, CArrayUnbound<int> *);
	IS_TRAITS_CHECK(true, Pointer, pointer, CArray<int, 2> *);
	IS_TRAITS_CHECK(true, Pointer, pointer, CFunction<int, int> *);

	IS_TRAITS_CHECK(false, Pointer, pointer, void);
	IS_TRAITS_CHECK(false, Pointer, pointer, int);
	IS_TRAITS_CHECK(false, Pointer, pointer, int &);
	IS_TRAITS_CHECK(false, Pointer, pointer, int &&);
	IS_TRAITS_CHECK(false, Pointer, pointer, CArrayUnbound<int>);
	IS_TRAITS_CHECK(false, Pointer, pointer, CArray<int, 2>);
	IS_TRAITS_CHECK(false, Pointer, pointer, CFunction<int, int>);
	IS_TRAITS_CHECK(false, Pointer, pointer, MemberPointer<Class, int>);
	IS_TRAITS_CHECK(false, Pointer, pointer, MemberPointer<Class, CFunction<void> >);
}