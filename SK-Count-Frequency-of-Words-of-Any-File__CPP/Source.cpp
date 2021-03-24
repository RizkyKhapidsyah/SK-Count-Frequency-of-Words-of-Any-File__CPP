#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <conio.h>

using namespace std;

bool buildMap();
void writeIndex();
void AddWordtoMap(std::string);

map <string, int> wordMap;

int main(int argc, char** argv) {

	if (buildMap()) {
		cout << "\n The map has " << wordMap.size() << " elements";
		writeIndex();
	}

	_getch();
	return 0;
}

bool buildMap() {

	string filename;

	cout << "\n Enter file name : ";
	cin >> filename;

	ifstream inputFile(filename.c_str());
	string line;

	if (inputFile.is_open()) {
		cout << "\n\n File opened Successfully...\n\n";
		while (getline(inputFile, line)) {
			std::size_t prev = 0, pos;

			while ((pos = line.find_first_of("~`=!@#$%^&*)/\?-_|[,. }] (_-+{;':""></", prev)) != std::string::npos) {
				if (pos > prev) {
					AddWordtoMap(line.substr(prev, pos - prev));
				}
				prev = pos + 1;
			}

			if (prev < line.length()) {
				AddWordtoMap(line.substr(prev, std::string::npos));
			}
		}

		inputFile.close();
	} else {
		cout << "\n-Unable to open file-\n" << endl;
		return false;
	}

	return true;
}

void AddWordtoMap(std::string str) {

	map<string, int> ::iterator it = wordMap.find(str);

	if (it != wordMap.end()) {
		it->second = it->second + 1;
	}
	else {
		wordMap.insert(std::make_pair(str, 1));
	}
}

void writeIndex() {
	for (map<string, int> ::iterator itr = wordMap.begin();
		itr != wordMap.end(); ++itr) {
		std::cout << "\n  " << setw(30) << itr->first << setw(10) << itr->second;
	}
}