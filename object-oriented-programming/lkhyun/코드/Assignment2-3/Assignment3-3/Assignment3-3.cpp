#include <iostream>
#include <string>
using namespace std;

class Student_info
{
private:
	char name[10] = { 0 };
	int age = 0;
	char university[100] = { 0 };
	char major[100] = { 0 };

public:
	Student_info(char* name, int age, char* univ, char* major)
	{
		for (int i = 0; name[i] != 0; i++)
			this->name[i] = name[i];
		this->age = age;
		for (int i = 0; univ[i] != 0; i++)
			this->university[i] = univ[i];
		for (int i = 0; major[i] != 0; i++)
			this->major[i] = major[i];
	}
	Student_info()
	{

	}
	bool find(char* name)
	{
	    int i = 0;
		while (this->name[i] != 0 || name[i] != 0)
		{
			if (this->name[i] == name[i])
			{
				i++;
				continue;
			}
			else
				return 0;
		}
		return 1;
	}
	void print()
	{
		cout << "Name : " << this->name << endl;
		cout << "Age : " << age << endl;
		cout << "University : " << university << endl;
		cout << "Major : " << major << endl;
	}
	void change(char* name, int age, char* univ, char* major)
	{
		for (int j = 0; j< 10; j++)
			this->name[j] = name[j];
		this->age = age;
		for (int j = 0; j < 100; j++)
			this->university[j] = univ[j];
		for (int j = 0; j < 100; j++)
			this->major[j] = major[j];
	}

};
int main()
{
	string command;
	char name[10] = { 0 };
	char nam[10] = { 0 };
	char univ[100] = { 0 };
	char major[100] = { 0 };
	int age = 0;
	int num = 0;
	Student_info list[10];
	
	while (1)
	{
		cout << "Please Enter Command(insert, find, change, print, exit) :";
		cin >> command;
		if (command == "insert")
		{
			cin >> name >> age >> univ >> major;
			list[num] = Student_info(name, age, univ, major);
			num++;
		}
		if (command == "find")
		{
			cin >> name;
			cout << "________find________" << endl;
			for (int i = 0; i < num; i++)
			{
				if (list[i].find(name) == 1)
				{
					list[i].print();
					cout << "__________________" << endl;
				}
					
				
			}
		}
		if (command == "print")
		{
			cout << "________print_________" << endl;
			for (int i = 0; i < num; i++)
			{
				list[i].print();
				cout << "__________________" << endl;
			}
		}
		if (command == "change")
		{
			cin >> name >> nam >> age >> univ >> major;
			for (int i = 0; i < num; i++)
			{
				if (list[i].find(name) == 1)
				{
					list[i].change(nam, age, univ, major);
					break;
				}
			}
		}
		if (command == "exit")
			break;
	}
	return 0;
}