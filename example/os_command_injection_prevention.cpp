

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"


#include "parameterized.hpp"



//=== Cpp2 type definitions and function declarations ===========================

#ifdef _MSC_VER
#define WIN32_MEAN_AND_LEAN
#include "WinSock2.h"
#endif
#include <sstream>
#include "parameterized.hpp"

struct systemcmd_parameterized_string_renderer {
	std::stringstream m_strBuilder;
	systemcmd_parameterized_string_renderer() {}

	void render_string(const char* a_str, size_t a_len) {
		m_strBuilder.write(a_str, a_len);
	}

	template<typename ArgT>
	void render_arg(const ArgT& a_arg) {
		// WARNING: This is FAR from being safe. It is very easy to bypass this measure of security!
		// It is only shown for demonstration purposes. A more through approach is needed here.
		// In general, system() can never be made safe (due to shell differences).
		m_strBuilder << '\"' << a_arg << '\"'; // NOTE: This is good for windows command line and bash. Is it good for other shells as well?
	}
};

#line 26 "os_command_injection_prevention_windows_only.cpp2"
[[nodiscard]] auto System(cpp2::in<std::string> a_oscmd) -> int;
 

#line 30 "os_command_injection_prevention_windows_only.cpp2"
[[nodiscard]] auto System(auto const& a_oscmd) -> int;
 

#line 36 "os_command_injection_prevention_windows_only.cpp2"
[[nodiscard]] auto main() -> int;
 

//=== Cpp2 function definitions =================================================


#line 26 "os_command_injection_prevention_windows_only.cpp2"
[[nodiscard]] auto System(cpp2::in<std::string> a_oscmd) -> int{
 return ::system(CPP2_UFCS_0(c_str, a_oscmd)); 
}

[[nodiscard]] auto System(auto const& a_oscmd) -> int{
 systemcmd_parameterized_string_renderer renderer {}; 
 cpp2::render_parameterized_string(renderer, a_oscmd);
 return ::system(CPP2_UFCS_0(c_str, CPP2_UFCS_0(str, std::move(renderer).m_strBuilder))); 
}

[[nodiscard]] auto main() -> int{
 // demonstrate os cmd injection
 auto hostname {"www.google.com & ls"}; 
 // normally (calling system) the above line would cause an os command injection (ls would execute)
 auto x {System("ping " + cpp2::embed(hostname))}; 
}

