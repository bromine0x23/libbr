#include "../test.hpp"
#include <libbr/math/float.hpp>

using namespace BR;

static inline auto to_float(UInt32 r) -> Float32 {
	return Detail::Math::Bind32(r).f;
}

static Float32 pos_zero = to_float(0x00000000U);
static Float32 neg_zero = -pos_zero;
static Float32 pos_min_subnormal = to_float(0x0007FFFFU);
static Float32 neg_min_subnormal = -pos_min_subnormal;
static Float32 pos_max_subnormal = to_float(0x00000001U);
static Float32 neg_max_subnormal = -pos_max_subnormal;
static Float32 pos_min_normal = to_float(0x00800000U);
static Float32 neg_min_normal = -pos_min_normal;
static Float32 pos_max_normal = to_float(0x7F7FFFFFU);
static Float32 neg_max_normal = -pos_max_normal;
static Float32 pos_inf = to_float(0x7F800000U);
static Float32 neg_inf = -pos_inf;
static Float32 pos_nan = to_float(0x7FFFFFFFU);

TEST(Float32, Classify) {
	EXPECT_EQ(classify(pos_max_normal), FloatCategory::Normal);
	EXPECT_EQ(classify(neg_max_normal), FloatCategory::Normal);
	EXPECT_EQ(classify(pos_min_normal), FloatCategory::Normal);
	EXPECT_EQ(classify(neg_min_normal), FloatCategory::Normal);
	EXPECT_EQ(classify(pos_max_subnormal), FloatCategory::SubNormal);
	EXPECT_EQ(classify(neg_max_subnormal), FloatCategory::SubNormal);
	EXPECT_EQ(classify(pos_min_subnormal), FloatCategory::SubNormal);
	EXPECT_EQ(classify(neg_min_subnormal), FloatCategory::SubNormal);
	EXPECT_EQ(classify(pos_zero), FloatCategory::Zero);
	EXPECT_EQ(classify(neg_zero), FloatCategory::Zero);
	EXPECT_EQ(classify(pos_inf), FloatCategory::Infinite);
	EXPECT_EQ(classify(neg_inf), FloatCategory::Infinite);
	EXPECT_EQ(classify(pos_nan), FloatCategory::NaN);
}

TEST(Float32, IsNormal) {
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

TEST(Float32, IsFinite) {
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

TEST(Float32, IsInfinite) {
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

TEST(Float32, IsNaN) {
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

TEST(Float32, sqrt) {
	EXPECT_TRUE(is_nan(sqrt(pos_nan)));
	EXPECT_TRUE(is_infinite(sqrt(pos_inf)));
	EXPECT_TRUE(is_nan(sqrt(neg_inf)));
	EXPECT_EQ(pos_zero, sqrt(pos_zero));
	EXPECT_EQ(neg_zero, sqrt(neg_zero));
	EXPECT_TRUE(is_nan(sqrt(-4.0F)));
	EXPECT_EQ(2.0F, sqrt(4.0F));
	EXPECT_EQ(4.0F, sqrt(16.0F));
}

TEST(Float32, Exp2) {
	EXPECT_EQ(4.0F, exp2(2.0F));
	EXPECT_EQ(16.0F, exp2(4.0F));
}

TEST(Float32, Environment) {
	FloatEnvironment environment;
	get_float_environment(environment);
}