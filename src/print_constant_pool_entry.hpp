#pragma once

#include "./print.hpp"
#include "./const_pool_entry.hpp"

#include <class_file/constant.hpp>
#include <absolute.hpp>

#include <c_string.hpp>
#include <posix/abort.hpp>

template<typename Type>
static void print_constant_pool_entry(
	Type x, auto entry_map
) {
	using namespace class_file;

	auto print_utf8 = [&](uint16 index) {
		constant::utf8 u = entry_map(index).template get<constant::utf8>();
		print("\"");
		print(u);
		print("\"[");
		print(index);
		print("]");
	};

	auto print_class = [&](uint16 index) {
		constant::_class c = entry_map(index).template get<constant::_class>();
		print("class = { ");
		print_utf8(c.name_index);
		print(" }[");
		print(index);
		print("]");
	};

	auto print_nat = [&](uint16 index) {
		constant::name_and_type n =
			entry_map(index).template get<constant::name_and_type>();
		print("name and type = { ");
		print_utf8(n.name_index);
		print(", ");
		print_utf8(n.descriptor_index);
		print(" }[");
		print(index);
		print("]");
	};

	if constexpr (same_as<Type, constant::utf8>) {
		print("utf8: \"");
		print(x);
		print("\"");
	}
	else if constexpr (same_as<Type, constant::_int>) {
		print("integer: ");
		print(x.value);
	}
	else if constexpr (same_as<Type, constant::_float>) {
		print("float: ");
		print((int32)x.value);
		print(".");
		print((nuint)(absolute(x.value - (int32)x.value) * 4.0F));
	}
	else if constexpr (same_as<Type, constant::_long>) {
		print("long: ");
		print(x.value);
	}
	else if constexpr (same_as<Type, constant::_double>) {
		print("double: ");
		print((int64)x.value);
		print(".");
		print((nuint)(absolute(x.value - (int64)x.value) * 8.0F));
	}
	else if constexpr (same_as<Type, constant::_class>) {
		print("class: ");
		print_utf8(x.name_index);
	}
	else if constexpr (same_as<Type, constant::string>) {
		print("string: \"");
		print_utf8(x.string_index);
	}

	else if constexpr (same_as<Type, constant::field_ref>) {
		print("field ref: ");
		print_class(x.class_index);
		print(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::method_ref>) {
		print("method ref: ");
		print_class(x.class_index);
		print(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::interface_method_ref>) {
		print("interface method ref: ");
		print_class(x.interface_index);
		print(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::name_and_type>) {
		print("name and type: name = ");
		print_utf8(x.name_index);
		print(", descriptor = ");
		print_utf8(x.descriptor_index);
	}
	else if constexpr (same_as<Type, constant::method_handle>) {
		c_string<c_string_type::known_size> name;

		using enum constant::method_handle::behavior_kind;
		switch (x.kind) {
			case get_field:
				name = c_string{ "get field" };          break;
			case get_static:
				name = c_string{ "get static" };         break;
			case put_field:
				name = c_string{ "put field" };          break;
			case put_static:
				name = c_string{ "put static" };         break;

			case invoke_virtual:
				name = c_string{ "invoke virtual" };     break;
			case new_invoke_special:
				name = c_string{ "new invoke special" }; break;

			case invoke_static:
				name = c_string{ "invoke static" };      break;
			case invoke_special:
				name = c_string{ "invoke special" };     break;

			case invoke_interface:
				name = c_string{ "invoke interface" };   break;
		}

		print("method handle: reference kind = \"");
		print(name);
		print("\", ");

		auto e = entry_map(x.reference_index);

		constant::class_index         class_index;
		constant::name_and_type_index nat_index;

		if((uint8)x.kind >= 1 && (uint8)x.kind <= 4) {
			constant::field_ref fr =
				e.template get<constant::field_ref>();
			print("field ref");
			class_index = fr.class_index;
			nat_index = fr.name_and_type_index;
		}
		else if(e.template is<constant::method_ref>()) {
			constant::method_ref mr =
				e.template get<constant::method_ref>();
			print("method ref");
			class_index = mr.class_index;
			nat_index = mr.name_and_type_index;
		}
		else {
			constant::interface_method_ref imr =
				e.template get<constant::interface_method_ref>();
			print("interface method ref");
			class_index = imr.interface_index;
			nat_index = imr.name_and_type_index;
		}
		print(" = { ");
		print_class(class_index);
		print(", ");
		print_nat(nat_index);
		print(" }[");
		print((uint16) x.reference_index);
		print("]");
	}
	else if constexpr (same_as<Type, constant::method_type>) {
		print("method type: ");
		print_utf8(x.descriptor_index);
	}
	else if constexpr (same_as<Type, constant::dynamic>) {
		print("dynamic: bootstrap method attr index = ");
		print(x.bootstrap_method_attr_index);
		print(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::invoke_dynamic>) {
		print("invoke dynamic: bootstrap method attr index = ");
		print(x.bootstrap_method_attr_index);
		print(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::module>) {
		print("module: ");
		print_utf8(x.name_index);
	}
	else if constexpr (same_as<Type, constant::package>) {
		print("package: ");
		print_utf8(x.name_index);
	}
	else if constexpr (same_as<Type, constant::unknown>) {
		printf("unknown tag: %d", x); abort();
	}
	else {
		printf("unimplemented tag: %d", Type::tag); abort();
	}

	print("\n");
}