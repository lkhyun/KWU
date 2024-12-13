#include <iostream>
#include <fstream>
using namespace std;
void ascending_order(int* ptr)
{
	int temp;
	int i;
	for (int i = 0; i < 19; i++)
	{
		for (int p=i+1;p<20;p++)
		{
			if (ptr[i] > ptr[p])
			{
				temp = ptr[i];
				ptr[i] = ptr[p];
				ptr[p] = temp;
			}
		}
		
	}
}
int main()
{
	int array[20] = { 0 };
	ifstream readtxt;
	readtxt.open("20numbers.txt");
	if (!readtxt)
	{
		cout << "파일을 열 수 없습니다.";
		exit(0);
	}
	cout << "Input array : ";
	for (int i = 0; i < 20; i++)
	{
		readtxt >> array[i];
		cout << array[i] << ' ';
	}
	readtxt.close();
	cout << endl;
	ascending_order(array);
	cout << "Sorted array : ";
	for (int p = 0; p < 20; p++)
	{
		cout << array[p] << ' ';
	}
	return 0;
}