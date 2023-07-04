

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"


#include "parameterized.hpp"



//=== Cpp2 type definitions and function declarations ===========================

#ifdef _MSC_VER
#define WIN32_MEAN_AND_LEAN
#include "WinSock2.h"
#endif
#include "parameterized.hpp"
#include "soci/session.h"
#include "soci/rowset.h"
#include "soci/mysql/soci-mysql.h"
#include "pasteur/bind/sql/soci.h"

bool get_name(const std::string &a_prompt, std::string &name) {
    std::cout << a_prompt;
    std::cin >> name;
    return std::cin.good();
}

#line 17 "sql_injection_prevention.cpp2"
auto SqlQuery(cpp2::in<std::string> a_connectionString) -> void;
    
#line 36 "sql_injection_prevention.cpp2"

void TrySqlQuery() {
	// demonstrate automatic sql query parameterization
	try {
		// WARNING: Never put username/password in source code. These are FAKE and
		// only here for demonstration purposes.
		SqlQuery("host=localhost db=demo user=root password=123456");
	}
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

[[nodiscard]] auto main() -> int;
 

//=== Cpp2 function definitions =================================================


#line 17 "sql_injection_prevention.cpp2"
auto SqlQuery(cpp2::in<std::string> a_connectionString) -> void{
    soci::session sql {soci::mysql, a_connectionString}; 

    std::string name {}; 
    if ((!(get_name("Enter username: ", name)))) {
  return ; 
 }

 std::string emailType {}; 
    if ((!(get_name("Enter email type: (private/business)", emailType)))) {
  return ; 
 }

    soci::rowset<std::string> rs {sql << "select email from demo.useremails where username = " + cpp2::embed(name) + " and type=" + cpp2::embed(emailType)}; 

    for ( auto const& email : rs ) {
  std::cout << cpp2::embed(name) + "'s email is " + cpp2::embed(email) + "\n";
 }
}

#line 50 "sql_injection_prevention.cpp2"
[[nodiscard]] auto main() -> int{
 // demonstrate automatic sql query parameterization
 TrySqlQuery();
}

