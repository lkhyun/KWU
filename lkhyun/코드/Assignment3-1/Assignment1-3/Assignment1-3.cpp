#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class mystring
{
private:
	char* str = (char*)calloc(100, sizeof(char));
public:
	friend mystring operator +=(mystring& A, char* temp);
	friend mystring operator -=(mystring& A, char temp);
	friend mystring operator --(mystring& A);
	friend mystring operator &&(mystring& A, char temp);
	friend void deletefunc(mystring& A);
	mystring (char* str)
	{
		
	}
	~mystring()
	{
	
	}
	void print()
	{
		int i = 0;
		while (str[i] != 0)
		{
			cout << str[i];
			i++;
		}
		cout << endl;
	}
	
};
mystring operator +=(mystring& A, char* temp)
{
	A.str=(char *)realloc(A.str, (strlen(A.str) + strlen(temp) + 1));
	if (A.str == NULL)
	{
		free(A.str);
	}
	A.str[strlen(A.str) - 1] = 0;
	if (strlen(temp) > 100)
		strncat(A.str, temp, 100);
	
	else
		strcat(A.str, temp);

	return A;
}
mystring operator -=(mystring& A, char temp)
{
	int i = 0;
	while (A.str[i] != 0)
	{
		if (A.str[i] == temp)
		{
			int j = i;
			while (A.str[j] != 0)
			{
				A.str[j] = A.str[j + 1];
				j++;
			}
			i = 0;
		}
		i++;
	}
	return A;
}
mystring operator --(mystring& A)
{
	for (int i = 0; A.str[i] != 0; i++)
	{
		if (A.str[i + 1] == 0)
		{
			A.str[i] = 0;
		}
	}
	return A;
}
mystring operator &&(mystring& A, char temp)
{
	int i = 0;
	while (A.str[i] != 0)
	{
		if (A.str[i] != temp)
		{
			A.str[i] = '0';
		}
		i++;
	}
	return A;
}
void deletefunc(mystring& A)
{
	free(A.str);
}
int main()
{
	int command = 0;
	char* str = new char[300]();
	char word = 0;
	mystring A(str);
	while (1)
	{
		cout << "Please Enter command(1 : add, 2 : delete_char, 3: delete_lastchar, 4 : and_operator, 5 : print, 6 : exit) : ";
		cin >> command;
		if (command == 1)
		{
			cin >> str;
			A = operator+=(A, str);
		}
		else if (command == 2)
		{
			cin >> word;
			A = operator-=(A, word);
		}
		else if (command == 3)
		{
			A = operator--(A);
		}
		else if (command == 4)
		{
			cin >> word;
			A = operator&&(A, word);
		}
		else if (command == 5)
		{
			A.print();
		}
		else if (command == 6)
		{
			delete[] str;
			deletefunc(A);
			break;
		}
	}
	return 0;
}

