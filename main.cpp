#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <clocale>

std::fstream ofs;
class FunctionProcessingMatrix
{
public:
	// Запуск программы и приветсивие 
	void WelcomeStartProgramm()
	{
		std::cout << "The Matrix Processing program welcomes you!\n";
		std::cout << "You can change the language to Russian or leave it in English! (Y - I want to change || N - I don't want to change) \n";

		while (std::cin >> answer)
		{
			answer = std::toupper(answer);

			if (answer == 'Y') 
			{
				lang = true;
				break;
			}
			else if (answer == 'N') 
			{
				lang = false;
				break;
			}
			else
			{	
				if (lang) std::cout << "Идиот? Тебе сказано ввести Y или N\n";
				else std::cout << "Char is`t valid! Error\n";
			}
		}

		if (lang)
		{
			std::cout << "\nВы можете подключить уже созданные вами матрицы! Введите Y или N, если хотите подключить!\n";
			std::cout << "Так же вы можете очистит свои давние запросы! Используйте D для очистки матриц в файле!\n";
		}
		else
		{
			std::cout << "\nDo you want to connect past requests? Enter Y or N!\n";
			std::cout << "You can clear the file! Enter D for cleaning\n";
		}

		// Проверка на введенный символ Y или N, ответ на вопрос нужно ли использовать прошлые матрицы
		while (std::cin >> answer)
		{
			answer = std::toupper(answer);

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
					if (lang)
						std::cout << "У вас отстутсвуют старые записи, но вы можете создать новые матрицы!\n";
					else
						std::cout << "You don't have any old requests!\n";
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
			else if (answer == 'D')
			{
				ofs.open("log.txt", std::ios::out);
				if (!ofs.is_open()) ErrorFunction();

				ofs.close();
				if (lang)
					std::cout << "Успешная очистка!";
				else
					std::cout << "Successful cleaning!";

				std::vector<std::vector<double>> matrix = createMatrix();
				actionBindFunction(matrix);
				break;
			}
			else
			{
				if (lang) std::cout << "Идиот? Тебе сказано ввести Y или N\n";
				else std::cout << "Char is`t valid! Error\n";
			}
		}

	}

public:
	void actionBindFunction(const std::vector<std::vector<double>>& matrix)
	{
		// Функции по обработки матрицы 
		if (lang)
		{
			std::cout << "\nВыбирите подходящую функцию и вызавити ее с помощию ввода цифры функции!\n";
			std::cout << "\nСуммирование всех элеменнтов в матрице (1) \n";
			std::cout << "Вычитание всех элеменнтов в матрице (2) \n";
			std::cout << "Произведение элементов матрицы в строчке (3) \n";
			std::cout << "Произведение элементов матрицы в столбце (4) \n";
			std::cout << "Нахождение средне арифметического значения в матрице (5) \n";
			std::cout << "Нахождение максимального значения в матрице (6) \n";
			std::cout << "Нахождение минимального значения в матрице (7) \n";
			std::cout << "Нахождение суммы всех подматриц в матрице (8) \n";
			std::cout << "Выход из программы (0)\n\n";
		}
		else
		{
			std::cout << "\nPlease, choose an action and enter number the action!\n";
			std::cout << "\nSummation of all matrix values (1) \n";
			std::cout << "Subtraction of all matrix values (2) \n";
			std::cout << "Products of matrix elements by rows (3) \n";
			std::cout << "Products of matrix elements by columns (4) \n";
			std::cout << "Finding the average mathematical number (5) \n";
			std::cout << "Finding maximal number (6) \n";
			std::cout << "Finding minimal number (7) \n";
			std::cout << "Finding matrix region sum (8) \n";
			std::cout << "Exit (0)\n\n";
		}

		
		bool IsExit = false;
		char action;
		std::vector<std::vector<double>> matrix_result;
		while (std::cin >> action)
		{
			switch (action)
			{
			case '1':
				// Нахождение суммы всех элементов матрицы
				if (lang)
					std::cout << "Суммирование всех элеменнтов в матрице -> " << SumAllValuesTheMatrix(matrix) << "\n";

				else  
					std::cout << "Summation of all matrix values -> " << SumAllValuesTheMatrix(matrix) << "\n";

				break;

			case '2':
				// Нахожденрие разности всех элементов матрицы
				if (lang)
					std::cout << "Вычитание всех элеменнтов в матрице -> " << SubtractionAllValuesTheMatrix(matrix) << "\n";

				else
					std::cout << "Subtraction of all matrix values -> " << SubtractionAllValuesTheMatrix(matrix) << "\n";

				break;

			case '3':
				// Нахождение произведения элементов по строчно
				if (lang)
					std::cout << "Произведение элементов матрицы в строчке -> " << ProductsTheMatrixElementsByRows(matrix) << "\n";
				else
					std::cout << "Products of matrix elements by rows -> " << ProductsTheMatrixElementsByRows(matrix) << "\n";

				break;

			case '4':
				// Нахождение произведения эелемнтов по столбцам
				if (lang)
					std::cout << "Произведение элементов матрицы в столбце -> " << ProductsTheMatrixElementsByColumns(matrix) << "\n";
				else
					std::cout << "Products of matrix elements by columns -> " << ProductsTheMatrixElementsByColumns(matrix) << "\n";

				break;

			case '5':
				// Нахождение средне арифметического значения в матрице
				if (lang)
					std::cout << "Нахождение средне арифметического значения в матрице -> " << FindTheAverageMathematicalNmberconstTheMatrix(matrix, rowN, colM) << "\n";
				else
					std::cout << "Finding the average mathematical number -> " << FindTheAverageMathematicalNmberconstTheMatrix(matrix, rowN, colM) << "\n";

				break;

			case '6':
				// Нахождение максимльного значения в матрице
				if (lang)
					std::cout << "Нахождение минимального значения в матрице -> " << FindMaxValueTheMatrix(matrix) << "\n";
				else
					std::cout << "Finding maximal number -> " << FindMaxValueTheMatrix(matrix) << "\n";
				
				break;

			case '7':
				// Нахождение минимального значения в матрице
				if (lang)
					std::cout << "Нахождение минимального значения в матрице -> " << FindMinValueTheMatrix(matrix) << "\n";
				else
					std::cout << "Finding minimal number -> " << FindMinValueTheMatrix(matrix) << "\n";

				break;

			case '8':
				// Нахождение суммы всех подматриц в матрице
				matrix_result = FindSumAllValueTheSubmatrix(matrix);
				if (lang)
					std::cout << "Нахождение суммы всех подматриц в матрице -> " << "\n";
				else
					std::cout << "Finding matrix region sum -> " << "\n";

				for (int i = 0; i != matrix.size(); ++i)
				{
					for (int j = 0; j != matrix[0].size(); ++j)
					{
						std::cout << matrix_result[i][j] << " ";
					}
					std::cout << "\n";
				}
				break;

			case '0':
				// Выход из программы
				if (lang)
					std::cout << "\nБлагодарим вас за использование программы Matrix Processing!\n";
				else
					std::cout << "\nThank you for using the Matrix Processing program!\n";
				IsExit = true;
				break;

			default:
				if (lang) std::cout
					<< "Идиот? Тебе сказано ввести Y или N\n";
				else 
					std::cout << "Char is`t valid! Error\n";
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
			ErrorFunction();
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

			ofs << " q\n";
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
		
		if (lang)
			std::cout << "\nПроверьте правильно ли вы введи свою матрицу. Если нет повторите ввод еще раз! (Y - верно, N - неверно)\n";
		else
			std::cout << "\nIf everything is correct, enter Y, if not, then N\n";

		while (std::cin >> answer)
		{	
			answer = std::toupper(answer);

			if (answer == 'Y') return true;
			else if (answer == 'N') return false;

			if (lang) std::cout << "Идиот? Тебе сказано ввести Y или N\n";
			else std::cout << "Char is`t valid! Error\n";
		}

;
	}
private:
	char answer;
	int countMatrix = 0;
	int rowN = 0;
	int colM = 0;
	bool lang = false;

private:

	// Обработчик ошибок
	void ErrorFunction()
	{
		if (lang)
			std::cout << "Проверьте, существует ли файл, или перезапустите программу!\n";
		else
			std::cout << "Check if the file exists, or restart the program\n";
	}

	// Выбор матрицы для использование по обработки матриц
	std::vector<std::vector<double>> SelectMatrixInTheFile()
	{
		if (lang)
			std::cout << "\nВыберите матрицу из списка и введите номер матрицы!\n";
		else
			std::cout << "\nPlease, select a matrix from the list and enter a number the matrix!\n";

		std::cin >> answer;
		
		while (std::cin >> answer)
		{
			if (answer >= '0' && answer <= '9')
			{
				if (lang) std::cout << "Идиот? Тебе сказано ввести Y или N\n";
				else std::cout << "Char is`t valid! Error\n";
			}
			else if (static_cast<int>(answer - '0') <= countMatrix) break;
			
			if (lang) std::cout << "Идиот? Тебе сказано ввести Y или N\n";
			else std::cout << "Char is`t valid! Error\n";
		}

		int row = 0;
		int col = 0;
		int selectMatrix_temp = static_cast<int>(answer - '0');

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
				--selectMatrix_temp;

			if (ch == 's' && selectMatrix_temp == 0)
			{
				prev = ch;
				++col;
			}

			else if (ch == 'q' && selectMatrix_temp == 0 && prev != ch)
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
		selectMatrix_temp = static_cast<int>(answer - '0');
		col = 0, row = 0;

		ofs.open("log.txt");
		if (!ofs.is_open()) ErrorFunction();

		// Записываем выбранную матрицу в переменную и вывод ее на экран как отдельную выбранную матрицу
		while (!ofs.eof())
		{
			char ch;
			ofs >> ch;
			if (ch == '&')
				--selectMatrix_temp;

			else if (ch == 's' && selectMatrix_temp == 0)
			{
				++col;
				std::cout << " ";
			}
			else if (ch == 'q' && selectMatrix_temp == 0)
			{
				col = 0;
				++row;
				std::cout << "\n";
			}

			if (((ch >= '0' && ch <= '9') || ch == '-' || ch == '.' || ch == '+' || ch == 'e') && selectMatrix_temp == 0)
			{
				std::cout << ch;
				matrix[row][col] = static_cast<int>(ch - '0');
			}

		}
		ofs.close();

		return matrix;
	}

	// Вывод матриц из файла log.txt на экран и нумеруем
	void coutMatrixOfTheFile()
	{
		// Если файл имеется проверяется если что нибудь в нем
		if (lang)
			std::cout << "\nПодожите не много идет анализ прошлых запросов!\n";
		else
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

			if (ch == '-' || ch == '.' || ch == '+' || ch == 'e' || (ch >= '0' && ch <= '9'))
				std::cout << ch;

			else if (ch == 'q')
				std::cout << "\n";

			else if (ch == 's')
				std::cout << " ";
		}

		if (countMatrix == 0) 
		{
			if (lang)
				std::cout << "\nУ вас нет предыдущих запросов!\n";
			else
				std::cout << "\nYou have no previous requests!\n";
		}

		ofs.close();
	}

	// Создаем новую матрицу
	std::vector<std::vector<double>> createMatrix()
	{
		// Задавание размеров матрицы 
		if (lang)
			std::cout << "\nПожалуйста, введите количество строк и столбцов матрицы!\n";
		else
			std::cout << "\nPlease, enter the number of rows and columns of the matrix!\n";

		int col = 0, row = 0;
		std::cin >> row >> col;

		rowN = row;
		colM = col;

		// Если размер матрицы равен 0 то выход из программы
		if (row == 0 && col == 0)
		{
			if (lang)
				std::cout << "Создать матрицу невозможно!\n";
			else
				std::cout << "It is`t possible to create a matrix!\n";
		}

		// Ввод матрицы по указанным размерам
		if (lang)
			std::cout << "\nВведите свою матрицу!\n";
		else
			std::cout << "\nPlease, enter the matrix!\n";
		std::vector<std::vector<double>> matrix = fillingMatrix(row, col);

		// Проверка матрицы на пустату
		if (matrix.empty())
		{
			if (lang)
				std::cout << "Создать матрицу невозможно!\n";
			else
				std::cout << "It is`t possible to create a matrix!\n";
		}

		// Пользоватеь проверяет правильно ли он заполнил свою матрицу, если ет дает повторую попытку
		if (lang)
			std::cout << "\nУбедитесь, что ваша матрица введена правильно\n";
		else
			std::cout << "\nPlease, check that your matrix is entered correctly\n";

		bool validMatrixEnter = IsCheckValidEnterMatrix(matrix, row, col);

		// Пользователь перезаписывает своб таблицу после не удачной попытки
		if (!validMatrixEnter)
		{
			if (lang)
				std::cout << "Повторите ввод матрицы еше раз!\n";
			else
				std::cout << "Please, re-enter the matrix for the last time!\n";

			matrix.clear();
			matrix = fillingMatrix(row, col);

			if (lang)
				std::cout << "\nВаша матрица\n";
			else
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
	double FindTheAverageMathematicalNmberconstTheMatrix(const std::vector<std::vector<double>>& matrix, int row, int col)
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

	std::vector<std::vector<double>> FindSumAllValueTheSubmatrix(const std::vector<std::vector<double>>& matrix)
	{
		std::vector<std::vector<double>> result(matrix[0].size(), std::vector<double>(matrix.size()));

		for (int i = 0; i != matrix.size(); ++i)
		{
			for (int j = 0; j != matrix[0].size(); ++j)
			{
				if (i > 0 && j > 0)
				{
					result[i][j] = matrix[i][j] + result[i - 1][j] + result[i][j - 1] + result[i - 1][j - 1];
				}
				else if (i > 0 && j == 0)
				{
					result[i][j] = matrix[i][j] + result[i - 1][j];
				}
				else if (i == 0 && j > 0)
				{
					result[i][j] = matrix[i][j] + result[i][j - 1];
				}
				else
				{
					result[i][j] = matrix[i][j];
				}
			}
		}
		return result;
	}

};

int main()
{
	setlocale(LC_ALL, "ru");
	// Вызов рограммы
	FunctionProcessingMatrix functionProcessingMatrix;
	functionProcessingMatrix.WelcomeStartProgramm();

}