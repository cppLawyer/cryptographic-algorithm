#include <iostream>
#include <string>
#include <fstream>
#include "programManager.h"


int main() {
	//input optional website
	//input username/email
	//input password
	//concept TEST
	programManager program;
	bool autorised;
	do {
		std::string userName, Password;
		std::cin >> userName;
		std::cin >> Password;
		autorised = program.passwordCheck(std::move(userName), std::move(Password));
	} while (!autorised);
    //first step is authorization//

	std::pair<std::string,std::string>* val = program.get_root_data();
	for (uint_fast16_t idx = 0; idx < program.passwordCount; ++idx) {
		std::cout << val[idx].first << std::endl;
		std::cout << val[idx].second << std::endl;
	}
	delete[] val;
	program.insertInformation("James231", "DutchUS1923");


}