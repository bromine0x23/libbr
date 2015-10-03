#pragma once

#include <libbr/config.hpp>

#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/type.hpp>

#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/enable_if.hpp>

#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_pointer.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/map_qualifier.hpp>
#include <libbr/type_operate/remove_all_extents.hpp>
#include <libbr/type_operate/remove_const.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/remove_extent.hpp>
#include <libbr/type_operate/remove_pointer.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_operate/remove_volatile.hpp>

#include <libbr/type_operate/make_signed.hpp>
#include <libbr/type_operate/make_unsigned.hpp>

#include <libbr/type_operate/call_result.hpp>
#include <libbr/type_operate/common.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/template_argument.hpp>
#include <libbr/type_operate/variadic_get.hpp>

#include <libbr/type_operate/alignment_of.hpp>

#include <libbr/type_operate/has_nothrow_copy_assignment.hpp>
#include <libbr/type_operate/has_nothrow_copy_constructor.hpp>
#include <libbr/type_operate/has_nothrow_default_constructor.hpp>
#include <libbr/type_operate/has_nothrow_destructor.hpp>
#include <libbr/type_operate/has_nothrow_move_assignment.hpp>
#include <libbr/type_operate/has_nothrow_move_constructor.hpp>
#include <libbr/type_operate/has_trivial_copy_assignment.hpp>
#include <libbr/type_operate/has_trivial_copy_constructor.hpp>
#include <libbr/type_operate/has_trivial_default_constructor.hpp>
#include <libbr/type_operate/has_trivial_destructor.hpp>
#include <libbr/type_operate/has_trivial_move_assignment.hpp>
#include <libbr/type_operate/has_trivial_move_constructor.hpp>
#include <libbr/type_operate/has_virtual_destructor.hpp>

#include <libbr/type_operate/is_trivially_assignable.hpp>
#include <libbr/type_operate/is_trivially_constructible.hpp>
#include <libbr/type_operate/is_trivially_copy_assignable.hpp>
#include <libbr/type_operate/is_trivially_copy_constructible.hpp>
#include <libbr/type_operate/is_trivially_default_constructible.hpp>
#include <libbr/type_operate/is_trivially_destructible.hpp>
#include <libbr/type_operate/is_trivially_move_assignable.hpp>
#include <libbr/type_operate/is_trivially_move_constructible.hpp>

#include <libbr/type_operate/has_operator_bit_and.hpp>
#include <libbr/type_operate/has_operator_bit_and_assign.hpp>
#include <libbr/type_operate/has_operator_bit_or.hpp>
#include <libbr/type_operate/has_operator_bit_or_assign.hpp>
#include <libbr/type_operate/has_operator_bit_xor.hpp>
#include <libbr/type_operate/has_operator_bit_xor_assign.hpp>
#include <libbr/type_operate/has_operator_complement.hpp>
#include <libbr/type_operate/has_operator_dereference.hpp>
#include <libbr/type_operate/has_operator_divide.hpp>
#include <libbr/type_operate/has_operator_divide_assign.hpp>
#include <libbr/type_operate/has_operator_equal.hpp>
#include <libbr/type_operate/has_operator_greater.hpp>
#include <libbr/type_operate/has_operator_greater_equal.hpp>
#include <libbr/type_operate/has_operator_left_shift.hpp>
#include <libbr/type_operate/has_operator_left_shift_assign.hpp>
#include <libbr/type_operate/has_operator_less.hpp>
#include <libbr/type_operate/has_operator_less_equal.hpp>
#include <libbr/type_operate/has_operator_logical_and.hpp>
#include <libbr/type_operate/has_operator_logical_not.hpp>
#include <libbr/type_operate/has_operator_logical_or.hpp>
#include <libbr/type_operate/has_operator_minus.hpp>
#include <libbr/type_operate/has_operator_minus_assign.hpp>
#include <libbr/type_operate/has_operator_modulo.hpp>
#include <libbr/type_operate/has_operator_modulo_assign.hpp>
#include <libbr/type_operate/has_operator_multiply.hpp>
#include <libbr/type_operate/has_operator_multiply_assign.hpp>
#include <libbr/type_operate/has_operator_new.hpp>
#include <libbr/type_operate/has_operator_not_equal.hpp>
#include <libbr/type_operate/has_operator_prefix_decrement.hpp>
#include <libbr/type_operate/has_operator_prefix_increment.hpp>
#include <libbr/type_operate/has_operator_plus.hpp>
#include <libbr/type_operate/has_operator_plus_assign.hpp>
#include <libbr/type_operate/has_operator_right_shift.hpp>
#include <libbr/type_operate/has_operator_right_shift_assign.hpp>
#include <libbr/type_operate/has_operator_suffix_decrement.hpp>
#include <libbr/type_operate/has_operator_suffix_increment.hpp>
#include <libbr/type_operate/has_operator_unary_minus.hpp>
#include <libbr/type_operate/has_operator_unary_plus.hpp>