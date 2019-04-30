#include "test.hpp"

#include <libbr/type_traits/is_lvalue_reference.hpp>

using namespace BR;

TEST(TypeTraits, IsLValueReference) {
	IS_TRAITS_CHECK(true, LValueReference, lvalue_reference, int &);
	IS_TRAITS_CHECK(true, LValueReference, lvalue_reference, int (&)[]);
	IS_TRAITS_CHECK(true, LValueReference, lvalue_reference, int (&)[2]);
	IS_TRAITS_CHECK(true, LValueReference, lvalue_reference, CFunction<int, int> &);

	IS_TRAITS_CHECK_CV(false, LValueReference, lvalue_reference, void);
	IS_TRAITS_CHECK_CV(false, LValueReference, lvalue_reference, int);
	IS_TRAITS_CHECK_CV(false, LValueReference, lvalue_reference, int *);
	IS_TRAITS_CHECK(false, LValueReference, lvalue_reference, int &&);
	IS_TRAITS_CHECK(false, LValueReference, lvalue_reference, int (&&)[]);
	IS_TRAITS_CHECK(false, LValueReference, lvalue_reference, int (&&)[2]);
	IS_TRAITS_CHECK(false, LValueReference, lvalue_reference, int []);
	IS_TRAITS_CHECK(false, LValueReference, lvalue_reference, int [2]);
}