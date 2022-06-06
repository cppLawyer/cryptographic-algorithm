#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H
#include "passwordManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
class programManager {
	std::string logInUsername;
	std::string logInPassword;
	std::string hashData;
	bool authorised = false;
	bool firstTime = false;
	passwordManager* pwp;
    inline void dataEncryption() noexcept{
        std::string data(std::move(logInUsername + logInPassword));
        hashData.clear();
        for (uint_fast16_t index = 0; index < data.size(); ++index)
             hashData += (data[index] + index - data.size() - (10 / (index + 1)));

        std::ofstream writeData("cred.key", std::ios_base::binary);
        writeData << (std::to_string(logInUsername.size()) + ":" + hashData);
        writeData.flush();
        writeData.close();
    }

    inline void dataDecryption() noexcept {
        std::ifstream readData;
        readData.open("cred.key", std::ios_base::binary);
        if (!readData.is_open()) {
            firstTime = true;
            return;
        }
        std::string firstLine;
        readData >> firstLine;
        std::istringstream dataStream(firstLine);
        std::string userNameSize;
        std::getline(dataStream, userNameSize, ':');
        firstLine.erase(firstLine.begin(), firstLine.begin() + userNameSize.size() + 1);
        uint_fast16_t sizeUserName = std::stoi(userNameSize);
        readData.close();
        std::string deCryptedHash;
        for (uint_fast16_t index = 0; index < firstLine.size(); ++index)
             deCryptedHash += (firstLine[index] - index + firstLine.size() + (10 / (index + 1)));

        hashData = std::move(firstLine);
        logInUsername = std::move(deCryptedHash.substr(0,sizeUserName));
        logInPassword = std::move(deCryptedHash.substr(sizeUserName, deCryptedHash.size()));
        std::cout << logInPassword;
        std::cout << logInUsername;
    }
public:
	uint_fast16_t passwordCount;
	std::pair<std::string,std::string>* get_root_data() noexcept {
			passwordCount = pwp->passwordRegister.size();
		std::pair<std::string, std::string>* mainData = new std::pair<std::string, std::string>[passwordCount];
		for (uint_fast16_t idx = 0; idx < passwordCount; ++idx)
			 mainData[idx] = (std::move(std::pair<std::string, std::string>(pwp->passwordRegister[idx].originalUserName, pwp->passwordRegister[idx].originalPassword)));
		
		return mainData;
	}
	inline constexpr bool passwordCheck(const std::string&& tmpUser, const std::string&& tmpWW) noexcept{
		if (firstTime) {
			logInUsername = tmpUser;
			logInPassword = tmpWW;
			pwp = new passwordManager(logInUsername[0]);
			return (authorised = true);
		}
		else {
			if (tmpUser == logInUsername) {
				if (tmpWW == logInPassword) {
					pwp = new passwordManager(logInUsername[0]);
					return (authorised = true);
				}
			}
		}
		std::cout << "Try Again\n";
		return false;
	}
	programManager() {
		dataDecryption();
	}
	inline constexpr void insertInformation(std::string&& userName, std::string&& password, std::string&& website) noexcept {
		if (!authorised)
			return;
		pwp->passwordRegister.emplace_back(userName, password, website);
	}

	inline constexpr void insertInformation(std::string&& userName, std::string&& password) noexcept {
		if (!authorised)
			return;
		pwp->passwordRegister.emplace_back(userName, password);
	}

	~programManager() {
		dataEncryption();
		delete pwp;
	}
};

#endif
