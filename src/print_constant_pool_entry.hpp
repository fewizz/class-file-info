#pragma once

#include "./const_pool.hpp"

#include <class_file/constant.hpp>

#include <c_string.hpp>
#include <number.hpp>

#include <posix/abort.hpp>

#include <print/print.hpp>

template<typename Type>
static void print_constant_pool_entry(
	Type x, const_pool const_pool
) {
	using namespace class_file;

	auto print_utf8 = [&](constant::utf8_index index) {
		constant::utf8 u = const_pool[index];
		print::out("\"", u, "\"[", (uint16) index, "]");
	};

	auto print_class = [&](constant::class_index index) {
		constant::_class c = const_pool[index];
		print::out("class = { ");
		print_utf8(c.name_index);
		print::out(" }[", (uint16) index, "]");
	};

	auto print_nat = [&](constant::name_and_type_index index) {
		constant::name_and_type n = const_pool[index];
		print::out("name and type = { ");
		print_utf8(n.name_index);
		print::out(", ");
		print_utf8(n.descriptor_index);
		print::out(" }[", (uint16) index, "]");
	};

	if constexpr (same_as<Type, constant::utf8>) {
		print::out("utf8: \"", x, "\"");
	}
	else if constexpr (same_as<Type, constant::_int>) {
		print::out("integer: ", x.value);
	}
	else if constexpr (same_as<Type, constant::_float>) {
		print::out("float: ", x.value);
	}
	else if constexpr (same_as<Type, constant::_long>) {
		print::out("long: ", x.value);
	}
	else if constexpr (same_as<Type, constant::_double>) {
		print::out("double: ", x.value);
	}
	else if constexpr (same_as<Type, constant::_class>) {
		print::out("class: ");
		print_utf8(x.name_index);
	}
	else if constexpr (same_as<Type, constant::string>) {
		print::out("string: \"");
		print_utf8(x.string_index);
	}

	else if constexpr (same_as<Type, constant::field_ref>) {
		print::out("field ref: ");
		print_class(x.class_index);
		print::out(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::method_ref>) {
		print::out("method ref: ");
		print_class(x.class_index);
		print::out(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::interface_method_ref>) {
		print::out("interface method ref: ");
		print_class(x.interface_index);
		print::out(", ");
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::name_and_type>) {
		print::out("name and type: name = ");
		print_utf8(x.name_index);
		print::out(", descriptor = ");
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

		print::out("method handle: reference kind = \"", name, "\", ");

		const_pool_entry e = const_pool.entry(x.reference_index);

		constant::class_index         class_index;
		constant::name_and_type_index nat_index;

		if((uint8)x.kind >= 1 && (uint8)x.kind <= 4) {
			constant::field_ref fr =
				e.template get_same_as<constant::field_ref>();
			print::out("field ref");
			class_index = fr.class_index;
			nat_index = fr.name_and_type_index;
		}
		else if(e.template is_same_as<constant::method_ref>()) {
			constant::method_ref mr =
				e.template get_same_as<constant::method_ref>();
			print::out("method ref");
			class_index = mr.class_index;
			nat_index = mr.name_and_type_index;
		}
		else {
			constant::interface_method_ref imr =
				e.template get_same_as<constant::interface_method_ref>();
			print::out("interface method ref");
			class_index = imr.interface_index;
			nat_index = imr.name_and_type_index;
		}
		print::out(" = { ");
		print_class(class_index);
		print::out(", ");
		print_nat(nat_index);
		print::out(" }[", (uint16) x.reference_index, "]");
	}
	else if constexpr (same_as<Type, constant::method_type>) {
		print::out("method type: ");
		print_utf8(x.descriptor_index);
	}
	else if constexpr (same_as<Type, constant::dynamic>) {
		print::out(
			"dynamic: bootstrap method attr index = ",
			x.bootstrap_method_attr_index,
			", "
		);
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::invoke_dynamic>) {
		print::out(
			"invoke dynamic: bootstrap method attr index = ",
			x.bootstrap_method_attr_index,
			", "
		);
		print_nat(x.name_and_type_index);
	}
	else if constexpr (same_as<Type, constant::module>) {
		print::out("module: ");
		print_utf8(x.name_index);
	}
	else if constexpr (same_as<Type, constant::package>) {
		print::out("package: ");
		print_utf8(x.name_index);
	}
	else if constexpr (same_as<Type, constant::unknown>) {
		print::err("unknown tag: ", x, "\n");
		posix::abort();
	}
	else {
		print::err("unimplemented tag: ", Type::tag, "\n");
		posix::abort();
	}

	print::out("\n");
}