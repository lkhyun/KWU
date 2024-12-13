#include <iostream>
using namespace std;

int main()
{
	int num1, num2;
	cout << "Enter Two Number :";
	cin >> num1 >> num2;
	if (num1 > num2)
		cout << num1 << '>' << num2;
	else if (num1 == num2)
		cout << num1 << '=' << num2;
	else
		cout << num1 << '<' << num2;
	return 0;
}