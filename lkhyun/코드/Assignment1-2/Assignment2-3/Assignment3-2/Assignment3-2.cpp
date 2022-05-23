#include <iostream>
using namespace std;

class My_string
{
private:
	char* str = new char[100]();

public:
	My_string(char* word)
	{
		for (int i = 0; word[i] != '\n'; i++)
			str[i] = word[i];
	}
	int my_strlen()
	{
		for (int i = 0;; i++)
		{
			if (str[i] == NULL)
				return i;
		}
	}
	void my_strcpy(char* string)
	{
		int num = my_strlen();
		for (int i = 0; i < num; i++)
			str[i] = NULL;
		for (int i = 0; string[i] != '\n'; i++)
			str[i] = string[i];

	}
	void my_strcat(char* string)
	{
		int num = my_strlen();
		for (int i = num; string[i - num] != '\n'; i++)
			str[i] = string[i-num];
	}
	void print()
	{
		int num = my_strlen();
		for (int i = 0; i < num; i++)
			cout << str[i];
		cout << endl;
	}
	~My_string()
	{
		delete[] str;
	}

};

int main()
{
	string command;
	char* str = new char[100]();
	cout << "First String : ";
	for (int i = 0;; i++)
	{
		str[i] = cin.get();
		if (str[i] == '\n')
			break;
	}
	My_string strclass = My_string(str);
	
	while (1)
	{
		cout << "Please Enter Command(strlen, strcpy, strcat, print, quit) :";
		cin >> command;
		if (command == "strlen")
		{
			cout << "String Length :" << strclass.my_strlen() << endl;
		}
		else if (command == "strcpy")
		{
			for (int i = 0;; i++)
			{
				if (i == 0)
					char trash = cin.get();
				str[i] = cin.get();
				if (str[i] == '\n')
					break;
			}
			strclass.my_strcpy(str);
			cout << "strcpy is done" << endl;
		}
		else if (command == "strcat")
		{
			for (int i = 0;; i++)
			{
				if (i == 0)
					char trash = cin.get();
				str[i] = cin.get();
				if (str[i] == '\n')
					break;
			}
			strclass.my_strcat(str);
			cout << "strcat is done" << endl;
		}
		else if (command == "print")
		{
			cout << "Current String :";
			strclass.print();
		}
		else if (command == "quit")
			break;
		
	}
	delete[] str;
	return 0;
}