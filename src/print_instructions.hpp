#pragma once

#include "abort.hpp"
#include <class/file/code/instruction.hpp>
#include <core/on_scope_exit.hpp>
#include <core/loop_action.hpp>
#include <stdio.h>

template<typename Type>
static void print_instructions(Type x) {
	using namespace class_file::code::instruction;

	on_scope_exit new_line_on_scope_exit{[](){
		putchar('\n');
	}};

	if constexpr (same_as<Type, nop>) fputs("nop", stdout);

	else if constexpr (same_as<Type, a_const_null>) fputs("a_const_null", stdout);
	else if constexpr (same_as<Type, i_const_m1>) fputs("i_const_m1", stdout);
	else if constexpr (same_as<Type, i_const_0>) fputs("i_const_0", stdout);
	else if constexpr (same_as<Type, i_const_1>) fputs("i_const_1", stdout);
	else if constexpr (same_as<Type, i_const_2>) fputs("i_const_2", stdout);
	else if constexpr (same_as<Type, i_const_3>) fputs("i_const_3", stdout);
	else if constexpr (same_as<Type, i_const_4>) fputs("i_const_4", stdout);
	else if constexpr (same_as<Type, i_const_5>) fputs("i_const_5", stdout);
	else if constexpr (same_as<Type, l_const_0>) fputs("l_const_0", stdout);
	else if constexpr (same_as<Type, l_const_1>) fputs("l_const_1", stdout);
	else if constexpr (same_as<Type, f_const_0>) fputs("f_const_0", stdout);
	else if constexpr (same_as<Type, f_const_1>) fputs("f_const_1", stdout);
	else if constexpr (same_as<Type, f_const_2>) fputs("f_const_2", stdout);
	else if constexpr (same_as<Type, d_const_0>) fputs("d_const_0", stdout);
	else if constexpr (same_as<Type, d_const_1>) fputs("d_const_1", stdout);

	else if constexpr (same_as<Type, bi_push>) {
		fputs("bi_push ", stdout);
		printf("%hhu", x.value);
	}
	else if constexpr (same_as<Type, si_push>) {
		fputs("si_push ", stdout);
		printf("%hu", x.value);
	}

	else if constexpr (same_as<Type, ldc>) {
		fputs("ldc ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, ldc_w>) {
		fputs("ldc_w ", stdout);
		printf("%hu", x.index);
	}
	else if constexpr (same_as<Type, ldc_2_w>) {
		fputs("ldc_2_w ", stdout);
		printf("%hu", x.index);
	}

	else if constexpr (same_as<Type, i_load>) {
		fputs("i_load ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, l_load>) {
		fputs("l_load ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, f_load>) {
		fputs("f_load ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, d_load>) {
		fputs("d_load ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, a_load>) {
		fputs("a_load ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, i_load_0>) fputs("i_load_0", stdout);
	else if constexpr (same_as<Type, i_load_1>) fputs("i_load_1", stdout);
	else if constexpr (same_as<Type, i_load_2>) fputs("i_load_2", stdout);
	else if constexpr (same_as<Type, i_load_3>) fputs("i_load_3", stdout);
	else if constexpr (same_as<Type, l_load_0>) fputs("l_load_0", stdout);
	else if constexpr (same_as<Type, l_load_1>) fputs("l_load_1", stdout);
	else if constexpr (same_as<Type, l_load_2>) fputs("l_load_2", stdout);
	else if constexpr (same_as<Type, l_load_3>) fputs("l_load_3", stdout);
	else if constexpr (same_as<Type, f_load_0>) fputs("f_load_0", stdout);
	else if constexpr (same_as<Type, f_load_1>) fputs("f_load_1", stdout);
	else if constexpr (same_as<Type, f_load_2>) fputs("f_load_2", stdout);
	else if constexpr (same_as<Type, f_load_3>) fputs("f_load_3", stdout);
	else if constexpr (same_as<Type, d_load_0>) fputs("d_load_0", stdout);
	else if constexpr (same_as<Type, d_load_1>) fputs("d_load_1", stdout);
	else if constexpr (same_as<Type, d_load_2>) fputs("d_load_2", stdout);
	else if constexpr (same_as<Type, d_load_3>) fputs("d_load_3", stdout);
	else if constexpr (same_as<Type, a_load_0>) fputs("a_load_0", stdout);
	else if constexpr (same_as<Type, a_load_1>) fputs("a_load_1", stdout);
	else if constexpr (same_as<Type, a_load_2>) fputs("a_load_2", stdout);
	else if constexpr (same_as<Type, a_load_3>) fputs("a_load_3", stdout);
	else if constexpr (same_as<Type, i_a_load>) fputs("i_a_load", stdout);
	else if constexpr (same_as<Type, l_a_load>) fputs("l_a_load", stdout);
	else if constexpr (same_as<Type, f_a_load>) fputs("f_a_load", stdout);
	else if constexpr (same_as<Type, d_a_load>) fputs("d_a_load", stdout);
	else if constexpr (same_as<Type, a_a_load>) fputs("a_a_load", stdout);
	else if constexpr (same_as<Type, b_a_load>) fputs("b_a_load", stdout);
	else if constexpr (same_as<Type, c_a_load>) fputs("c_a_load", stdout);
	else if constexpr (same_as<Type, s_a_load>) fputs("s_a_load", stdout);

	else if constexpr (same_as<Type, i_store>) {
		fputs("i_store ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, l_store>) {
		fputs("l_store ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, f_store>) {
		fputs("f_store ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, d_store>) {
		fputs("d_store ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, a_store>) {
		fputs("a_store ", stdout);
		printf("%hhu", x.index);
	}
	else if constexpr (same_as<Type, i_store_0>) fputs("i_store_0", stdout);
	else if constexpr (same_as<Type, i_store_1>) fputs("i_store_1", stdout);
	else if constexpr (same_as<Type, i_store_2>) fputs("i_store_2", stdout);
	else if constexpr (same_as<Type, i_store_3>) fputs("i_store_3", stdout);
	else if constexpr (same_as<Type, l_store_0>) fputs("l_store_0", stdout);
	else if constexpr (same_as<Type, l_store_1>) fputs("l_store_1", stdout);
	else if constexpr (same_as<Type, l_store_2>) fputs("l_store_2", stdout);
	else if constexpr (same_as<Type, l_store_3>) fputs("l_store_3", stdout);
	else if constexpr (same_as<Type, f_store_0>) fputs("f_store_0", stdout);
	else if constexpr (same_as<Type, f_store_1>) fputs("f_store_1", stdout);
	else if constexpr (same_as<Type, f_store_2>) fputs("f_store_2", stdout);
	else if constexpr (same_as<Type, f_store_3>) fputs("f_store_3", stdout);
	else if constexpr (same_as<Type, d_store_0>) fputs("d_store_0", stdout);
	else if constexpr (same_as<Type, d_store_1>) fputs("d_store_1", stdout);
	else if constexpr (same_as<Type, d_store_2>) fputs("d_store_2", stdout);
	else if constexpr (same_as<Type, d_store_3>) fputs("d_store_3", stdout);
	else if constexpr (same_as<Type, a_store_0>) fputs("a_store_0", stdout);
	else if constexpr (same_as<Type, a_store_1>) fputs("a_store_1", stdout);
	else if constexpr (same_as<Type, a_store_2>) fputs("a_store_2", stdout);
	else if constexpr (same_as<Type, a_store_3>) fputs("a_store_3", stdout);
	else if constexpr (same_as<Type, i_a_store>) fputs("i_a_store", stdout);
	else if constexpr (same_as<Type, l_a_store>) fputs("l_a_store", stdout);
	else if constexpr (same_as<Type, f_a_store>) fputs("f_a_store", stdout);
	else if constexpr (same_as<Type, d_a_store>) fputs("d_a_store", stdout);
	else if constexpr (same_as<Type, a_a_store>) fputs("a_a_store", stdout);
	else if constexpr (same_as<Type, b_a_store>) fputs("b_a_store", stdout);
	else if constexpr (same_as<Type, c_a_store>) fputs("c_a_store", stdout);
	else if constexpr (same_as<Type, s_a_store>) fputs("s_a_store", stdout);

	else if constexpr (same_as<Type, pop>) fputs("pop", stdout);
	else if constexpr (same_as<Type, pop_2>) fputs("pop_2", stdout);
	else if constexpr (same_as<Type, dup>) fputs("dup", stdout);
	else if constexpr (same_as<Type, dup_x1>) fputs("dup_x1", stdout);
	else if constexpr (same_as<Type, dup_x2>) fputs("dup_x2", stdout);
	else if constexpr (same_as<Type, dup_2>) fputs("dup_2", stdout);
	else if constexpr (same_as<Type, dup_2_x1>) fputs("dup_2_x1", stdout);
	else if constexpr (same_as<Type, dup_2_x2>) fputs("dup_2_x2", stdout);
	else if constexpr (same_as<Type, swap>) fputs("swap", stdout);

	else if constexpr (same_as<Type, i_add>) fputs("i_add", stdout);
	else if constexpr (same_as<Type, l_add>) fputs("l_add", stdout);
	else if constexpr (same_as<Type, f_add>) fputs("f_add", stdout);
	else if constexpr (same_as<Type, d_add>) fputs("d_add", stdout);
	else if constexpr (same_as<Type, i_sub>) fputs("i_sub", stdout);
	else if constexpr (same_as<Type, l_sub>) fputs("l_sub", stdout);
	else if constexpr (same_as<Type, f_sub>) fputs("f_sub", stdout);
	else if constexpr (same_as<Type, d_sub>) fputs("d_sub", stdout);
	else if constexpr (same_as<Type, i_mul>) fputs("i_mul", stdout);
	else if constexpr (same_as<Type, l_mul>) fputs("l_mul", stdout);
	else if constexpr (same_as<Type, f_mul>) fputs("f_mul", stdout);
	else if constexpr (same_as<Type, d_mul>) fputs("d_mul", stdout);
	else if constexpr (same_as<Type, i_div>) fputs("i_div", stdout);
	else if constexpr (same_as<Type, l_div>) fputs("l_div", stdout);
	else if constexpr (same_as<Type, f_div>) fputs("f_div", stdout);
	else if constexpr (same_as<Type, d_div>) fputs("d_div", stdout);
	else if constexpr (same_as<Type, i_rem>) fputs("i_rem", stdout);
	else if constexpr (same_as<Type, l_rem>) fputs("l_rem", stdout);
	else if constexpr (same_as<Type, f_rem>) fputs("f_rem", stdout);
	else if constexpr (same_as<Type, d_rem>) fputs("d_rem", stdout);
	else if constexpr (same_as<Type, i_neg>) fputs("i_neg", stdout);
	else if constexpr (same_as<Type, l_neg>) fputs("l_neg", stdout);
	else if constexpr (same_as<Type, f_neg>) fputs("f_neg", stdout);
	else if constexpr (same_as<Type, d_neg>) fputs("d_neg", stdout);
	else if constexpr (same_as<Type, i_sh_l>) fputs("i_sh_l", stdout);
	else if constexpr (same_as<Type, l_sh_l>) fputs("l_sh_l", stdout);
	else if constexpr (same_as<Type, i_sh_r>) fputs("i_sh_r", stdout);
	else if constexpr (same_as<Type, l_sh_r>) fputs("l_sh_r", stdout);
	else if constexpr (same_as<Type, i_u_sh_r>) fputs("i_u_sh_r", stdout);
	else if constexpr (same_as<Type, l_u_sh_r>) fputs("l_u_sh_r", stdout);
	else if constexpr (same_as<Type, i_and>) fputs("i_and", stdout);
	else if constexpr (same_as<Type, l_and>) fputs("l_and", stdout);
	else if constexpr (same_as<Type, i_or>) fputs("i_or", stdout);
	else if constexpr (same_as<Type, l_or>) fputs("l_or", stdout);
	else if constexpr (same_as<Type, i_xor>) fputs("i_xor", stdout);
	else if constexpr (same_as<Type, l_xor>) fputs("l_xor", stdout);
	else if constexpr (same_as<Type, i_inc>) {
		printf("iinc ", stdout);
		printf("%hhu, %hhd", x.index, x.value);
	}
	else if constexpr (same_as<Type, i_to_l>) fputs("i_to_l", stdout);
	else if constexpr (same_as<Type, i_to_f>) fputs("i_to_f", stdout);
	else if constexpr (same_as<Type, i_to_d>) fputs("i_to_d", stdout);
	else if constexpr (same_as<Type, l_to_i>) fputs("l_to_i", stdout);
	else if constexpr (same_as<Type, l_to_f>) fputs("l_to_f", stdout);
	else if constexpr (same_as<Type, l_to_d>) fputs("l_to_d", stdout);
	else if constexpr (same_as<Type, f_to_i>) fputs("f_to_i", stdout);
	else if constexpr (same_as<Type, f_to_l>) fputs("f_to_l", stdout);
	else if constexpr (same_as<Type, f_to_d>) fputs("f_to_d", stdout);
	else if constexpr (same_as<Type, d_to_i>) fputs("d_to_i", stdout);
	else if constexpr (same_as<Type, d_to_l>) fputs("d_to_l", stdout);
	else if constexpr (same_as<Type, d_to_f>) fputs("d_to_f", stdout);
	else if constexpr (same_as<Type, i_to_b>) fputs("i_to_b", stdout);
	else if constexpr (same_as<Type, i_to_c>) fputs("i_to_c", stdout);
	else if constexpr (same_as<Type, i_to_s>) fputs("i_to_s", stdout);

	else if constexpr (same_as<Type, l_cmp>) fputs("l_cmp", stdout);

	else if constexpr (same_as<Type, f_cmp_l>) fputs("f_cmp_l", stdout);
	else if constexpr (same_as<Type, f_cmp_g>) fputs("f_cmp_g", stdout);
	else if constexpr (same_as<Type, d_cmp_l>) fputs("d_cmp_l", stdout);
	else if constexpr (same_as<Type, d_cmp_g>) fputs("d_cmp_g", stdout);

	else if constexpr (same_as<Type, if_eq>) {
		fputs("if_eq ", stdout);
		printf("%hd", x.branch);
	}
	else if constexpr (same_as<Type, if_ne>) {
		fputs("if_ne ", stdout);
		printf("%hd", x.branch);
	}
	else if constexpr (same_as<Type, if_lt>) {
		fputs("if_lt ", stdout);
		printf("%hd", x.branch);
	}
	else if constexpr (same_as<Type, if_ge>) {
		fputs("if_ge ", stdout);
		printf("%hd", x.branch);
	}
	else if constexpr (same_as<Type, if_gt>) {
		fputs("if_gt ", stdout);
		printf("%hd", x.branch);
	}
	else if constexpr (same_as<Type, if_le>) {
		fputs("if_le ", stdout);
		printf("%hd", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_eq>) {
		printf("if_i_cmp_eq %hd", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_ne>) {
		printf("if_i_cmp_ne %hd", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_lt>) {
		printf("if_i_cmp_lt %hd", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_ge>) {
		printf("if_i_cmp_ge %hd", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_gt>) {
		printf("if_i_cmp_gt %hd", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_le>) {
		printf("if_i_cmp_le %hd", x.branch);
	}
	else if constexpr (same_as<Type, if_a_cmp_eq>) {
		printf("if_a_cmp_eq %hd", x.branch);
	}
	else if constexpr (same_as<Type, if_a_cmp_ne>) {
		printf("if_a_cmp_ne %hd", x.branch);
	}
	else if constexpr (same_as<Type, go_to>) {
		printf("goto %hd", x.branch);
	}
	else if constexpr (same_as<Type, jmp_sr>) {
		printf("jmp_sr %hd", x.branch);
	}
	else if constexpr (same_as<Type, return_sr>) {
		printf("return_sr %hhu", x.index);
	}
	else if constexpr (same_as<Type, table_switch>) {
		printf("table_switch %d", x._default);
		for(auto p : x.offsets) {
			printf(" %d", p);
		}
	}
	else if constexpr (same_as<Type, lookup_switch>) {
		printf("lookup_switch %d", x._default);
		for(auto p : x.pairs) {
			printf(" %d:%d", p.match, p.offset);
		}
	}
	else if constexpr (same_as<Type, i_return>) {
		fputs("i_return", stdout);
	}
	else if constexpr (same_as<Type, l_return>) {
		fputs("l_return", stdout);
	}
	else if constexpr (same_as<Type, f_return>) {
		fputs("f_return", stdout);
	}
	else if constexpr (same_as<Type, d_return>) {
		fputs("d_return", stdout);
	}
	else if constexpr (same_as<Type, a_return>) {
		fputs("a_return", stdout);
	}
	else if constexpr (same_as<Type, _return>) {
		fputs("return", stdout);
	}

	else if constexpr (same_as<Type, get_static>) {
		printf("get_static %hu", x.index);
	}
	else if constexpr (same_as<Type, put_static>) {
		printf("put_static %hu", x.index);
	}
	else if constexpr (same_as<Type, get_field>) {
		printf("get_field %hu", x.index);
	}
	else if constexpr (same_as<Type, put_field>) {
		printf("put_field %hu", x.index);
	}
	else if constexpr (same_as<Type, invoke_virtual>) {
		printf("invoke_virtual %hu", x.index);
	}
	else if constexpr (same_as<Type, invoke_special>) {
		printf("invoke_special %hu", x.index);
	}
	else if constexpr (same_as<Type, invoke_static>) {
		printf("invoke_static %hu", x.index);
	}
	else if constexpr (same_as<Type, invoke_interface>) {
		printf("invoke_interface %hu %hhu", x.index, x.count);
	}
	else if constexpr (same_as<Type, invoke_dynamic>) {
		printf("invoked_ynamic %hu", x.index);
	}
	else if constexpr (same_as<Type, _new>) printf("new %hu", x.index);
	else if constexpr (same_as<Type, new_array>) {
		printf("new_array %hhu", x.type);
	}
	else if constexpr (same_as<Type, a_new_array>) {
		printf("a_new_array %hu", x.index);
	}
	else if constexpr (same_as<Type, array_length>) printf("array_length");
	else if constexpr (same_as<Type, a_throw>) printf("a_throw");
	else if constexpr (same_as<Type, check_cast>) {
		printf("check_cast %hu", x.index);
	}
	else if constexpr (same_as<Type, instance_of>) {
		printf("instance_of %hu", x.index);
	}
	else if constexpr (same_as<Type, monitor_enter>) {
		fputs("monitor_enter", stdout);
	}
	else if constexpr (same_as<Type, monitor_exit>) {
		fputs("monitor_exit", stdout);
	}
	else if constexpr (same_as<Type, wide_format_1>) {
		fputs("wide ", stdout);

		switch(x.other_code) {
			case i_load::code: fputs("i_load", stdout);
			case f_load::code: fputs("f_load", stdout);
			case a_load::code: fputs("a_load", stdout);
			case l_load::code: fputs("l_load", stdout);
			case d_load::code: fputs("d_load", stdout);

			case i_store::code: fputs("i_store", stdout);
			case f_store::code: fputs("f_store", stdout);
			case a_store::code: fputs("a_store", stdout);
			case l_store::code: fputs("l_store", stdout);
			case d_store::code: fputs("d_store", stdout);

			case return_sr::code: fputs("return_sr", stdout);
		}

		fprintf(stdout, " %hu", x.index);
	}
	else if constexpr (same_as<Type, wide_format_2>) {
		fprintf(stdout, "wide %hu %hu", x.index, x.value);
	}
	else if constexpr (same_as<Type, multi_new_array>) {
		fprintf(stdout, "multi_new_array %hu %hhu", x.index, x.dimensions);
	}
	else if constexpr (same_as<Type, if_null>) {
		printf("if_null %hu", x.branch);
	}
	else if constexpr (same_as<Type, if_non_null>) {
		printf("if_non_null %hu", x.branch);
	}
	else if constexpr (same_as<Type, goto_w>) {
		fprintf(stdout, "goto_w %u", x.branch);
	}
	else if constexpr (same_as<Type, jmp_sr_w>) {
		fprintf(stdout, "jmp_sr_w %u", x.branch);
	}
	else if constexpr (same_as<Type, uint8>) {
		printf("unknown instruction: %hhu\n", x);
		abort();
	}
	else {
		x.non_existent_function();
	}
}