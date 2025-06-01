#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>
using namespace std;
class Field {
  private:
	vector<vector<char>> field;
	bool isRunning = true;
	int rows;
	int cols;
	void createField(int rows, int cols) {
		field.resize(rows, vector<char>(cols, 'n'));
	};
	// проверяет, пустая ли клетка
	bool checkCellIsEmpty(int cell) {
		int cellIdx = cell - 1;
		int row = cellIdx / cols;
		int col = cellIdx % cols;

		// Проверка выхода за границы
		if (row < 0 || row >= rows || col < 0 || col >= cols) {
			return false;
		}

		return field[row][col] == 'n';
	}
	// отрисовывает поле
	void printField() const {
		system("clear");
		for (int i = 0; i < field.size(); i++) {
			for (int c = 0; c < field[i].size(); c++) {
				if (field[i][c] == 'n') {
					cout << i * cols + c + 1;
				} else {
					cout << field[i][c];
				};
			}
			cout << endl;
		};
	};
	// запись действия игрока
	int getPlayerCell() {
		string userInput;
		int userInt;
		while (true) {
			cout << "Введите номер клетки: ";
			cin >> userInput;
			try {
				userInt = stoi(userInput);
				return userInt;
			} catch (const invalid_argument) {
				cerr << "Введите число" << endl;
			} catch (const out_of_range) {
				cerr << "Число слишком большое" << endl;
			}
		};
		return userInt;
	}

  public:
	// констурктор поля, создает его забирая длину и ширину + создает поле
	Field(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		createField(rows, cols);
	}
	// главный цикл
	void mainloop() {
		do {
			this->printField();
			this->getPlayerCell();
		} while (this->isRunning);
	}
};

int main() {
	Field field(3, 3);
	field.mainloop();
}
