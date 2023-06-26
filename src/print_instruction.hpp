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

using namespace class_file;
using namespace class_file::attribute::code::instruction;

struct print_instruction {

	const_pool& const_pool;

	template<
		same_as_any<
			constant::method_ref_index,
			constant::interface_method_ref_index
		> IndexType
	>
	void print_method_ref(IndexType index) {
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
			print::out(name, desc);
		}
	};

	void print_field_ref(constant::field_ref_index index) {
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

	void print_class_name(constant::class_index index) {
		constant::_class c = const_pool[index];
		constant::utf8 name = const_pool[c.name_index];
		print::out(name);
	};

	void operator () (nop) { print::out("nop"); }

	void operator () (a_const_null) { print::out("a_const_null"); }
	void operator () (i_const_m1) { print::out("i_const_m1"); }
	void operator () (i_const_0) { print::out("i_const_0"); }
	void operator () (i_const_1) { print::out("i_const_1"); }
	void operator () (i_const_2) { print::out("i_const_2"); }
	void operator () (i_const_3) { print::out("i_const_3"); }
	void operator () (i_const_4) { print::out("i_const_4"); }
	void operator () (i_const_5) { print::out("i_const_5"); }
	void operator () (l_const_0) { print::out("l_const_0"); }
	void operator () (l_const_1) { print::out("l_const_1"); }
	void operator () (f_const_0) { print::out("f_const_0"); }
	void operator () (f_const_1) { print::out("f_const_1"); }
	void operator () (f_const_2) { print::out("f_const_2"); }
	void operator () (d_const_0) { print::out("d_const_0"); }
	void operator () (d_const_1) { print::out("d_const_1"); }

	void operator () (bi_push x) { print::out("bi_push ", x.value); }
	void operator () (si_push x) { print::out("si_push ", x.value); }

	void operator () (ldc x) { print::out("ldc ", (uint8) x.index); }
	void operator () (ldc_w x) { print::out("ldc_w ", (uint16) x.index); }
	void operator () (ldc_2_w x) { print::out("ldc_2_w ", (uint16) x.index); }

	void operator () (i_load x) { print::out("i_load ", x.index); }
	void operator () (l_load x) { print::out("l_load ", x.index); }
	void operator () (f_load x) { print::out("f_load ", x.index); }
	void operator () (d_load x) { print::out("d_load ", x.index); }
	void operator () (a_load x) { print::out("a_load ", x.index); }
	void operator () (i_load_0) { print::out("i_load_0"); }
	void operator () (i_load_1) { print::out("i_load_1"); }
	void operator () (i_load_2) { print::out("i_load_2"); }
	void operator () (i_load_3) { print::out("i_load_3"); }
	void operator () (l_load_0) { print::out("l_load_0"); }
	void operator () (l_load_1) { print::out("l_load_1"); }
	void operator () (l_load_2) { print::out("l_load_2"); }
	void operator () (l_load_3) { print::out("l_load_3"); }
	void operator () (f_load_0) { print::out("f_load_0"); }
	void operator () (f_load_1) { print::out("f_load_1"); }
	void operator () (f_load_2) { print::out("f_load_2"); }
	void operator () (f_load_3) { print::out("f_load_3"); }
	void operator () (d_load_0) { print::out("d_load_0"); }
	void operator () (d_load_1) { print::out("d_load_1"); }
	void operator () (d_load_2) { print::out("d_load_2"); }
	void operator () (d_load_3) { print::out("d_load_3"); }
	void operator () (a_load_0) { print::out("a_load_0"); }
	void operator () (a_load_1) { print::out("a_load_1"); }
	void operator () (a_load_2) { print::out("a_load_2"); }
	void operator () (a_load_3) { print::out("a_load_3"); }
	void operator () (i_a_load) { print::out("i_a_load"); }
	void operator () (l_a_load) { print::out("l_a_load"); }
	void operator () (f_a_load) { print::out("f_a_load"); }
	void operator () (d_a_load) { print::out("d_a_load"); }
	void operator () (a_a_load) { print::out("a_a_load"); }
	void operator () (b_a_load) { print::out("b_a_load"); }
	void operator () (c_a_load) { print::out("c_a_load"); }
	void operator () (s_a_load) { print::out("s_a_load"); }

	void operator () (i_store x) { print::out("i_store ", x.index); }
	void operator () (l_store x) { print::out("l_store ", x.index); }
	void operator () (f_store x) { print::out("f_store ", x.index); }
	void operator () (d_store x) { print::out("d_store ", x.index); }
	void operator () (a_store x) { print::out("a_store ", x.index); }
	void operator () (i_store_0) { print::out("i_store_0"); }
	void operator () (i_store_1) { print::out("i_store_1"); }
	void operator () (i_store_2) { print::out("i_store_2"); }
	void operator () (i_store_3) { print::out("i_store_3"); }
	void operator () (l_store_0) { print::out("l_store_0"); }
	void operator () (l_store_1) { print::out("l_store_1"); }
	void operator () (l_store_2) { print::out("l_store_2"); }
	void operator () (l_store_3) { print::out("l_store_3"); }
	void operator () (f_store_0) { print::out("f_store_0"); }
	void operator () (f_store_1) { print::out("f_store_1"); }
	void operator () (f_store_2) { print::out("f_store_2"); }
	void operator () (f_store_3) { print::out("f_store_3"); }
	void operator () (d_store_0) { print::out("d_store_0"); }
	void operator () (d_store_1) { print::out("d_store_1"); }
	void operator () (d_store_2) { print::out("d_store_2"); }
	void operator () (d_store_3) { print::out("d_store_3"); }
	void operator () (a_store_0) { print::out("a_store_0"); }
	void operator () (a_store_1) { print::out("a_store_1"); }
	void operator () (a_store_2) { print::out("a_store_2"); }
	void operator () (a_store_3) { print::out("a_store_3"); }
	void operator () (i_a_store) { print::out("i_a_store"); }
	void operator () (l_a_store) { print::out("l_a_store"); }
	void operator () (f_a_store) { print::out("f_a_store"); }
	void operator () (d_a_store) { print::out("d_a_store"); }
	void operator () (a_a_store) { print::out("a_a_store"); }
	void operator () (b_a_store) { print::out("b_a_store"); }
	void operator () (c_a_store) { print::out("c_a_store"); }
	void operator () (s_a_store) { print::out("s_a_store"); }

	void operator () (pop) { print::out("pop"); }
	void operator () (pop_2) { print::out("pop_2"); }
	void operator () (dup) { print::out("dup"); }
	void operator () (dup_x1) { print::out("dup_x1"); }
	void operator () (dup_x2) { print::out("dup_x2"); }
	void operator () (dup_2) { print::out("dup_2"); }
	void operator () (dup_2_x1) { print::out("dup_2_x1"); }
	void operator () (dup_2_x2) { print::out("dup_2_x2"); }
	void operator () (swap) { print::out("swap"); }

	void operator () (i_add) { print::out("i_add"); }
	void operator () (l_add) { print::out("l_add"); }
	void operator () (f_add) { print::out("f_add"); }
	void operator () (d_add) { print::out("d_add"); }
	void operator () (i_sub) { print::out("i_sub"); }
	void operator () (l_sub) { print::out("l_sub"); }
	void operator () (f_sub) { print::out("f_sub"); }
	void operator () (d_sub) { print::out("d_sub"); }
	void operator () (i_mul) { print::out("i_mul"); }
	void operator () (l_mul) { print::out("l_mul"); }
	void operator () (f_mul) { print::out("f_mul"); }
	void operator () (d_mul) { print::out("d_mul"); }
	void operator () (i_div) { print::out("i_div"); }
	void operator () (l_div) { print::out("l_div"); }
	void operator () (f_div) { print::out("f_div"); }
	void operator () (d_div) { print::out("d_div"); }
	void operator () (i_rem) { print::out("i_rem"); }
	void operator () (l_rem) { print::out("l_rem"); }
	void operator () (f_rem) { print::out("f_rem"); }
	void operator () (d_rem) { print::out("d_rem"); }
	void operator () (i_neg) { print::out("i_neg"); }
	void operator () (l_neg) { print::out("l_neg"); }
	void operator () (f_neg) { print::out("f_neg"); }
	void operator () (d_neg) { print::out("d_neg"); }
	void operator () (i_sh_l) { print::out("i_sh_l"); }
	void operator () (l_sh_l) { print::out("l_sh_l"); }
	void operator () (i_sh_r) { print::out("i_sh_r"); }
	void operator () (l_sh_r) { print::out("l_sh_r"); }
	void operator () (i_u_sh_r) { print::out("i_u_sh_r"); }
	void operator () (l_u_sh_r) { print::out("l_u_sh_r"); }
	void operator () (i_and) { print::out("i_and"); }
	void operator () (l_and) { print::out("l_and"); }
	void operator () (i_or) { print::out("i_or"); }
	void operator () (l_or) { print::out("l_or"); }
	void operator () (i_xor) { print::out("i_xor"); }
	void operator () (l_xor) { print::out("l_xor"); }
	void operator () (i_inc x) { print::out("iinc ", x.index, ", ", x.value); }
	void operator () (i_to_l) { print::out("i_to_l"); }
	void operator () (i_to_f) { print::out("i_to_f"); }
	void operator () (i_to_d) { print::out("i_to_d"); }
	void operator () (l_to_i) { print::out("l_to_i"); }
	void operator () (l_to_f) { print::out("l_to_f"); }
	void operator () (l_to_d) { print::out("l_to_d"); }
	void operator () (f_to_i) { print::out("f_to_i"); }
	void operator () (f_to_l) { print::out("f_to_l"); }
	void operator () (f_to_d) { print::out("f_to_d"); }
	void operator () (d_to_i) { print::out("d_to_i"); }
	void operator () (d_to_l) { print::out("d_to_l"); }
	void operator () (d_to_f) { print::out("d_to_f"); }
	void operator () (i_to_b) { print::out("i_to_b"); }
	void operator () (i_to_c) { print::out("i_to_c"); }
	void operator () (i_to_s) { print::out("i_to_s"); }

	void operator () (l_cmp) { print::out("l_cmp"); }

	void operator () (f_cmp_l) { print::out("f_cmp_l"); }
	void operator () (f_cmp_g) { print::out("f_cmp_g"); }
	void operator () (d_cmp_l) { print::out("d_cmp_l"); }
	void operator () (d_cmp_g) { print::out("d_cmp_g"); }

	void operator () (if_eq x) { print::out("if_eq ", x.branch); }
	void operator () (if_ne x) { print::out("if_ne ", x.branch); }
	void operator () (if_lt x) { print::out("if_lt ", x.branch); }
	void operator () (if_ge x) { print::out("if_ge ", x.branch); }
	void operator () (if_gt x) { print::out("if_gt ", x.branch); }
	void operator () (if_le x) { print::out("if_le ", x.branch); }
	void operator () (if_i_cmp_eq x) { print::out("if_i_cmp_eq ", x.branch); }
	void operator () (if_i_cmp_ne x) { print::out("if_i_cmp_ne ", x.branch); }
	void operator () (if_i_cmp_lt x) { print::out("if_i_cmp_lt ", x.branch); }
	void operator () (if_i_cmp_ge x) { print::out("if_i_cmp_ge ", x.branch); }
	void operator () (if_i_cmp_gt x) { print::out("if_i_cmp_gt ", x.branch); }
	void operator () (if_i_cmp_le x) { print::out("if_i_cmp_le ", x.branch); }
	void operator () (if_a_cmp_eq x) { print::out("if_a_cmp_eq ", x.branch); }
	void operator () (if_a_cmp_ne x) { print::out("if_a_cmp_ne ", x.branch); }
	void operator () (go_to x) { print::out("goto ", x.branch); }
	void operator () (jmp_sr x) { print::out("jmp_sr ", x.branch); }
	void operator () (return_sr x) { print::out("return_sr ", x.index); }
	void operator () (table_switch x, auto offsets_input_stream) {
		print::out("table_switch ", x._default);
		while(x.offsets_count > 0) {
			print::out(" ", read<table_switch::offset>(offsets_input_stream));
			--x.offsets_count;
		}
	}
	void operator () (lookup_switch x) {
		print::out("lookup_switch ", x._default);
		for(auto p : x.pairs) {
			print::out(" ", p.match, ":", p.offset);
		}
	}
	void operator () (i_return) { print::out("i_return"); }
	void operator () (l_return) { print::out("l_return"); }
	void operator () (f_return) { print::out("f_return"); }
	void operator () (d_return) { print::out("d_return"); }
	void operator () (a_return) { print::out("a_return"); }
	void operator () (_return) { print::out("return"); }

	void operator () (get_static x) {
		print::out("get_static ");
		print_field_ref(x.index);
	}
	void operator () (put_static x) {
		print::out("put_static ");
		print_field_ref(x.index);
	}
	void operator () (get_field x) {
		print::out("get_field ");
		print_field_ref(x.index);
	}
	void operator () (put_field x) {
		print::out("put_field ");
		print_field_ref(x.index);
	}
	void operator () (invoke_virtual x) {
		print::out("invoke_virtual ");
		print_method_ref(x.index);
	}
	void operator () (invoke_special x) {
		print::out("invoke_special ");
		print_method_ref((constant::method_ref_index) x.index);
	}
	void operator () (invoke_static x) {
		print::out("invoke_static ");
		print_method_ref((constant::method_ref_index) x.index);
	}
	void operator () (invoke_interface x) {
		print::out("invoke_interface ", (uint16) x.index);
		print_method_ref(x.index);
	}
	void operator () (invoke_dynamic x) {
		print::out("invoked_ynamic ", (uint16) x.index);
	}
	void operator () (_new x) {
		print::out("new ");
		print_class_name(x.index);
	}
	void operator () (new_array x) {
		print::out("new_array ", (uint8) x.type);
	}
	void operator () (a_new_array x) {
		print::out("a_new_array ");
		print_class_name(x.index);
	}
	void operator () (array_length) { print::out("array_length"); }
	void operator () (a_throw) { print::out("a_throw"); }
	void operator () (check_cast x) {
		print::out("check_cast ");
		print_class_name(x.index);
	}
	void operator () (instance_of x) {
		print::out("instance_of ");
		print_class_name(x.index);
	}
	void operator () (monitor_enter) { print::out("monitor_enter"); }
	void operator () (monitor_exit) { print::out("monitor_exit"); }
	void operator () (wide_format_1 x) {
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
	void operator () (wide_format_2 x) {
		print::out("wide ", x.index, " ", x.value);
	}
	void operator () (multi_new_array x) {
		print::out("multi_new_array ", x.index, " ", x.dimensions);
	}
	void operator () (if_null x) {
		print::out("if_null ", x.branch);
	}
	void operator () (if_non_null x) {
		print::out("if_non_null ", x.branch);
	}
	void operator () (go_to_w x) {
		print::out("go_to_w ", x.branch);
	}
	void operator () (jmp_sr_w x) {
		print::out("jmp_sr_w ", x.branch);
	}
	void operator () (unknown x) {
		print::err("unknown instruction: ", x.code);
		posix::abort();
	}
	void operator () (auto) {
		posix::abort();
	}
};