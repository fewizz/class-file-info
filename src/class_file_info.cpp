#include "./const_pool.hpp"
#include "./print_instruction.hpp"
#include "./print_constant_pool_entry.hpp"

#include <class_file/reader.hpp>
#include <on_scope_exit.hpp>
#include <c_string.hpp>

#include <posix/memory.hpp>
#include <posix/default_error_handler.cpp>

template<typename Iterator>
void read_code_attribute(
	class_file::attribute::code::reader<Iterator> max_stack_reader,
	const_pool& const_pool
) {
	auto [max_stack, max_locals_reader]
		= max_stack_reader.read_and_get_max_locals_reader();
	print("max stack: ");
	print(max_stack);
	print("\n");

	auto [max_locals, code_reader]
		= max_locals_reader.read_and_get_code_reader();
	print("max locals: ");
	print(max_locals);
	print("\n");

	auto it_begin = code_reader.read_as_span().iterator();
	auto prev_it = it_begin;
	code_reader.read_and_get_exception_table_reader(
	[&]<typename Type>(Type x, auto it) {
		print("[");
		print((nuint)prev_it - (nuint)it_begin);
		prev_it = it;
		print("] ");
		print_instruction(x, const_pool);
		return loop_action::next;
	});
}

int main(int argc, const char** argv) {
	if(argc != 2) {
		posix::std_err.write_from(
			c_string{"usage: class_info.cpp <path to class file>"}
		);
		return 1;
	}

	body<posix::file> file = posix::open_file(
		c_string{ argv[1] },
		posix::file_access_modes {
			posix::file_access_mode::read,
			posix::file_access_mode::binary
		}
	);
	auto size = file->set_offset_to_end();
	file->set_offset(0);
	posix::memory_for_range_of<uint8> data {
		posix::allocate_memory_for<uint8>(size)
	};
	file->read_to(data);

	using namespace class_file;

	reader magic_reader{ (char*) data.iterator() };
	auto [is_there_any_magic, version_reader] =
		magic_reader.read_and_check_and_get_version_reader();

	if(!is_there_any_magic) {
		posix::std_err.write_from(c_string{ "no magic here..." });
		return 1;
	}

	auto [version, constant_pool_reader] =
		version_reader.read_and_get_constant_pool_reader();
	print("version: ");
	print(version.major);
	print(".");
	print(version.minor);
	print("\n");

	uint16 const_pool_size = constant_pool_reader.read_count();
	storage<const_pool_entry> const_pool_storages[const_pool_size];
	list const_pool_list{ span{ const_pool_storages, const_pool_size } };

	auto access_flags_reader =
		constant_pool_reader.read_and_get_access_flags_reader(
			[&]<typename Type>(Type x) {
				if constexpr(
					same_as<Type, constant::unknown> ||
					same_as<Type, constant::skip>
				) {
					const_pool_list.emplace_back(const_pool_entry{});
				}
				else {
					const_pool_list.emplace_back(x);
				}
				
			}
		);

	print("constant pool:\n");

	const_pool const_pool {
		(const_pool_entry*) const_pool_storages, const_pool_size
	};

	const_pool.for_each_indexed([&](const_pool_entry e, uint16 index) {
		if(!e.has_value()) {
			return;
		}
		e.view([&]<typename Type>(Type x) {
			print("\t[");
			print((uint32) index + 1);
			print("] ");
			print_constant_pool_entry(x, const_pool);
		});
	});


	auto [access_flags, this_reader] =
		access_flags_reader.read_and_get_this_class_reader();
	print("access flags: ");
	print((uint16) access_flags);
	print("\n");

	auto [this_index, super_reader] =
		this_reader.read_and_get_super_class_reader();
	print("this class:");
	auto this_name = const_pool[const_pool[this_index].name_index];
	print(this_name);
	print("["); print((uint16) this_index); print("]");
	print("\n");

	auto [super_index, interfaces_reader] =
		super_reader.read_and_get_interfaces_reader();
	print("super class: ");
	auto super_name
		= const_pool[const_pool[super_index].name_index];
	print(super_name);
	print("["); print((uint16) super_index); print("]");
	print("\n");

	print("interfaces:\n");
	auto fields_reader =
		interfaces_reader
		.read_and_get_fields_reader([&](constant::interface_index index) {
			print("\t");
			constant::utf8 i_name = const_pool[const_pool[index].name_index];
			print(i_name);
			print("\n");
		}
	);

	print("fields:\n");
	auto methods_reader =
	fields_reader.read_and_get_methods_reader([&](auto field_reader) {
		auto [access_flags, name_index_reader] =
			field_reader.read_access_flags_and_get_name_index_reader();
		print("\taccess flags: ");
		print((uint16) access_flags);
		print(", name: ");

		auto [name_index, descriptor_index_reader] =
			name_index_reader.read_and_get_descriptor_index_reader();
		constant::utf8 name = const_pool[name_index];
		print(name);

		auto [descriptor_index, attributes_reader] =
			descriptor_index_reader.read_and_get_attributes_reader();

		print(", descriptor: ");
		constant::utf8 descriptor = const_pool[descriptor_index];
		print(descriptor);
		print("\n");

		return attributes_reader.read_and_get_advanced_iterator(
			[&](constant::utf8_index index) { return const_pool[index]; },
			[&](auto) {

			}
		);
	});

	print("methods:\n");
	[[maybe_unused]] auto _ =
	methods_reader.read_and_get_attributes_reader([&](auto method_reader) {
		auto [access_flags, name_index_reader] =
			method_reader.read_access_flags_and_get_name_index_reader();
		print("\taccess flags: ");
		print((uint16) access_flags);
		print(", name: ");

		auto [name_index, descriptor_index_reader] =
			name_index_reader.read_and_get_descriptor_index_reader();
		auto name = const_pool[name_index];
		print(name);

		auto [descriptor_index, attributes_reader] =
			descriptor_index_reader.read_and_get_attributes_reader();
		auto descriptor = const_pool[descriptor_index];
		print(", descriptor: ");
		print(descriptor);
		print("\n");

		return attributes_reader.read_and_get_advanced_iterator(
			[&](constant::utf8_index index) { return const_pool[index]; },
			[&]<typename AttributeReader>(AttributeReader x) {
				if constexpr (
					AttributeReader::attribute_type == attribute::type::code
				) {
					read_code_attribute(x, const_pool);
				}
			}
		);
	});

}