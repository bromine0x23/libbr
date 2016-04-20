#include <libbr/container/tuple.hpp>
#include <gtest/gtest.h>
#include <libbr/container/array.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/string/string.hpp>

using namespace BR;

struct Empty0 {};

struct Empty1 {};

TEST(TestTuple, EmptyMember) {
	using NotEmpty = int;
	ASSERT_EQ(sizeof(Tuple<NotEmpty, Empty0>), sizeof(NotEmpty));
	ASSERT_EQ(sizeof(Tuple<Empty0, NotEmpty>), sizeof(NotEmpty));
	ASSERT_EQ(sizeof(Tuple<NotEmpty, Empty0, Empty1>), sizeof(NotEmpty));
	ASSERT_EQ(sizeof(Tuple<Empty0, NotEmpty, Empty1>), sizeof(NotEmpty));
	ASSERT_EQ(sizeof(Tuple<Empty0, Empty1, NotEmpty>), sizeof(NotEmpty));
}

TEST(TestTuple, MakeTuple) {
	int i = 2;
	double d = 2.5;
	Tuple< int, int &, double & > t = make_tuple(1, reference(i), reference(d));

	EXPECT_EQ(1, t.get<0>());
	EXPECT_EQ(2, t.get<1>());
	EXPECT_EQ(2.5, t.get<2>());

	i = 3;
	d = 3.5;

	EXPECT_EQ(1, t.get<0>());
	EXPECT_EQ(3, t.get<1>());
	EXPECT_EQ(3.5, t.get<2>());

	t.get<1>() = 0;
	t.get<2>() = 0;

	EXPECT_EQ(0, i);
	EXPECT_EQ(0, d);
}

TEST(TestTuple, AssignPair) {
	using P = Pair< double, char >;
	using T = Tuple< int, short >;
	P p(2.5, 'a');
	T t;
	t = p;
	EXPECT_EQ(2, t.get<0>());
	EXPECT_EQ(short('a'), t.get<1>());

}

template< typename TTuple >
static void test_forward_as_tuple0(TTuple const & t) {
	ASSERT_EQ(TupleSize<TTuple>::value, 0);
}

template< typename TTuple >
static void test_forward_as_tuple1a(TTuple const & t) {
	ASSERT_EQ(TupleSize<TTuple>::value, 1);
	EXPECT_TRUE((IsSame< TupleElement<0, TTuple>, int && >::value));
	EXPECT_EQ(1, get<0>(t));
}

template< typename TTuple >
static void test_forward_as_tuple1b(TTuple const & t) {
	ASSERT_EQ(TupleSize<TTuple>::value, 1);
	EXPECT_TRUE((IsSame< TupleElement<0, TTuple>, int & >::value));
	EXPECT_EQ(2, get<0>(t));
}

template< typename TTuple >
static void test_forward_as_tuple2(TTuple const & t) {
	ASSERT_EQ(TupleSize<TTuple>::value, 2);
	EXPECT_TRUE((IsSame< TupleElement<0, TTuple>, double & >::value));
	EXPECT_TRUE((IsSame< TupleElement<1, TTuple>, char & >::value));
	EXPECT_EQ(2.5, get<0>(t));
	EXPECT_EQ('a', get<1>(t));
}

TEST(TestTuple, ForwardAsTuple) {
//	test_forward_as_tuple0(forward_as_tuple());
//	test_forward_as_tuple1a(forward_as_tuple(1));

//	int i = 2;
//	test_forward_as_tuple1b(forward_as_tuple(i));
//
//	double d = 2.5;
//	char c = 'a';
//	test_forward_as_tuple2(forward_as_tuple(d, c));
}

TEST(TestTuple, TupleCat) {
	{
		Tuple<> t = tuple_cat();
		BR_FORCE_USE(t);
	} {
		Tuple<> t0;
		Tuple<> t1 = tuple_cat(t0);
		BR_FORCE_USE(t1);
	} {
		Tuple<> t = tuple_cat(Tuple<>());
		BR_FORCE_USE(t);
	} {
		//Tuple<> t = tuple_cat< Array< int, 0 > >(Array< int, 0 >());
		//BR_FORCE_USE(t);
	} {
		Tuple<int> t0(1);
		Tuple<int> t = tuple_cat(t0);
		EXPECT_EQ(t.get<0>(), 1);
	}
}