#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	int** Matrix = new int* [10];
	for (int i = 0; i < 10; i++)
	{
		Matrix[i] = new int[11];
	}

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Matrix[i][j] = rand() % 101;
			if (j == 9)
				Matrix[i][j + 1] = 0;
		}
	}

	cout << "Original Matrix" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout.setf(ios::left);
			cout <<setw(7)<< Matrix[i][j];
		}
		cout << endl;
	}

	for (int p = 0; p < 10; p++)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = i + 1; j < 10; j++)
			{
				if (Matrix[p][i] > Matrix[p][j])
				{
					int temp = Matrix[p][i];
					Matrix[p][i] = Matrix[p][j];
					Matrix[p][j] = temp;

				}
			}
		}
		for (int i = 0; i < 10; i++)
		{
			Matrix[p][10] += Matrix[p][i];
		}
	}

	cout << "Sort by row" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout.setf(ios::left);
			cout << setw(7) << Matrix[i][j];
		}
		cout << setw(7) << "Sum is " << Matrix[i][10] << '(' << &Matrix[i][10] << ')' << endl;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (Matrix[i][10] > Matrix[j][10])
			{
				int* temp = Matrix[i];
				Matrix[i] = Matrix[j];
				Matrix[j] = temp;
			}
		}
	}

	cout << "Sort by Sum" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout.setf(ios::left);
			cout << setw(7) << Matrix[i][j];
		}
		cout << setw(7) << "Sum is " << Matrix[i][10] << '(' << &Matrix[i][10] << ')' << endl;
	}

	for (int i = 0; i < 10; i++)
		delete[] Matrix[i];
	delete[] Matrix;
	return 0;
}
