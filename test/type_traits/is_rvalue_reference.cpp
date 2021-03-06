#include "test.hpp"

#include <libbr/type_traits/is_rvalue_reference.hpp>

using namespace BR;

TEST(TypeTraits, IsRValueReference) {
	IS_TRAITS_CHECK(true, RValueReference, rvalue_reference, int &&);
	IS_TRAITS_CHECK(true, RValueReference, rvalue_reference, int (&&)[]);
	IS_TRAITS_CHECK(true, RValueReference, rvalue_reference, int (&&)[2]);
	IS_TRAITS_CHECK(true, RValueReference, rvalue_reference, CFunction<int, int> &&);

	IS_TRAITS_CHECK_CV(false, RValueReference, rvalue_reference, void);
	IS_TRAITS_CHECK_CV(false, RValueReference, rvalue_reference, int);
	IS_TRAITS_CHECK_CV(false, RValueReference, rvalue_reference, int *);
	IS_TRAITS_CHECK(false, RValueReference, rvalue_reference, int &);
	IS_TRAITS_CHECK(false, RValueReference, rvalue_reference, int (&)[]);
	IS_TRAITS_CHECK(false, RValueReference, rvalue_reference, int (&)[2]);
	IS_TRAITS_CHECK(false, RValueReference, rvalue_reference, int []);
	IS_TRAITS_CHECK(false, RValueReference, rvalue_reference, int [2]);
}