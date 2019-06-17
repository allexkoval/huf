#include "packing.h"
#include "unpacking.h"




int main(int argc, char* argv[]) {
	Zip *zip = new Zip("C:\\test\\act.png", "C:\\test");
	zip->zipping();
	std::cout << "Zipping Done" << std::endl;
	//std::cout << "Starting..." << std::endl;
	Unzip *unz = new Unzip("C:\\test\\unpack");
	unz->unzipping("C:\\test\\zipped.zipp");
	std::cout << "Unzipping Done" << std::endl;
	system("Pause");



	/*
	ifstream unpack("C:\\test\\output.zipp", ios::out | ios::binary);
	ofstream output("C:\\test\\unzipped.txt", ios::out | ios::binary);
	Node *p = root;
	count = 0;
	char byte = unpack.get();
	while (!unpack.eof()) {
		bool b = byte & (1 << (7 - count));
		if (b) p = p->right; else p = p->left;
		if (p->left == NULL && p->right == NULL) {
			output << p->c;
			p = root;
		}
		count++;
		if (count == 8) {
			count = 0;
			byte = unpack.get();
		}
	}
	cout << endl;
	unpack.close();
	output.close();
	system("Pause");
	return 0;
	*/
}