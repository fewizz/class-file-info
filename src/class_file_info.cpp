#if 0

root=$(dirname `realpath ${BASH_SOURCE[0]}`)/../

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
	${root}/src/class_file_info.cpp
then
	${root}/build/class-file-info $@
fi
exit 0
#endif

#include "abort.hpp"
#include "const_pool_entry.hpp"
#include "print_instruction.hpp"
#include "print_constant_pool_entry.hpp"

#include <class_file/reader.hpp>
#include <on_scope_exit.hpp>
#include <c_string.hpp>

#include <stdio.h>

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

	code_reader([]<typename Type>(Type x, auto) {
		print_instruction(x);
		return loop_action::next;
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

	reader reader{ data };
	auto [is_there_any_magic, version_reader] =
		reader.check_for_magic_and_get_version_reader();

	if(!is_there_any_magic) {
		fputs("no magic here...", stderr);
		return 1;
	}

	auto [version0, constant_pool_reader] =
		version_reader.read_and_get_constant_pool_reader();
	class_file::version version = version0;
	printf("version: %hu.%hu\n", version.major, version.minor);

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

	fputs("constant pool:\n", stdout);

	entry_index = 0;

	for(const_pool_entry& e : const_pool) {
		e.view([&]<typename Type>(Type x) {
			++entry_index;
			if constexpr (!same_as<Type, elements::none>) {
				printf("\t[%u] ", (uint32) entry_index);
			}
			print_constant_pool_entry(x, entry);
		});
	}

	auto [access_flags, this_reader] =
		access_flags_reader.read_and_get_this_class_reader();
	printf("access flags: 0x%.4x\n", (uint16) access_flags);

	auto [this_index, super_reader] =
		this_reader.read_and_get_super_class_reader();
	printf("this class: index: %hu, name: ", (uint16) this_index);
	auto this_name = utf8(_class(this_index).name_index);
	fwrite(this_name.elements_ptr(), 1, this_name.size(), stdout);
	printf("\n");

	auto [super_index, interfaces_reader] =
		super_reader.read_and_get_interfaces_reader();
	printf("super class: ");
	auto super_name = utf8(_class(super_index).name_index);
	fwrite(super_name.elements_ptr(), 1, super_name.size(), stdout);
	printf("\n");

	printf("interfaces:\n");
	auto fiels_reader =
		interfaces_reader.read_and_get_fields_reader([&](auto name_index) {
			printf("\t");
			auto interface_name = utf8(_class(name_index).name_index);
			fwrite(
				interface_name.elements_ptr(), 1, interface_name.size(), stdout
			);
			printf("\n");
		}
	);

	printf("fields:\n");
	auto methods_reader =
	fiels_reader.read_and_get_methods_reader([&](auto field_reader) {
		auto [access_flags, name_index_reader] =
			field_reader.read_access_flags_and_get_name_index_reader();
		printf("\taccess flags: 0x%.4x, name: ", (uint16) access_flags);

		auto [name_index, descriptor_index_reader] =
			name_index_reader.read_and_get_descriptor_index_reader();
		auto name = utf8(name_index);
		fwrite(name.elements_ptr(), 1, name.size(), stdout);

		auto [descriptor_index, attributes_reader] =
			descriptor_index_reader.read_and_get_attributes_reader();

		printf(", descriptor: ");
		auto descriptor = utf8(descriptor_index);
		fwrite(descriptor.elements_ptr(), 1, descriptor.size(), stdout);
		printf("\n");

		return attributes_reader.read_and_get_advanced_iterator(
			utf8,
			[&](auto) {

			}
		);
	});

	printf("methods:\n");
	[[maybe_unused]] auto _ =
	methods_reader.read_and_get_attributes_reader([&](auto method_reader) {
		auto [access_flags, name_index_reader] =
			method_reader.read_access_flags_and_get_name_index_reader();
		printf("\taccess flags: 0x%.4x, name: ", (uint16) access_flags);

		auto [name_index, descriptor_index_reader] =
			name_index_reader.read_and_get_descriptor_index_reader();
		auto name = utf8(name_index);
		fwrite(name.elements_ptr(), 1, name.size(), stdout);

		auto [descriptor_index, attributes_reader] =
			descriptor_index_reader.read_and_get_attributes_reader();
		auto descriptor = utf8(descriptor_index);
		printf(", descriptor: ");
		fwrite(descriptor.elements_ptr(), 1, descriptor.size(), stdout);
		printf("\n");

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