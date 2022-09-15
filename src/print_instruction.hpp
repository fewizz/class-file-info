#pragma once

#include "./print.hpp"

#include <class_file/attribute/code/instruction.hpp>
#include <on_scope_exit.hpp>
#include <loop_action.hpp>
#include <c_string.hpp>
#include <number.hpp>
#include <array.hpp>

#include <posix/abort.hpp>

template<typename Type>
static void print_instruction(Type x) {

	using namespace class_file::attribute::code::instruction;

	on_scope_exit new_line_on_scope_exit{[](){
		print("\n");
	}};

	if constexpr (same_as<Type, nop>) {
		print("nop");
	}

	else if constexpr (same_as<Type, a_const_null>)
		print("a_const_null");
	else if constexpr (same_as<Type, i_const_m1>) print("i_const_m1");
	else if constexpr (same_as<Type, i_const_0>) print("i_const_0");
	else if constexpr (same_as<Type, i_const_1>) print("i_const_1");
	else if constexpr (same_as<Type, i_const_2>) print("i_const_2");
	else if constexpr (same_as<Type, i_const_3>) print("i_const_3");
	else if constexpr (same_as<Type, i_const_4>) print("i_const_4");
	else if constexpr (same_as<Type, i_const_5>) print("i_const_5");
	else if constexpr (same_as<Type, l_const_0>) print("l_const_0");
	else if constexpr (same_as<Type, l_const_1>) print("l_const_1");
	else if constexpr (same_as<Type, f_const_0>) print("f_const_0");
	else if constexpr (same_as<Type, f_const_1>) print("f_const_1");
	else if constexpr (same_as<Type, f_const_2>) print("f_const_2");
	else if constexpr (same_as<Type, d_const_0>) print("d_const_0");
	else if constexpr (same_as<Type, d_const_1>) print("d_const_1");

	else if constexpr (same_as<Type, bi_push>) {
		print("bi_push ");
		print(x.value);
	}
	else if constexpr (same_as<Type, si_push>) {
		print("si_push ");
		print(x.value);
	}

	else if constexpr (same_as<Type, ldc>) {
		print("ldc ");
		print((uint8) x.index);
	}
	else if constexpr (same_as<Type, ldc_w>) {
		print("ldc_w ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, ldc_2_w>) {
		print("ldc_2_w ");
		print((uint16) x.index);
	}

	else if constexpr (same_as<Type, i_load>) {
		print("i_load ");
		print(x.index);
	}
	else if constexpr (same_as<Type, l_load>) {
		print("l_load ");
		print(x.index);
	}
	else if constexpr (same_as<Type, f_load>) {
		print("f_load ");
		print(x.index);
	}
	else if constexpr (same_as<Type, d_load>) {
		print("d_load ");
		print(x.index);
	}
	else if constexpr (same_as<Type, a_load>) {
		print("a_load ");
		print(x.index);
	}
	else if constexpr (same_as<Type, i_load_0>) print("i_load_0");
	else if constexpr (same_as<Type, i_load_1>) print("i_load_1");
	else if constexpr (same_as<Type, i_load_2>) print("i_load_2");
	else if constexpr (same_as<Type, i_load_3>) print("i_load_3");
	else if constexpr (same_as<Type, l_load_0>) print("l_load_0");
	else if constexpr (same_as<Type, l_load_1>) print("l_load_1");
	else if constexpr (same_as<Type, l_load_2>) print("l_load_2");
	else if constexpr (same_as<Type, l_load_3>) print("l_load_3");
	else if constexpr (same_as<Type, f_load_0>) print("f_load_0");
	else if constexpr (same_as<Type, f_load_1>) print("f_load_1");
	else if constexpr (same_as<Type, f_load_2>) print("f_load_2");
	else if constexpr (same_as<Type, f_load_3>) print("f_load_3");
	else if constexpr (same_as<Type, d_load_0>) print("d_load_0");
	else if constexpr (same_as<Type, d_load_1>) print("d_load_1");
	else if constexpr (same_as<Type, d_load_2>) print("d_load_2");
	else if constexpr (same_as<Type, d_load_3>) print("d_load_3");
	else if constexpr (same_as<Type, a_load_0>) print("a_load_0");
	else if constexpr (same_as<Type, a_load_1>) print("a_load_1");
	else if constexpr (same_as<Type, a_load_2>) print("a_load_2");
	else if constexpr (same_as<Type, a_load_3>) print("a_load_3");
	else if constexpr (same_as<Type, i_a_load>) print("i_a_load");
	else if constexpr (same_as<Type, l_a_load>) print("l_a_load");
	else if constexpr (same_as<Type, f_a_load>) print("f_a_load");
	else if constexpr (same_as<Type, d_a_load>) print("d_a_load");
	else if constexpr (same_as<Type, a_a_load>) print("a_a_load");
	else if constexpr (same_as<Type, b_a_load>) print("b_a_load");
	else if constexpr (same_as<Type, c_a_load>) print("c_a_load");
	else if constexpr (same_as<Type, s_a_load>) print("s_a_load");

	else if constexpr (same_as<Type, i_store>) {
		print("i_store ");
		print(x.index);
	}
	else if constexpr (same_as<Type, l_store>) {
		print("l_store ");
		print(x.index);
	}
	else if constexpr (same_as<Type, f_store>) {
		print("f_store ");
		print(x.index);
	}
	else if constexpr (same_as<Type, d_store>) {
		print("d_store ");
		print(x.index);
	}
	else if constexpr (same_as<Type, a_store>) {
		print("a_store ");
		print(x.index);
	}
	else if constexpr (same_as<Type, i_store_0>) print("i_store_0");
	else if constexpr (same_as<Type, i_store_1>) print("i_store_1");
	else if constexpr (same_as<Type, i_store_2>) print("i_store_2");
	else if constexpr (same_as<Type, i_store_3>) print("i_store_3");
	else if constexpr (same_as<Type, l_store_0>) print("l_store_0");
	else if constexpr (same_as<Type, l_store_1>) print("l_store_1");
	else if constexpr (same_as<Type, l_store_2>) print("l_store_2");
	else if constexpr (same_as<Type, l_store_3>) print("l_store_3");
	else if constexpr (same_as<Type, f_store_0>) print("f_store_0");
	else if constexpr (same_as<Type, f_store_1>) print("f_store_1");
	else if constexpr (same_as<Type, f_store_2>) print("f_store_2");
	else if constexpr (same_as<Type, f_store_3>) print("f_store_3");
	else if constexpr (same_as<Type, d_store_0>) print("d_store_0");
	else if constexpr (same_as<Type, d_store_1>) print("d_store_1");
	else if constexpr (same_as<Type, d_store_2>) print("d_store_2");
	else if constexpr (same_as<Type, d_store_3>) print("d_store_3");
	else if constexpr (same_as<Type, a_store_0>) print("a_store_0");
	else if constexpr (same_as<Type, a_store_1>) print("a_store_1");
	else if constexpr (same_as<Type, a_store_2>) print("a_store_2");
	else if constexpr (same_as<Type, a_store_3>) print("a_store_3");
	else if constexpr (same_as<Type, i_a_store>) print("i_a_store");
	else if constexpr (same_as<Type, l_a_store>) print("l_a_store");
	else if constexpr (same_as<Type, f_a_store>) print("f_a_store");
	else if constexpr (same_as<Type, d_a_store>) print("d_a_store");
	else if constexpr (same_as<Type, a_a_store>) print("a_a_store");
	else if constexpr (same_as<Type, b_a_store>) print("b_a_store");
	else if constexpr (same_as<Type, c_a_store>) print("c_a_store");
	else if constexpr (same_as<Type, s_a_store>) print("s_a_store");

	else if constexpr (same_as<Type, pop>) print("pop");
	else if constexpr (same_as<Type, pop_2>) print("pop_2");
	else if constexpr (same_as<Type, dup>) print("dup");
	else if constexpr (same_as<Type, dup_x1>) print("dup_x1");
	else if constexpr (same_as<Type, dup_x2>) print("dup_x2");
	else if constexpr (same_as<Type, dup_2>) print("dup_2");
	else if constexpr (same_as<Type, dup_2_x1>) print("dup_2_x1");
	else if constexpr (same_as<Type, dup_2_x2>) print("dup_2_x2");
	else if constexpr (same_as<Type, swap>) print("swap");

	else if constexpr (same_as<Type, i_add>) print("i_add");
	else if constexpr (same_as<Type, l_add>) print("l_add");
	else if constexpr (same_as<Type, f_add>) print("f_add");
	else if constexpr (same_as<Type, d_add>) print("d_add");
	else if constexpr (same_as<Type, i_sub>) print("i_sub");
	else if constexpr (same_as<Type, l_sub>) print("l_sub");
	else if constexpr (same_as<Type, f_sub>) print("f_sub");
	else if constexpr (same_as<Type, d_sub>) print("d_sub");
	else if constexpr (same_as<Type, i_mul>) print("i_mul");
	else if constexpr (same_as<Type, l_mul>) print("l_mul");
	else if constexpr (same_as<Type, f_mul>) print("f_mul");
	else if constexpr (same_as<Type, d_mul>) print("d_mul");
	else if constexpr (same_as<Type, i_div>) print("i_div");
	else if constexpr (same_as<Type, l_div>) print("l_div");
	else if constexpr (same_as<Type, f_div>) print("f_div");
	else if constexpr (same_as<Type, d_div>) print("d_div");
	else if constexpr (same_as<Type, i_rem>) print("i_rem");
	else if constexpr (same_as<Type, l_rem>) print("l_rem");
	else if constexpr (same_as<Type, f_rem>) print("f_rem");
	else if constexpr (same_as<Type, d_rem>) print("d_rem");
	else if constexpr (same_as<Type, i_neg>) print("i_neg");
	else if constexpr (same_as<Type, l_neg>) print("l_neg");
	else if constexpr (same_as<Type, f_neg>) print("f_neg");
	else if constexpr (same_as<Type, d_neg>) print("d_neg");
	else if constexpr (same_as<Type, i_sh_l>) print("i_sh_l");
	else if constexpr (same_as<Type, l_sh_l>) print("l_sh_l");
	else if constexpr (same_as<Type, i_sh_r>) print("i_sh_r");
	else if constexpr (same_as<Type, l_sh_r>) print("l_sh_r");
	else if constexpr (same_as<Type, i_u_sh_r>) print("i_u_sh_r");
	else if constexpr (same_as<Type, l_u_sh_r>) print("l_u_sh_r");
	else if constexpr (same_as<Type, i_and>) print("i_and");
	else if constexpr (same_as<Type, l_and>) print("l_and");
	else if constexpr (same_as<Type, i_or>) print("i_or");
	else if constexpr (same_as<Type, l_or>) print("l_or");
	else if constexpr (same_as<Type, i_xor>) print("i_xor");
	else if constexpr (same_as<Type, l_xor>) print("l_xor");
	else if constexpr (same_as<Type, i_inc>) {
		print("iinc ");
		print(x.index);
		print(", ");
		print(x.value);
	}
	else if constexpr (same_as<Type, i_to_l>) print("i_to_l");
	else if constexpr (same_as<Type, i_to_f>) print("i_to_f");
	else if constexpr (same_as<Type, i_to_d>) print("i_to_d");
	else if constexpr (same_as<Type, l_to_i>) print("l_to_i");
	else if constexpr (same_as<Type, l_to_f>) print("l_to_f");
	else if constexpr (same_as<Type, l_to_d>) print("l_to_d");
	else if constexpr (same_as<Type, f_to_i>) print("f_to_i");
	else if constexpr (same_as<Type, f_to_l>) print("f_to_l");
	else if constexpr (same_as<Type, f_to_d>) print("f_to_d");
	else if constexpr (same_as<Type, d_to_i>) print("d_to_i");
	else if constexpr (same_as<Type, d_to_l>) print("d_to_l");
	else if constexpr (same_as<Type, d_to_f>) print("d_to_f");
	else if constexpr (same_as<Type, i_to_b>) print("i_to_b");
	else if constexpr (same_as<Type, i_to_c>) print("i_to_c");
	else if constexpr (same_as<Type, i_to_s>) print("i_to_s");

	else if constexpr (same_as<Type, l_cmp>) print("l_cmp");

	else if constexpr (same_as<Type, f_cmp_l>) print("f_cmp_l");
	else if constexpr (same_as<Type, f_cmp_g>) print("f_cmp_g");
	else if constexpr (same_as<Type, d_cmp_l>) print("d_cmp_l");
	else if constexpr (same_as<Type, d_cmp_g>) print("d_cmp_g");

	else if constexpr (same_as<Type, if_eq>) {
		print("if_eq ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_ne>) {
		print("if_ne ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_lt>) {
		print("if_lt ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_ge>) {
		print("if_ge ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_gt>) {
		print("if_gt ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_le>) {
		print("if_le ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_eq>) {
		print("if_i_cmp_eq ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_ne>) {
		print("if_i_cmp_ne ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_lt>) {
		print("if_i_cmp_lt ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_ge>) {
		print("if_i_cmp_ge ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_gt>) {
		print("if_i_cmp_gt ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_le>) {
		print("if_i_cmp_le ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_a_cmp_eq>) {
		print("if_a_cmp_eq ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_a_cmp_ne>) {
		print("if_a_cmp_ne ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, go_to>) {
		print("goto ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, jmp_sr>) {
		print("jmp_sr ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, return_sr>) {
		print("return_sr ");
		print(x.index);
	}
	else if constexpr (same_as<Type, table_switch>) {
		print("table_switch ");
		print(x._default);
		for(auto p : x.offsets) {
			print(" ");
			print(p);
		}
	}
	else if constexpr (same_as<Type, lookup_switch>) {
		print("lookup_switch ");
		print(x._default);
		for(auto p : x.pairs) {
			print(" ");
			print(p.match);
			print(":");
			print(p.offset);
		}
	}
	else if constexpr (same_as<Type, i_return>) {
		print("i_return");
	}
	else if constexpr (same_as<Type, l_return>) {
		print("l_return");
	}
	else if constexpr (same_as<Type, f_return>) {
		print("f_return");
	}
	else if constexpr (same_as<Type, d_return>) {
		print("d_return");
	}
	else if constexpr (same_as<Type, a_return>) {
		print("a_return");
	}
	else if constexpr (same_as<Type, _return>) {
		print("return");
	}

	else if constexpr (same_as<Type, get_static>) {
		print("get_static ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, put_static>) {
		print("put_static ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, get_field>) {
		print("get_field ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, put_field>) {
		print("put_field ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, invoke_virtual>) {
		print("invoke_virtual ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, invoke_special>) {
		print("invoke_special ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, invoke_static>) {
		print("invoke_static ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, invoke_interface>) {
		print("invoke_interface ");
		print((uint16) x.index);
		print(x.count);
	}
	else if constexpr (same_as<Type, invoke_dynamic>) {
		print("invoked_ynamic ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, _new>) {
		print("new ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, new_array>) {
		print("new_array ");
		print((uint8) x.type);
	}
	else if constexpr (same_as<Type, a_new_array>) {
		print("a_new_array ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, array_length>) print("array_length");
	else if constexpr (same_as<Type, a_throw>) print("a_throw");
	else if constexpr (same_as<Type, check_cast>) {
		print("check_cast ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, instance_of>) {
		print("instance_of ");
		print((uint16) x.index);
	}
	else if constexpr (same_as<Type, monitor_enter>) {
		print("monitor_enter");
	}
	else if constexpr (same_as<Type, monitor_exit>) {
		print("monitor_exit");
	}
	else if constexpr (same_as<Type, wide_format_1>) {
		print("wide ");

		switch(x.other_code) {
			case i_load::code: print("i_load");
			case f_load::code: print("f_load");
			case a_load::code: print("a_load");
			case l_load::code: print("l_load");
			case d_load::code: print("d_load");

			case i_store::code: print("i_store");
			case f_store::code: print("f_store");
			case a_store::code: print("a_store");
			case l_store::code: print("l_store");
			case d_store::code: print("d_store");

			case return_sr::code: print("return_sr");
		}

		print(" ");
		print(x.index);
	}
	else if constexpr (same_as<Type, wide_format_2>) {
		print("wide ");
		print(x.index);
		print(" ");
		print(x.value);
	}
	else if constexpr (same_as<Type, multi_new_array>) {
		print("multi_new_array ");
		print(x.index);
		print(" ");
		print(x.dimensions);
	}
	else if constexpr (same_as<Type, if_null>) {
		print("if_null ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, if_non_null>) {
		print("if_non_null ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, goto_w>) {
		print("goto_w ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, jmp_sr_w>) {
		print("jmp_sr_w ");
		print(x.branch);
	}
	else if constexpr (same_as<Type, uint8>) {
		posix::std_err().write_from(c_string{ "unknown instruction: "});
		for_each_digit_in_number(x, 10, [](auto digit) {
			posix::std_err().write_from(array{ digit + '0' });
		});
		abort();
	}
	else {
		x.non_existent_function();
	}
}