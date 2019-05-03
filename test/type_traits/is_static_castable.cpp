#include "test.hpp"

#include <libbr/type_traits/is_static_castable.hpp>

using namespace BR;

TEST(TypeTraits, IsStaticCastable) {
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, void, void);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, int, short);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, short, int);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, double, float);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, float, double);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, int *, void *);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, Class *, void *);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, void *, int *);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, void *, Class *);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, Base &, Derived &);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, Derived[5], Base *);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, Class, Class &&);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, EnumClass, int);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, int, Enum);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, int, EnumClass);
	IS_TRAITS_CHECK(true, StaticCastable, static_castable, auto (Derived::*)(...) -> void, auto (Base::*)(...) -> void);

	IS_TRAITS_CHECK(false, StaticCastable, static_castable, void, int);
	IS_TRAITS_CHECK(false, StaticCastable, static_castable, Class, Struct);
	IS_TRAITS_CHECK(false, StaticCastable, static_castable, Class &, Class *);
}