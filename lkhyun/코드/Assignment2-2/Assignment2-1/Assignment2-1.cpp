#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
	int num = 1;
	int* stack = (int*)malloc(sizeof(int)*1);
	if (stack == NULL)
		return -1;
	string pushpop;
	while (num != 0)
	{
		cout << "Please Enter Command(push, pop) :";
		cin >> pushpop;
		if (pushpop == "push")
		{
			int push = 0;
			cin >> push;
			stack[num-1] = push;
			num++;
			stack = (int*)realloc(stack, sizeof(int) * num);
			if (stack == NULL) break;
		}
		else if (pushpop == "pop")
		{
			num--;
			stack = (int*)realloc(stack, sizeof(int) * num);
			if (stack == NULL) break;
		}
		for (int j = 0;j<num-1; j++)
			cout << stack[j] << endl;
	}
	free(stack);
	return 0;
}