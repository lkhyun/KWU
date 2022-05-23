#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

char small(char a);
char* small(char* a);

struct node
{
	char name[50] = { 0 };
	node* next;
};
class chain
{
private:
	node* head;
	node* tail;
	int index = 0;
public:
	chain()
	{
		head = tail = NULL;
	}
	char lastword()
	{
		for (int i = 0;tail->name[i]!=0; i++)
		{
			if (tail->name[i + 1] == 0)
			{
				return small(tail->name[i]);
			}
		}
		return 0;
	}
	bool existence(char* newword)
	{
		node* a = head;
		for(int i=0;i<index;i++)
		{
			if (strcmp(small(newword), small(a->name)) == 0)
				return 1;
			a = a->next;
		}
		return 0;
	}
	void addword(char* arr)
	{
		node* a = new node;
		strcpy(a->name, arr);
		if (head == NULL)
		{
			head = a;
			tail = a;
		}
		else
		{
			node* temp = tail;
			tail->next = a;
			tail = a;
		}
		index++;
	}
	char small(char a)
	{
		char p = a;
		if (a >= 65 && a <= 90)
			p = a + 32;
		return p;
	}
	char* small(char* a)
	{
		char* p = a;
		for (int i = 0; a[i] != 0; i++)
		{
			if (a[i] >= 65 && a[i] <= 90)
			{
				p[i] = a[i] + 32;
			}
		}
		return p;
	}
	void print()
	{
		node* temp = head;
		for(int i=0;i<index;i++)
		{
			for (int i = 0; temp->name[i] != 0; i++)
			{
				cout << temp->name[i];
			}
			cout << " -> ";
			temp = temp->next;
		}
		cout << endl;
	}
	void memoryfree()
	{
		node* a = head;
		node* b = a->next;
		for (int i = 0; i < index - 1; i++)
		{
			b = a->next;
			delete a;
			a = b;
		}
		delete a;
	}
};
int main()
{
	chain A;
	char word[50] = { 0 };
	char smallword[50] = { 0 };

	int index = 0;
	while (1)
	{
		cout << "CMD(Word/exit)>> ";
		cin >> word;
		strcpy(smallword, word);
		if (strcmp(small(smallword), "exit") == 0)
			break;
		if (index == 0)
		{
			A.addword(word);
			index++;
			A.print();
			continue;
		}
		if (A.existence(smallword))
			cout << "Already Exists" << endl;
		else
		{
			if (A.lastword() == small(smallword[0]))
				A.addword(word);
			else
				cout << "Not chained" << endl;
		}
		A.print();
	}
	if (index != 0)
		A.memoryfree();

	return 0;
}
char small(char a)
{
	char p = a;
	if (a >= 65 && a <= 90)
		p = a + 32;
	return p;
}
char* small(char* a)
{
	for (int i = 0; a[i] != 0; i++)
	{
		if (a[i] >= 65 && a[i] <= 90)
		{
			a[i] = a[i] + 32;
		}
	}
	return a;
}