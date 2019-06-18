#pragma once
#include "Node.h"
#include <vector>
#include <fstream>
#include <list>
#include <string>
#include <map>
#include "info.h"

class Zip {
private:
	std::string filename;
	std::string path;
	std::string zippedFile;
	std::vector<bool> code;
	std::map<char, std::vector<bool> > table;
	std::list<Node*> t;
	std::string vocab = "";
	std::string writeTree = "";

public:
	Zip(std::string fileToPack, std::string pathToFile) {
		filename = fileToPack;
		path = pathToFile + "\\";
		zippedFile = path + "zipped.zipp";
	}


	struct MyCompare {
		bool operator()(Node *l, Node *r) const {
			return l->a < r->a;
		}
	};
	void zipping();
	void BuildTable(Node *root);
	void treeTable(Node *root);
};

void Zip::zipping() {
	std::ifstream inpFile(filename.c_str(), std::ios::out | std::ios::binary);
	std::map<char, int> m;
	char b = inpFile.get();
	while (!inpFile.eof())
	{
		m[b]++;
		b = inpFile.get();
	}
	std::map<char, int>::iterator i;
	for (i = m.begin(); i != m.end(); ++i)
	{
		Node *p = new Node();
		p->c = i->first;
		p->a = i->second;
		t.push_back(p);
	}
	//creating a tree
	while (t.size() != 1) {
		t.sort(MyCompare());
		Node *SonL = t.front();
		t.pop_front();
		Node *SonR = t.front();
		t.pop_front();

		Node *parent = new Node(SonL, SonR);
		t.push_back(parent);
	}

	Node *root = t.front();		//tree root												
	BuildTable(root);
	treeTable(root);
	writeTree = vocab + "||" + writeTree;
	inpFile.clear();
	inpFile.seekg(0);

	std::ofstream out(zippedFile.c_str(), std::ios::out | std::ios::binary);
	
	Info * inf = new Info(filename, path);
	inf->getInfo(writeTree);
	
	std::ifstream info((path + "info.txt").c_str(), std::ios::out | std::ios::binary);
	char c = info.get();
	while (!info.eof()) {
		out.put(c);// << c;
		c = info.get();
	}
	int count = 0;
	char buf = 0;

	while (!inpFile.eof()) {
		c = inpFile.get();
		std::vector<bool> x = table[c];
		for (int n = 0; n < x.size(); n++)
		{
			buf = buf | x[n] << (7 - count);
			count++;
			if (count == 8) {
				count = 0;
				out.put(buf);// << buf;
				buf = 0;
			}
		}

	}
	inpFile.close();
	out.close();
}

void Zip::treeTable(Node *root) {
	if (root->left != NULL) {
		writeTree.append("D");
		treeTable(root->left);
	}
	if (root->right != NULL) {
		writeTree.append("U");
		treeTable(root->right);
	}
};

void Zip::BuildTable(Node *root) {
	if (root->left != NULL) {
		code.push_back(0);
		BuildTable(root->left);
	}
	if (root->right != NULL) {
		code.push_back(1);
		BuildTable(root->right);
	}
	if (root->left == NULL && root->right == NULL) {
		table[root->c] = code;
		vocab += root->c;
	}
	if (!code.empty())
		code.pop_back();
};