#include "test.hpp"

#include <libbr/math/relation.hpp>

using namespace BR;

TEST(Math, Relation) {
	EXPECT_EQ(Relation::LT, to_relation(-1000.0));
	EXPECT_EQ(Relation::LT, to_relation(-100LL));
	EXPECT_EQ(Relation::LT, to_relation(-10));
	EXPECT_EQ(Relation::LT, to_relation(-1));
	EXPECT_EQ(Relation::EQ, to_relation(0));
	EXPECT_EQ(Relation::EQ, to_relation(0LL));
	EXPECT_EQ(Relation::EQ, to_relation(0.0));
	EXPECT_EQ(Relation::GT, to_relation(1));
	EXPECT_EQ(Relation::GT, to_relation(10));
	EXPECT_EQ(Relation::GT, to_relation(100LL));
	EXPECT_EQ(Relation::GT, to_relation(1000.0));
}
