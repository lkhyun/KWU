#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	int max_value = 0;
	int min_value = 0;
	int* ptr1 = new int[10];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		ptr1[i] = rand() % 10;
	}

	max_value= ptr1[0];
	min_value= ptr1[0];
	for (int i = 0; i < 9; i++)
	{
		if (max_value < ptr1[i + 1])//ÃÖ´ñ°ª
			max_value = ptr1[i + 1];
		
		if (min_value > ptr1[i + 1])//ÃÖ¼Ú°ª
			min_value = ptr1[i + 1];	
	}

	for (int i = 0; i < 10; i++)
	{
		cout << hex << "Memory Address is " << &ptr1[i] << endl << "Value is " << ptr1[i]<<endl;
	}
	cout << hex << "Max Data is " << max_value << '(';
	for (int i = 0; i < 10; i++)
	{
		if (max_value==ptr1[i])
			cout << hex << &ptr1[i] << ' ';
	}
	cout << ')' << endl;

	cout << hex << "Min Data is " << min_value<< '(';
	for (int i = 0; i < 10; i++)
	{
		if (min_value == ptr1[i])
			cout << hex << &ptr1[i] << ' ';

	}
	cout << ')' << endl;
	delete[] ptr1;
	return 0;
}