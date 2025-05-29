#include <format>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool readFile(const string file, string &content);
void writeToFile(const string content, const string inputFileName,
				 ofstream &outputFile);
void printHelp();

int main(int argc, char *argv[]) {
	vector<string> files = {"urls.py", "views.py"};
	ifstream inputFile;
	ofstream outputFile;
	string outputFileName = "fullcode.txt";
	// для пользовательских файлов
	vector<string> userFiles;
	bool captureInputFiles = false;

	// пробег по флагам
	for (int i = 1; i < argc; i++) {
		string arg = argv[i];

		if (captureInputFiles) {
			// если следующий аргумент флаг, заканчиваем захват файлов
			if (!arg.empty() && arg[0] == '-') {
				captureInputFiles = false;
				i--;
			} else {
				userFiles.push_back(arg);
			}
		} else if (arg == "--files") {
			captureInputFiles = true;
		} else if (arg == "-o") {
			if (i + 1 < argc) {
				outputFileName = argv[++i];
			} else {
				cerr << "Ошибка: -o требует имя файла вывода" << endl;
				return 1;
			}
		} else if (arg == "-h" | arg == "--help") {
			printHelp();
			return 0;
		}
	}

	outputFile.open(outputFileName);

	// если пользователь ввел свои файлы, то заготовленные файлы заменяются на
	// пользовательские
	if (!userFiles.empty()) {
		files = userFiles;
	}

	// пробег по всем файлам из списка
	string content;
	for (string file : files) {
		if (readFile(file, content)) {
			// запись в файл
			writeToFile(content, file, outputFile);
		}
	}
	outputFile.close();
	return 0;
}

bool readFile(const string file, string &content) {
	// открытие файла
	ifstream inputFile(file);

	// проверка открыт ли файл, если нет - вывод сообщения ошибки и переход
	// к следующему
	if (!inputFile.is_open()) {
		cerr << "Файл " << file << " не открыт!" << endl;
		return false;
	} else {
		cout << "Файл " << file << " открыт успешно!" << endl;
	}

	// чтение сырого файла
	stringstream buffer;
	buffer << inputFile.rdbuf();
	content = buffer.str();
	inputFile.close();
	return true;
}

void writeToFile(const string content, const string inputFileName,
				 ofstream &outputFile) {
	outputFile << "start of " << inputFileName << endl;
	outputFile << content << endl;
	outputFile << "end of " << inputFileName << endl;
}

void printHelp() {
	cout << "-o - выбор для файла, в который будет записываться вывод\n"
		 << "--files - ввод файлов для записи\n";
}
