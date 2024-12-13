#include<iostream>
using namespace std;

int main()
{
	int num1, num2;
	cout << "Enter Two Numbers :";
	cin >> num1 >> num2;
	cout << num1 << " + " << num2 << ": " << num1 + num2 << endl;
	cout << num1 << " - " << num2 << ": " << num1 - num2 << endl;
	cout << num1 << " * " << num2 << ": " << num1 * num2 << endl;
	cout << num1 << " / " << num2 << ": " << (float)num1 / num2 << endl;
	cout << num1 << " % " << num2 << ": " << num1 % num2;
	return 0;

}