#include "test.hpp"

#include <libbr/memory/unique_pointer.hpp>

#include <libbr/utility/transfer.hpp>

using namespace BR;

TEST(Memory, UniquePointer) {

	UniquePointer<int> pointer0 = nullptr;
	UniquePointer<int> pointer1 = make_unique_pointer<int>(1);
	UniquePointer<int> pointer2(transfer(pointer1));

	EXPECT_EQ(nullptr, pointer0);
	EXPECT_EQ(nullptr, pointer1);
	EXPECT_EQ(1, *pointer2);

	pointer2.swap(pointer0);
	EXPECT_EQ(1, *pointer0);

	pointer0.release();
	EXPECT_EQ(nullptr, pointer0);

}