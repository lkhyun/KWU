#include <iostream>
#include <iomanip>
using namespace std;
int compare_tool(char num, int num2);

int main()
{
	char board[9] = { 1,'0','0','0','0','0','0','0','0'};
	char num1;
	char num2 = 0;
	char num3[4] = { 0 };
	while(1)
	{
		for (int i = 1; i < 10; i++)
		{
			if (board[i - 1] == 1)
				board[i - 1] = 'H';
			cout.setf(ios::left);
			cout << setw(15) << board[i - 1];
			if (i % 3 == 0)
				cout << endl;

		}
		cout << "Enter Move Command(a: Left, d: Right, w: Up, s: Down, q: Finish) : ";
		cin >> num1;
		num1=compare_tool(num1,num2);
		if (num1 == 10)
			break;
		board[num2] = '0';
		num2 += num1;
		board[num2] = 1;
		
	}
	
	return 0;
}
int compare_tool(char num, int num2)
{
	if (num == 'a')
	{
		num = -1;
		if ((num2 + num) % 3 == 2 || (num2 + num) < 0)
			num = 0;
	}

	if (num == 'd')
	{
		num = 1;
		if ((num2 + num) % 3 == 0 || (num2 + num) > 8)
			num = 0;
	}

	if (num == 'w')
	{
		num = -3;
		if ((num2 + num) < 0)
			num = 0;
	}

	if (num == 's')
	{
		num = 3;
		if ((num2 + num) > 8)
			num = 0;
	}
	if (num == 'q')
		num = 10;
	return num;
}