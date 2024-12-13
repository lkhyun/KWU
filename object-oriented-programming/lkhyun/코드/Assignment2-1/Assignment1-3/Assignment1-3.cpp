#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int main()
{
	int a1, a2;
	int b1, b2;
	cout << "Matrix A :";
	cin >> a1 >> a2;
	cout << "Matrix B :";
	cin >> b1 >> b2;
	cout << endl;

	int** A_Matrix = new int*[a1];
	for (int i = 0; i < a1; i++)
		A_Matrix[i] = new int[a2];

	int** B_Matrix = new int*[b1] ;
	for (int i = 0; i < b1; i++)
		B_Matrix[i] = new int[b2];

	int** C_Matrix = new int* [a1];
	for (int i = 0; i < a1; i++)
		C_Matrix[i] = new int[b2];

	srand(time(NULL));
	for (int i = 0; i < a1; i++)
	{
		for (int j = 0; j < a2; j++)
		{
			A_Matrix[i][j] = rand() % 11;
		}
	}
	for (int i = 0; i < b1; i++)
	{
		for (int j = 0; j < b2; j++)
		{
			B_Matrix[i][j] = rand() % 11;
		}
	}

	for (int i = 0; i < a1; i++)
	{
		for (int j = 0; j < b2; j++)
		{
			C_Matrix[i][j] = 0;
		}
	}

	cout << "A Matrix :" << endl;
	for (int i = 0; i < a1; i++)
	{
		for (int j = 0; j < a2; j++)
		{
			cout.setf(ios::left);
			cout << setw(5) << A_Matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "B_Matrix :" << endl;
	for (int i = 0; i < b1; i++)
	{
		for (int j = 0; j < b2; j++)
		{
			cout.setf(ios::left);
			cout << setw(5) << B_Matrix[i][j];
				
		}
		cout << endl;
	}
	cout << endl;
	
	if (a2 != b1)
		cout << "Can't Operate Matrix Multiplication(" << a2 << "!=" << b1 << ')';
	else
	{
		cout << "A*B Result :" << endl;
		for (int p = 0; p < a1; p++)
		{
			for (int i = 0; i < b2; i++)
			{
				for (int j = 0; j < a2; j++)
				{
					C_Matrix[p][i] += A_Matrix[p][j] * B_Matrix[j][i];
				}
				cout.setf(ios::left);
				cout << setw(5) << C_Matrix[p][i];

			}
			cout << endl;
		}
	}
	
	for (int i = 0; i < a1; i++)
		delete[] A_Matrix[i];
	delete[] A_Matrix;
	for (int i = 0; i < b1; i++)
		delete[] B_Matrix[i];
	delete[] B_Matrix;
	for (int i = 0; i < a1; i++)
		delete[] C_Matrix[i];
	delete[] C_Matrix;

	return 0;
}