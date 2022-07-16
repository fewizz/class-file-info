#if 0

d=`realpath ${BASH_SOURCE[0]}`
d=`dirname ${d}`
root=`realpath ${d}/../`

mkdir -p ${root}/build

if clang++ \
	-std=c++20 \
	-Wall -Wextra \
	-g \
	-nostdinc++ \
	-I ${root}/include/ \
	-I ${root}/../core/include \
	-I ${root}/../class-file/include \
	-o ${root}/build/class-file-info \
	${d}/class_file_info.cpp
then
	${root}/build/class-file-info $@
fi
exit 0
#endif

#include "const_pool_entry.hpp"

#include <class/file/reader.hpp>
#include <core/on_scope_exit.hpp>
#include <core/c_string.hpp>
#include <stdio.h>

extern "C" [[noreturn]] void abort();

extern "C" void* __cdecl malloc(nuint size);
extern "C" void  __cdecl free(void* ptr);

template<typename Iterator>
void read_code_attribute(
	class_file::attribute::code::reader<Iterator> max_stack_reader
) {
	auto [max_locals_reader, max_stack] = max_stack_reader();
	printf("max stack: %d\n", max_stack);

	auto [code_reader, max_locals] = max_locals_reader();
	printf("max locals: %d\n", max_locals);

	using namespace class_file::code::instruction;

	code_reader([&]<typename Type>(Type x, auto) {
		on_scope_exit new_line_on_scope_exit{[](){
			putchar('\n');
		}};

		if constexpr (same_as<Type, nop>) fputs("nop", stdout);

		if constexpr (same_as<Type, a_const_null>) fputs("a_const_null", stdout);
		if constexpr (same_as<Type, i_const_m1>) fputs("i_const_m1", stdout);
		if constexpr (same_as<Type, i_const_0>) fputs("i_const_0", stdout);
		if constexpr (same_as<Type, i_const_1>) fputs("i_const_1", stdout);
		if constexpr (same_as<Type, i_const_2>) fputs("i_const_2", stdout);
		if constexpr (same_as<Type, i_const_3>) fputs("i_const_3", stdout);
		if constexpr (same_as<Type, i_const_4>) fputs("i_const_4", stdout);
		if constexpr (same_as<Type, i_const_5>) fputs("i_const_5", stdout);
		if constexpr (same_as<Type, l_const_0>) fputs("l_const_0", stdout);
		if constexpr (same_as<Type, l_const_1>) fputs("l_const_1", stdout);

		if constexpr (same_as<Type, bi_push>) {
			fputs("bi_push ", stdout);
			printf("%hhu", x.value);
		}
		if constexpr (same_as<Type, si_push>) {
			fputs("si_push ", stdout);
			printf("%hu", x.value);
		}

		if constexpr (same_as<Type, ldc>) {
			fputs("ldc ", stdout);
			printf("%hhu", x.index);
		}
		if constexpr (same_as<Type, ldc_w>) {
			fputs("ldc_w ", stdout);
			printf("%hu", x.index);
		}

		if constexpr (same_as<Type, i_load>) {
			fputs("i_load ", stdout);
			printf("%hhu", x.index);
		}
		if constexpr (same_as<Type, l_load>) {
			fputs("l_load ", stdout);
			printf("%hhu", x.index);
		}
		if constexpr (same_as<Type, a_load>) {
			fputs("a_load ", stdout);
			printf("%hhu", x.index);
		}
		if constexpr (same_as<Type, i_load_0>) fputs("i_load_0", stdout);
		if constexpr (same_as<Type, i_load_1>) fputs("i_load_1", stdout);
		if constexpr (same_as<Type, i_load_2>) fputs("i_load_2", stdout);
		if constexpr (same_as<Type, i_load_3>) fputs("i_load_3", stdout);
		if constexpr (same_as<Type, l_load_0>) fputs("l_load_0", stdout);
		if constexpr (same_as<Type, l_load_1>) fputs("l_load_1", stdout);
		if constexpr (same_as<Type, l_load_2>) fputs("l_load_2", stdout);
		if constexpr (same_as<Type, l_load_3>) fputs("l_load_3", stdout);
		if constexpr (same_as<Type, f_load_0>) fputs("f_load_0", stdout);
		if constexpr (same_as<Type, f_load_1>) fputs("f_load_1", stdout);
		if constexpr (same_as<Type, f_load_2>) fputs("f_load_2", stdout);
		if constexpr (same_as<Type, f_load_3>) fputs("f_load_3", stdout);
		if constexpr (same_as<Type, d_load_0>) fputs("d_load_0", stdout);
		if constexpr (same_as<Type, d_load_1>) fputs("d_load_1", stdout);
		if constexpr (same_as<Type, d_load_2>) fputs("d_load_2", stdout);
		if constexpr (same_as<Type, d_load_3>) fputs("d_load_3", stdout);
		if constexpr (same_as<Type, a_load_0>) fputs("a_load_0", stdout);
		if constexpr (same_as<Type, a_load_1>) fputs("a_load_1", stdout);
		if constexpr (same_as<Type, a_load_2>) fputs("a_load_2", stdout);
		if constexpr (same_as<Type, a_load_3>) fputs("a_load_3", stdout);
		if constexpr (same_as<Type, a_a_load>) fputs("a_a_load", stdout);
		if constexpr (same_as<Type, b_a_load>) fputs("b_a_load", stdout);
		if constexpr (same_as<Type, c_a_load>) fputs("c_a_load", stdout);

		if constexpr (same_as<Type, i_store>) {
			fputs("i_store ", stdout);
			printf("%hhu", x.index);
		}
		if constexpr (same_as<Type, l_store>) {
			fputs("l_store ", stdout);
			printf("%hhu", x.index);
		}
		if constexpr (same_as<Type, a_store>) {
			fputs("a_store ", stdout);
			printf("%hhu", x.index);
		}
		if constexpr (same_as<Type, i_store_0>) fputs("i_store_0", stdout);
		if constexpr (same_as<Type, i_store_1>) fputs("i_store_1", stdout);
		if constexpr (same_as<Type, i_store_2>) fputs("i_store_2", stdout);
		if constexpr (same_as<Type, i_store_3>) fputs("i_store_3", stdout);
		if constexpr (same_as<Type, a_store_0>) fputs("a_store_0", stdout);
		if constexpr (same_as<Type, a_store_1>) fputs("a_store_1", stdout);
		if constexpr (same_as<Type, a_store_2>) fputs("a_store_2", stdout);
		if constexpr (same_as<Type, a_store_3>) fputs("a_store_3", stdout);
		if constexpr (same_as<Type, a_a_store>) fputs("a_a_store", stdout);
		if constexpr (same_as<Type, b_a_store>) fputs("b_a_store", stdout);
		if constexpr (same_as<Type, c_a_store>) fputs("c_a_store", stdout);

		if constexpr (same_as<Type, pop>) fputs("pop", stdout);
		if constexpr (same_as<Type, dup>) fputs("dup", stdout);
		if constexpr (same_as<Type, dup_2>) fputs("dup_2", stdout);

		if constexpr (same_as<Type, i_add>) fputs("i_add", stdout);
		if constexpr (same_as<Type, l_add>) fputs("l_add", stdout);
		if constexpr (same_as<Type, i_sub>) fputs("i_sub", stdout);
		if constexpr (same_as<Type, l_sub>) fputs("l_sub", stdout);
		if constexpr (same_as<Type, i_mul>) fputs("i_mul", stdout);
		if constexpr (same_as<Type, l_mul>) fputs("l_mul", stdout);
		if constexpr (same_as<Type, d_mul>) fputs("d_mul", stdout);
		if constexpr (same_as<Type, i_div>) fputs("i_div", stdout);
		if constexpr (same_as<Type, i_neg>) fputs("i_neg", stdout);
		if constexpr (same_as<Type, i_sh_l>) fputs("i_shl", stdout);
		if constexpr (same_as<Type, l_sh_l>) fputs("l_shl", stdout);
		if constexpr (same_as<Type, i_sh_r>) fputs("i_shr", stdout);
		if constexpr (same_as<Type, i_and>) fputs("i_and", stdout);
		if constexpr (same_as<Type, i_or>) fputs("i_or", stdout);
		if constexpr (same_as<Type, i_xor>) fputs("i_xor", stdout);
		if constexpr (same_as<Type, i_inc>) {
			printf("iinc ", stdout);
			printf("%hhu, %hhd", x.index, x.value);
		}
		if constexpr (same_as<Type, i_to_l>) fputs("i_to_l", stdout);
		if constexpr (same_as<Type, i_to_d>) fputs("i_to_d", stdout);
		if constexpr (same_as<Type, l_to_i>) fputs("l_to_i", stdout);
		if constexpr (same_as<Type, f_to_d>) fputs("f_to_d", stdout);
		if constexpr (same_as<Type, d_to_i>) fputs("d_to_i", stdout);
		if constexpr (same_as<Type, i_to_b>) fputs("i_to_b", stdout);
		if constexpr (same_as<Type, i_to_c>) fputs("i_to_c", stdout);

		if constexpr (same_as<Type, l_cmp>) fputs("l_cmp", stdout);

		if constexpr (same_as<Type, if_eq>) {
			fputs("if_eq ", stdout);
			printf("%d", x.branch);
		}
		if constexpr (same_as<Type, if_ne>) {
			fputs("if_ne ", stdout);
			printf("%d", x.branch);
		}
		if constexpr (same_as<Type, if_lt>) {
			fputs("if_lt ", stdout);
			printf("%d", x.branch);
		}
		if constexpr (same_as<Type, if_ge>) {
			fputs("if_ge ", stdout);
			printf("%d", x.branch);
		}
		if constexpr (same_as<Type, if_gt>) {
			fputs("if_gt ", stdout);
			printf("%d", x.branch);
		}
		if constexpr (same_as<Type, if_le>) {
			fputs("if_le ", stdout);
			printf("%d", x.branch);
		}
		if constexpr (same_as<Type, if_i_cmp_eq>) {
			printf("if_i_cmp_eq %d", x.branch);
		}
		if constexpr (same_as<Type, if_i_cmp_ne>) {
			printf("if_i_cmp_ne %d", x.branch);
		}
		if constexpr (same_as<Type, if_i_cmp_lt>) {
			printf("if_i_cmp_lt %d", x.branch);
		}
		if constexpr (same_as<Type, if_i_cmp_ge>) {
			printf("if_i_cmp_ge %d", x.branch);
		}
		if constexpr (same_as<Type, if_i_cmp_gt>) {
			printf("if_i_cmp_gt %d", x.branch);
		}
		if constexpr (same_as<Type, if_i_cmp_le>) {
			printf("if_i_cmp_le %d", x.branch);
		}
		if constexpr (same_as<Type, if_a_cmp_eq>) {
			printf("if_a_cmp_eq %d", x.branch);
		}
		if constexpr (same_as<Type, if_a_cmp_ne>) {
			printf("if_a_cmp_ne %d", x.branch);
		}
		if constexpr (same_as<Type, go_to>) printf("goto %d", x.branch);
		if constexpr (same_as<Type, table_switch>) {
			printf("table_switch %d", x._default);
			for(auto p : x.offsets) {
				printf(" %d", p);
			}
		}
		if constexpr (same_as<Type, lookup_switch>) {
			printf("lookup_switch %d", x._default);
			for(auto p : x.pairs) {
				printf(" %d:%d", p.match, p.offset);
			}
		}
		if constexpr (same_as<Type, i_return>) {
			fputs("i_return", stdout);
			return false;
		}
		if constexpr (same_as<Type, l_return>) {
			fputs("l_return", stdout);
			return false;
		}
		if constexpr (same_as<Type, d_return>) {
			fputs("d_return", stdout);
			return false;
		}
		if constexpr (same_as<Type, a_return>) {
			fputs("a_return", stdout);
			return false;
		}
		if constexpr (same_as<Type, _return>) {
			fputs("return", stdout);
			return false;
		}

		if constexpr (same_as<Type, get_static>) {
			printf("get_static %d", x.index);
		}
		if constexpr (same_as<Type, put_static>) {
			printf("put_static %d", x.index);
		}
		if constexpr (same_as<Type, get_field>) {
			printf("get_field %d", x.index);
		}
		if constexpr (same_as<Type, put_field>) {
			printf("put_field %d", x.index);
		}
		if constexpr (same_as<Type, invoke_virtual>) {
			fputs("invoke_virtual ", stdout);
			
		}
		if constexpr (same_as<Type, invoke_special>) {
			printf("invoke_special %d", x.index);
		}
		if constexpr (same_as<Type, invoke_static>) {
			printf("invoke_static %hu", x.index);
		}
		if constexpr (same_as<Type, invoke_interface>) {
			printf("invoke_interface %hu %hhu", x.index, x.count);
		}
		if constexpr (same_as<Type, invoke_dynamic>) {
			printf("invoked_ynamic %d", x.index);
		}
		if constexpr (same_as<Type, _new>) printf("new %d", x.index);
		if constexpr (same_as<Type, new_array>) {
			printf("new_array %hhu", x.type);
		}
		if constexpr (same_as<Type, a_new_array>) {
			printf("a_new_array %hu", x.index);
		}
		if constexpr (same_as<Type, array_length>) printf("array_length");
		if constexpr (same_as<Type, a_throw>) printf("a_throw");
		if constexpr (same_as<Type, check_cast>) {
			printf("check_cast %hu", x.index);
		}
		if constexpr (same_as<Type, instance_of>) {
			printf("instance_of %hu", x.index);
		}
		if constexpr (same_as<Type, monitor_enter>) {
			fputs("monitor_enter", stdout);
		}
		if constexpr (same_as<Type, monitor_exit>) {
			fputs("monitor_exit", stdout);
		}
		if constexpr (same_as<Type, if_null>) {
			printf("if_null %d", x.branch);
		}
		if constexpr (same_as<Type, if_non_null>) {
			printf("if_non_null %d", x.branch);
		}
		if constexpr (same_as<Type, uint8>) {
			printf("unknown instruction: %d\n", x);
			abort();
		}
	});
}

int main(int argc, const char** argv) {
	if(argc != 2) {
		fputs("usage: class_info.cpp <path to class file>", stderr);
		return 1;
	}

	FILE* f = fopen(argv[1], "rb");
	if(f == nullptr) {
		fputs("could't open file", stderr);
		return 1;
	}
	fseek(f, 0, SEEK_END);
	nuint size = ftell(f);
	rewind(f);
	uint8* data = (uint8*) malloc(size);
	if(!data) {
		fputs("could't allocate memory for class data", stderr);
		return 1;
	}
	fread(data, 1, size, f);

	using namespace class_file;

	reader read_magic{ data };
	auto [read_version, is_there_any_magic] = read_magic();

	if(!is_there_any_magic) {
		fputs("no magic here...", stderr);
		return 1;
	}

	auto [read_constant_pool, version0] = read_version();
	class_file::version version = version0;
	printf("version: %hu.%hu\n", version.major, version.minor);

	uint16 constant_pool_size = read_constant_pool.entries_count();
	const_pool_entry const_pool[constant_pool_size];

	nuint entry_index = 0;
	auto access_flags_reader = read_constant_pool(
		[&]<typename Type>(Type x) {
			if constexpr(
				!same_as<Type, constant::unknown> &&
				!same_as<Type, constant::skip>
			) {
				const_pool[entry_index] = x;
			}
			++entry_index;
		}
	);

	auto entry = [&](uint16 index) { return const_pool[index - 1]; };
	auto _class = [&](uint16 index) {
		return entry(index).get<constant::_class>();
	};
	auto utf8 = [&](uint16 index) {
		return const_pool[index - 1].get<constant::utf8>();
	};

	fputs("constant pool:\n", stdout);

	entry_index = 0;

	auto print_utf8 = [&](uint16 index) {
		constant::utf8 u = utf8(index);
		fputc('\"', stdout);
		fwrite(u.data(), 1, u.size(), stdout);
		fprintf(stdout, "\"[%hu]", index);
	};

	auto print_class = [&](uint16 index) {
		constant::_class c = _class(index);
		fputs("class = { ", stdout);
		print_utf8(c.name_index);
		fprintf(stdout, " }[%hu]", index);
	};

	auto print_nat = [&](uint16 index) {
		constant::name_and_type n = entry(index).get<constant::name_and_type>();
		fputs("name and type = { ", stdout);
		print_utf8(n.name_index);
		fputs(", ", stdout);
		print_utf8(n.descriptor_index);
		fprintf(stdout, " }[%hu]", index);
	};

	for(const_pool_entry& e : const_pool) {
		e.view([&]<typename Type>(Type x) {
			++entry_index;

			if constexpr (!same_as<Type, elements::none>) {
				printf("\t[%d] ", entry_index);
			}

			if constexpr (same_as<Type, constant::utf8>) {
				fputs("utf8: \"", stdout);
				fwrite(x.begin(), 1, x.size(), stdout);
				fputc('\"', stdout);
			}
			else if constexpr (same_as<Type, constant::_int>) {
				printf("integer: %d", x.value);
			}
			else if constexpr (same_as<Type, constant::_float>) {
				printf("float: %f", x.value);
			}
			else if constexpr (same_as<Type, constant::_long>) {
				printf("long: %lld", x.value);
			}
			else if constexpr (same_as<Type, constant::_double>) {
				printf("double: %lf", x.value);
			}
			else if constexpr (same_as<Type, constant::_class>) {
				fputs("class: ", stdout);
				print_utf8(x.name_index);
			}
			else if constexpr (same_as<Type, constant::string>) {
				fputs("string: \"", stdout);
				print_utf8(x.string_index);
			}

			else if constexpr (same_as<Type, constant::field_ref>) {
				fputs("field ref: ", stdout);
				print_class(x.class_index);
				fputs(", ", stdout);
				print_nat(x.name_and_type_index);
			}
			else if constexpr (same_as<Type, constant::method_ref>) {
				fputs("method ref: ", stdout);
				print_class(x.class_index);
				fputs(", ", stdout);
				print_nat(x.name_and_type_index);
			}
			else if constexpr (same_as<Type, constant::interface_method_ref>) {
				fputs("interface method ref: ", stdout);
				print_class(x.class_index);
				fputs(", ", stdout);
				print_nat(x.name_and_type_index);
			}
			else if constexpr (same_as<Type, constant::name_and_type>) {
				fputs("name and type: name = ", stdout);
				print_utf8(x.name_index);
				fputs(", descriptor = ", stdout);
				print_utf8(x.descriptor_index);
			}
			else if constexpr (same_as<Type, constant::method_handle>) {
				c_string<c_string_type::known_size> name;

				switch (x.reference_kind) {
					case 1: name = "get field";          break;
					case 2: name = "get static";         break;
					case 3: name = "put field";          break;
					case 4: name = "put static";         break;

					case 5: name = "invoke virtual";     break;
					case 8: name = "new invoke special"; break;

					case 6: name = "invoke static";      break;
					case 7: name = "invoke special";     break;

					case 9: name = "invoke interface";   break;
				}

				fputs("method handle: reference kind = \"", stdout);
				fwrite(name.data(), 1, name.size(), stdout);
				fputs("\", ", stdout);

				auto e = entry(x.reference_index);

				uint16 class_index;
				uint16 nat_index;

				if(x.reference_kind >= 1 && x.reference_kind <= 4) {
					constant::field_ref fr =
						e.template get<constant::field_ref>();
					fputs("field ref", stdout);
					class_index = fr.class_index;
					nat_index = fr.name_and_type_index;
				}
				else if(e.template is<constant::method_ref>()) {
					constant::method_ref mr =
						e.template get<constant::method_ref>();
					fputs("method ref", stdout);
					class_index = mr.class_index;
					nat_index = mr.name_and_type_index;
				}
				else {
					constant::interface_method_ref imr =
						e.template get<constant::interface_method_ref>();
					fputs("interface method ref", stdout);
					class_index = imr.class_index;
					nat_index = imr.name_and_type_index;
				}
				fputs(" = { ", stdout);
				print_class(class_index);
				fputs(", ", stdout);
				print_nat(nat_index);
				fprintf(stdout, " }[%hhu]", x.reference_index);
			}
			else if constexpr (same_as<Type, constant::method_type>) {
				fputs("method type: ", stdout);
				print_utf8(x.descriptor_index);
			}
			else if constexpr (same_as<Type, constant::dynamic>) {
				printf(
					"dynamic: bootstrap method attr index = %hhu, ",
					x.bootstrap_method_attr_index
				);
				print_nat(x.name_and_type_index);
			}
			else if constexpr (same_as<Type, constant::invoke_dynamic>) {
				printf(
					"invoke dynamic: bootstrap method attr index = %hhu, ",
					x.bootstrap_method_attr_index
				);
				print_nat(x.name_and_type_index);
			}
			else if constexpr (same_as<Type, constant::module>) {
				fputs("module: ", stdout);
				print_utf8(x.name_index);
			}
			else if constexpr (same_as<Type, constant::package>) {
				fputs("package: ", stdout);
				print_utf8(x.name_index);
			}
			else if constexpr (same_as<Type, elements::none>) {}
			else if constexpr (same_as<Type, constant::unknown>) {
				printf("unknown tag: %d", x); abort();
			}
			else {
				printf("unimplemented tag: %d", Type::tag); abort();
			}

			printf("\n");
		});
	}

	auto [read_this, access_flags] = access_flags_reader();
	printf("access flags: 0x%.4x\n", access_flags);

	auto [read_super, this_index] = read_this();
	printf("this class: index: %d, name: ", this_index);
	auto this_name = utf8(_class(this_index).name_index);
	fwrite(this_name.data(), 1, this_name.size(), stdout);
	printf("\n");

	auto [read_interfaces, super_index] = read_super();
	printf("super class: ");
	auto super_name = utf8(_class(super_index).name_index);
	fwrite(super_name.data(), 1, super_name.size(), stdout);
	printf("\n");

	printf("interfaces:\n");
	auto read_fields = read_interfaces([&](auto name_index) {
		printf("\t");
		auto interface_name = utf8(_class(name_index).name_index);
		fwrite(interface_name.data(), 1, interface_name.size(), stdout);
		printf("\n");
	});

	printf("fields:\n");
	auto read_methods = read_fields([&](auto field_reader) {
		auto [name_index_reader, access_flags] = field_reader();
		printf("\taccess flags: 0x%.4x, name: ", access_flags);

		auto [descriptor_index_reader, name_index] = name_index_reader();
		auto name = utf8(name_index);
		fwrite(name.data(), 1, name.size(), stdout);

		auto [read_attributes, descriptor_index] {
			descriptor_index_reader()
		};

		printf(", descriptor: ");
		auto descriptor = utf8(descriptor_index);
		fwrite(descriptor.data(), 1, descriptor.size(), stdout);
		printf("\n");

		return read_attributes(
			utf8,
			[&](auto) {

			}
		);
	});

	printf("methods:\n");
	[[maybe_unused]] auto _ = read_methods([&](auto method_reader) {
		auto [read_name_index, access_flags] = method_reader();
		printf("\taccess flags: 0x%.4x, name: ", access_flags);

		auto [read_descriptor_index, name_index] = read_name_index();
		auto name = utf8(name_index);
		fwrite(name.data(), 1, name.size(), stdout);

		auto [read_attributes, descriptor_index] = read_descriptor_index();
		auto descriptor = utf8(descriptor_index);
		printf(", descriptor: ");
		fwrite(descriptor.begin(), 1, descriptor.size(), stdout);
		printf("\n");

		return read_attributes(
			utf8,
			[&]<typename AttributeReader>(AttributeReader x) {
				if constexpr (AttributeReader::type == attribute::type::code) {
					read_code_attribute(x);
				}
			}
		);
	});

}