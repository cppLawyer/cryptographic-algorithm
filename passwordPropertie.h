#ifndef PASSWORDPROPERTIE_H
#define PASSWORDPROPERTIE_H
#include <string>


struct passwordPropertie{
	std::string originalPassword;
	std::string originalUserName;
	std::string websiteURL;
	std::string hashData;
	inline passwordPropertie(std::string&& HashUW):hashData(std::move(HashUW)) {}
	inline passwordPropertie(std::string& originalUserName, std::string& originalPassword) : 
		originalUserName(std::move(originalUserName)), originalPassword(std::move(originalPassword)) {
	}
	inline passwordPropertie(std::string& originalUserName, std::string& originalPassword, std::string& webiste) :
		originalUserName(std::move(originalUserName)), originalPassword(std::move(originalPassword)),websiteURL(std::move(webiste)) {
	}
	passwordPropertie() = delete;
};

#endif // !PASSWORDPROPERTIE_H
