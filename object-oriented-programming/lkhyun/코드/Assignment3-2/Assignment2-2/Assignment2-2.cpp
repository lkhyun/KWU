#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
using namespace std;

class univ
{
private:
	char U_Name[20];
	int year;
	char U_StuID[20];
public:
	univ(){}
	univ(char* U_Name, int year, char* U_StuID)
	{
		strcpy(this->U_Name, U_Name);
		strcpy(this->U_StuID, U_StuID);
		this->year = year;
	}
	bool returnid(char* temp)
	{
		if (strcmp(U_StuID, temp) == 0)
			return 1;
		else
			return 0;
		
	}
	void print()
	{
		cout << "�б�: " << U_Name << endl;
		cout << "�й�: " << U_StuID << endl;
		cout << "�г�: " << year << endl;
	}

};

class depart: public univ
{
private:
	char Object_Oriented_Programing;
	char Digital_Logic_Circuit;
public:
	depart(){}
	depart(char* U_Name, int year, char* U_StuID, char OOP, char DLC) :univ(U_Name, year, U_StuID)
	{
		Object_Oriented_Programing = OOP;
		Digital_Logic_Circuit = DLC;
	}
	void print()
	{
		univ::print();
		cout << "��ü�������α׷��� ����: " << Object_Oriented_Programing << endl;
		cout << "�����г�ȸ�� ����: " << Digital_Logic_Circuit << endl;
	}
};

class information :public depart
{
private:
	char Name[10];
	int age;
public:
	information() {}
	information(char* U_Name, int year, char* U_StuID, char OOP, char DLC, char* Name, int age) :depart(U_Name, year, U_StuID, OOP, DLC)
	{
		strcpy(this->Name, Name);
		this->age = age;
	}
	bool returnname(char* temp)
	{
		if (strcmp(Name, temp) == 0)
			return 1;
		else
			return 0;
	}
	void print()
	{
		depart::print();
	}
};

int main()
{
	class information** control = new information*[100]();
	string command;
	char U_Name[20];
	int year;
	char U_StuID[20];
	char OOP;
	char DLC;
	char Name[10];
	int age;
	int index = 0;

	while (1)
	{
		cin >> command;
		if (command == "INSERT")
		{
			cout << "�б� :";
			cin >> U_Name;
			cout << "�й� :";
			cin >> U_StuID;
			cout << "�г� :";
			cin >> year;
			cout << "��ü�������α׷��� ���� :";
			cin >> OOP;
			cout << "�����г�ȸ�� ���� :";
			cin >> DLC;
			cout << "�̸� :";
			cin >> Name;
			cout << "���� :";
			cin >> age;
			control[index] = new information(U_Name, year, U_StuID, OOP, DLC, Name, age);
			index++;
		}
		else if (command == "FIND")
		{
			cin >> Name;
			cin >> U_StuID;
			for (int i = 0; i < index; i++)
			{
				if (control[i]->returnid(U_StuID) == 1)
					if (control[i]->returnname(Name) == 1)
						control[i]->print();
			}
		}
		else if (command == "EXIT")
		{
			for (int i = 0; i < index; i++)
				delete control[i];
			delete[] control;
			break;
		}
	}
	return 0;
}



