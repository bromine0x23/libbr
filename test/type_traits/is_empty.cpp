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
	IS_TRAITS_CHECK_CV(true, Empty, empty, Empty);
	IS_TRAITS_CHECK_CV(true, Empty, empty, Empty0);
	IS_TRAITS_CHECK_CV(true, Empty, empty, Empty1);
	IS_TRAITS_CHECK_CV(true, Empty, empty, Empty2);

	IS_TRAITS_CHECK_CV(false, Empty, empty, void);
	IS_TRAITS_CHECK_CV(false, Empty, empty, int);
	IS_TRAITS_CHECK_CV(false, Empty, empty, int *);
	IS_TRAITS_CHECK(false, Empty, empty, int &);
	IS_TRAITS_CHECK(false, Empty, empty, int &&);
	IS_TRAITS_CHECK(false, Empty, empty, int []);
	IS_TRAITS_CHECK(false, Empty, empty, int [2]);
	IS_TRAITS_CHECK(false, Empty, empty, int(int));
	IS_TRAITS_CHECK_CV(false, Empty, empty, Enum);
	IS_TRAITS_CHECK_CV(false, Empty, empty, EnumClass);
	IS_TRAITS_CHECK_CV(false, Empty, empty, Union);
	IS_TRAITS_CHECK_CV(false, Empty, empty, Abstract);
	IS_TRAITS_CHECK_CV(false, Empty, empty, Polymorphic);
	IS_TRAITS_CHECK_CV(false, Empty, empty, NonEmpty0);
	IS_TRAITS_CHECK_CV(false, Empty, empty, NonEmpty1);
}