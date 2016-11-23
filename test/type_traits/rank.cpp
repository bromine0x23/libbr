#include "test.hpp"

#include<libbr/type_traits/rank.hpp>

using namespace BR;

TEST(TypeTraits, Rank) {
	INTEGRAL_TRAITS_CHECK(0, Rank, rank, int);
	INTEGRAL_TRAITS_CHECK(1, Rank, rank, int[]);
	INTEGRAL_TRAITS_CHECK(2, Rank, rank, int[][3]);
	INTEGRAL_TRAITS_CHECK(2, Rank, rank, int[2][3]);
	INTEGRAL_TRAITS_CHECK(3, Rank, rank, int[2][3][5]);
	INTEGRAL_TRAITS_CHECK(0, Rank, rank, int(*)[2][3]);
	INTEGRAL_TRAITS_CHECK(0, Rank, rank, int(&)[2][3]);
	INTEGRAL_TRAITS_CHECK(0, Rank, rank, int(&&)[2][3]);
}