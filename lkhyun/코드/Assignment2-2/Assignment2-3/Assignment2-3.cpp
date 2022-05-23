#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	unsigned int num = 0;
	do
	{
		cout << "Please enter the length of matrix : ";
		cin >> num;
	} while (num < 2);
	unsigned int** matrix = new unsigned int* [num];
	for (unsigned int p = 0; p < num; p++)
		matrix[p] = new unsigned int[num];
	
	unsigned int i = 0;
	unsigned int j = 0;
	long long k = 0;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			matrix[i][j] = 1;
		}
	}
	i = 0; j = 0;
	while (k <= (num * num)-1)
	{
		while(1)
		{
			if (matrix[i][j] == 1)
			{
				matrix[i][j] = k;
				k++;
			}
				
			if (j + 1 < num)
			{
				if (matrix[i][j + 1] == 1)
					j++;
				else
				{
					i++;
					break;
				}
			}
			else
			{
				i++;
				break;
			}
			
		}
		while (1)
		{
			if (matrix[i][j] == 1)
			{
				matrix[i][j] = k;
				k++;
			}
			if (i + 1 < num)
			{
				if (matrix[i + 1][j] == 1)
					i++;
				else
				{
					j--;
					break;
				}
			}
			else
			{
				j--;
				break;
			}

		}
		while (1)
		{
			if (matrix[i][j] == 1)
			{
				matrix[i][j] = k;
				k++;
			}
			if (j - 1 >= 0 && j != 0)
			{
				if (matrix[i][j - 1] == 1)
					j--;
				else
				{
					i--;
					break;
				}
			}
			else
			{
				i--;
				break;
			}

		}
		while (1)
		{
			if (matrix[i][j] == 1)
			{
				matrix[i][j] = k;
				k++;
			}
			if (i - 1 >= 0 && i != 0)
			{
				if (matrix[i - 1][j] == 1)
					i--;
				else
				{
					j++;
					break;
				}
			}
			else
			{
				j++;
				break;
			}
		}
	}
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			cout.setf(ios::left);
			cout<<setw(3)<< matrix[i][j];
		}
		cout << endl;
	}
	for (i = 0; i < num; i++)
		delete[] matrix[i];
	delete[] matrix;
	return 0;
}
