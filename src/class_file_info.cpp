#include "const_pool_entry.hpp"
#include "print_instruction.hpp"
#include "print_constant_pool_entry.hpp"

#include <class_file/reader.hpp>
#include <on_scope_exit.hpp>
#include <c_string.hpp>

#include <posix/memory.hpp>
#include <posix/default_error_handler.cpp>

extern "C" void* __cdecl malloc(nuint size);
extern "C" void  __cdecl free(void* ptr);

template<typename Iterator>
void read_code_attribute(
	class_file::attribute::code::reader<Iterator> max_stack_reader
) {
	auto [max_locals_reader, max_stack] = max_stack_reader();
	print("max stack: ");
	print(max_stack);
	print("\n");

	auto [code_reader, max_locals] = max_locals_reader();
	print("max locals: ");
	print(max_locals);
	print("\n");

	code_reader([]<typename Type>(Type x, auto) {
		print_instruction(x);
		return loop_action::next;
	});
}

int main(int argc, const char** argv) {
	if(argc != 2) {
		posix::std_err().write_from(
			c_string{"usage: class_info.cpp <path to class file>"}
		);
		return 1;
	}

	posix::own_file file = posix::open_file(
		c_string{ argv[1] },
		posix::file_access_modes{ posix::file_access_mode::read }
	);
	auto size = file->set_offset_to_end();
	file->set_offset(0);
	posix::memory_for_range_of<uint8> data {
		posix::allocate_memory_for<uint8>(size)
	};
	file->read_to(data);

	using namespace class_file;

	reader reader{ data.iterator() };
	auto [is_there_any_magic, version_reader] =
		reader.check_for_magic_and_get_version_reader();

	if(!is_there_any_magic) {
		posix::std_err().write_from(c_string{ "no magic here..." });
		return 1;
	}

	auto [version0, constant_pool_reader] =
		version_reader.read_and_get_constant_pool_reader();
	class_file::version version = version0;
	print("version: ");
	print(version.major);
	print(".");
	print(version.minor);
	print("\n");

	uint16 constant_pool_size = constant_pool_reader.entries_count();
	const_pool_entry const_pool[constant_pool_size];

	nuint entry_index = 0;
	auto access_flags_reader =
		constant_pool_reader.read_and_get_access_flags_reader(
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
		return entry(index).get<constant::utf8>();
	};

	print("constant pool:\n");

	entry_index = 0;

	for(const_pool_entry& e : const_pool) {
		++entry_index;
		if(!e.has_value()) {
			continue;
		}
		e.view([&]<typename Type>(Type x) {
			print("\t[");
			print((uint32) entry_index);
			print("] ");
			print_constant_pool_entry(x, entry);
		});
	}

	auto [access_flags, this_reader] =
		access_flags_reader.read_and_get_this_class_reader();
	print("access flags: ");
	print((uint16) access_flags);
	print("\n");

	auto [this_index, super_reader] =
		this_reader.read_and_get_super_class_reader();
	print("this class: index: ");
	print((uint16) this_index);
	print(", name: ");
	auto this_name = utf8(_class(this_index).name_index);
	print(this_name);
	print("\n");

	auto [super_index, interfaces_reader] =
		super_reader.read_and_get_interfaces_reader();
	print("super class: ");
	auto super_name = utf8(_class(super_index).name_index);
	print(super_name);
	print("\n");

	print("interfaces:\n");
	auto fiels_reader =
		interfaces_reader.read_and_get_fields_reader([&](auto name_index) {
			print("\t");
			auto interface_name = utf8(_class(name_index).name_index);
			print(interface_name);
			print("\n");
		}
	);

	print("fields:\n");
	auto methods_reader =
	fiels_reader.read_and_get_methods_reader([&](auto field_reader) {
		auto [access_flags, name_index_reader] =
			field_reader.read_access_flags_and_get_name_index_reader();
		print("\taccess flags: ");
		print((uint16) access_flags);
		print(", name: ");

		auto [name_index, descriptor_index_reader] =
			name_index_reader.read_and_get_descriptor_index_reader();
		auto name = utf8(name_index);
		print(name);

		auto [descriptor_index, attributes_reader] =
			descriptor_index_reader.read_and_get_attributes_reader();

		print(", descriptor: ");
		auto descriptor = utf8(descriptor_index);
		print(descriptor);
		print("\n");

		return attributes_reader.read_and_get_advanced_iterator(
			utf8,
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
		auto name = utf8(name_index);
		print(name);

		auto [descriptor_index, attributes_reader] =
			descriptor_index_reader.read_and_get_attributes_reader();
		auto descriptor = utf8(descriptor_index);
		print(", descriptor: ");
		print(descriptor);
		print("\n");

		return attributes_reader.read_and_get_advanced_iterator(
			utf8,
			[&]<typename AttributeReader>(AttributeReader x) {
				if constexpr (
					AttributeReader::attribute_type == attribute::type::code
				) {
					read_code_attribute(x);
				}
			}
		);
	});

}