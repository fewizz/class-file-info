#pragma once

#include "const_pool_entry.hpp"
#include "abort.hpp"

#include <class_file/constant.hpp>

#include <c_string.hpp>

#include <stdio.h>

template<typename Type>
static void print_constant_pool_entry(
	Type x, auto entry_map
) {
	using namespace class_file;

	auto print_utf8 = [&](uint16 index) {
		constant::utf8 u = entry_map(index).template get<constant::utf8>();
		fputc('\"', stdout);
		fwrite(u.elements_ptr(), 1, u.size(), stdout);
		fprintf(stdout, "\"[%hu]", index);
	};

	auto print_class = [&](uint16 index) {
		constant::_class c = entry_map(index).template get<constant::_class>();
		fputs("class = { ", stdout);
		print_utf8(c.name_index);
		fprintf(stdout, " }[%hu]", index);
	};

	auto print_nat = [&](uint16 index) {
		constant::name_and_type n =
			entry_map(index).template get<constant::name_and_type>();
		fputs("name and type = { ", stdout);
		print_utf8(n.name_index);
		fputs(", ", stdout);
		print_utf8(n.descriptor_index);
		fprintf(stdout, " }[%hu]", index);
	};

	if constexpr (same_as<Type, constant::utf8>) {
		fputs("utf8: \"", stdout);
		fwrite(x.elements_ptr(), 1, x.size(), stdout);
		fputc('\"', stdout);
	}
	else if constexpr (same_as<Type, constant::_int>) {
		printf("integer: %d", x.value);
	}
	else if constexpr (same_as<Type, constant::_float>) {
		printf("float: %f", x.value);
	}
	else if constexpr (same_as<Type, constant::_long>) {
		printf("long: %ld", x.value);
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
		print_class(x.interface_index);
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

		using enum constant::method_handle::behavior_kind;
		switch (x.kind) {
			case get_field:          name = "get field";          break;
			case get_static:         name = "get static";         break;
			case put_field:          name = "put field";          break;
			case put_static:         name = "put static";         break;

			case invoke_virtual:     name = "invoke virtual";     break;
			case new_invoke_special: name = "new invoke special"; break;

			case invoke_static:      name = "invoke static";      break;
			case invoke_special:     name = "invoke special";     break;

			case invoke_interface:   name = "invoke interface";   break;
		}

		fputs("method handle: reference kind = \"", stdout);
		fwrite(name.elements_ptr(), 1, name.size(), stdout);
		fputs("\", ", stdout);

		auto e = entry_map(x.reference_index);

		constant::class_index         class_index;
		constant::name_and_type_index nat_index;

		if((uint8)x.kind >= 1 && (uint8)x.kind <= 4) {
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
			class_index = imr.interface_index;
			nat_index = imr.name_and_type_index;
		}
		fputs(" = { ", stdout);
		print_class(class_index);
		fputs(", ", stdout);
		print_nat(nat_index);
		fprintf(stdout, " }[%hu]", x.reference_index);
	}
	else if constexpr (same_as<Type, constant::method_type>) {
		fputs("method type: ", stdout);
		print_utf8(x.descriptor_index);
	}
	else if constexpr (same_as<Type, constant::dynamic>) {
		printf(
			"dynamic: bootstrap method attr index = %hu, ",
			x.bootstrap_method_attr_index
		);
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::invoke_dynamic>) {
		printf(
			"invoke dynamic: bootstrap method attr index = %hu, ",
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
}