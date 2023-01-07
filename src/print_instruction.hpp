#pragma once

#include "./const_pool.hpp"

#include <class_file/attribute/code/instruction.hpp>

#include <on_scope_exit.hpp>
#include <loop_action.hpp>
#include <c_string.hpp>
#include <number.hpp>
#include <array.hpp>

#include <posix/abort.hpp>

#include <print/print.hpp>

template<typename Type>
static void print_instruction(Type x, const_pool& const_pool) {

	using namespace class_file;
	using namespace attribute::code::instruction;

	on_scope_exit new_line_on_scope_exit{[](){
		print::out("\n");
	}};

	auto print_method_ref =
	[&]<same_as_any<
		constant::method_ref_index,
		constant::interface_method_ref_index
	> IndexType>(
		 IndexType index
	) {
		auto method_ref = const_pool[index];
		{
			constant::_class c = [&]() {
				if constexpr(
					same_as<IndexType, constant::method_ref_index>
				) { return const_pool[method_ref.class_index]; }
				if constexpr(
					same_as<IndexType, constant::interface_method_ref_index>
				) { return const_pool[method_ref.interface_index]; }
			}();
			constant::utf8 class_name = const_pool[c.name_index];
			print::out(class_name);
		}
		print::out(".");
		{
			constant::name_and_type nat
				= const_pool[method_ref.name_and_type_index];
			constant::utf8 name = const_pool[nat.name_index];
			constant::utf8 desc = const_pool[nat.descriptor_index];
			print::out(name, desc);
		}
	};

	auto print_field_ref =
	[&](constant::field_ref_index index) {
		auto method_ref = const_pool[index];
		{
			constant::_class c = const_pool[method_ref.class_index];
			constant::utf8 class_name = const_pool[c.name_index];
			print::out(class_name);
		}
		print::out(".");
		{
			constant::name_and_type nat
				= const_pool[method_ref.name_and_type_index];
			constant::utf8 name = const_pool[nat.name_index];
			constant::utf8 desc = const_pool[nat.descriptor_index];
			print::out(name, " ", desc);
		}
	};

	auto print_class_name =
	[&](constant::class_index index) {
		constant::_class c = const_pool[index];
		constant::utf8 name = const_pool[c.name_index];
		print::out(name);
	};

	if constexpr (same_as<Type, nop>) {
		print::out("nop");
	}

	else if constexpr (same_as<Type, a_const_null>)
		print::out("a_const_null");
	else if constexpr (same_as<Type, i_const_m1>) print::out("i_const_m1");
	else if constexpr (same_as<Type, i_const_0>) print::out("i_const_0");
	else if constexpr (same_as<Type, i_const_1>) print::out("i_const_1");
	else if constexpr (same_as<Type, i_const_2>) print::out("i_const_2");
	else if constexpr (same_as<Type, i_const_3>) print::out("i_const_3");
	else if constexpr (same_as<Type, i_const_4>) print::out("i_const_4");
	else if constexpr (same_as<Type, i_const_5>) print::out("i_const_5");
	else if constexpr (same_as<Type, l_const_0>) print::out("l_const_0");
	else if constexpr (same_as<Type, l_const_1>) print::out("l_const_1");
	else if constexpr (same_as<Type, f_const_0>) print::out("f_const_0");
	else if constexpr (same_as<Type, f_const_1>) print::out("f_const_1");
	else if constexpr (same_as<Type, f_const_2>) print::out("f_const_2");
	else if constexpr (same_as<Type, d_const_0>) print::out("d_const_0");
	else if constexpr (same_as<Type, d_const_1>) print::out("d_const_1");

	else if constexpr (same_as<Type, bi_push>) {
		print::out("bi_push ", x.value);
	}
	else if constexpr (same_as<Type, si_push>) {
		print::out("si_push ", x.value);
	}

	else if constexpr (same_as<Type, ldc>) {
		print::out("ldc ", (uint8) x.index);
	}
	else if constexpr (same_as<Type, ldc_w>) {
		print::out("ldc_w ", (uint16) x.index);
	}
	else if constexpr (same_as<Type, ldc_2_w>) {
		print::out("ldc_2_w ", (uint16) x.index);
	}

	else if constexpr (same_as<Type, i_load>) {
		print::out("i_load ", x.index);
	}
	else if constexpr (same_as<Type, l_load>) {
		print::out("l_load ", x.index);
	}
	else if constexpr (same_as<Type, f_load>) {
		print::out("f_load ", x.index);
	}
	else if constexpr (same_as<Type, d_load>) {
		print::out("d_load ", x.index);
	}
	else if constexpr (same_as<Type, a_load>) {
		print::out("a_load ", x.index);
	}
	else if constexpr (same_as<Type, i_load_0>) print::out("i_load_0");
	else if constexpr (same_as<Type, i_load_1>) print::out("i_load_1");
	else if constexpr (same_as<Type, i_load_2>) print::out("i_load_2");
	else if constexpr (same_as<Type, i_load_3>) print::out("i_load_3");
	else if constexpr (same_as<Type, l_load_0>) print::out("l_load_0");
	else if constexpr (same_as<Type, l_load_1>) print::out("l_load_1");
	else if constexpr (same_as<Type, l_load_2>) print::out("l_load_2");
	else if constexpr (same_as<Type, l_load_3>) print::out("l_load_3");
	else if constexpr (same_as<Type, f_load_0>) print::out("f_load_0");
	else if constexpr (same_as<Type, f_load_1>) print::out("f_load_1");
	else if constexpr (same_as<Type, f_load_2>) print::out("f_load_2");
	else if constexpr (same_as<Type, f_load_3>) print::out("f_load_3");
	else if constexpr (same_as<Type, d_load_0>) print::out("d_load_0");
	else if constexpr (same_as<Type, d_load_1>) print::out("d_load_1");
	else if constexpr (same_as<Type, d_load_2>) print::out("d_load_2");
	else if constexpr (same_as<Type, d_load_3>) print::out("d_load_3");
	else if constexpr (same_as<Type, a_load_0>) print::out("a_load_0");
	else if constexpr (same_as<Type, a_load_1>) print::out("a_load_1");
	else if constexpr (same_as<Type, a_load_2>) print::out("a_load_2");
	else if constexpr (same_as<Type, a_load_3>) print::out("a_load_3");
	else if constexpr (same_as<Type, i_a_load>) print::out("i_a_load");
	else if constexpr (same_as<Type, l_a_load>) print::out("l_a_load");
	else if constexpr (same_as<Type, f_a_load>) print::out("f_a_load");
	else if constexpr (same_as<Type, d_a_load>) print::out("d_a_load");
	else if constexpr (same_as<Type, a_a_load>) print::out("a_a_load");
	else if constexpr (same_as<Type, b_a_load>) print::out("b_a_load");
	else if constexpr (same_as<Type, c_a_load>) print::out("c_a_load");
	else if constexpr (same_as<Type, s_a_load>) print::out("s_a_load");

	else if constexpr (same_as<Type, i_store>) {
		print::out("i_store ", x.index);
	}
	else if constexpr (same_as<Type, l_store>) {
		print::out("l_store ", x.index);
	}
	else if constexpr (same_as<Type, f_store>) {
		print::out("f_store ", x.index);
	}
	else if constexpr (same_as<Type, d_store>) {
		print::out("d_store ", x.index);
	}
	else if constexpr (same_as<Type, a_store>) {
		print::out("a_store ", x.index);
	}
	else if constexpr (same_as<Type, i_store_0>) print::out("i_store_0");
	else if constexpr (same_as<Type, i_store_1>) print::out("i_store_1");
	else if constexpr (same_as<Type, i_store_2>) print::out("i_store_2");
	else if constexpr (same_as<Type, i_store_3>) print::out("i_store_3");
	else if constexpr (same_as<Type, l_store_0>) print::out("l_store_0");
	else if constexpr (same_as<Type, l_store_1>) print::out("l_store_1");
	else if constexpr (same_as<Type, l_store_2>) print::out("l_store_2");
	else if constexpr (same_as<Type, l_store_3>) print::out("l_store_3");
	else if constexpr (same_as<Type, f_store_0>) print::out("f_store_0");
	else if constexpr (same_as<Type, f_store_1>) print::out("f_store_1");
	else if constexpr (same_as<Type, f_store_2>) print::out("f_store_2");
	else if constexpr (same_as<Type, f_store_3>) print::out("f_store_3");
	else if constexpr (same_as<Type, d_store_0>) print::out("d_store_0");
	else if constexpr (same_as<Type, d_store_1>) print::out("d_store_1");
	else if constexpr (same_as<Type, d_store_2>) print::out("d_store_2");
	else if constexpr (same_as<Type, d_store_3>) print::out("d_store_3");
	else if constexpr (same_as<Type, a_store_0>) print::out("a_store_0");
	else if constexpr (same_as<Type, a_store_1>) print::out("a_store_1");
	else if constexpr (same_as<Type, a_store_2>) print::out("a_store_2");
	else if constexpr (same_as<Type, a_store_3>) print::out("a_store_3");
	else if constexpr (same_as<Type, i_a_store>) print::out("i_a_store");
	else if constexpr (same_as<Type, l_a_store>) print::out("l_a_store");
	else if constexpr (same_as<Type, f_a_store>) print::out("f_a_store");
	else if constexpr (same_as<Type, d_a_store>) print::out("d_a_store");
	else if constexpr (same_as<Type, a_a_store>) print::out("a_a_store");
	else if constexpr (same_as<Type, b_a_store>) print::out("b_a_store");
	else if constexpr (same_as<Type, c_a_store>) print::out("c_a_store");
	else if constexpr (same_as<Type, s_a_store>) print::out("s_a_store");

	else if constexpr (same_as<Type, pop>) print::out("pop");
	else if constexpr (same_as<Type, pop_2>) print::out("pop_2");
	else if constexpr (same_as<Type, dup>) print::out("dup");
	else if constexpr (same_as<Type, dup_x1>) print::out("dup_x1");
	else if constexpr (same_as<Type, dup_x2>) print::out("dup_x2");
	else if constexpr (same_as<Type, dup_2>) print::out("dup_2");
	else if constexpr (same_as<Type, dup_2_x1>) print::out("dup_2_x1");
	else if constexpr (same_as<Type, dup_2_x2>) print::out("dup_2_x2");
	else if constexpr (same_as<Type, swap>) print::out("swap");

	else if constexpr (same_as<Type, i_add>) print::out("i_add");
	else if constexpr (same_as<Type, l_add>) print::out("l_add");
	else if constexpr (same_as<Type, f_add>) print::out("f_add");
	else if constexpr (same_as<Type, d_add>) print::out("d_add");
	else if constexpr (same_as<Type, i_sub>) print::out("i_sub");
	else if constexpr (same_as<Type, l_sub>) print::out("l_sub");
	else if constexpr (same_as<Type, f_sub>) print::out("f_sub");
	else if constexpr (same_as<Type, d_sub>) print::out("d_sub");
	else if constexpr (same_as<Type, i_mul>) print::out("i_mul");
	else if constexpr (same_as<Type, l_mul>) print::out("l_mul");
	else if constexpr (same_as<Type, f_mul>) print::out("f_mul");
	else if constexpr (same_as<Type, d_mul>) print::out("d_mul");
	else if constexpr (same_as<Type, i_div>) print::out("i_div");
	else if constexpr (same_as<Type, l_div>) print::out("l_div");
	else if constexpr (same_as<Type, f_div>) print::out("f_div");
	else if constexpr (same_as<Type, d_div>) print::out("d_div");
	else if constexpr (same_as<Type, i_rem>) print::out("i_rem");
	else if constexpr (same_as<Type, l_rem>) print::out("l_rem");
	else if constexpr (same_as<Type, f_rem>) print::out("f_rem");
	else if constexpr (same_as<Type, d_rem>) print::out("d_rem");
	else if constexpr (same_as<Type, i_neg>) print::out("i_neg");
	else if constexpr (same_as<Type, l_neg>) print::out("l_neg");
	else if constexpr (same_as<Type, f_neg>) print::out("f_neg");
	else if constexpr (same_as<Type, d_neg>) print::out("d_neg");
	else if constexpr (same_as<Type, i_sh_l>) print::out("i_sh_l");
	else if constexpr (same_as<Type, l_sh_l>) print::out("l_sh_l");
	else if constexpr (same_as<Type, i_sh_r>) print::out("i_sh_r");
	else if constexpr (same_as<Type, l_sh_r>) print::out("l_sh_r");
	else if constexpr (same_as<Type, i_u_sh_r>) print::out("i_u_sh_r");
	else if constexpr (same_as<Type, l_u_sh_r>) print::out("l_u_sh_r");
	else if constexpr (same_as<Type, i_and>) print::out("i_and");
	else if constexpr (same_as<Type, l_and>) print::out("l_and");
	else if constexpr (same_as<Type, i_or>) print::out("i_or");
	else if constexpr (same_as<Type, l_or>) print::out("l_or");
	else if constexpr (same_as<Type, i_xor>) print::out("i_xor");
	else if constexpr (same_as<Type, l_xor>) print::out("l_xor");
	else if constexpr (same_as<Type, i_inc>) {
		print::out("iinc ", x.index, ", ", x.value);
	}
	else if constexpr (same_as<Type, i_to_l>) print::out("i_to_l");
	else if constexpr (same_as<Type, i_to_f>) print::out("i_to_f");
	else if constexpr (same_as<Type, i_to_d>) print::out("i_to_d");
	else if constexpr (same_as<Type, l_to_i>) print::out("l_to_i");
	else if constexpr (same_as<Type, l_to_f>) print::out("l_to_f");
	else if constexpr (same_as<Type, l_to_d>) print::out("l_to_d");
	else if constexpr (same_as<Type, f_to_i>) print::out("f_to_i");
	else if constexpr (same_as<Type, f_to_l>) print::out("f_to_l");
	else if constexpr (same_as<Type, f_to_d>) print::out("f_to_d");
	else if constexpr (same_as<Type, d_to_i>) print::out("d_to_i");
	else if constexpr (same_as<Type, d_to_l>) print::out("d_to_l");
	else if constexpr (same_as<Type, d_to_f>) print::out("d_to_f");
	else if constexpr (same_as<Type, i_to_b>) print::out("i_to_b");
	else if constexpr (same_as<Type, i_to_c>) print::out("i_to_c");
	else if constexpr (same_as<Type, i_to_s>) print::out("i_to_s");

	else if constexpr (same_as<Type, l_cmp>) print::out("l_cmp");

	else if constexpr (same_as<Type, f_cmp_l>) print::out("f_cmp_l");
	else if constexpr (same_as<Type, f_cmp_g>) print::out("f_cmp_g");
	else if constexpr (same_as<Type, d_cmp_l>) print::out("d_cmp_l");
	else if constexpr (same_as<Type, d_cmp_g>) print::out("d_cmp_g");

	else if constexpr (same_as<Type, if_eq>) {
		print::out("if_eq ", x.branch);
	}
	else if constexpr (same_as<Type, if_ne>) {
		print::out("if_ne ", x.branch);
	}
	else if constexpr (same_as<Type, if_lt>) {
		print::out("if_lt ", x.branch);
	}
	else if constexpr (same_as<Type, if_ge>) {
		print::out("if_ge ", x.branch);
	}
	else if constexpr (same_as<Type, if_gt>) {
		print::out("if_gt ", x.branch);
	}
	else if constexpr (same_as<Type, if_le>) {
		print::out("if_le ", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_eq>) {
		print::out("if_i_cmp_eq ", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_ne>) {
		print::out("if_i_cmp_ne ", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_lt>) {
		print::out("if_i_cmp_lt ", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_ge>) {
		print::out("if_i_cmp_ge ", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_gt>) {
		print::out("if_i_cmp_gt ", x.branch);
	}
	else if constexpr (same_as<Type, if_i_cmp_le>) {
		print::out("if_i_cmp_le ", x.branch);
	}
	else if constexpr (same_as<Type, if_a_cmp_eq>) {
		print::out("if_a_cmp_eq ", x.branch);
	}
	else if constexpr (same_as<Type, if_a_cmp_ne>) {
		print::out("if_a_cmp_ne ", x.branch);
	}
	else if constexpr (same_as<Type, go_to>) {
		print::out("goto ", x.branch);
	}
	else if constexpr (same_as<Type, jmp_sr>) {
		print::out("jmp_sr ", x.branch);
	}
	else if constexpr (same_as<Type, return_sr>) {
		print::out("return_sr ", x.index);
	}
	else if constexpr (same_as<Type, table_switch>) {
		print::out("table_switch ", x._default);
		for(auto p : x.offsets) {
			print::out(" ", p);
		}
	}
	else if constexpr (same_as<Type, lookup_switch>) {
		print::out("lookup_switch ", x._default);
		for(auto p : x.pairs) {
			print::out(" ", p.match, ":", p.offset);
		}
	}
	else if constexpr (same_as<Type, i_return>) {
		print::out("i_return");
	}
	else if constexpr (same_as<Type, l_return>) {
		print::out("l_return");
	}
	else if constexpr (same_as<Type, f_return>) {
		print::out("f_return");
	}
	else if constexpr (same_as<Type, d_return>) {
		print::out("d_return");
	}
	else if constexpr (same_as<Type, a_return>) {
		print::out("a_return");
	}
	else if constexpr (same_as<Type, _return>) {
		print::out("return");
	}

	else if constexpr (same_as<Type, get_static>) {
		print::out("get_static ");
		print_field_ref(x.index);
	}
	else if constexpr (same_as<Type, put_static>) {
		print::out("put_static ");
		print_field_ref(x.index);
	}
	else if constexpr (same_as<Type, get_field>) {
		print::out("get_field ");
		print_field_ref(x.index);
	}
	else if constexpr (same_as<Type, put_field>) {
		print::out("put_field ");
		print_field_ref(x.index);
	}
	else if constexpr (same_as<Type, invoke_virtual>) {
		print::out("invoke_virtual ");
		print_method_ref(x.index);
	}
	else if constexpr (same_as<Type, invoke_special>) {
		print::out("invoke_special ");
		print_method_ref(x.index);
	}
	else if constexpr (same_as<Type, invoke_static>) {
		print::out("invoke_static ");
		print_method_ref(x.index);
	}
	else if constexpr (same_as<Type, invoke_interface>) {
		print::out("invoke_interface ", (uint16) x.index);
		print_method_ref(x.index);
	}
	else if constexpr (same_as<Type, invoke_dynamic>) {
		print::out("invoked_ynamic ", (uint16) x.index);
	}
	else if constexpr (same_as<Type, _new>) {
		print::out("new ");
		print_class_name(x.index);
	}
	else if constexpr (same_as<Type, new_array>) {
		print::out("new_array ", (uint8) x.type);
	}
	else if constexpr (same_as<Type, a_new_array>) {
		print::out("a_new_array ");
		print_class_name(x.index);
	}
	else if constexpr (same_as<Type, array_length>) print::out("array_length");
	else if constexpr (same_as<Type, a_throw>) print::out("a_throw");
	else if constexpr (same_as<Type, check_cast>) {
		print::out("check_cast ");
		print_class_name(x.index);
	}
	else if constexpr (same_as<Type, instance_of>) {
		print::out("instance_of ");
		print_class_name(x.index);
	}
	else if constexpr (same_as<Type, monitor_enter>) {
		print::out("monitor_enter");
	}
	else if constexpr (same_as<Type, monitor_exit>) {
		print::out("monitor_exit");
	}
	else if constexpr (same_as<Type, wide_format_1>) {
		print::out("wide ");

		switch(x.other_code) {
			case i_load::code: print::out("i_load");
			case f_load::code: print::out("f_load");
			case a_load::code: print::out("a_load");
			case l_load::code: print::out("l_load");
			case d_load::code: print::out("d_load");

			case i_store::code: print::out("i_store");
			case f_store::code: print::out("f_store");
			case a_store::code: print::out("a_store");
			case l_store::code: print::out("l_store");
			case d_store::code: print::out("d_store");

			case return_sr::code: print::out("return_sr");
		}

		print::out(" ");
		print::out(x.index);
	}
	else if constexpr (same_as<Type, wide_format_2>) {
		print::out("wide ", x.index, " ", x.value);
	}
	else if constexpr (same_as<Type, multi_new_array>) {
		print::out("multi_new_array ", x.index, " ", x.dimensions);
	}
	else if constexpr (same_as<Type, if_null>) {
		print::out("if_null ", x.branch);
	}
	else if constexpr (same_as<Type, if_non_null>) {
		print::out("if_non_null ", x.branch);
	}
	else if constexpr (same_as<Type, go_to_w>) {
		print::out("go_to_w ", x.branch);
	}
	else if constexpr (same_as<Type, jmp_sr_w>) {
		print::out("jmp_sr_w ", x.branch);
	}
	else if constexpr (same_as<Type, unknown>) {
		print::err("unknown instruction: ", x.code);
		posix::abort();
	}
	else {
		x.non_existent_function();
	}
}