#include "test.hpp"

#include <libbr/type_transform/replace_first_template_argument.hpp>

using namespace BR;

TEST(TypeTransform, ReplaceFirstTemplateArgument) {
	TRANSFORM_CHECK(ReplaceFirstTemplateArgument, TypeWrapper<int>, TypeWrapper<void>, int)
}