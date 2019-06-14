#pragma once
#include "Node.h"
#include <fstream>
#include <vector>
//#include <iostream>

class Unzip {
private:
	std::string path;
public:
	Unzip(std::string pathh) {
		path = pathh + "\\";
	}
	void unzipping(std::string fl);
};

void Unzip::unzipping(std::string fl) {
	std::ifstream inp(fl.c_str(), std::ios::out | std::ios::binary);
	char info_block_size[5];
	inp.read(info_block_size, 5);
	int size = atoi(info_block_size);
	char* infoBlock = new char[size];
	inp.read(infoBlock, size);
	std::vector<std::string> tokens;
	char *tok = strtok(infoBlock, "||");
	
	while (tok) {
		if (strlen(tok) == 0) break;
		tokens.push_back(tok);
		tok = strtok(NULL, "||");
	}
	char byte[1];

	std::string name = tokens[0].c_str();
	std::string vocab = tokens[1].c_str();
	std::string tree = tokens[1].c_str();

	std::string fullPath = path + name;

	//TODO build a tree

	std::ofstream unzip(fullPath, std::ios::out | std::ios::binary);

	//TODO unzipping


	unzip.close();
}