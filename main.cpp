#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::fstream ofs;

class FunctionProcessingMatrix
{
public:
	// Запуск программы и приветсивие 
	void WelcomeStartProgramm()
	{
		std::cout << "The Matrix Processing program welcomes you!\n";
		std::cout << "\nDo you want to connect past requests? Enter Y or N!\n";

		// Проверка на введенный символ Y или N, ответ на вопрос нужно ли использовать прошлые матрицы
		while (std::cin >> answer)
		{
			if (answer == 'Y')
			{
				// Ответ Y (да) проверяется наличие файла log.txt
				ofs.open("log.txt");
				if (ofs.is_open())
				{
					coutMatrixOfTheFile();
					if (countMatrix == 0)
					{
						// Если отсутсвуют записи то Создаем матрицу
						std::cout << "\nYou don't have any old requests!\n";
						std::vector<std::vector<double>> matrix = createMatrix();
						actionBindFunction(matrix);
						break;
					}
					else
					{
						// Если есть записи о матрица в файле log.txt выводим все матрицы на экран
						std::vector<std::vector<double>> matrix = SelectMatrixInTheFile();
						actionBindFunction(matrix);
						break;
					}
				}
				else
				{
					// Если файл отсутсвует то создаем
					std::cout << "You don't have any old requests!\n";
					std::ofstream ofs("log.txt");
					std::vector<std::vector<double>> matrix = createMatrix();
					actionBindFunction(matrix);
					break;
				}
			}
			else if (answer == 'N')
			{
				// Если пользователь не хочет использвовать старые записи, создаем новые и записываем
				std::vector<std::vector<double>> matrix = createMatrix();
				actionBindFunction(matrix);
				break;
			}
			else
			{
				std::cout << "Fatal error!";
				break;
			}
		}

	}

public:
	void actionBindFunction(const std::vector<std::vector<double>>& matrix)
	{
		// Функции по обработки матрицы 
		std::cout << "\nPlease, choose an action and enter number the action!\n";
		std::cout << "\nSummation of all matrix values (1) \n";
		std::cout << "Subtraction of all matrix values (2) \n";
		std::cout << "Products of matrix elements by rows (3) \n";
		std::cout << "Products of matrix elements by columns (4) \n";
		std::cout << "Finding the average mathematical number (5) \n";
		std::cout << "Finding maximal number (6) \n";
		std::cout << "Finding minimal number (7) \n";
		std::cout << "Exit (0)\n\n";

		bool IsExit = false;
		char action;
		while (std::cin >> action)
		{
			switch (action)
			{
			case '1':
				std::cout << "Summation of all matrix values -> " << SumAllValuesTheMatrix(matrix) << "\n";
				break;

			case '2':
				std::cout << "Subtraction of all matrix values -> " << SubtractionAllValuesTheMatrix(matrix) << "\n";
				break;

			case '3':
				std::cout << "Products of matrix elements by rows -> " << ProductsTheMatrixElementsByRows(matrix) << "\n";
				break;

			case '4':
				std::cout << "Products of matrix elements by columns -> " << ProductsTheMatrixElementsByColumns(matrix) << "\n";
				break;

			case '5':
				std::cout << "Finding the average mathematical number -> " << FindTheAverageMathematicalNmberconstTheMatrix(matrix, rowN, colM) << "\n";
				break;

			case '6':
				std::cout << "Finding maximal number -> " << FindMaxValueTheMatrix(matrix) << "\n";
				break;

			case '7':
				std::cout << "Finding minimal number -> " << FindMinValueTheMatrix(matrix) << "\n";
				break;

			case '0':
				std::cout << "\nThank you for using the Matrix Processing program!\n";
				IsExit = true;
				break;

			default:
				std::cout << "Fatal error!\n";
			}
			if (IsExit) break;
		}
	}

	std::vector<std::vector<double>> fillingMatrix(int& row, int& col)
	{
		// создаие матрицы и иницализация 0.0 по размерам row, col
		std::vector<std::vector<double>> matrix(row, std::vector<double>(col));

		// Проверка открыт ли файл еслинет прпосим перезапустить программу
		ofs.open("log.txt", std::ios::app);
		if (!ofs.is_open())
		{
			std::cout << "Fatal error! Reload Programm.\n";
			return matrix;
		}
		ofs << "&\n";

		// Заполнение матрицы пользователем
		for (int i = 0; i != row; ++i)
		{
			for (int j = 0; j != col; ++j)
			{
				// инициализация и сохраение матрицы
				std::cin >> matrix[i][j];
				ofs << matrix[i][j] << " s ";
			}

			ofs << " e\n";
		}
		ofs.close();

		return matrix;
	}

	// Фукция проверки пользователем правильо ли о загрузил матрицу, если нет то дает повторную попытку 
	bool IsCheckValidEnterMatrix(const std::vector<std::vector<double>>& matrix, int& row, int& col)
	{
		for (int i = 0; i != row; ++i)
		{
			for (int j = 0; j != col; ++j)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "\nIf everything is correct, enter Y, if not, then N\n";

		char enterCh;
		std::cin >> enterCh;

		// Проверка какой символ был введен Y или N 
		if (enterCh == 'Y') return true;
		else if (enterCh == 'N') return false;
		else std::cout << "Fatal error!";
	}
private:
	char answer;
	int countMatrix = 0;
	int rowN = 0;
	int colM = 0;

private:
	// Выбор матрицы для использование по обработки матриц
	std::vector<std::vector<double>> SelectMatrixInTheFile()
	{
		std::cout << "\nPlease, select a matrix from the list and enter a number!\n";

		int selectMatrix = 0;
		std::cin >> selectMatrix;

		if (selectMatrix > countMatrix) ErrorFunction();

		int row = 0;
		int col = 0;
		int selectMatrix_temp = selectMatrix;
		
		ofs.open("log.txt");
		if (!ofs.is_open()) ErrorFunction();

		std::cout << "\n";
		char prev;
		// Считываем выбранную матрицу пользователем. Подсчитывает количество строк и столбцов
		while (!ofs.eof())
		{
			char ch;
			ofs >> ch;
			if (ch == '&') 
				--selectMatrix;

			if (ch == 's' && selectMatrix == 0)
			{
				prev = ch;
				++col;
			}

			else if (ch == 'e' && selectMatrix == 0 && prev != ch)
			{
				prev = ch;
				++row;
			}
		}

		col /= row;
		colM = col;
		rowN = row;

		ofs.close();

		std::vector<std::vector<double>> matrix(row, std::vector<double>(col));
		selectMatrix = selectMatrix_temp;
		col = 0, row = 0;

		ofs.open("log.txt");
		if (!ofs.is_open()) ErrorFunction();

		// Записываем выбранную матрицу в переменную и вывод ее на экран как отдельную выбранную матрицу
		while (!ofs.eof())
		{
			char ch;
			ofs >> ch;
			if (ch == '&')
				--selectMatrix;

			else if (ch == 's' && selectMatrix == 0)
			{
				++col;
				std::cout << " ";
			}
			else if (ch == 'e' && selectMatrix == 0)
			{
				col = 0;
				++row;
				std::cout << "\n";
			}

			if (((ch >= '0' && ch <= '9') || ch == '-' || ch == '.') && selectMatrix == 0)
			{
				std::cout << ch;
				matrix[row][col] = static_cast<int>(ch - '0');
			}
				
		}
		ofs.close();

		return matrix;
	}

	// Обработчик ошибок
	void ErrorFunction()
	{
		std::cout << "Fatal Error";
		return;
	}

	// Вывод матриц из файла log.txt на экран и нумеруем
	void coutMatrixOfTheFile()
	{
		// Если файл имеется проверяется если что нибудь в нем
		std::cout << "\nPlease wait, the analysis of previous requests is in progress!\n";
		while (!ofs.eof())
		{
			char ch;
			ofs >> ch;
			// Нумерация матрицы
			if (ch == '&')
			{
				++countMatrix;
				std::cout << "\n(" << countMatrix << ")\n";
			}

			if (ch == '-' || ch == '.' || (ch >= '0' && ch <= '9'))
				std::cout << ch;

			else if (ch == 'e')
				std::cout << "\n";

			else if (ch == 's')
				std::cout << " ";
		}

		if (countMatrix == 0) std::cout << "\nYou have no previous requests!\n";

		ofs.close();
	}
	
	// Создаем новую матрицу
	std::vector<std::vector<double>> createMatrix()
	{
		// Задавание размеров матрицы 
		std::cout << "\nPlease, enter the number of rows and columns of the matrix!\n";

		int col = 0, row = 0;
		std::cin >> row >> col;

		rowN = row;
		colM = col;

		// Если размер матрицы равен 0 то выход из программы
		if (row == 0 && col == 0)
		{
			ErrorFunction();
		}

		// Ввод матрицы по указанным размерам
		std::cout << "\nPlease, enter the matrix!\n";
		std::vector<std::vector<double>> matrix = fillingMatrix(row, col);

		// Проверка матрицы на пустату
		if (matrix.empty())
		{
			ErrorFunction();
		}

		// Пользоватеь проверяет правильно ли он заполнил свою матрицу, если ет дает повторую попытку
		std::cout << "\nPlease, check that your matrix is entered correctly\n";
		bool validMatrixEnter = IsCheckValidEnterMatrix(matrix, row, col);

		// Пользователь перезаписывает своб таблицу после не удачной попытки
		if (!validMatrixEnter)
		{
			std::cout << "Please, re-enter the matrix for the last time!\n";
			matrix.clear();
			matrix = fillingMatrix(row, col);

			std::cout << "\nYour Matrix\n";
			for (int i = 0; i != row; ++i)
			{
				for (int j = 0; j != col; ++j)
				{
					std::cout << matrix[i][j] << " ";
				}
				std::cout << "\n";
			}
		}
		return matrix;
	}


	// Нахождение суммы всех значений матрицы
	int SumAllValuesTheMatrix(const std::vector<std::vector<double>>& matrix)
	{
		int sum = 0;

		for (int i = 0; i != matrix.size(); ++i)
		{
			for (int j = 0; j != matrix[0].size(); ++j)
			{
				sum += matrix[i][j];
			}
		}
		return sum;
	}

	// Вычитание всех значений матрицы
	double SubtractionAllValuesTheMatrix(const std::vector<std::vector<double>>& matrix)
	{
		double sum = 0;

		for (int i = 0; i != matrix.size(); ++i)
		{
			for (int j = 0; j != matrix[0].size(); ++j)
			{
				sum -= matrix[i][j];
			}
		}
		return sum;
	}

	// Умножение елементов матрицы по строчно
	double ProductsTheMatrixElementsByRows(const std::vector<std::vector<double>>& matrix)
	{
		double result = 0;

		for (int i = 0; i != matrix.size(); ++i)
		{
			double temp_result = 1;

			for (int j = 0; j != matrix[0].size(); ++j)
			{
				temp_result *= matrix[i][j];
			}

			result += temp_result;
		}

		return result;
	}

	// Умножение елементов матрицы по столбцам
	double ProductsTheMatrixElementsByColumns(const std::vector<std::vector<double>>& matrix)
	{
		double result = 0;

		for (int i = 0; i != matrix.size(); ++i)
		{
			double temp_result = 1;

			for (int j = 0; j != matrix[0].size(); ++j)
			{
				temp_result *= matrix[j][i];
			}

			result += temp_result;
		}

		return result;
	}

	// Нахождеие максимального значения матрицы
	double FindMaxValueTheMatrix(const std::vector<std::vector<double>>& matrix)
	{
		double maxVal = DBL_MIN;

		for (int i = 0; i != matrix.size(); ++i)
		{
			for (int j = 0; j != matrix[0].size(); ++j)
			{
				if (maxVal < matrix[i][j]) maxVal = matrix[i][j];
			}
		}
		return maxVal;
	}

	// Нахождление минимального значения матрицы
	double FindMinValueTheMatrix(const std::vector<std::vector<double>>& matrix)
	{
		double minVal = DBL_MAX;

		for (int i = 0; i != matrix.size(); ++i)
		{
			for (int j = 0; j != matrix[0].size(); ++j)
			{
				if (minVal > matrix[i][j]) minVal = matrix[i][j];
			}
		}
		return minVal;
	}

	// Нахождение средне арифметического значения матрица
	int FindTheAverageMathematicalNmberconstTheMatrix(const std::vector<std::vector<double>>& matrix, int row, int col)
	{
		int average = 0;
		int sum = 0;

		for (int i = 0; i != matrix.size(); ++i)
		{
			for (int j = 0; j != matrix[0].size(); ++j)
			{
				sum += matrix[i][j];
			}
		}
		average = sum / (row * col);
		return average;
	}

};

int main()
{
	// Вызов рограммы
	FunctionProcessingMatrix functionProcessingMatrix;
	functionProcessingMatrix.WelcomeStartProgramm();
}