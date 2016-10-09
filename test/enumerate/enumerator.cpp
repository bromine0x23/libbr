#include "../test.hpp"
#include <libbr/enumerate/enumerator.hpp>
#include <libbr/container/array.hpp>
#include <libbr/container/forward_list.hpp>

using namespace BR;

static bool is_even(int v) {
	return v % 2 == 0;
}

TEST(Enumerator, CArray) {
	int array[] = { 0, 1, 2, 3, 4 };
	auto enumerator = make_enumerator(array, array + 5);

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(0, enumerator.peek());
	EXPECT_EQ(0, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(1, enumerator.peek());
	EXPECT_EQ(1, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(2, enumerator.peek());
	EXPECT_EQ(2, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(3, enumerator.peek());
	EXPECT_EQ(3, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(4, enumerator.peek());
	EXPECT_EQ(4, enumerator.peek());

	EXPECT_FALSE(enumerator.move());
	EXPECT_FALSE(enumerator.move());
}

TEST(Enumerator, ForwardList) {
	ForwardList<int> list = { 0, 1, 2, 3, 4 };
	auto enumerator = make_enumerator(list.begin(), list.end());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(0, enumerator.peek());
	EXPECT_EQ(0, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(1, enumerator.peek());
	EXPECT_EQ(1, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(2, enumerator.peek());
	EXPECT_EQ(2, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(3, enumerator.peek());
	EXPECT_EQ(3, enumerator.peek());

	EXPECT_TRUE(enumerator.move());
	EXPECT_EQ(4, enumerator.peek());
	EXPECT_EQ(4, enumerator.peek());

	EXPECT_FALSE(enumerator.move());
	EXPECT_FALSE(enumerator.move());
}

struct S {
	int v;

	bool greater_than_five() const noexcept {
		return v > 10;
	}
};

TEST(Enumerator, Class) {
	auto array = Array< S, 5 >::build([](int i){
		return S{i};
	});
	auto enumerator = make_enumerator(array.begin(), array.end());
}