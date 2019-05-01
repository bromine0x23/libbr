#include "test.hpp"

#include <libbr/type_traits/is_reference.hpp>

using namespace BR;

TEST(TypeTraits, IsReference) {
	IS_TRAITS_CHECK(true, Reference, reference, int &);
	IS_TRAITS_CHECK(true, Reference, reference, int &&);
	IS_TRAITS_CHECK(true, Reference, reference, int (&)[]);
	IS_TRAITS_CHECK(true, Reference, reference, int (&&)[]);
	IS_TRAITS_CHECK(true, Reference, reference, int (&)[2]);
	IS_TRAITS_CHECK(true, Reference, reference, int (&&)[2]);
	IS_TRAITS_CHECK(true, Reference, reference, CFunction<int, int> &);
	IS_TRAITS_CHECK(true, Reference, reference, CFunction<int, int> &&);

	IS_TRAITS_CHECK(false, Reference, reference, void);
	IS_TRAITS_CHECK(false, Reference, reference, int);
	IS_TRAITS_CHECK(false, Reference, reference, int *);
	IS_TRAITS_CHECK(false, Reference, reference, int[]);
	IS_TRAITS_CHECK(false, Reference, reference, int[2]);
	IS_TRAITS_CHECK(false, Reference, reference, CFunction<int, int>);
	IS_TRAITS_CHECK(false, Reference, reference, CFunction<int, int> *);
}