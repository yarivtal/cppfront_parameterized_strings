

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"


#include "parameterized.hpp"



//=== Cpp2 type definitions and function declarations ===========================

#include "parameterized.hpp"
#include "spdlog/spdlog.h"
#include "pasteur/bind/log/spdlog.h"

#line 5 "log_forgery_prevention.cpp2"
[[nodiscard]] auto main() -> int;
 

//=== Cpp2 function definitions =================================================


#line 5 "log_forgery_prevention.cpp2"
[[nodiscard]] auto main() -> int{
 // demonstarte logging (with automatic sanitization)
 auto userUnsanitizedInput {"some bad thing\n[2023-04-14 00:39:23.260] [info] All ok "}; 
 // normally the above user inputs causes injection of an extra line
 spdlog::info("User entered {}", userUnsanitizedInput);
 // with string interpolation newlines are automatically sanitized
 spdlog::info("User entered " + cpp2::embed(std::move(userUnsanitizedInput)));
}

