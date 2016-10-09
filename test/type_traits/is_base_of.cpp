#include "test.hpp"

#include<libbr/type_traits/is_base_of.hpp>

using namespace BR;

namespace {

class MultiDerived : public Class, public Derived {};

class ProtectedInherit : protected Base {};

class PrivateInherit : private Base {};

class VirtualInherit : public virtual Base {};

class AbstractBase {
public:
	virtual void f() = 0;
};

class AbstractDerived : public AbstractBase {
public:
	virtual void g() = 0;
};

class NonDerived {};

} // namespace [anonymous]

TEST(TypeTraits, IsBaseOf) {
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, Base);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Derived, Derived);
	IS_TRAITS_CHECK(false, BaseOf, base_of, void, void);
	IS_TRAITS_CHECK(false, BaseOf, base_of, int, int);
	IS_TRAITS_CHECK(false, BaseOf, base_of, Union, Union);
	IS_TRAITS_CHECK(false, BaseOf, base_of, Enum, Enum);
	IS_TRAITS_CHECK(false, BaseOf, base_of, EnumClass, EnumClass);

	IS_TRAITS_CHECK(false, BaseOf, base_of, Base, void);
	IS_TRAITS_CHECK(false, BaseOf, base_of, Base, void const);
	IS_TRAITS_CHECK(false, BaseOf, base_of, void, Derived);
	IS_TRAITS_CHECK(false, BaseOf, base_of, void const, Derived);

	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, Derived);
	IS_TRAITS_CHECK(false, BaseOf, base_of, Derived, Base);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, Derived const);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, Derived volatile);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, Derived const volatile);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base const, Derived);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base volatile, Derived);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base const volatile, Derived);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Derived, Derived const);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Derived, Derived volatile);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Derived, Derived const volatile);

	IS_TRAITS_CHECK(true , BaseOf, base_of, Class, MultiDerived);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, MultiDerived);
	IS_TRAITS_CHECK(true , BaseOf, base_of, Derived, MultiDerived);

	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, ProtectedInherit);
	IS_TRAITS_CHECK(false, BaseOf, base_of, ProtectedInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, PrivateInherit);
	IS_TRAITS_CHECK(false, BaseOf, base_of, PrivateInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, FinalInherit);
	IS_TRAITS_CHECK(false, BaseOf, base_of, FinalInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, base_of, Base, VirtualInherit);
	IS_TRAITS_CHECK(false, BaseOf, base_of, VirtualInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, base_of, Polymorphic, PolymorphicDerived);
	IS_TRAITS_CHECK(false, BaseOf, base_of, PolymorphicDerived, Polymorphic);

	IS_TRAITS_CHECK(false, BaseOf, base_of, Base, NonDerived);
	IS_TRAITS_CHECK(false, BaseOf, base_of, NonDerived, Base);
}