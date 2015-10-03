/**
 * @file
 * @brief 类型特性模块
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>

#include <libbr/type_traits/allocator_constructor_usage.hpp>
#include <libbr/type_traits/allocator_traits.hpp>
#include <libbr/type_traits/char_traits.hpp>
#include <libbr/type_traits/cv_traits.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/type_traits/use_allocator.hpp>

#include <libbr/type_traits/intrinsics.hpp>

#include <libbr/type_traits/is_abstract.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_class.hpp>
#include <libbr/type_traits/is_compound.hpp>
#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_enum.hpp>
#include <libbr/type_traits/is_floating_point.hpp>
#include <libbr/type_traits/is_function.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_integer.hpp>
#include <libbr/type_traits/is_literal_type.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_member_function_pointer.hpp>
#include <libbr/type_traits/is_member_object_pointer.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_null_pointer.hpp>
#include <libbr/type_traits/is_object.hpp>
#include <libbr/type_traits/is_pod.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/is_polymorphic.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_referenceable.hpp>
#include <libbr/type_traits/is_rvalue_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_scalar.hpp>
#include <libbr/type_traits/is_signed.hpp>
#include <libbr/type_traits/is_standard_layout.hpp>
#include <libbr/type_traits/is_static_castable.hpp>
#include <libbr/type_traits/is_template_instance.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/type_traits/is_union.hpp>
#include <libbr/type_traits/is_unsigned.hpp>
#include <libbr/type_traits/is_virtual_base_of.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/type_traits/is_volatile.hpp>

#include <libbr/type_traits/alignment_of.hpp>
#include <libbr/type_traits/extent.hpp>
#include <libbr/type_traits/rank.hpp>

#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_trivially_constructible.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>

#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_trivially_assignable.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>

#include <libbr/type_traits/has_default_constructor.hpp>
#include <libbr/type_traits/has_trivial_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>

#include <libbr/type_traits/has_copy_constructor.hpp>
#include <libbr/type_traits/has_trivial_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>

#include <libbr/type_traits/has_move_constructor.hpp>
#include <libbr/type_traits/has_trivial_move_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>

#include <libbr/type_traits/has_copy_assign.hpp>
#include <libbr/type_traits/has_trivial_copy_assign.hpp>
#include <libbr/type_traits/has_nothrow_copy_assign.hpp>

#include <libbr/type_traits/has_move_assign.hpp>
#include <libbr/type_traits/has_trivial_move_assign.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>

#include <libbr/type_traits/has_destructor.hpp>
#include <libbr/type_traits/has_trivial_destructor.hpp>
#include <libbr/type_traits/has_nothrow_destructor.hpp>
#include <libbr/type_traits/has_virtual_destructor.hpp>

#include <libbr/type_traits/has_operator_plus.hpp>
#include <libbr/type_traits/has_operator_plus_assign.hpp>
#include <libbr/type_traits/has_operator_minus.hpp>
#include <libbr/type_traits/has_operator_minus_assign.hpp>
#include <libbr/type_traits/has_operator_multiply.hpp>
#include <libbr/type_traits/has_operator_multiply_assign.hpp>
#include <libbr/type_traits/has_operator_divide.hpp>
#include <libbr/type_traits/has_operator_divide_assign.hpp>
#include <libbr/type_traits/has_operator_modulo.hpp>
#include <libbr/type_traits/has_operator_modulo_assign.hpp>
#include <libbr/type_traits/has_operator_bit_and.hpp>
#include <libbr/type_traits/has_operator_bit_and_assign.hpp>
#include <libbr/type_traits/has_operator_bit_or.hpp>
#include <libbr/type_traits/has_operator_bit_or_assign.hpp>
#include <libbr/type_traits/has_operator_bit_xor.hpp>
#include <libbr/type_traits/has_operator_bit_xor_assign.hpp>
#include <libbr/type_traits/has_operator_left_shift.hpp>
#include <libbr/type_traits/has_operator_left_shift_assign.hpp>
#include <libbr/type_traits/has_operator_right_shift.hpp>
#include <libbr/type_traits/has_operator_right_shift_assign.hpp>
#include <libbr/type_traits/has_operator_equal.hpp>
#include <libbr/type_traits/has_operator_not_equal.hpp>
#include <libbr/type_traits/has_operator_greater.hpp>
#include <libbr/type_traits/has_operator_greater_equal.hpp>
#include <libbr/type_traits/has_operator_less.hpp>
#include <libbr/type_traits/has_operator_less_equal.hpp>
#include <libbr/type_traits/has_operator_logical_not.hpp>
#include <libbr/type_traits/has_operator_logical_and.hpp>
#include <libbr/type_traits/has_operator_logical_or.hpp>
#include <libbr/type_traits/has_operator_unary_plus.hpp>
#include <libbr/type_traits/has_operator_unary_minus.hpp>
#include <libbr/type_traits/has_operator_complement.hpp>
#include <libbr/type_traits/has_operator_dereference.hpp>
#include <libbr/type_traits/has_operator_prefix_increment.hpp>
#include <libbr/type_traits/has_operator_prefix_decrement.hpp>
#include <libbr/type_traits/has_operator_suffix_increment.hpp>
#include <libbr/type_traits/has_operator_suffix_decrement.hpp>
#include <libbr/type_traits/has_operator_new.hpp>

#include <libbr/type_traits/is_swappable.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>