#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;
class node
{
public:
	node* prev=NULL;
	node* next=NULL;
	char name[20] = { 0 };
	int id = 0;
};

class list
{
private:
	node* head;
public:
	list()
	{
		head = NULL;
	}
	void insert(int id, char* name)
	{
		if (head == NULL)//처음 입력받을 때
		{
			node* a = new node;
			a->id = id;
			strcpy(a->name, name);
			head = a;
		}
		else
		{
			node* temp = head;
			while (temp != NULL)//id 중복 확인
			{
				if (temp->id == id)
					break;
				temp = temp->next;
			}
			if (temp == NULL) //temp가 null이면 중복되는 것이 없었다는 뜻
			{
				temp = head;
				node* a = new node;
				a->id = id;
				strcpy(a->name, name);
				while (temp != NULL)
				{
					if (temp->id > id)
					{
						if (temp == head)
						{
							a->next = temp;
							temp->prev = a;
							head = a;
							break;
						}
						else
						{
							temp->prev->next = a;
							a->prev = temp->prev;
							a->next = temp;
							temp->prev = a;
							break;
						}
					}
					if (temp->next == NULL)
					{
						temp->next = a;
						a->prev = temp;
						break;
					}
					temp = temp->next;
				}
			}
		}
	}
	void print()
	{
		node* temp = head;
		while (temp != NULL)
		{
			cout << temp->id << " " << temp->name << endl;
			temp = temp->next;
		}
	}
	void print_reverse()
	{
		node* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		while (temp != head)
		{
			cout << temp->id << " " << temp->name << endl;
			temp = temp->prev;
		}
		cout << head->id << " " << head->name << endl;
	}
	void sort_by_name()
	{
		node* temp1 = head;
		node* temp2 = temp1->next;
		char temp3[20];
		int temp;
		while (temp1->next != NULL)
		{
			while (temp2 != NULL)
			{
				if (strcmp(temp1->name, temp2->name) > 0)
				{
					strcpy(temp3, temp1->name);
					strcpy(temp1->name, temp2->name);
					strcpy(temp2->name, temp3);
					temp = temp1->id;
					temp1->id = temp2->id;
					temp2->id = temp;
				}
				temp2 = temp2->next;
			}
			temp1 = temp1->next;
			temp2 = temp1->next;
		}
		
	}
	void sort_by_ID()
	{
		node* temp1 = head;
		node* temp2 = temp1->next;
		char temp3[20];
		int temp;
		while (temp1->next != NULL)
		{
			while (temp2 != NULL)
			{
				if (temp1->id > temp2->id)
				{
					strcpy(temp3, temp1->name);
					strcpy(temp1->name, temp2->name);
					strcpy(temp2->name, temp3);
					temp = temp1->id;
					temp1->id = temp2->id;
					temp2->id = temp;
				}
				temp2 = temp2->next;
			}
			temp1 = temp1->next;
			temp2 = temp1->next;
		}
	}
	void delnode(int id)
	{
		node* temp1 = head;
		while (temp1 != NULL)
		{
			if (temp1->id == id)
			{
				if (temp1->prev != NULL)
					temp1->prev->next = temp1->next;
				if (temp1->next != NULL)
					temp1->next->prev = temp1->prev;
				if (temp1->prev == NULL)
				{
					head = temp1->next;
				}
				delete temp1;
				temp1 = head;
				continue;
			}
			temp1 = temp1->next;
		}
	}
	void memoryfree()
	{
		node* temp = head;
		while (head != NULL)
		{
			head = temp->next;
			delete temp;
			temp = head;
		}
	}
};
int main()
{
	list data;
	char name[20];
	int id;
	int command;
	while (1)
	{
		cout << "Please Enter command(1:insert, 2:print, 3:print_reverse, 4:sort_by_name, 5:sort_by_ID, 6:delete, 7:exit) :";
		cin >> command;
		if (command == 1)
		{
			cin >> id;
			cin >> name;
			data.insert(id, name);
		}
		else if (command == 2)
		{
			data.print();
		}
		else if (command == 3)
		{
			data.print_reverse();
		}
		else if (command == 4)
		{
			data.sort_by_name();
		}
		else if (command == 5)
		{
			data.sort_by_ID();
		}
		else if (command == 6)
		{
			cin >> id;
			data.delnode(id);
		}
		else if (command == 7)
		{
			data.memoryfree();
			break;
		}

	}
	return 0;
}