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

#include "abort.hpp"
#include "const_pool_entry.hpp"
#include "print_instruction.hpp"
#include "print_constant_pool_entry.hpp"

#include <class/file/reader.hpp>
#include <core/on_scope_exit.hpp>
#include <core/c_string.hpp>
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

	using namespace class_file::code::instruction;

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

	for(const_pool_entry& e : const_pool) {
		e.view([&]<typename Type>(Type x) {
			++entry_index;
			if constexpr (!same_as<Type, elements::none>) {
				printf("\t[%d] ", entry_index);
			}
			print_constant_pool_entry(x, entry);
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