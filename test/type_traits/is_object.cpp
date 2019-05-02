#include "test.hpp"

#include <libbr/type_traits/is_object.hpp>

using namespace BR;

TEST(TypeTraits, IsObject) {
	IS_TRAITS_CHECK_CV(true, Object, object, int);
	IS_TRAITS_CHECK_CV(true, Object, object, int *);
	IS_TRAITS_CHECK_CV(true, Object, object, double);
	IS_TRAITS_CHECK_CV(true, Object, object, Class);
	IS_TRAITS_CHECK_CV(true, Object, object, Struct);
	IS_TRAITS_CHECK_CV(true, Object, object, Abstract);
	IS_TRAITS_CHECK_CV(true, Object, object, Polymorphic);
	IS_TRAITS_CHECK(true, Object, object, int []);
	IS_TRAITS_CHECK(true, Object, object, int [2]);

	IS_TRAITS_CHECK(false, Object, object, void);
	IS_TRAITS_CHECK(false, Object, object, int &);
	IS_TRAITS_CHECK(false, Object, object, int &&);
	IS_TRAITS_CHECK(false, Object, object, auto () -> void);
	IS_TRAITS_CHECK(false, Object, object, auto () -> int);
	IS_TRAITS_CHECK(false, Object, object, auto (int) -> int);
	IS_TRAITS_CHECK(false, Object, object, auto (...) -> int);
}