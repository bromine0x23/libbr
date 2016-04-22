#include "test.hpp"

#include<libbr/type_traits/is_base_of.hpp>

using namespace BR;

namespace {

class MultiDerived : public Class, public Derived {};

class ProtectedInherit : protected Base {};

class PrivateInherit : private Base {};

class FinalInherit final : public Base {};

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
	IS_TRAITS_CHECK(true , BaseOf, Base, Base);
	IS_TRAITS_CHECK(true , BaseOf, Derived, Derived);
	IS_TRAITS_CHECK(false, BaseOf, void, void);
	IS_TRAITS_CHECK(false, BaseOf, int, int);
	IS_TRAITS_CHECK(false, BaseOf, Union, Union);
	IS_TRAITS_CHECK(false, BaseOf, Enum, Enum);
	IS_TRAITS_CHECK(false, BaseOf, EnumClass, EnumClass);

	IS_TRAITS_CHECK(false, BaseOf, Base, void);
	IS_TRAITS_CHECK(false, BaseOf, Base, void const);
	IS_TRAITS_CHECK(false, BaseOf, void, Derived);
	IS_TRAITS_CHECK(false, BaseOf, void const, Derived);

	IS_TRAITS_CHECK(true , BaseOf, Base, Derived);
	IS_TRAITS_CHECK(false, BaseOf, Derived, Base);
	IS_TRAITS_CHECK(true , BaseOf, Base, Derived const);
	IS_TRAITS_CHECK(true , BaseOf, Base, Derived volatile);
	IS_TRAITS_CHECK(true , BaseOf, Base, Derived const volatile);
	IS_TRAITS_CHECK(true , BaseOf, Base const, Derived);
	IS_TRAITS_CHECK(true , BaseOf, Base volatile, Derived);
	IS_TRAITS_CHECK(true , BaseOf, Base const volatile, Derived);
	IS_TRAITS_CHECK(true , BaseOf, Derived, Derived const);
	IS_TRAITS_CHECK(true , BaseOf, Derived, Derived volatile);
	IS_TRAITS_CHECK(true , BaseOf, Derived, Derived const volatile);

	IS_TRAITS_CHECK(true , BaseOf, Class, MultiDerived);
	IS_TRAITS_CHECK(true , BaseOf, Base, MultiDerived);
	IS_TRAITS_CHECK(true , BaseOf, Derived, MultiDerived);

	IS_TRAITS_CHECK(true , BaseOf, Base, ProtectedInherit);
	IS_TRAITS_CHECK(false, BaseOf, ProtectedInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, Base, PrivateInherit);
	IS_TRAITS_CHECK(false, BaseOf, PrivateInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, Base, FinalInherit);
	IS_TRAITS_CHECK(false, BaseOf, FinalInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, Base, VirtualInherit);
	IS_TRAITS_CHECK(false, BaseOf, VirtualInherit, Base);

	IS_TRAITS_CHECK(true , BaseOf, Polymorphic, PolymorphicDerived);
	IS_TRAITS_CHECK(false, BaseOf, PolymorphicDerived, Polymorphic);

	IS_TRAITS_CHECK(false, BaseOf, Base, NonDerived);
	IS_TRAITS_CHECK(false, BaseOf, NonDerived, Base);
}