#include "test.hpp"

#include <libbr/type_traits/is_member_function_pointer.hpp>

using namespace BR;

TEST(TypeTraits, IsMemberFunctionPointer) {
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)()                   -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)() const             -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)()       volatile    -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)() const volatile    -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)()                &  -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)()                && -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(int)                   -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(int) const             -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(int)       volatile    -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(int) const volatile    -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(int)                &  -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(int)                && -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(...)                   -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(...) const             -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(...)       volatile    -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(...) const volatile    -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(...)                &  -> void);
	IS_TRAITS_CHECK(true, MemberFunctionPointer, member_function_pointer, auto (Class::*)(...)                && -> void);

	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, void);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, int);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, int *);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, int &);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, int &&);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, int []);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, int [2]);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, CFunction<void> *);
	IS_TRAITS_CHECK(false, MemberFunctionPointer, member_function_pointer, int Class::*);
}