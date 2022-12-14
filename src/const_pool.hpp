#pragma once

#include "./const_pool_entry.hpp"

#include <span.hpp>

struct const_pool : span<const_pool_entry, uint16> {
	using base_type = span<const_pool_entry, uint16>;
	using base_type::base_type;

	const_pool_entry entry(uint16 index) {
		return base_type::operator[](index - 1);
	};

	template<typename Type>
	Type entry(uint16 index) {
		return entry(index).get_same_as<Type>();
	};

	class_file::constant::_class operator [] (
		class_file::constant::class_index index
	) { return entry<class_file::constant::_class>(index); }
	
	class_file::constant::utf8 operator [] (
		class_file::constant::utf8_index index
	) { return entry<class_file::constant::utf8>(index); }

	class_file::constant::name_and_type operator [] (
		class_file::constant::name_and_type_index index
	) { return entry<class_file::constant::name_and_type>(index); }

	class_file::constant::method_ref operator [] (
		class_file::constant::method_ref_index index
	) { return entry<class_file::constant::method_ref>(index); }
	
	class_file::constant::interface_method_ref operator [] (
		class_file::constant::interface_method_ref_index index
	) { return entry<class_file::constant::interface_method_ref>(index); }

	class_file::constant::field_ref operator [] (
		class_file::constant::field_ref_index index
	) { return entry<class_file::constant::field_ref>(index); }

};
