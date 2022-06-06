#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H
#include "passwordPropertie.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
#include <vector>
class passwordManager {
	uint_fast16_t passwordCount = 0;
	std::ofstream writeData;
	std::ifstream readData;
	uint_fast16_t uniqueNumber;

	inline void EncoderAlgorithm() noexcept {
		writeData.open("HashPassword.bin", std::ios_base::binary);
		for (uint_fast16_t it = 0; it < passwordRegister.size(); ++it) {
			std::string data = std::move(passwordRegister[it].originalUserName + passwordRegister[it].originalPassword);
			passwordRegister[it].hashData = (std::move(std::to_string(passwordRegister[it].originalUserName.size()) + ":"));
			for (uint_fast16_t itx = 0; itx < data.size(); ++itx)
				passwordRegister[it].hashData += (data[itx] + itx - data.size() - (uniqueNumber / (itx + 1)));
			writeData << passwordRegister[it].hashData << std::endl;
		}
		writeData.flush();
		writeData.close();
		return;
	}

	inline void DecoderAlgorithm() noexcept {
		//readData//
		readData.open("HashPassword.bin", std::ios_base::binary);
		if(!readData.is_open())
			      return;
		
		
		while(!readData.eof()){
			uint_fast8_t sizeUserName;
			std::string firstLine;
			readData >> firstLine;
			if(firstLine.empty()) {
				readData.close();
				passwordCount = 0;
				return;
			}
			std::istringstream dataStream(firstLine);
			std::string userNameSize;
			std::getline(dataStream, userNameSize, ':');
			sizeUserName = std::stoi(userNameSize);
			firstLine.erase(firstLine.begin(), firstLine.begin() + userNameSize.size() + 1);
			passwordRegister.emplace_back(std::move(firstLine));
			std::string tempUsername, tempPassword;

			for (uint_fast16_t it = 0; it < passwordRegister[passwordCount].hashData.size(); ++it) {
				if (it < sizeUserName) {
					tempUsername += (passwordRegister[passwordCount].hashData[it] - it + passwordRegister[passwordCount].hashData.size() + (uniqueNumber / (it + 1)));
				}
				else {
					tempPassword += (passwordRegister[passwordCount].hashData[it] - it + passwordRegister[passwordCount].hashData.size() + (uniqueNumber / (it + 1)));
				}
			}
			passwordRegister[passwordCount].originalUserName = std::move(tempUsername);
			passwordRegister[passwordCount++].originalPassword = std::move(tempPassword);
		}
		readData.close();
	}
public:
	std::vector<passwordPropertie> passwordRegister;
	inline passwordManager(uint_fast16_t uniqueTemp):uniqueNumber(uniqueTemp) {
		DecoderAlgorithm();
	}
	inline ~passwordManager() noexcept{
		EncoderAlgorithm();
	}


};

#endif // !PASSWORDMANAGER_H
