#include "test.hpp"

#include <libbr/type_traits/is_template_instance.hpp>

using namespace BR;

TEST(TypeTraits, IsTemplateInstance) {
	IS_TRAITS_CHECK(false, TemplateInstance, template_instance, void);
}