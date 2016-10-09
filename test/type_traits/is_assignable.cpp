#include "test.hpp"

#include<libbr/type_traits/is_assignable.hpp>

using namespace BR;

namespace {

struct DeletedConstructor {
	DeletedConstructor() = delete;
};

struct DeletedCopyAssign {
	auto operator=(DeletedCopyAssign const &) -> DeletedCopyAssign & = delete;
	auto operator=(DeletedCopyAssign &&) -> DeletedCopyAssign & = default;
};

struct AnyAssign {
	template< typename T >
	void operator=(T &&) {}
};

struct DeletedAnyAssign {
	template< typename T >
	void operator=(T &&) = delete;
};

template< typename TTo >
struct ImplicitTo {
	operator TTo();
};

template< typename TTo >
struct ExplicitTo {
	explicit operator TTo();
};

template< typename TTo >
struct DeleteImplicitTo {
	operator TTo() = delete;
};

template< typename TTo >
struct DeleteExplicitTo {
	explicit operator TTo() = delete;
};

union NonTrivialUnion {
	int i;
	struct NonTrivial {
		NonTrivial();
		NonTrivial(NonTrivial const &);
		auto operator=(NonTrivial const &) -> NonTrivial &;
		~NonTrivial();
	} n;
};

} // namespace [anonymous]

TEST(TypeTraits, IsAssignable) {
	IS_TRAITS_CHECK(false, Assignable, assignable, int, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, int, int &);
	IS_TRAITS_CHECK(false, Assignable, assignable, int, int const);
	IS_TRAITS_CHECK(false, Assignable, assignable, int, int const &);

	IS_TRAITS_CHECK(true, Assignable, assignable, int &, int);
	IS_TRAITS_CHECK(true, Assignable, assignable, int &, int &);
	IS_TRAITS_CHECK(true, Assignable, assignable, int &, int const);
	IS_TRAITS_CHECK(true, Assignable, assignable, int &, int const &);

	IS_TRAITS_CHECK(false, Assignable, assignable, int const, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const, int &);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const, int const);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const, int const &);

	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, int &);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, int const);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, int const &);

	IS_TRAITS_CHECK(false, Assignable, assignable, bool, bool);
	IS_TRAITS_CHECK(false, Assignable, assignable, bool, bool &);
	IS_TRAITS_CHECK(false, Assignable, assignable, bool, bool const);
	IS_TRAITS_CHECK(false, Assignable, assignable, bool, bool const &);

	IS_TRAITS_CHECK(true, Assignable, assignable, bool &, bool);
	IS_TRAITS_CHECK(true, Assignable, assignable, bool &, bool &);
	IS_TRAITS_CHECK(true, Assignable, assignable, bool &, bool const);
	IS_TRAITS_CHECK(true, Assignable, assignable, bool &, bool const &);

	IS_TRAITS_CHECK(false, Assignable, assignable, NullPointer, NullPointer);
	IS_TRAITS_CHECK(false, Assignable, assignable, NullPointer, NullPointer &);
	IS_TRAITS_CHECK(false, Assignable, assignable, NullPointer, NullPointer const);
	IS_TRAITS_CHECK(false, Assignable, assignable, NullPointer, NullPointer const &);

	IS_TRAITS_CHECK(true, Assignable, assignable, NullPointer &, NullPointer);
	IS_TRAITS_CHECK(true, Assignable, assignable, NullPointer &, NullPointer &);
	IS_TRAITS_CHECK(true, Assignable, assignable, NullPointer &, NullPointer const);
	IS_TRAITS_CHECK(true, Assignable, assignable, NullPointer &, NullPointer const &);

	IS_TRAITS_CHECK(false, Assignable, assignable, void, void);
	IS_TRAITS_CHECK(false, Assignable, assignable, void, void const);
	IS_TRAITS_CHECK(false, Assignable, assignable, void, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, void const, void);
	IS_TRAITS_CHECK(false, Assignable, assignable, void const, void const);
	IS_TRAITS_CHECK(false, Assignable, assignable, void const, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, int, void);
	IS_TRAITS_CHECK(false, Assignable, assignable, int, void const);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, void);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, void const);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const, void);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const, void const);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, void);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, void const);

	IS_TRAITS_CHECK(false, Assignable, assignable, int[], int[]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int[], int[1]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int[], void);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[], int[]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[], int(&)[]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[], int[1]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[], int(&)[1]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[], void);
	IS_TRAITS_CHECK(false, Assignable, assignable, void, int[]);
	IS_TRAITS_CHECK(false, Assignable, assignable, void, int(&)[]);

	IS_TRAITS_CHECK(false, Assignable, assignable, int[2], int[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int[2], int[1]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int[2], void);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[2], int[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[2], int(&)[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[2], int[1]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[2], int(&)[1]);
	IS_TRAITS_CHECK(false, Assignable, assignable, int(&)[2], void);
	IS_TRAITS_CHECK(false, Assignable, assignable, void, int[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, void, int(&)[2]);

	IS_TRAITS_CHECK(false, Assignable, assignable, void, void());
	IS_TRAITS_CHECK(false, Assignable, assignable, void, void(&)());
	IS_TRAITS_CHECK(false, Assignable, assignable, void(), void);
	IS_TRAITS_CHECK(false, Assignable, assignable, void(), void());
	IS_TRAITS_CHECK(false, Assignable, assignable, void(), void(&)());
	IS_TRAITS_CHECK(false, Assignable, assignable, void(&)(), void);
	IS_TRAITS_CHECK(false, Assignable, assignable, void(&)(), void());
	IS_TRAITS_CHECK(false, Assignable, assignable, void(&)(), void(&)());

	IS_TRAITS_CHECK(false, Assignable, assignable, Enum, Enum);
	IS_TRAITS_CHECK(false, Assignable, assignable, Enum, Enum &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Enum, Enum const);
	IS_TRAITS_CHECK(false, Assignable, assignable, Enum, Enum const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Enum &, Enum);
	IS_TRAITS_CHECK(true , Assignable, assignable, Enum &, Enum &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Enum &, Enum const);
	IS_TRAITS_CHECK(true , Assignable, assignable, Enum &, Enum const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Enum &, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, Enum &, int &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Enum &, int const);
	IS_TRAITS_CHECK(false, Assignable, assignable, Enum &, int const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, int &, Enum);
	IS_TRAITS_CHECK(true , Assignable, assignable, int &, Enum &);
	IS_TRAITS_CHECK(true , Assignable, assignable, int &, Enum const);
	IS_TRAITS_CHECK(true , Assignable, assignable, int &, Enum const &);

	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass, EnumClass);
	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass, EnumClass &);
	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass, EnumClass const);
	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass, EnumClass const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, EnumClass &, EnumClass);
	IS_TRAITS_CHECK(true , Assignable, assignable, EnumClass &, EnumClass &);
	IS_TRAITS_CHECK(true , Assignable, assignable, EnumClass &, EnumClass const);
	IS_TRAITS_CHECK(true , Assignable, assignable, EnumClass &, EnumClass const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass &, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass &, int &);
	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass &, int const);
	IS_TRAITS_CHECK(false, Assignable, assignable, EnumClass &, int const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, EnumClass);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, EnumClass &);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, EnumClass const);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, EnumClass const &);

	IS_TRAITS_CHECK(true, Assignable, assignable, Empty &, Empty);
	IS_TRAITS_CHECK(true, Assignable, assignable, Empty &, Empty &);
	IS_TRAITS_CHECK(true, Assignable, assignable, Empty &, Empty const);
	IS_TRAITS_CHECK(true, Assignable, assignable, Empty &, Empty const &);
	IS_TRAITS_CHECK(true, Assignable, assignable, Empty, Empty);
	IS_TRAITS_CHECK(true, Assignable, assignable, Empty, Empty &);
	IS_TRAITS_CHECK(true, Assignable, assignable, Empty, Empty const);
	IS_TRAITS_CHECK(true, Assignable, assignable, Empty, Empty const &);

	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Base);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Base &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Base const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Base &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Derived);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Derived &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Derived const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base &, Derived &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Base);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Base &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Base const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Base &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Derived);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Derived &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Derived const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base const &, Derived &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived &, Base);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived &, Base &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived &, Base const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived &, Base &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, Derived &, Derived);
	IS_TRAITS_CHECK(true , Assignable, assignable, Derived &, Derived &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Derived &, Derived const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Derived &, Derived &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Base);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Base &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Base const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Base &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Derived);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Derived &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Derived const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived const &, Derived &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base * &, Base *);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base * &, Base * &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base * &, Derived *);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base * &, Derived * &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Base *);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Base * &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Base const *);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Base const * &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Derived *);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Derived * &);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Derived const *);
	IS_TRAITS_CHECK(true , Assignable, assignable, Base const * &, Derived const * &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base * const &, Base * &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Base * const &, Derived * &);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived * &, Base *);
	IS_TRAITS_CHECK(false, Assignable, assignable, Derived * &, Base * &);

	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &, DeletedConstructor);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &, DeletedConstructor &);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &, DeletedConstructor &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &, DeletedConstructor const);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &, DeletedConstructor const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &, DeletedConstructor const &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &&, DeletedConstructor);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &&, DeletedConstructor &);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &&, DeletedConstructor &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &&, DeletedConstructor const);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &&, DeletedConstructor const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedConstructor &&, DeletedConstructor const &&);

	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedCopyAssign &, DeletedCopyAssign);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedCopyAssign &, DeletedCopyAssign &);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedCopyAssign &, DeletedCopyAssign &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedCopyAssign &, DeletedCopyAssign const);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedCopyAssign &, DeletedCopyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedCopyAssign &, void);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedCopyAssign &, void());
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedCopyAssign &, void(&)());
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedCopyAssign &, int);

	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, int);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, int &);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, int *);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, int [2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, int (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, NullPointer);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, NullPointer &);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, NullPointer *);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, NullPointer [2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, NullPointer (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Enum);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Enum &);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Enum *);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Enum [2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Enum (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, EnumClass);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, EnumClass &);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, EnumClass *);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, EnumClass [2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, EnumClass (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Union);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Union &);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Union *);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Union [2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Union (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Empty);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Empty &);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Empty *);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Empty [2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, Empty (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, AnyAssign);
	IS_TRAITS_CHECK(true, Assignable, assignable, AnyAssign &, AnyAssign &);

	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedAnyAssign, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedAnyAssign, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedAnyAssign &, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(true , Assignable, assignable, DeletedAnyAssign &, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign const, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign const, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign const &, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign const &, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, int);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, int &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, int *);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, int [2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, int (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, NullPointer);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, NullPointer &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, NullPointer *);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, NullPointer [2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, NullPointer (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Enum);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Enum &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Enum *);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Enum [2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Enum (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, EnumClass);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, EnumClass &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, EnumClass *);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, EnumClass [2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, EnumClass (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Empty);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Empty &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Empty *);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Empty [2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Empty (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Union);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Union &);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Union *);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Union [2]);
	IS_TRAITS_CHECK(false, Assignable, assignable, DeletedAnyAssign &, Union (&)[2]);

	IS_TRAITS_CHECK(false, Assignable, assignable, int, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int, ExplicitTo<int>);
	IS_TRAITS_CHECK(true , Assignable, assignable, int &, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, ExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const, ExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, ExplicitTo<int>);
	IS_TRAITS_CHECK(true , Assignable, assignable, void(*&)(), ImplicitTo<void(*)()>);
	IS_TRAITS_CHECK(false, Assignable, assignable, void(*&)(), ExplicitTo<void(*)()>);

	IS_TRAITS_CHECK(false, Assignable, assignable, int, DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int, DeleteExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int &, DeleteExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const , DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const , DeleteExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, assignable, int const &, DeleteExplicitTo<int>);

	IS_TRAITS_CHECK(false, Assignable, assignable, NonTrivialUnion &, NonTrivialUnion);
	IS_TRAITS_CHECK(false, Assignable, assignable, NonTrivialUnion &, NonTrivialUnion &);
	IS_TRAITS_CHECK(false, Assignable, assignable, NonTrivialUnion &, NonTrivialUnion &&);
	IS_TRAITS_CHECK(false, Assignable, assignable, NonTrivialUnion &, NonTrivialUnion const &);
	IS_TRAITS_CHECK(false, Assignable, assignable, NonTrivialUnion &, NonTrivialUnion const &&);

	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &, Abstract);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &, Abstract &);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &, Abstract &&);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &, Abstract const &);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &, Abstract const &&);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &&, Abstract);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &&, Abstract &);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &&, Abstract &&);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &&, Abstract const &);
	IS_TRAITS_CHECK(true, Assignable, assignable, Abstract &&, Abstract const &&);
}