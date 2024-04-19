#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::fstream ofs;

class FunctionProcessingMatrix
{
public:
	// ������ ��������� � ����������� 
	void WelcomeStartProgramm()
	{
		std::cout << "The Matrix Processing program welcomes you!\n";
		std::cout << "\nDo you want to connect past requests? Enter Y or N!\n";

		// �������� �� ��������� ������ Y ��� N, ����� �� ������ ����� �� ������������ ������� �������
		while (std::cin >> answer)
		{
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
						std::cout << "\nYou don't have any old requests!\n";
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
					std::cout << "You don't have any old requests!\n";
					std::ofstream ofs("log.txt");
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
		// ������� �� ��������� ������� 
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
		// ������� ������� � ������������ 0.0 �� �������� row, col
		std::vector<std::vector<double>> matrix(row, std::vector<double>(col));

		// �������� ������ �� ���� ������� ������� ������������� ���������
		ofs.open("log.txt", std::ios::app);
		if (!ofs.is_open())
		{
			std::cout << "Fatal error! Reload Programm.\n";
			return matrix;
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

			ofs << " e\n";
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

		std::cout << "\nIf everything is correct, enter Y, if not, then N\n";

		char enterCh;
		std::cin >> enterCh;

		// �������� ����� ������ ��� ������ Y ��� N 
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
	// ����� ������� ��� ������������� �� ��������� ������
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
		// ��������� ��������� ������� �������������. ������������ ���������� ����� � ��������
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

		// ���������� ��������� ������� � ���������� � ����� �� �� ����� ��� ��������� ��������� �������
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

	// ���������� ������
	void ErrorFunction()
	{
		std::cout << "Fatal Error";
		return;
	}

	// ����� ������ �� ����� log.txt �� ����� � ��������
	void coutMatrixOfTheFile()
	{
		// ���� ���� ������� ����������� ���� ��� ������ � ���
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
	
	// ������� ����� �������
	std::vector<std::vector<double>> createMatrix()
	{
		// ��������� �������� ������� 
		std::cout << "\nPlease, enter the number of rows and columns of the matrix!\n";

		int col = 0, row = 0;
		std::cin >> row >> col;

		rowN = row;
		colM = col;

		// ���� ������ ������� ����� 0 �� ����� �� ���������
		if (row == 0 && col == 0)
		{
			ErrorFunction();
		}

		// ���� ������� �� ��������� ��������
		std::cout << "\nPlease, enter the matrix!\n";
		std::vector<std::vector<double>> matrix = fillingMatrix(row, col);

		// �������� ������� �� �������
		if (matrix.empty())
		{
			ErrorFunction();
		}

		// ����������� ��������� ��������� �� �� �������� ���� �������, ���� �� ���� �������� �������
		std::cout << "\nPlease, check that your matrix is entered correctly\n";
		bool validMatrixEnter = IsCheckValidEnterMatrix(matrix, row, col);

		// ������������ �������������� ���� ������� ����� �� ������� �������
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
	// ����� ��������
	FunctionProcessingMatrix functionProcessingMatrix;
	functionProcessingMatrix.WelcomeStartProgramm();
}