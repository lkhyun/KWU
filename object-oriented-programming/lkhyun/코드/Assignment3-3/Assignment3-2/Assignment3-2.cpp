#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class node
{
public:
	char name[20];
	node* prev1 = NULL;
	node* next1 = NULL;
	node* prev2 = NULL;
	node* next2 = NULL;
	int rail = 0;
};

class subway
{
private:
	node* head = NULL;
	node* tail = NULL;
	node* govern = NULL;
	node* start = NULL;
	node* finish = NULL;
public:
	void onerail(char* name)
	{
		node* n = new node;
		strcpy(n->name, name);
		if (head == NULL)
		{
			head = n;
			tail = n;
		}
		else if(head==tail)
		{
			head->next1 = n;
			tail = n;
			tail->prev1 = head;
		}
		else
		{
			tail->next1 = n;
			n->prev1 = tail;
			tail = n;
		}
	}
	void searchgovern()
	{
		char gover[10] = "시청";
		node* search = head;
		while (1)
		{
			if (strcmp(search->name, gover) == 0)
				break;
			search = search->next1;
		}
		govern = search;
		head = NULL;
		tail = NULL;
	}

	void tworail(char* name)
	{
		node* n = new node;
		strcpy(n->name, name);
		if (head == NULL)
		{
			head = n;
			tail = n;
		}
		else if (head == tail)
		{
			head->next2 = n;
			tail = n;
			tail->prev2 = head;
		}
		else
		{
			tail->next2 = n;
			n->prev2 = tail;
			tail = n;
		}
	}
	void connectgovern()
	{
		tail->next2 = head;
		head->prev2 = tail;
		
		node* search = head;
		while (strcmp(search->name,govern->name))
			search = search->next2;
		govern->next2 = search->next2;
		govern->prev2 = search->prev2;
	}
	int onetwo(char* name)
	{
		node* temp = govern;
		do 
		{
			if (strcmp(temp->name, name) == 0)
				return 2;
			temp = temp->next2;
		} while (strcmp(temp->name,govern->name)!=0);
		return 1;
	}
	void searchstart(char* name,int temp)
	{
		node* a = govern;
		if (temp == 1)
		{
			while (a != NULL)
			{ 
				if (strcmp(a->name, name) == 0)
				{
					start = a;
					start->rail = 1;
					return;
				}
				a = a->prev1;
			}
			a = govern;
			while (a != NULL)
			{
				if (strcmp(a->name, name) == 0)
				{
					start = a;
					start->rail = 1;
					return;
				}
				a = a->next1;
			}
		}
		else if (temp == 2)
		{
			do
			{
				if (strcmp(a->name, name) == 0)
				{
					start = a;
					start->rail = 2;
					return;
				}
				a = a->next2;
			} while (a != govern);
		}
	}
	void searchfinish(char* name, int temp)
	{
		node* a = govern;
		if (temp == 1)
		{
			while (a != NULL)
			{
				if (strcmp(a->name, name) == 0)
				{
					finish = a;
					finish->rail = 1;
					return;
				}
				a = a->prev1;
			}
			a = govern;
			while (a != NULL)
			{
				if (strcmp(a->name, name) == 0)
				{
					finish = a;
					finish->rail = 1;
					return;
				}
				a = a->next1;
			}
		}
		else if (temp == 2)
		{
			do
			{
				if (strcmp(a->name, name) == 0)
				{
					finish = a;
					finish->rail = 2;
					return;
				}
				a = a->next2;
			} while (a != govern);
		}
	}
	void searchpath()
	{
		if (start->rail == 1 && finish->rail == 1)
		{
			print1to1(start);
		}
		else if (start->rail == 1 && finish->rail == 2)
		{
			print1to2(start);
			print2to2(govern);
		}
		else if (start->rail == 2 && finish->rail == 1)
		{
			print2to1(start);
			print1to1(govern);
		}
		else if (start->rail == 2 && finish->rail == 2)
		{
			print2to2(start);
		}
	}
	void print1to1(node*select)
	{
		node* a = select;
		while (a != NULL)
		{
			if (strcmp(a->name, finish->name) == 0)
			{
				a = select;
				while (strcmp(a->name, finish->name) != 0)
				{
					cout << a->name << "->";
					a = a->prev1;
				}
				cout << a->name;
				return;
			}
			a = a->prev1;
		}
		a = select;
		while (a != NULL)
		{
			if (strcmp(a->name, finish->name) == 0)
			{
				a = select;
				while (strcmp(a->name, finish->name) != 0)
				{
					cout << a->name << "->";
					a = a->next1;
				}
				cout << a->name;
				return;
			}
			a = a->next1;
		}
	}
	void print1to2(node*select)
	{
		node* a = select;
		while (a != NULL)
		{
			if (strcmp(a->name, govern->name) == 0)
			{
				a = select;
				while (strcmp(a->name, govern->name) != 0)
				{
					cout << a->name << "->";
					a = a->prev1;
				}
				return;
			}
			a = a->prev1;
		}
		a = select;
		while (a != NULL)
		{
			if (strcmp(a->name, govern->name) == 0)
			{
				a = select;
				while (strcmp(a->name, govern->name) != 0)
				{
					cout << a->name << "->";
					a = a->next1;
				}
				return;
			}
			a = a->next1;
		}
	}
	void print2to1(node* select)
	{
		node* a = select;
		int distance = 0;
		while (strcmp(a->name, govern->name) != 0)
		{
			a = a->prev2;
			distance++;
		}
		a = select;
		while(strcmp(a->name, govern->name) != 0)
		{
			a = a->next2;
			distance--;
		} 
		a = select;
		if (distance < 0)
		{
			while (strcmp(a->name, govern->name) != 0)
			{
				cout << a->name << "->";
				a = a->prev2;
			}
		}
		else if (distance > 0)
		{
			while (strcmp(a->name, govern->name) != 0)
			{
				cout << a->name << "->";
				a = a->next2;
			}
		}
		else
			return;
	}
	void print2to2(node* select)
	{
		node* a = select;
		int distance = 0;
		while(strcmp(a->name, finish->name) != 0)
		{
			a = a->prev2;
			distance++;
		} 
		a = select;
		while(strcmp(a->name, finish->name) != 0)
		{
			a = a->next2;
			distance--;
		}
		a = select;
		if (distance < 0)
		{
			while(strcmp(a->name, finish->name) != 0)
			{
				cout << a->name << "->";
				a = a->prev2;
			}
			cout << a->name;
		}
		else
		{
			while(strcmp(a->name, finish->name) != 0)
			{
				cout << a->name << "->";
				a = a->next2;
			} 
			cout << a->name;
		}
	}
	void memoryfree()
	{
		node* a = govern;
		int index = 0;
		while (govern->prev1 != NULL)
		{
			a = govern->prev1;
			govern->prev1 = a->prev1;
			delete a;
		}
		while (govern->next1 != NULL)
		{
			a = govern->next1;
			govern->next1 = a->next1;
			delete a;
		}
		while (govern->next2 != NULL)
		{
			if (index++ == 0)
			{
				a = govern->prev2;
				a->next2 = NULL;
				govern->prev2 = NULL;
			}
			a = govern->next2;
			govern->next2 = a->next2;
			delete a;
		}
	}
	
};

int main()
{
	subway A;
	char name[20];
	char start[10];
	char finish[10];
	ifstream readtxt;

	readtxt.open("Assignment3-3-2-1.txt");
	if (!readtxt)
	{
		cout << "파일을 열 수 없습니다.";
		exit(0);
	}
	while (!readtxt.eof())
	{
		readtxt >> name;
		A.onerail(name);
	}
	readtxt.close();
	A.searchgovern();

	readtxt.open("Assignment3-3-2-2.txt");
	if (!readtxt)
	{
		cout << "파일을 열 수 없습니다.";
		exit(0);
	}
	while (!readtxt.eof())
	{
		readtxt >> name;
		A.tworail(name);
	}
	readtxt.close();
	A.connectgovern();

	cout << "출발역: ";
	cin >> start;
	A.searchstart(start, A.onetwo(start));
	cout << "도착역: ";
	cin >> finish;
	A.searchfinish(finish, A.onetwo(finish));
	A.searchpath();
	A.memoryfree();
	return 0;
}
