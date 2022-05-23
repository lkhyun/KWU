#include <iostream>
#include <cstring>
using namespace std;

class Student
{
private:
	char name[20] = { 0 };
	int Score = 0;
public:
	Student()
	{
		
	}
	char* returnname() { return name; }
	int returnscore() { return Score; }
	void Insert()
	{
		cout << "Name :";
		cin >> name;
		cout << "Score :";
		cin >> Score;
	}
};
int main()
{
	int command = 0;
	Student* control=new Student[30];
	int number = 0;
	int align[30] = { 0 };
	
	while (command==0)
	{
		cout << "Please Enter Command(1: insert, 2: sort by name, 3: sort by score, 4: quit) :";
		cin >> command;

		if (command == 1)
		{
			control[number].Insert();
			number++;
		}
		else if (command == 2)
		{
			for (int i = 0; i < number - 1; i++)
			{
				for (int j = i+1; j < number; j++)
				{
					if (strcmp(control[i].returnname(), control[j].returnname()) > 0)
					{
						Student temp = control[i];
						control[i] = control[j];
						control[j] = temp;
					}
				}
				
			}
			for (int i = 0; i < number; i++)
			{
				cout << control[i].returnname() << control[i].returnscore() << endl;
			}
		}
		else if (command == 3)
		{
			for (int i = 0; i < number - 1; i++)
			{
				for (int j = i+1; j < number; j++)
				{
					if (control[i].returnscore()>control[j].returnscore())
					{
						Student temp = control[i];
						control[i] = control[j];
						control[j] = temp;
					}
				}

			}
			for (int i = 0; i < number; i++)
			{
				cout << control[i].returnname() << control[i].returnscore() << endl;
			}
		}
		else if (command == 4)
			break;
		command = 0;
	}
	delete[] control;
	return 0;
}