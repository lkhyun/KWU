#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
char big(char temp);
class node1
{
public:
	char str[20];
	node1* next1 = NULL;
};
class node2
{
public:
	char order;
	node1* next1 = NULL;
	node2* next2 = NULL;
};

class linkedlist
{
private:
	node2* head = NULL;
	node2* tail = NULL;
public:
	linkedlist()
	{
		head = new node2;
		head->order = 65;
		tail = head;
		for (int i = 66; i < 91; i++)
		{
			node2* n = new node2;
			n->order = i;
			tail->next2 = n;
			tail = n;
		}
		tail->next2 = NULL;
	}
	void insertnode(char* temp)
	{
		node2* n = head;
		while (n != NULL)
		{
			if (n->order == big(temp[0]))
			{
				if (n->next1 == NULL)
				{
					node1* a = new node1;
					n->next1 = a;
					strcpy(a->str, temp);
					break;
				}
				else
				{
					node1* a = n->next1;
					while (a->next1 != NULL)
					{
						a = a->next1;
					}
					node1* b = new node1;
					a->next1 = b;
					strcpy(b->str, temp);
					break;
				}
			
			}
			n = n->next2;
		}
	}
	void print()
	{
		node2* n = head;
		node1* a = n->next1;
		while (n != NULL)
		{
			if (a != NULL)
				cout << n->order;

			while (a != NULL)
			{
				cout << "->" << a->str;
				a = a->next1;
			}
			if (n->next1 != NULL)
			{
				cout << endl;
			}
			n = n->next2;
			if(n!=NULL)
				a = n->next1;
			
			
		}
	}
	void nodealign()
	{
		node2* n = head;
		node1* a = n->next1;
		node1* temp = NULL;
		char tempname[20];
		while (n != NULL)
		{
			if (a!=NULL)
			{
				while (a->next1 != NULL)
				{
					temp = a->next1;
					while (temp != NULL)
					{
						if (strcmpi(a->str, temp->str) > 0)
						{
							strcpy(tempname, a->str);
							strcpy(a->str, temp->str);
							strcpy(temp->str, tempname);
						}
						temp = temp->next1;
					}
					a = a->next1;
				}
			}
			n = n->next2;
			if(n!=NULL)
				a = n->next1;
			
		}
	}

	void deletenode()
	{
		node2* temp2 = head;
		node1* temp1 = NULL;
		
		while (head != NULL)
		{
			temp1 = head->next1;
			if (temp1 != NULL)
			{
				node1* temp3 = temp1;
				while (temp1 != NULL)
				{
					temp1 = temp3->next1;
					delete temp3;
					temp3 = temp1;
				}
			}
			head = temp2->next2;
			delete temp2;
			temp2 = head;
		}
	}
};
char big(char temp)
{
	char a = temp;
	if (temp >= 97 && temp <= 122)
	{
		a = temp - 32;
	}
	return a;
}
int main()
{
	class linkedlist A;
	char temp[20];
	ifstream readtxt;
	readtxt.open("Assignment.txt");
	if (!readtxt)
	{
		cout << "파일을 열 수 없습니다.";
		exit(0);
	}
	while(!readtxt.eof())
	{
		readtxt >> temp;
		A.insertnode(temp);
	}
	readtxt.close();
	A.nodealign();
	A.print();
	A.deletenode();
	return 0;
}
