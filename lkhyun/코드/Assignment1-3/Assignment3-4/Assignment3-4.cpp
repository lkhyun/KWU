#include <iostream>
#include <iomanip>
using namespace std;
int compare_tool(char num, int num2);

int main()
{
	char board[25] = { 1,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };
	char num1;
	char num2 = 0;
	int num3 = 0;//ÀÚÃë¿ë
	int arr[4] = { 0 };

	while (1)
	{
		for (int i = 1; i < 26; i++)
		{
			if (board[i - 1] == 1)
				board[i - 1] = 'H';
			cout.setf(ios::left);
			cout << setw(5) << board[i - 1];
			if (i % 5 == 0)
				cout << endl;

		}
		cout << "Enter Move Command(a: Left, d: Right, w: Up, s: Down, q: Finish) : ";
		cin >> num1;
		num1 = compare_tool(num1, num2);
		if (num1 == 10)
			break;
		if (num1 != 0)
		{
			if (num3 / 4 != 0 && arr[0] != arr[3])
			{
				board[arr[num3 % 4]] = '0';
			}
			board[num2] = 'X';
			arr[num3 % 4] = num2;
			num2 += num1;
			board[num2] = 1;
			num3++;
		}
	}

	return 0;
}
int compare_tool(char num, int num2)
{
	if (num == 'a')
	{
		num = -1;
		if ((num2 + num) % 5 == 4 || (num2 + num) < 0)
			num = 0;
	}

	if (num == 'd')
	{
		num = 1;
		if ((num2 + num) % 5 == 0 || (num2 + num) > 24)
			num = 0;
	}

	if (num == 'w')
	{
		num = -5;
		if ((num2 + num) < 0)
			num = 0;
	}

	if (num == 's')
	{
		num = 5;
		if ((num2 + num) > 24)
			num = 0;
	}
	if (num == 'q')
		num = 10;
	return num;
}