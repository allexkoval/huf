#pragma once
#include <string>
#include <fstream>
#include <iostream>


class Info {
private:
	std::string filen;
	std::string packPath;
	std::string tree;


public:
	Info(std::string packedFile, std::string filePath) {
		filen = packedFile;
		packPath = filePath;

	}
	void getInfo(std::string treeSize);
	std::string getFileName(std::string s) {
		return s.substr(s.find_last_of("\\") + 1, s.size());
	}
};

int digs(int w) {
	int yield = 0;
	while (w > 10) {
		yield++;
		w /= 10;
	}
	return yield + 1;
}

void Info::getInfo(std::string treeSize) {
	std::basic_string<char> s_info = "";
	remove((this->packPath + "info.txt").c_str());
	std::ofstream inf((this->packPath + "info.txt").c_str(), std::ios::app | std::ios::out | std::ios::binary);

	if (inf.is_open()) {
		std::string name = getFileName(filen);
		s_info.append(name);
		s_info.append("||");
	}

	int fileNameSize = s_info.size();
	int am = treeSize.size() + 2;
	int res = fileNameSize + am + 2;
	int fd = digs(res);

	if (fd < 5) {
		for (int i = 5 - fd; i > 0; i--) {
			inf << "0";
		}
		//int s = digs(res);
		inf << res;

	}
	inf << "||";
	inf << s_info;
	inf << treeSize;
	inf << "||";
	inf.close();
}
