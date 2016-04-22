#include "test.hpp"

#include<libbr/type_traits/is_empty.hpp>

using namespace BR;

namespace {

class Empty0 {
	using Type = int;
};

class Empty1 {
	static int data;
};

class Empty2 {
	int f();
};

class NonEmpty0 {
	int data;
};

class NonEmpty1 {
	virtual int f();
	virtual ~NonEmpty1();
};

} // namespace [anonymous]

TEST(TypeTraits, IsEmpty) {
	IS_TRAITS_CHECK_CV(true, Empty, Empty);
	IS_TRAITS_CHECK_CV(true, Empty, Empty0);
	IS_TRAITS_CHECK_CV(true, Empty, Empty1);
	IS_TRAITS_CHECK_CV(true, Empty, Empty2);

	IS_TRAITS_CHECK_CV(false, Empty, void);
	IS_TRAITS_CHECK_CV(false, Empty, int);
	IS_TRAITS_CHECK_CV(false, Empty, int *);
	IS_TRAITS_CHECK(false, Empty, int &);
	IS_TRAITS_CHECK(false, Empty, int &&);
	IS_TRAITS_CHECK(false, Empty, int []);
	IS_TRAITS_CHECK(false, Empty, int [2]);
	IS_TRAITS_CHECK(false, Empty, int(int));
	IS_TRAITS_CHECK_CV(false, Empty, Enum);
	IS_TRAITS_CHECK_CV(false, Empty, EnumClass);
	IS_TRAITS_CHECK_CV(false, Empty, Union);
	IS_TRAITS_CHECK_CV(false, Empty, Abstract);
	IS_TRAITS_CHECK_CV(false, Empty, Polymorphic);
	IS_TRAITS_CHECK_CV(false, Empty, NonEmpty0);
	IS_TRAITS_CHECK_CV(false, Empty, NonEmpty1);
}