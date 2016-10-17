#include "../test.hpp"
#include <libbr/math/float.hpp>

using namespace BR;

static Float64 pos_zero = BR::Detail::Float::to_float(0x00000000U, 0x00000000U);
static Float64 neg_zero = -pos_zero;
static Float64 pos_min_subnormal = BR::Detail::Float::to_float(0x00000000U, 0x00000001U);
static Float64 neg_min_subnormal = -pos_min_subnormal;
static Float64 pos_max_subnormal = BR::Detail::Float::to_float(0x000FFFFFU, 0xFFFFFFFFU);
static Float64 neg_max_subnormal = -pos_max_subnormal;
static Float64 pos_min_normal = BR::Detail::Float::to_float(0x00100000U, 0x00000000U);
static Float64 neg_min_normal = -pos_min_normal;
static Float64 pos_max_normal = BR::Detail::Float::to_float(0x7FEFFFFFU, 0xFFFFFFFFU);
static Float64 neg_max_normal = -pos_max_normal;
static Float64 pos_inf = BR::Detail::Float::to_float(0x7FF00000U, 0x00000000U);
static Float64 neg_inf = -pos_inf;
static Float64 pos_nan = BR::Detail::Float::to_float(0x7FFFFFFFFFFFFFFFULL);

TEST(TestFloat64, Classify) {
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

TEST(TestFloat64, IsNormal) {
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

TEST(TestFloat64, IsFinite) {
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

TEST(TestFloat64, IsInfinite) {
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

TEST(TestFloat64, IsNaN) {
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