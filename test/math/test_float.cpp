#include "test_math.hpp"

static void test_float32();

void test_float() {
	test_float32();
}

void test_float32() {
	using BR::Float32;
	using BR::FloatCategory;

	Float32 pos_max_normal = +3.40282346E38f;
	Float32 neg_max_normal = -3.40282346E38f;
	Float32 pos_min_normal = +1.17549435E-38f;
	Float32 neg_min_normal = -1.17549435E-38f;
	Float32 pos_max_subnormal = +1.17549421E-38f;
	Float32 neg_max_subnormal = -1.17549421E-38f;
	Float32 pos_min_subnormal = +1.40129846E-45f;
	Float32 neg_min_subnormal = -1.40129846E-45f;
	Float32 pos_zero = +0.0f;
	Float32 neg_zero = -0.0f;
	Float32 pos_inf = +BR::infinity32();
	Float32 neg_inf = -BR::infinity32();
	Float32 pos_nan = +BR::nan32();
	Float32 neg_nan = -BR::nan32();

	BR_ASSERT(BR::classify(pos_max_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(neg_max_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(pos_min_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(neg_min_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(pos_max_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(neg_max_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(pos_min_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(neg_min_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(pos_zero) == FloatCategory::zero);
	BR_ASSERT(BR::classify(neg_zero) == FloatCategory::zero);
	BR_ASSERT(BR::classify(pos_inf) == FloatCategory::infinite);
	BR_ASSERT(BR::classify(neg_inf) == FloatCategory::infinite);
	BR_ASSERT(BR::classify(pos_nan) == FloatCategory::nan);
	BR_ASSERT(BR::classify(neg_nan) == FloatCategory::nan);

	BR_ASSERT(BR::is_normal(pos_max_normal));
	BR_ASSERT(BR::is_normal(neg_max_normal));
	BR_ASSERT(BR::is_normal(pos_min_normal));
	BR_ASSERT(BR::is_normal(neg_min_normal));
	BR_ASSERT(!BR::is_normal(pos_max_subnormal));
	BR_ASSERT(!BR::is_normal(neg_max_subnormal));
	BR_ASSERT(!BR::is_normal(pos_min_subnormal));
	BR_ASSERT(!BR::is_normal(neg_min_subnormal));
	BR_ASSERT(!BR::is_normal(pos_zero));
	BR_ASSERT(!BR::is_normal(neg_zero));
	BR_ASSERT(!BR::is_normal(pos_inf));
	BR_ASSERT(!BR::is_normal(neg_inf));
	BR_ASSERT(!BR::is_normal(pos_nan));
	BR_ASSERT(!BR::is_normal(neg_nan));


	BR_ASSERT(BR::is_finite(pos_max_normal));
	BR_ASSERT(BR::is_finite(neg_max_normal));
	BR_ASSERT(BR::is_finite(pos_min_normal));
	BR_ASSERT(BR::is_finite(neg_min_normal));
	BR_ASSERT(BR::is_finite(pos_max_subnormal));
	BR_ASSERT(BR::is_finite(neg_max_subnormal));
	BR_ASSERT(BR::is_finite(pos_min_subnormal));
	BR_ASSERT(BR::is_finite(neg_min_subnormal));
	BR_ASSERT(BR::is_finite(pos_zero));
	BR_ASSERT(BR::is_finite(neg_zero));
	BR_ASSERT(!BR::is_finite(pos_inf));
	BR_ASSERT(!BR::is_finite(neg_inf));
	BR_ASSERT(!BR::is_finite(pos_nan));
	BR_ASSERT(!BR::is_finite(neg_nan));

	BR_ASSERT(!BR::is_infinite(pos_max_normal));
	BR_ASSERT(!BR::is_infinite(neg_max_normal));
	BR_ASSERT(!BR::is_infinite(pos_min_normal));
	BR_ASSERT(!BR::is_infinite(neg_min_normal));
	BR_ASSERT(!BR::is_infinite(pos_max_subnormal));
	BR_ASSERT(!BR::is_infinite(neg_max_subnormal));
	BR_ASSERT(!BR::is_infinite(pos_min_subnormal));
	BR_ASSERT(!BR::is_infinite(neg_min_subnormal));
	BR_ASSERT(!BR::is_infinite(pos_zero));
	BR_ASSERT(!BR::is_infinite(neg_zero));
	BR_ASSERT(BR::is_infinite(pos_inf));
	BR_ASSERT(BR::is_infinite(neg_inf));
	BR_ASSERT(!BR::is_infinite(pos_nan));
	BR_ASSERT(!BR::is_infinite(neg_nan));

	BR_ASSERT(!BR::is_nan(pos_max_normal));
	BR_ASSERT(!BR::is_nan(neg_max_normal));
	BR_ASSERT(!BR::is_nan(pos_min_normal));
	BR_ASSERT(!BR::is_nan(neg_min_normal));
	BR_ASSERT(!BR::is_nan(pos_max_subnormal));
	BR_ASSERT(!BR::is_nan(neg_max_subnormal));
	BR_ASSERT(!BR::is_nan(pos_min_subnormal));
	BR_ASSERT(!BR::is_nan(neg_min_subnormal));
	BR_ASSERT(!BR::is_nan(pos_zero));
	BR_ASSERT(!BR::is_nan(neg_zero));
	BR_ASSERT(!BR::is_nan(pos_inf));
	BR_ASSERT(!BR::is_nan(neg_inf));
	BR_ASSERT(BR::is_nan(pos_nan));
	BR_ASSERT(BR::is_nan(neg_nan));
}

void test_float64() {
	using BR::Float64;
	using BR::FloatCategory;

	Float64 pos_zero = +0.0;
	Float64 neg_zero = -0.0;
	Float64 pos_min_subnormal = +4.9406564584124654E-324;
	Float64 neg_min_subnormal = -4.9406564584124654E-324;
	Float64 pos_max_subnormal = +2.2250738585072009E-308;
	Float64 neg_max_subnormal = -2.2250738585072009E-308;
	Float64 pos_min_normal = +2.2250738585072014E-308;
	Float64 neg_min_normal = -2.2250738585072014E-38f;
	Float64 pos_max_normal = +1.7976931348623157E308;
	Float64 neg_max_normal = -1.7976931348623157E308;
	Float64 pos_inf = +BR::infinity64();
	Float64 neg_inf = -BR::infinity64();
	Float64 pos_nan = +BR::nan64();
	Float64 neg_nan = -BR::nan64();

	BR_ASSERT(BR::classify(pos_max_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(neg_max_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(pos_min_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(neg_min_normal) == FloatCategory::normal);
	BR_ASSERT(BR::classify(pos_max_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(neg_max_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(pos_min_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(neg_min_subnormal) == FloatCategory::subnormal);
	BR_ASSERT(BR::classify(pos_zero) == FloatCategory::zero);
	BR_ASSERT(BR::classify(neg_zero) == FloatCategory::zero);
	BR_ASSERT(BR::classify(pos_inf) == FloatCategory::infinite);
	BR_ASSERT(BR::classify(neg_inf) == FloatCategory::infinite);
	BR_ASSERT(BR::classify(pos_nan) == FloatCategory::nan);
	BR_ASSERT(BR::classify(neg_nan) == FloatCategory::nan);

	BR_ASSERT(BR::is_normal(pos_max_normal));
	BR_ASSERT(BR::is_normal(neg_max_normal));
	BR_ASSERT(BR::is_normal(pos_min_normal));
	BR_ASSERT(BR::is_normal(neg_min_normal));
	BR_ASSERT(!BR::is_normal(pos_max_subnormal));
	BR_ASSERT(!BR::is_normal(neg_max_subnormal));
	BR_ASSERT(!BR::is_normal(pos_min_subnormal));
	BR_ASSERT(!BR::is_normal(neg_min_subnormal));
	BR_ASSERT(!BR::is_normal(pos_zero));
	BR_ASSERT(!BR::is_normal(neg_zero));
	BR_ASSERT(!BR::is_normal(pos_inf));
	BR_ASSERT(!BR::is_normal(neg_inf));
	BR_ASSERT(!BR::is_normal(pos_nan));
	BR_ASSERT(!BR::is_normal(neg_nan));


	BR_ASSERT(BR::is_finite(pos_max_normal));
	BR_ASSERT(BR::is_finite(neg_max_normal));
	BR_ASSERT(BR::is_finite(pos_min_normal));
	BR_ASSERT(BR::is_finite(neg_min_normal));
	BR_ASSERT(BR::is_finite(pos_max_subnormal));
	BR_ASSERT(BR::is_finite(neg_max_subnormal));
	BR_ASSERT(BR::is_finite(pos_min_subnormal));
	BR_ASSERT(BR::is_finite(neg_min_subnormal));
	BR_ASSERT(BR::is_finite(pos_zero));
	BR_ASSERT(BR::is_finite(neg_zero));
	BR_ASSERT(!BR::is_finite(pos_inf));
	BR_ASSERT(!BR::is_finite(neg_inf));
	BR_ASSERT(!BR::is_finite(pos_nan));
	BR_ASSERT(!BR::is_finite(neg_nan));

	BR_ASSERT(!BR::is_infinite(pos_max_normal));
	BR_ASSERT(!BR::is_infinite(neg_max_normal));
	BR_ASSERT(!BR::is_infinite(pos_min_normal));
	BR_ASSERT(!BR::is_infinite(neg_min_normal));
	BR_ASSERT(!BR::is_infinite(pos_max_subnormal));
	BR_ASSERT(!BR::is_infinite(neg_max_subnormal));
	BR_ASSERT(!BR::is_infinite(pos_min_subnormal));
	BR_ASSERT(!BR::is_infinite(neg_min_subnormal));
	BR_ASSERT(!BR::is_infinite(pos_zero));
	BR_ASSERT(!BR::is_infinite(neg_zero));
	BR_ASSERT(BR::is_infinite(pos_inf));
	BR_ASSERT(BR::is_infinite(neg_inf));
	BR_ASSERT(!BR::is_infinite(pos_nan));
	BR_ASSERT(!BR::is_infinite(neg_nan));

	BR_ASSERT(!BR::is_nan(pos_max_normal));
	BR_ASSERT(!BR::is_nan(neg_max_normal));
	BR_ASSERT(!BR::is_nan(pos_min_normal));
	BR_ASSERT(!BR::is_nan(neg_min_normal));
	BR_ASSERT(!BR::is_nan(pos_max_subnormal));
	BR_ASSERT(!BR::is_nan(neg_max_subnormal));
	BR_ASSERT(!BR::is_nan(pos_min_subnormal));
	BR_ASSERT(!BR::is_nan(neg_min_subnormal));
	BR_ASSERT(!BR::is_nan(pos_zero));
	BR_ASSERT(!BR::is_nan(neg_zero));
	BR_ASSERT(!BR::is_nan(pos_inf));
	BR_ASSERT(!BR::is_nan(neg_inf));
	BR_ASSERT(BR::is_nan(pos_nan));
	BR_ASSERT(BR::is_nan(neg_nan));
}