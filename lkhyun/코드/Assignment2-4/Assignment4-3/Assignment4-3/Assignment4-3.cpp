#include <iostream>
using namespace std;
struct node
{
	int number;
	node* next;
};
class linked_list
{
private:
	node* head;
	node* tail;
public:
	linked_list()
	{
		head = tail = NULL;
	}
	void insertnode(int num)
	{
		node* n = new node;
		n->number = num;
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
			tail = n;
		}
		else
		{
			tail->next = n;
			tail = n;
		}
	}
	void findnode(int num)
	{
		node* a = head;
		int index = 0;
		while (a != NULL)
		{
			if (a->number == num)
			{
				cout << index + 1 << endl;
			}
			a = a->next;
			index++;

		}
	}
	void deletenode(int num)
	{
		node* a = head;
		int index = 0;
		while (a != NULL)
		{
			if (a->number == num)
			{
				if (head->number == num)
				{
					head = a->next;
					delete a;
					a = head;
					index = 0;
					continue;
				}
				node* b;
				a = head;
				for (int i = 0; i < index-1; i++)
					a = a->next;
				b = a->next;
				a->next = b->next;
				delete b;
				a = head;
				index = 0;
			}
			a = a->next;
			index++;
		}
	}
	void printnode()
	{
		int num = 0;
		node* a = head;
		while (a != NULL)
		{
			cout << a->number << endl;
			a = a->next;
			num++;
		}
		cout << "Number of nodes in the list: " << num<<endl;
	}
	void memoryfree()
	{
		node* a = head;
		node* b = a->next;
		while (b != NULL)
		{
			b = a->next;
			delete a;
			a = b;
		}
	}
};
int main()
{
	string command;
	linked_list list;
	int num = 0;

	while (1)
	{
		cout << "Please Enter Command(1:insert, 2:find, 3:delete, 4:print, 5:quit) : ";
		cin >> command;
		if (command == "insert")
		{
			cin >> num;
			list.insertnode(num);
		}
		else if (command == "find")
		{
			cin >> num;
			list.findnode(num);
		}
		else if (command == "delete")
		{
			cin >> num;
			list.deletenode(num);
		}
		else if (command == "print")
		{
			list.printnode();
		}
		else if (command == "quit")
		{
			list.memoryfree();
			return 0;
		}
	}
}