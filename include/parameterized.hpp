#pragma once

#include <iostream>
#include <string>
#include <exception>
//#include <sstream>
#include <utility>
#include "pasteur/pstr.h"

namespace cpp2 {

using namespace pstr;

struct ostream_parameterized_string_renderer {
	std::ostream& m_os;
	ostream_parameterized_string_renderer(std::ostream& a_os) : m_os(a_os) {}

	void render_string(const char* a_str, size_t a_len) {
		m_os.write(a_str, a_len);
	}

	template<typename ArgT>
	void render_arg(const ArgT& a_arg) {
		m_os << ::cpp2::to_string(a_arg);
	}
};

} // cpp2

template<size_t NUM_FORMAT_STRINGS, typename... Args>
auto operator<<(std::ostream &a_os, const pstr::parameterized_string<NUM_FORMAT_STRINGS, Args...> &a_parameterized) -> std::ostream& {
	pstr::render_parameterized_string(cpp2::ostream_parameterized_string_renderer(a_os), a_parameterized);
	return a_os;
}

