#pragma once

#include <posix/io.hpp>
#include <array.hpp>

void print(integer auto number) {
	for_each_digit_in_number(number, 10, [](nuint digit) {
		posix::std_out().write_from(array{ (char)digit + '0' });
	});
};

template<nuint Size>
void print(const char (&str_array)[Size]) {
	posix::std_out().write_from(c_string{ str_array });
};

template<contiguous_range Range>
void print(Range&& range) {
	posix::std_out().write_from(range);
};