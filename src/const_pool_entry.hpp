#pragma once

#include <core/meta/elements/one_of.hpp>
#include <core/meta/elements/none.hpp>
#include <class/file/constant.hpp>

using const_pool_entry_base_type = elements::one_of<
	elements::none,
	class_file::constant::utf8,
	class_file::constant::_int,
	class_file::constant::_float,
	class_file::constant::_long,
	class_file::constant::_double,
	class_file::constant::_class,
	class_file::constant::string,
	class_file::constant::field_ref,
	class_file::constant::method_ref,
	class_file::constant::interface_method_ref,
	class_file::constant::name_and_type,
	class_file::constant::method_handle,
	class_file::constant::method_type,
	class_file::constant::dynamic,
	class_file::constant::invoke_dynamic,
	class_file::constant::module,
	class_file::constant::package
>;

struct const_pool_entry : const_pool_entry_base_type {

	using base_type = const_pool_entry_base_type;

	using base_type::base_type;

	const_pool_entry() : base_type{ elements::none{} } {}

};