#include <iostream>
using namespace std;

int main()
{
	char Array1[50];
	char Array2[50];
	char num1;
	char num2;
	char temp;
	cout << "Array 1 :";
	cin >> Array1;
	cout << endl;
	cout << "Array 2 :";
	cin >> Array2;

	for (int i = 0; ; i++)
	{
		if (Array1[i] == NULL)
			break;
		num1 = Array1[i];
		num2 = Array2[i];
		if (Array1[i] >= 65 && Array1[i] <= 90)
			num1 = num1 + 32;
		if (Array2[i] >= 65 && Array2[i] <= 90)
			num2 = num2 + 32;
		if (num1 < num2)
		{
			temp = Array1[i];
			Array1[i] = Array2[i];
			Array2[i] = temp;
		}
		
	}
	cout << "Exchanged Array 1 :";
	for (int i = 0; ; i++)
	{
		if (Array1[i] == NULL)
			break;
		cout << Array1[i];
	}
	cout << endl;
	cout << "Exchanged Array 2 :";
	for (int i = 0; 1; i++)
	{
		if (Array2[i] == NULL)
			break;
		cout << Array2[i];
	}
	
	return 0;
}