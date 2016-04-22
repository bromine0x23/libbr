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
	IS_TRAITS_CHECK(false, Assignable, int, int);
	IS_TRAITS_CHECK(false, Assignable, int, int &);
	IS_TRAITS_CHECK(false, Assignable, int, int const);
	IS_TRAITS_CHECK(false, Assignable, int, int const &);

	IS_TRAITS_CHECK(true, Assignable, int &, int);
	IS_TRAITS_CHECK(true, Assignable, int &, int &);
	IS_TRAITS_CHECK(true, Assignable, int &, int const);
	IS_TRAITS_CHECK(true, Assignable, int &, int const &);

	IS_TRAITS_CHECK(false, Assignable, int const, int);
	IS_TRAITS_CHECK(false, Assignable, int const, int &);
	IS_TRAITS_CHECK(false, Assignable, int const, int const);
	IS_TRAITS_CHECK(false, Assignable, int const, int const &);

	IS_TRAITS_CHECK(false, Assignable, int const &, int);
	IS_TRAITS_CHECK(false, Assignable, int const &, int &);
	IS_TRAITS_CHECK(false, Assignable, int const &, int const);
	IS_TRAITS_CHECK(false, Assignable, int const &, int const &);

	IS_TRAITS_CHECK(false, Assignable, bool, bool);
	IS_TRAITS_CHECK(false, Assignable, bool, bool &);
	IS_TRAITS_CHECK(false, Assignable, bool, bool const);
	IS_TRAITS_CHECK(false, Assignable, bool, bool const &);

	IS_TRAITS_CHECK(true, Assignable, bool &, bool);
	IS_TRAITS_CHECK(true, Assignable, bool &, bool &);
	IS_TRAITS_CHECK(true, Assignable, bool &, bool const);
	IS_TRAITS_CHECK(true, Assignable, bool &, bool const &);

	IS_TRAITS_CHECK(false, Assignable, NullPointer, NullPointer);
	IS_TRAITS_CHECK(false, Assignable, NullPointer, NullPointer &);
	IS_TRAITS_CHECK(false, Assignable, NullPointer, NullPointer const);
	IS_TRAITS_CHECK(false, Assignable, NullPointer, NullPointer const &);

	IS_TRAITS_CHECK(true, Assignable, NullPointer &, NullPointer);
	IS_TRAITS_CHECK(true, Assignable, NullPointer &, NullPointer &);
	IS_TRAITS_CHECK(true, Assignable, NullPointer &, NullPointer const);
	IS_TRAITS_CHECK(true, Assignable, NullPointer &, NullPointer const &);

	IS_TRAITS_CHECK(false, Assignable, void, void);
	IS_TRAITS_CHECK(false, Assignable, void, void const);
	IS_TRAITS_CHECK(false, Assignable, void, int);
	IS_TRAITS_CHECK(false, Assignable, void const, void);
	IS_TRAITS_CHECK(false, Assignable, void const, void const);
	IS_TRAITS_CHECK(false, Assignable, void const, int);
	IS_TRAITS_CHECK(false, Assignable, int, void);
	IS_TRAITS_CHECK(false, Assignable, int, void const);
	IS_TRAITS_CHECK(false, Assignable, int &, void);
	IS_TRAITS_CHECK(false, Assignable, int &, void const);
	IS_TRAITS_CHECK(false, Assignable, int const, void);
	IS_TRAITS_CHECK(false, Assignable, int const, void const);
	IS_TRAITS_CHECK(false, Assignable, int const &, void);
	IS_TRAITS_CHECK(false, Assignable, int const &, void const);

	IS_TRAITS_CHECK(false, Assignable, int[], int[]);
	IS_TRAITS_CHECK(false, Assignable, int[], int[1]);
	IS_TRAITS_CHECK(false, Assignable, int[], void);
	IS_TRAITS_CHECK(false, Assignable, int(&)[], int[]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[], int(&)[]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[], int[1]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[], int(&)[1]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[], void);
	IS_TRAITS_CHECK(false, Assignable, void, int[]);
	IS_TRAITS_CHECK(false, Assignable, void, int(&)[]);

	IS_TRAITS_CHECK(false, Assignable, int[2], int[2]);
	IS_TRAITS_CHECK(false, Assignable, int[2], int[1]);
	IS_TRAITS_CHECK(false, Assignable, int[2], void);
	IS_TRAITS_CHECK(false, Assignable, int(&)[2], int[2]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[2], int(&)[2]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[2], int[1]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[2], int(&)[1]);
	IS_TRAITS_CHECK(false, Assignable, int(&)[2], void);
	IS_TRAITS_CHECK(false, Assignable, void, int[2]);
	IS_TRAITS_CHECK(false, Assignable, void, int(&)[2]);

	IS_TRAITS_CHECK(false, Assignable, void, void());
	IS_TRAITS_CHECK(false, Assignable, void, void(&)());
	IS_TRAITS_CHECK(false, Assignable, void(), void);
	IS_TRAITS_CHECK(false, Assignable, void(), void());
	IS_TRAITS_CHECK(false, Assignable, void(), void(&)());
	IS_TRAITS_CHECK(false, Assignable, void(&)(), void);
	IS_TRAITS_CHECK(false, Assignable, void(&)(), void());
	IS_TRAITS_CHECK(false, Assignable, void(&)(), void(&)());

	IS_TRAITS_CHECK(false, Assignable, Enum, Enum);
	IS_TRAITS_CHECK(false, Assignable, Enum, Enum &);
	IS_TRAITS_CHECK(false, Assignable, Enum, Enum const);
	IS_TRAITS_CHECK(false, Assignable, Enum, Enum const &);
	IS_TRAITS_CHECK(true , Assignable, Enum &, Enum);
	IS_TRAITS_CHECK(true , Assignable, Enum &, Enum &);
	IS_TRAITS_CHECK(true , Assignable, Enum &, Enum const);
	IS_TRAITS_CHECK(true , Assignable, Enum &, Enum const &);
	IS_TRAITS_CHECK(false, Assignable, Enum &, int);
	IS_TRAITS_CHECK(false, Assignable, Enum &, int &);
	IS_TRAITS_CHECK(false, Assignable, Enum &, int const);
	IS_TRAITS_CHECK(false, Assignable, Enum &, int const &);
	IS_TRAITS_CHECK(true , Assignable, int &, Enum);
	IS_TRAITS_CHECK(true , Assignable, int &, Enum &);
	IS_TRAITS_CHECK(true , Assignable, int &, Enum const);
	IS_TRAITS_CHECK(true , Assignable, int &, Enum const &);

	IS_TRAITS_CHECK(false, Assignable, EnumClass, EnumClass);
	IS_TRAITS_CHECK(false, Assignable, EnumClass, EnumClass &);
	IS_TRAITS_CHECK(false, Assignable, EnumClass, EnumClass const);
	IS_TRAITS_CHECK(false, Assignable, EnumClass, EnumClass const &);
	IS_TRAITS_CHECK(true , Assignable, EnumClass &, EnumClass);
	IS_TRAITS_CHECK(true , Assignable, EnumClass &, EnumClass &);
	IS_TRAITS_CHECK(true , Assignable, EnumClass &, EnumClass const);
	IS_TRAITS_CHECK(true , Assignable, EnumClass &, EnumClass const &);
	IS_TRAITS_CHECK(false, Assignable, EnumClass &, int);
	IS_TRAITS_CHECK(false, Assignable, EnumClass &, int &);
	IS_TRAITS_CHECK(false, Assignable, EnumClass &, int const);
	IS_TRAITS_CHECK(false, Assignable, EnumClass &, int const &);
	IS_TRAITS_CHECK(false, Assignable, int &, EnumClass);
	IS_TRAITS_CHECK(false, Assignable, int &, EnumClass &);
	IS_TRAITS_CHECK(false, Assignable, int &, EnumClass const);
	IS_TRAITS_CHECK(false, Assignable, int &, EnumClass const &);

	IS_TRAITS_CHECK(true, Assignable, Empty &, Empty);
	IS_TRAITS_CHECK(true, Assignable, Empty &, Empty &);
	IS_TRAITS_CHECK(true, Assignable, Empty &, Empty const);
	IS_TRAITS_CHECK(true, Assignable, Empty &, Empty const &);
	IS_TRAITS_CHECK(true, Assignable, Empty, Empty);
	IS_TRAITS_CHECK(true, Assignable, Empty, Empty &);
	IS_TRAITS_CHECK(true, Assignable, Empty, Empty const);
	IS_TRAITS_CHECK(true, Assignable, Empty, Empty const &);

	IS_TRAITS_CHECK(true , Assignable, Base &, Base);
	IS_TRAITS_CHECK(true , Assignable, Base &, Base &);
	IS_TRAITS_CHECK(true , Assignable, Base &, Base const &);
	IS_TRAITS_CHECK(true , Assignable, Base &, Base &&);
	IS_TRAITS_CHECK(true , Assignable, Base &, Derived);
	IS_TRAITS_CHECK(true , Assignable, Base &, Derived &);
	IS_TRAITS_CHECK(true , Assignable, Base &, Derived const &);
	IS_TRAITS_CHECK(true , Assignable, Base &, Derived &&);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Base);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Base &);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Base const &);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Base &&);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Derived);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Derived &);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Derived const &);
	IS_TRAITS_CHECK(false, Assignable, Base const &, Derived &&);
	IS_TRAITS_CHECK(false, Assignable, Derived &, Base);
	IS_TRAITS_CHECK(false, Assignable, Derived &, Base &);
	IS_TRAITS_CHECK(false, Assignable, Derived &, Base const &);
	IS_TRAITS_CHECK(false, Assignable, Derived &, Base &&);
	IS_TRAITS_CHECK(true , Assignable, Derived &, Derived);
	IS_TRAITS_CHECK(true , Assignable, Derived &, Derived &);
	IS_TRAITS_CHECK(true , Assignable, Derived &, Derived const &);
	IS_TRAITS_CHECK(true , Assignable, Derived &, Derived &&);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Base);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Base &);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Base const &);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Base &&);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Derived);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Derived &);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Derived const &);
	IS_TRAITS_CHECK(false, Assignable, Derived const &, Derived &&);
	IS_TRAITS_CHECK(true , Assignable, Base * &, Base *);
	IS_TRAITS_CHECK(true , Assignable, Base * &, Base * &);
	IS_TRAITS_CHECK(true , Assignable, Base * &, Derived *);
	IS_TRAITS_CHECK(true , Assignable, Base * &, Derived * &);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Base *);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Base * &);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Base const *);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Base const * &);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Derived *);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Derived * &);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Derived const *);
	IS_TRAITS_CHECK(true , Assignable, Base const * &, Derived const * &);
	IS_TRAITS_CHECK(false, Assignable, Base * const &, Base * &);
	IS_TRAITS_CHECK(false, Assignable, Base * const &, Derived * &);
	IS_TRAITS_CHECK(false, Assignable, Derived * &, Base *);
	IS_TRAITS_CHECK(false, Assignable, Derived * &, Base * &);

	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &, DeletedConstructor);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &, DeletedConstructor &);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &, DeletedConstructor &&);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &, DeletedConstructor const);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &, DeletedConstructor const &);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &, DeletedConstructor const &&);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &&, DeletedConstructor);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &&, DeletedConstructor &);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &&, DeletedConstructor &&);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &&, DeletedConstructor const);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &&, DeletedConstructor const &);
	IS_TRAITS_CHECK(true , Assignable, DeletedConstructor &&, DeletedConstructor const &&);

	IS_TRAITS_CHECK(true , Assignable, DeletedCopyAssign &, DeletedCopyAssign);
	IS_TRAITS_CHECK(false, Assignable, DeletedCopyAssign &, DeletedCopyAssign &);
	IS_TRAITS_CHECK(true , Assignable, DeletedCopyAssign &, DeletedCopyAssign &&);
	IS_TRAITS_CHECK(false, Assignable, DeletedCopyAssign &, DeletedCopyAssign const);
	IS_TRAITS_CHECK(false, Assignable, DeletedCopyAssign &, DeletedCopyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, DeletedCopyAssign &, void);
	IS_TRAITS_CHECK(false, Assignable, DeletedCopyAssign &, void());
	IS_TRAITS_CHECK(false, Assignable, DeletedCopyAssign &, void(&)());
	IS_TRAITS_CHECK(false, Assignable, DeletedCopyAssign &, int);

	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, int);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, int &);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, int *);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, int [2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, int (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, NullPointer);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, NullPointer &);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, NullPointer *);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, NullPointer [2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, NullPointer (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Enum);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Enum &);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Enum *);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Enum [2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Enum (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, EnumClass);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, EnumClass &);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, EnumClass *);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, EnumClass [2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, EnumClass (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Union);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Union &);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Union *);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Union [2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Union (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Empty);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Empty &);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Empty *);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Empty [2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, Empty (&)[2]);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, AnyAssign);
	IS_TRAITS_CHECK(true, Assignable, AnyAssign &, AnyAssign &);

	IS_TRAITS_CHECK(true , Assignable, DeletedAnyAssign, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(true , Assignable, DeletedAnyAssign, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(true , Assignable, DeletedAnyAssign &, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(true , Assignable, DeletedAnyAssign &, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign const, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign const, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign const &, DeletedAnyAssign &&);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign const &, DeletedAnyAssign const &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, int);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, int &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, int *);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, int [2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, int (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, NullPointer);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, NullPointer &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, NullPointer *);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, NullPointer [2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, NullPointer (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Enum);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Enum &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Enum *);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Enum [2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Enum (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, EnumClass);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, EnumClass &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, EnumClass *);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, EnumClass [2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, EnumClass (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Empty);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Empty &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Empty *);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Empty [2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Empty (&)[2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Union);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Union &);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Union *);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Union [2]);
	IS_TRAITS_CHECK(false, Assignable, DeletedAnyAssign &, Union (&)[2]);

	IS_TRAITS_CHECK(false, Assignable, int, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int, ExplicitTo<int>);
	IS_TRAITS_CHECK(true , Assignable, int &, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int &, ExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const, ExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const &, ImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const &, ExplicitTo<int>);
	IS_TRAITS_CHECK(true , Assignable, void(*&)(), ImplicitTo<void(*)()>);
	IS_TRAITS_CHECK(false, Assignable, void(*&)(), ExplicitTo<void(*)()>);

	IS_TRAITS_CHECK(false, Assignable, int, DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int, DeleteExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int &, DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int &, DeleteExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const , DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const , DeleteExplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const &, DeleteImplicitTo<int>);
	IS_TRAITS_CHECK(false, Assignable, int const &, DeleteExplicitTo<int>);

	IS_TRAITS_CHECK(false, Assignable, NonTrivialUnion &, NonTrivialUnion);
	IS_TRAITS_CHECK(false, Assignable, NonTrivialUnion &, NonTrivialUnion &);
	IS_TRAITS_CHECK(false, Assignable, NonTrivialUnion &, NonTrivialUnion &&);
	IS_TRAITS_CHECK(false, Assignable, NonTrivialUnion &, NonTrivialUnion const &);
	IS_TRAITS_CHECK(false, Assignable, NonTrivialUnion &, NonTrivialUnion const &&);

	IS_TRAITS_CHECK(true, Assignable, Abstract &, Abstract);
	IS_TRAITS_CHECK(true, Assignable, Abstract &, Abstract &);
	IS_TRAITS_CHECK(true, Assignable, Abstract &, Abstract &&);
	IS_TRAITS_CHECK(true, Assignable, Abstract &, Abstract const &);
	IS_TRAITS_CHECK(true, Assignable, Abstract &, Abstract const &&);
	IS_TRAITS_CHECK(true, Assignable, Abstract &&, Abstract);
	IS_TRAITS_CHECK(true, Assignable, Abstract &&, Abstract &);
	IS_TRAITS_CHECK(true, Assignable, Abstract &&, Abstract &&);
	IS_TRAITS_CHECK(true, Assignable, Abstract &&, Abstract const &);
	IS_TRAITS_CHECK(true, Assignable, Abstract &&, Abstract const &&);
}