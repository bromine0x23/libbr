#include "../test.hpp"
#include <libbr/math/float.hpp>

using namespace BR;

static Float32 pos_zero = BR::Detail::Math::to_float32(0x00000000);
static Float32 neg_zero = -pos_zero;
static Float32 pos_min_subnormal = BR::Detail::Math::to_float32(0x0007FFFF);
static Float32 neg_min_subnormal = -pos_min_subnormal;
static Float32 pos_max_subnormal = BR::Detail::Math::to_float32(0x00000001);
static Float32 neg_max_subnormal = -pos_max_subnormal;
static Float32 pos_min_normal = BR::Detail::Math::to_float32(0x00800000);
static Float32 neg_min_normal = -pos_min_normal;
static Float32 pos_max_normal = BR::Detail::Math::to_float32(0x7F7FFFFF);
static Float32 neg_max_normal = -pos_max_normal;
static Float32 pos_inf = BR::Detail::Math::to_float32(0x7F800000);
static Float32 neg_inf = -pos_inf;
static Float32 pos_nan = BR::Detail::Math::to_float32(0x7FFFFFFF);

TEST(TestFloat32, Classify) {
	EXPECT_EQ(classify(pos_max_normal), FloatCategory::normal);
	EXPECT_EQ(classify(neg_max_normal), FloatCategory::normal);
	EXPECT_EQ(classify(pos_min_normal), FloatCategory::normal);
	EXPECT_EQ(classify(neg_min_normal), FloatCategory::normal);
	EXPECT_EQ(classify(pos_max_subnormal), FloatCategory::subnormal);
	EXPECT_EQ(classify(neg_max_subnormal), FloatCategory::subnormal);
	EXPECT_EQ(classify(pos_min_subnormal), FloatCategory::subnormal);
	EXPECT_EQ(classify(neg_min_subnormal), FloatCategory::subnormal);
	EXPECT_EQ(classify(pos_zero), FloatCategory::zero);
	EXPECT_EQ(classify(neg_zero), FloatCategory::zero);
	EXPECT_EQ(classify(pos_inf), FloatCategory::infinite);
	EXPECT_EQ(classify(neg_inf), FloatCategory::infinite);
	EXPECT_EQ(classify(pos_nan), FloatCategory::nan);
}

TEST(TestFloat32, IsNormal) {
	EXPECT_TRUE(is_normal(pos_max_normal));
	EXPECT_TRUE(is_normal(neg_max_normal));
	EXPECT_TRUE(is_normal(pos_min_normal));
	EXPECT_TRUE(is_normal(neg_min_normal));
	EXPECT_FALSE(is_normal(pos_max_subnormal));
	EXPECT_FALSE(is_normal(neg_max_subnormal));
	EXPECT_FALSE(is_normal(pos_min_subnormal));
	EXPECT_FALSE(is_normal(neg_min_subnormal));
	EXPECT_FALSE(is_normal(pos_zero));
	EXPECT_FALSE(is_normal(neg_zero));
	EXPECT_FALSE(is_normal(pos_inf));
	EXPECT_FALSE(is_normal(neg_inf));
	EXPECT_FALSE(is_normal(pos_nan));
}

TEST(TestFloat32, IsFinite) {
	EXPECT_TRUE(is_finite(pos_max_normal));
	EXPECT_TRUE(is_finite(neg_max_normal));
	EXPECT_TRUE(is_finite(pos_min_normal));
	EXPECT_TRUE(is_finite(neg_min_normal));
	EXPECT_TRUE(is_finite(pos_max_subnormal));
	EXPECT_TRUE(is_finite(neg_max_subnormal));
	EXPECT_TRUE(is_finite(pos_min_subnormal));
	EXPECT_TRUE(is_finite(neg_min_subnormal));
	EXPECT_TRUE(is_finite(pos_zero));
	EXPECT_TRUE(is_finite(neg_zero));
	EXPECT_FALSE(is_finite(pos_inf));
	EXPECT_FALSE(is_finite(neg_inf));
	EXPECT_FALSE(is_finite(pos_nan));
}

TEST(TestFloat32, IsInfinite) {
	EXPECT_FALSE(is_infinite(pos_max_normal));
	EXPECT_FALSE(is_infinite(neg_max_normal));
	EXPECT_FALSE(is_infinite(pos_min_normal));
	EXPECT_FALSE(is_infinite(neg_min_normal));
	EXPECT_FALSE(is_infinite(pos_max_subnormal));
	EXPECT_FALSE(is_infinite(neg_max_subnormal));
	EXPECT_FALSE(is_infinite(pos_min_subnormal));
	EXPECT_FALSE(is_infinite(neg_min_subnormal));
	EXPECT_FALSE(is_infinite(pos_zero));
	EXPECT_FALSE(is_infinite(neg_zero));
	EXPECT_TRUE(is_infinite(pos_inf));
	EXPECT_TRUE(is_infinite(neg_inf));
	EXPECT_FALSE(is_infinite(pos_nan));
}

TEST(TestFloat32, IsNaN) {
	EXPECT_FALSE(is_nan(pos_max_normal));
	EXPECT_FALSE(is_nan(neg_max_normal));
	EXPECT_FALSE(is_nan(pos_min_normal));
	EXPECT_FALSE(is_nan(neg_min_normal));
	EXPECT_FALSE(is_nan(pos_max_subnormal));
	EXPECT_FALSE(is_nan(neg_max_subnormal));
	EXPECT_FALSE(is_nan(pos_min_subnormal));
	EXPECT_FALSE(is_nan(neg_min_subnormal));
	EXPECT_FALSE(is_nan(pos_zero));
	EXPECT_FALSE(is_nan(neg_zero));
	EXPECT_FALSE(is_nan(pos_inf));
	EXPECT_FALSE(is_nan(neg_inf));
	EXPECT_TRUE(is_nan(pos_nan));
}