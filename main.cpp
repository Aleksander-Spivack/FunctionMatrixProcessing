#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <clocale>

std::fstream ofs;
class FunctionProcessingMatrix
{
public:
	// ������ ��������� � ����������� 
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
				if (lang) std::cout << "�����? ���� ������� ������ Y ��� N\n";
				else std::cout << "Char is`t valid! Error\n";
			}
		}

		if (lang)
		{
			std::cout << "\n�� ������ ���������� ��� ��������� ���� �������! ������� Y ��� N, ���� ������ ����������!\n";
			std::cout << "��� �� �� ������ ������� ���� ������ �������! ����������� D ��� ������� ������ � �����!\n";
		}
		else
		{
			std::cout << "\nDo you want to connect past requests? Enter Y or N!\n";
			std::cout << "You can clear the file! Enter D for cleaning\n";
		}

		// �������� �� ��������� ������ Y ��� N, ����� �� ������ ����� �� ������������ ������� �������
		while (std::cin >> answer)
		{
			answer = std::toupper(answer);

			if (answer == 'Y')
			{
				// ����� Y (��) ����������� ������� ����� log.txt
				ofs.open("log.txt");
				if (ofs.is_open())
				{
					coutMatrixOfTheFile();
					if (countMatrix == 0)
					{
						// ���� ���������� ������ �� ������� �������
						std::vector<std::vector<double>> matrix = createMatrix();
						actionBindFunction(matrix);
						break;
					}
					else
					{
						// ���� ���� ������ � ������� � ����� log.txt ������� ��� ������� �� �����
						std::vector<std::vector<double>> matrix = SelectMatrixInTheFile();
						actionBindFunction(matrix);
						break;
					}
				}
				else
				{
					// ���� ���� ���������� �� �������
					if (lang)
						std::cout << "� ��� ����������� ������ ������, �� �� ������ ������� ����� �������!\n";
					else
						std::cout << "You don't have any old requests!\n";
					std::vector<std::vector<double>> matrix = createMatrix();
					actionBindFunction(matrix);
					break;
				}
			}
			else if (answer == 'N')
			{
				// ���� ������������ �� ����� ������������� ������ ������, ������� ����� � ����������
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
					std::cout << "�������� �������!";
				else
					std::cout << "Successful cleaning!";

				std::vector<std::vector<double>> matrix = createMatrix();
				actionBindFunction(matrix);
				break;
			}
			else
			{
				if (lang) std::cout << "�����? ���� ������� ������ Y ��� N\n";
				else std::cout << "Char is`t valid! Error\n";
			}
		}

	}

public:
	void actionBindFunction(const std::vector<std::vector<double>>& matrix)
	{
		// ������� �� ��������� ������� 
		if (lang)
		{
			std::cout << "\n�������� ���������� ������� � �������� �� � ������� ����� ����� �������!\n";
			std::cout << "\n������������ ���� ���������� � ������� (1) \n";
			std::cout << "��������� ���� ���������� � ������� (2) \n";
			std::cout << "������������ ��������� ������� � ������� (3) \n";
			std::cout << "������������ ��������� ������� � ������� (4) \n";
			std::cout << "���������� ������ ��������������� �������� � ������� (5) \n";
			std::cout << "���������� ������������� �������� � ������� (6) \n";
			std::cout << "���������� ������������ �������� � ������� (7) \n";
			std::cout << "���������� ����� ���� ��������� � ������� (8) \n";
			std::cout << "����� �� ��������� (0)\n\n";
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
				// ���������� ����� ���� ��������� �������
				if (lang)
					std::cout << "������������ ���� ���������� � ������� -> " << SumAllValuesTheMatrix(matrix) << "\n";

				else  
					std::cout << "Summation of all matrix values -> " << SumAllValuesTheMatrix(matrix) << "\n";

				break;

			case '2':
				// ����������� �������� ���� ��������� �������
				if (lang)
					std::cout << "��������� ���� ���������� � ������� -> " << SubtractionAllValuesTheMatrix(matrix) << "\n";

				else
					std::cout << "Subtraction of all matrix values -> " << SubtractionAllValuesTheMatrix(matrix) << "\n";

				break;

			case '3':
				// ���������� ������������ ��������� �� �������
				if (lang)
					std::cout << "������������ ��������� ������� � ������� -> " << ProductsTheMatrixElementsByRows(matrix) << "\n";
				else
					std::cout << "Products of matrix elements by rows -> " << ProductsTheMatrixElementsByRows(matrix) << "\n";

				break;

			case '4':
				// ���������� ������������ ��������� �� ��������
				if (lang)
					std::cout << "������������ ��������� ������� � ������� -> " << ProductsTheMatrixElementsByColumns(matrix) << "\n";
				else
					std::cout << "Products of matrix elements by columns -> " << ProductsTheMatrixElementsByColumns(matrix) << "\n";

				break;

			case '5':
				// ���������� ������ ��������������� �������� � �������
				if (lang)
					std::cout << "���������� ������ ��������������� �������� � ������� -> " << FindTheAverageMathematicalNmberconstTheMatrix(matrix, rowN, colM) << "\n";
				else
					std::cout << "Finding the average mathematical number -> " << FindTheAverageMathematicalNmberconstTheMatrix(matrix, rowN, colM) << "\n";

				break;

			case '6':
				// ���������� ������������ �������� � �������
				if (lang)
					std::cout << "���������� ������������ �������� � ������� -> " << FindMaxValueTheMatrix(matrix) << "\n";
				else
					std::cout << "Finding maximal number -> " << FindMaxValueTheMatrix(matrix) << "\n";
				
				break;

			case '7':
				// ���������� ������������ �������� � �������
				if (lang)
					std::cout << "���������� ������������ �������� � ������� -> " << FindMinValueTheMatrix(matrix) << "\n";
				else
					std::cout << "Finding minimal number -> " << FindMinValueTheMatrix(matrix) << "\n";

				break;

			case '8':
				// ���������� ����� ���� ��������� � �������
				matrix_result = FindSumAllValueTheSubmatrix(matrix);
				if (lang)
					std::cout << "���������� ����� ���� ��������� � ������� -> " << "\n";
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
				// ����� �� ���������
				if (lang)
					std::cout << "\n���������� ��� �� ������������� ��������� Matrix Processing!\n";
				else
					std::cout << "\nThank you for using the Matrix Processing program!\n";
				IsExit = true;
				break;

			default:
				if (lang) std::cout
					<< "�����? ���� ������� ������ Y ��� N\n";
				else 
					std::cout << "Char is`t valid! Error\n";
			}
			if (IsExit) break;
		}
	}

	std::vector<std::vector<double>> fillingMatrix(int& row, int& col)
	{
		// ������� ������� � ������������ 0.0 �� �������� row, col
		std::vector<std::vector<double>> matrix(row, std::vector<double>(col));

		// �������� ������ �� ���� ������� ������� ������������� ���������
		ofs.open("log.txt", std::ios::app);
		if (!ofs.is_open())
		{	
			ErrorFunction();
		}
		ofs << "&\n";

		// ���������� ������� �������������
		for (int i = 0; i != row; ++i)
		{
			for (int j = 0; j != col; ++j)
			{
				// ������������� � ��������� �������
				std::cin >> matrix[i][j];
				ofs << matrix[i][j] << " s ";
			}

			ofs << " q\n";
		}
		ofs.close();

		return matrix;
	}

	// ������ �������� ������������� �������� �� � �������� �������, ���� ��� �� ���� ��������� ������� 
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
			std::cout << "\n��������� ��������� �� �� ����� ���� �������. ���� ��� ��������� ���� ��� ���! (Y - �����, N - �������)\n";
		else
			std::cout << "\nIf everything is correct, enter Y, if not, then N\n";

		while (std::cin >> answer)
		{	
			answer = std::toupper(answer);

			if (answer == 'Y') return true;
			else if (answer == 'N') return false;

			if (lang) std::cout << "�����? ���� ������� ������ Y ��� N\n";
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

	// ���������� ������
	void ErrorFunction()
	{
		if (lang)
			std::cout << "���������, ���������� �� ����, ��� ������������� ���������!\n";
		else
			std::cout << "Check if the file exists, or restart the program\n";
	}

	// ����� ������� ��� ������������� �� ��������� ������
	std::vector<std::vector<double>> SelectMatrixInTheFile()
	{
		if (lang)
			std::cout << "\n�������� ������� �� ������ � ������� ����� �������!\n";
		else
			std::cout << "\nPlease, select a matrix from the list and enter a number the matrix!\n";

		std::cin >> answer;
		
		while (std::cin >> answer)
		{
			if (answer >= '0' && answer <= '9')
			{
				if (lang) std::cout << "�����? ���� ������� ������ Y ��� N\n";
				else std::cout << "Char is`t valid! Error\n";
			}
			else if (static_cast<int>(answer - '0') <= countMatrix) break;
			
			if (lang) std::cout << "�����? ���� ������� ������ Y ��� N\n";
			else std::cout << "Char is`t valid! Error\n";
		}

		int row = 0;
		int col = 0;
		int selectMatrix_temp = static_cast<int>(answer - '0');

		ofs.open("log.txt");
		if (!ofs.is_open()) ErrorFunction();

		std::cout << "\n";
		char prev;

		// ��������� ��������� ������� �������������. ������������ ���������� ����� � ��������
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

		// ���������� ��������� ������� � ���������� � ����� �� �� ����� ��� ��������� ��������� �������
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

	// ����� ������ �� ����� log.txt �� ����� � ��������
	void coutMatrixOfTheFile()
	{
		// ���� ���� ������� ����������� ���� ��� ������ � ���
		if (lang)
			std::cout << "\n�������� �� ����� ���� ������ ������� ��������!\n";
		else
			std::cout << "\nPlease wait, the analysis of previous requests is in progress!\n";

		while (!ofs.eof())
		{
			char ch;
			ofs >> ch;
			// ��������� �������
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
				std::cout << "\n� ��� ��� ���������� ��������!\n";
			else
				std::cout << "\nYou have no previous requests!\n";
		}

		ofs.close();
	}

	// ������� ����� �������
	std::vector<std::vector<double>> createMatrix()
	{
		// ��������� �������� ������� 
		if (lang)
			std::cout << "\n����������, ������� ���������� ����� � �������� �������!\n";
		else
			std::cout << "\nPlease, enter the number of rows and columns of the matrix!\n";

		int col = 0, row = 0;
		std::cin >> row >> col;

		rowN = row;
		colM = col;

		// ���� ������ ������� ����� 0 �� ����� �� ���������
		if (row == 0 && col == 0)
		{
			if (lang)
				std::cout << "������� ������� ����������!\n";
			else
				std::cout << "It is`t possible to create a matrix!\n";
		}

		// ���� ������� �� ��������� ��������
		if (lang)
			std::cout << "\n������� ���� �������!\n";
		else
			std::cout << "\nPlease, enter the matrix!\n";
		std::vector<std::vector<double>> matrix = fillingMatrix(row, col);

		// �������� ������� �� �������
		if (matrix.empty())
		{
			if (lang)
				std::cout << "������� ������� ����������!\n";
			else
				std::cout << "It is`t possible to create a matrix!\n";
		}

		// ����������� ��������� ��������� �� �� �������� ���� �������, ���� �� ���� �������� �������
		if (lang)
			std::cout << "\n���������, ��� ���� ������� ������� ���������\n";
		else
			std::cout << "\nPlease, check that your matrix is entered correctly\n";

		bool validMatrixEnter = IsCheckValidEnterMatrix(matrix, row, col);

		// ������������ �������������� ���� ������� ����� �� ������� �������
		if (!validMatrixEnter)
		{
			if (lang)
				std::cout << "��������� ���� ������� ��� ���!\n";
			else
				std::cout << "Please, re-enter the matrix for the last time!\n";

			matrix.clear();
			matrix = fillingMatrix(row, col);

			if (lang)
				std::cout << "\n���� �������\n";
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


	// ���������� ����� ���� �������� �������
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

	// ��������� ���� �������� �������
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

	// ��������� ��������� ������� �� �������
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

	// ��������� ��������� ������� �� ��������
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

	// ��������� ������������� �������� �������
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

	// ����������� ������������ �������� �������
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

	// ���������� ������ ��������������� �������� �������
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
	// ����� ��������
	FunctionProcessingMatrix functionProcessingMatrix;
	functionProcessingMatrix.WelcomeStartProgramm();

}