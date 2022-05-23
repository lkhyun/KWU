#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int num = 0;
	cout << "Enter any Number :";
	cin >> num;

	for (int i = 1; i <= 20; i++)
	{
		cout.setf(ios::left);
		cout << setw(5)<< i;
		if (i % num == 0)
		{
			cout << endl;
		}
	}
	return 0;
}