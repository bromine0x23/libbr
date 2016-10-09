#include "test.hpp"

#include<libbr/type_traits/has_destructor.hpp>

using namespace BR;

TEST(TypeTraits, HasDestructor) {
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, bool);
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, int);
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, void *);
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, int *);
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, Enum);
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, EnumClass);
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, Union);
	HAS_TRAITS_CHECK_CV(true, Destructor, destructor, Class);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int &);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int &&);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int [2]);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int [2][3]);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int(&)[2]);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int(&&)[2]);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int(*)(int));
	HAS_TRAITS_CHECK(true, Destructor, destructor, int(&)(int));
	HAS_TRAITS_CHECK(true, Destructor, destructor, int(&&)(int));
	HAS_TRAITS_CHECK(true, Destructor, destructor, int Class::*);
	HAS_TRAITS_CHECK(true, Destructor, destructor, int(Class::*)(int));

	HAS_TRAITS_CHECK_CV(false, Destructor, destructor, void);
	HAS_TRAITS_CHECK_CV(false, Destructor, destructor, DeleteDestructor);
	HAS_TRAITS_CHECK_CV(false, Destructor, destructor, AbstractDeleteDestructor);
	HAS_TRAITS_CHECK(false, Destructor, destructor, void());
	HAS_TRAITS_CHECK(false, Destructor, destructor, int []);
	HAS_TRAITS_CHECK(false, Destructor, destructor, int const []);
	HAS_TRAITS_CHECK(false, Destructor, destructor, int volatile []);
	HAS_TRAITS_CHECK(false, Destructor, destructor, int const volatile []);
	HAS_TRAITS_CHECK(false, Destructor, destructor, DeleteDestructor []);
	HAS_TRAITS_CHECK(false, Destructor, destructor, DeleteDestructor [2]);
}