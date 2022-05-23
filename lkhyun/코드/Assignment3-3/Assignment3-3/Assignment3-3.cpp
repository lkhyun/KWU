#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class queue
{
public:
	char menu[10];
	int time = 0;
	int data[10] = { 0 };
	queue* next2 = NULL;
	void makingqueue();
};
void queue::makingqueue()
{
	int index = 0;
	for (int i = time - 1; i > 0; i--)
	{
		data[index++] = i;
	}
}
class cooker
{
public:
	char name[10];
	cooker* next1 = NULL;
	queue* head2 = NULL;
	queue* n2 = NULL;
	void insertmenu(char* menu, int time);
};
void cooker:: insertmenu(char* menu, int time)
{
	if (head2 == NULL)
	{
		queue* temp = new queue;
		strcpy(temp->menu, menu);
		temp->time = time;
		head2 = temp;
		return;
	}
	n2 = head2;
	queue* temp = new queue;
	strcpy(temp->menu, menu);
	temp->time = time;
	while (n2->next2 != NULL)
		n2 = n2->next2;
	n2->next2 = temp;
}
class cookerlist
{
private:
	cooker* head1 = NULL;
	cooker* n1 = NULL;
public:
	void insertcooker(char* name, char* menu, int time);
	void queueinitializing();
};
void cookerlist:: insertcooker(char* name, char* menu, int time)
{
	if (head1 == NULL)
	{
		cooker* temp = new cooker;
		strcpy(temp->name, name);
		temp->insertmenu(menu, time);
		head1 = temp;
	}
	else
	{
		n1 = head1;
		while (n1 != NULL)
		{
			if (strcmp(n1->name, name) == 0)
			{
				n1->insertmenu(menu, time);
				return;
			}
			n1 = n1->next1;
		}
		n1 = head1;
		cooker* temp = new cooker;
		strcpy(temp->name, name);
		temp->insertmenu(menu, time);
		while (n1->next1 != NULL)
			n1 = n1->next1;
		n1->next1 = temp;
	}
}
void cookerlist:: queueinitializing()
{
	n1 = head1;
	while (n1 != NULL)
	{
		
	}
	
}

int main()
{
	ifstream readtxt;
	class cookerlist cook;
	char cooker[10];
	char menu[20];
	int time;

	readtxt.open("Assignment3-3-3-1.txt");
	if (!readtxt)
	{
		cout << "파일을 열 수 없습니다.";
		exit(0);
	}
	while (!readtxt.eof())
	{
		readtxt >>cooker>> menu >> time;
		cook.insertcooker(cooker, menu, time);
	}
	readtxt.close();
	return 0;
}
