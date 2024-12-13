#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
	int num1 = 10;
	int num2 = 10;
	char* str1 = (char*)calloc(num1,sizeof(char));
	if (str1 == NULL) return -1;
	char* str2 = (char*)calloc(num2,sizeof(char));
	if (str2 == NULL) return -1;

	cout << "String 1 : ";
	
	for(int i=0;;i++)
	{
		
		if (str1[i - 1] == '\n')
		{
			num1 = i - 1;
			break;
		}
			
		str1[i] = cin.get();
		if (str1[i] != '\n' && i % 10 == 9)
		{
			num1 += 10;
			if (str1 != NULL)
			{
				str1 = (char*)realloc(str1, sizeof(char) * num1);
				if (str1 == NULL)
				{
					free(str1);
					break;
				}
					
			}
			
		}
	}

	cout << "String 2 : ";

	for (int i = 0;; i++)
	{

		if (str2[i - 1] == '\n')
		{
			num2 = i - 1;
			break;
		}
			
		str2[i] = cin.get();
		if (str2[i] != '\n' && i % 10 == 9)
		{
			num2 += 10;
			if (str2 != NULL)
			{
				str2 = (char*)realloc(str2, sizeof(char) * num2);
				if (str2 == NULL)
				{
					free(str2);
					break;
				}
					
			}
		}
			
	}
	char* str3 = (char*)calloc(num1 + num2 + 1, sizeof(char));
	if (str3 == NULL) return -1;

	for (int i = 0; i < num1; i++)
	{
		str3[i] = str1[i];
	}

	for (int i = 0; i < num2; i++)
	{
		str3[i + num1] = str2[i];
	}

	for (int i = 0;; i++)
	{
		if (str3[i] == 0)
			break;
		cout << str3[i];
	}
	
	free(str1);
	free(str2);
	free(str3);
	
	return 0;
}