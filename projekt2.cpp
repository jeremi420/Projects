//POP 2017-01-23 projekt 2 Wielewski Jeremi EiT 8 161317 visual studio 2015
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

char* RandCharsAscii(int first, int last);
char* TworzTabele();

void KodujPlik(string inputFileName, string outputFileName) {
	string line;
	ifstream inputFile;
	ofstream outputFile;
	system("del output.txt");
	system("copy NUL output.txt");
	char* tabela = TworzTabele();
	inputFile.open(inputFileName);
	outputFile.open(outputFileName);
	if (inputFile.is_open() && outputFile.is_open()) {
		while (getline(inputFile, line)) {
			for (int i = 0; i < line.size(); i++) {
				for (int j = 65; j <= 90; j++) {
					if (line[i] == (char)j) {
						line[i] = tabela[j - 65];
					}
				}
				for (int j = 97; j <= 122; j++) {
					if (line[i] == (char)j) {
						line[i] = tabela[j - 71];
					}
				}
			}
			outputFile << line << "\n";
		}
		string echo = "echo ";
		string output = " > output.txt:str";
		string command(tabela);
		echo += command;
		echo += output;
		inputFile.close();
		outputFile.close();
		system(echo.c_str());
	}
	else { cout << "unable to open"; }
}

char* RandCharsAscii(int first, int last) {
	
	int random;
	int length = last - first + 1;
	char* array = new char[length];
	bool* CzyZajete = new bool[length];
	for (int i = 0; i < length; i++)
	{
		array[i] = ' ';
		CzyZajete[i] = false;
	}
	for (int i = first; i <= last; i++) {
		while (array[i - first] == ' ') {
			random = (rand() % length) + first;
			if (!CzyZajete[random - first]) {
				array[i - first] = (char)random;
				CzyZajete[random - first] = true;
			}
		}
	}
	return array;
}

char* TworzTabele() {
	char* tabela;
	tabela = RandCharsAscii(65, 90);
	char* male = RandCharsAscii(97, 122);
	for (int i = 26; i < 52; i++) {
		tabela[i] = male[i - 26];
	}
	return tabela;
}

int main() {
	string fileName;
	srand(time(NULL));
	cout << "podaj plik do zakodowania" << endl;
	cin >> fileName;
	KodujPlik(fileName, "output.txt");
	system("CLS");
	TworzTabele();
	system("PAUSE");
}