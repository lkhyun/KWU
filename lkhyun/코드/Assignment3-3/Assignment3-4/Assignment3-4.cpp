#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class majornode;
class idnode;
class namenode;

class majornode
{
public:
	char major[50];
	majornode* next1 = NULL;
	idnode* next2 = NULL;
};
class idnode
{
public:
	int id;
	idnode* next2 = NULL;
	namenode* next3 = NULL;
};
class namenode
{
public:
	char name[30];
	namenode* right = NULL;
	namenode* left = NULL;
};

class studentinfo
{
private:
	majornode* head = NULL;
	majornode* n1 = NULL;
	idnode* n2 = NULL;
	namenode* n3 = NULL;

public:
	void buildlist(char* major, int id, char* name);
	void accessmajor(char* major);
	void accessid(int id);
	void accessname(char* name);
	void print_all();
	void print_major(char* major);
	void print_id(int id);
	void print_name(char* name);
	void deletenode(char*major,int id,char*name);
	majornode* deletemajor(char* major);
	idnode* deleteid(int id);
	void deletename(char* name);
	void memoryfree();
	void treeprint(namenode* search);
	void treeprint2(namenode* search,char*name);

};
void studentinfo::buildlist(char* major, int id, char* name)
{
	accessmajor(major);
	accessid(id);
	accessname(name);
}

void studentinfo::accessmajor(char* major)
{
	if (head == NULL)
	{
		majornode* temp1 = new majornode;
		strcpy(temp1->major, major);
		head = temp1;
		n1 = head;
	}
	else
	{
		n1 = head;
		while (n1->next1 != NULL)
		{
			if (strcmp(n1->major, major) == 0)
				return;
			n1 = n1->next1;
		}
		if (n1->next1 == NULL)
		{
			if (strcmp(n1->major, major) != 0)
			{
				majornode* a = head;
				n1 = head;
				majornode* temp1 = new majornode;
				strcpy(temp1->major, major);
				while (1)
				{
					if (strcmp(head->major, major) > 0)
					{
						temp1->next1 = head;
						head = temp1;
						n1 = temp1;
						return;
					}
					else if (strcmp(n1->major, major) < 0)
					{
						a = n1;
						n1 = n1->next1;
					}
					if (n1 == NULL)
					{
						a->next1 = temp1;
						n1 = temp1;
						return;
					}
					if (strcmp(n1->major, major) > 0)
					{
						a->next1 = temp1;
						temp1->next1 = n1;
						n1 = temp1;
						return;
					}
				}
			}
		}
	}
}
void studentinfo::accessid(int id)
{
	if (n1->next2 == NULL)
	{
		idnode* temp2 = new idnode;
		temp2->id = id;
		n1->next2 = temp2;
		n2 = n1->next2;
	}
	else
	{
		n2 = n1->next2;
		while (n2->next2 != NULL)
		{
			if (n2->id == id)
				return;
			n2 = n2->next2;
		}
		if (n2->next2 == NULL)
		{
			if (n2->id != id)
			{
				idnode* b = n1->next2;
				n2 = n1->next2;
				idnode* temp2 = new idnode;
				temp2->id=id;
				while (1)
				{
					if (n2->id > id)
					{
						temp2->next2 = n2;
						n1->next2 = temp2;
						n2 = temp2;
						return;
					}
					else if (n2->id < id)
					{
						b = n2;
						n2 = n2->next2;
					}
					if (n2 == NULL)
					{
						b->next2 = temp2;
						n2 = temp2;
						return;
					}
					if (n2->id > id)
					{
						b->next2 = temp2;
						temp2->next2 = n2;
						n2 = temp2;
						return;
					}
				}
			}
		}
	}
}
void studentinfo::accessname(char* name)
{
	if (n2->next3 == NULL)
	{
		namenode* temp3 = new namenode;
		strcpy(temp3->name, name);
		n2->next3 = temp3;
		n3 = n2->next3;
		return;
	}
	n3 = n2->next3;
	while (n3 != NULL)
	{
		if (strcmp(n3->name, name) < 0)
		{
			if (n3->right == NULL)
			{
				n3->right = new namenode;
				strcpy(n3->right->name, name);
				n3 = n3->right;
				break;
			}
			n3 = n3->right;
		}
		else if (strcmp(n3->name, name) > 0)
		{
			if (n3->left == NULL)
			{
				n3->left = new namenode;
				strcpy(n3->left->name, name);
				n3 = n3->left;
				break;
			}
			n3 = n3->left;
		}
		else
			break;
	}
}
void studentinfo::treeprint(namenode* search)
{
	if (search != NULL)
	{
		treeprint(search->left);
		cout << n1->major << "->" << n2->id << "->" << search->name << endl;
		treeprint(search->right);
	}
}
void studentinfo::treeprint2(namenode* search, char* name)
{
	if (search != NULL)
	{
		treeprint2(search->left,name);
		if (strcmp(search->name, name) == 0)
		{
			cout << n1->major << "->" << n2->id << "->" << search->name << endl;
		}
		treeprint2(search->right,name);
	}
}

void studentinfo::print_all()
{
	n1 = head;
	n2 = n1->next2;
	n3 = n2->next3;
	while (n1 != NULL)
	{
		while (n2 != NULL)
		{
			treeprint(n3);
			n2 = n2->next2;
			if (n2 != NULL)
				n3 = n2->next3;
		}
		n1 = n1->next1;
		if (n1 != NULL)
			n2 = n1->next2;
		if (n2 != NULL)
			n3 = n2->next3;
	}
}
void studentinfo::print_major(char* major)
{
	n1 = head;
	n2 = NULL;
	n3 = NULL;
	while (n1 != NULL)
	{
		if (strcmp(n1->major, major) == 0)
		{
			n2 = n1->next2;
			if(n2!=NULL)
				n3 = n2->next3;
			break;
		}
		n1 = n1->next1;
	}
	while (n2 != NULL)
	{
		treeprint(n3);
		n2 = n2->next2;
		if (n2 != NULL)
			n3 = n2->next3;
	}
}
void studentinfo::print_id(int id)
{
	n1 = head;
	n2 = NULL;
	n3 = NULL;
	while (n1 != NULL)
	{
		n2 = n1->next2;
		while (n2 != NULL)
		{
			if (n2->id == id)
			{
				n3 = n2->next3;
				treeprint(n3);
			}
			n2 = n2->next2;
		}
		n1 = n1->next1;
	}
}
void studentinfo::print_name(char* name)
{
	n1 = head;
	n2 = n1->next2;
	n3 = n2->next3;
	while (n1 != NULL)
	{
		while (n2 != NULL)
		{
			treeprint2(n3,name);
			n2 = n2->next2;
			if (n2 != NULL)
				n3 = n2->next3;
		}
		n1 = n1->next1;
		if (n1 != NULL)
			n2 = n1->next2;
		if (n2 != NULL)
			n3 = n2->next3;
	}
}
void studentinfo::deletenode(char* major,int id,char* name)
{
	majornode*temp1= deletemajor(major);
	idnode* temp2=deleteid(id);
	deletename(name);
	cout << "Delete_Name : " << name << endl;
	if (n2->next3 == NULL)
	{
		if (temp2 == NULL)
		{
			n1->next2 = n2->next2;
			cout << "Delete_Year : " << n2->id << endl;
			delete n2;
		}
		else
		{
			temp2->next2 = n2->next2;
			cout << "Delete_Year : " << n2->id << endl;
			delete n2;
		}
	}
	if (n1->next2 == NULL)
	{
		if (temp1 == NULL)
		{
			head = n1->next1;
			cout << "Delete_Major : " << n1->major << endl;
			delete n1;
		}
		else
		{
			temp1->next1 = n1->next1;
			cout << "Delete_Major : " << n1->major << endl;
			delete n1;
		}
	}

}
majornode* studentinfo::deletemajor(char* major)
{
	majornode* a = NULL;
	n1 = head;
	while (n1 != NULL)
	{
		if (strcmp(n1->major, major) == 0)
			return a;
		a = n1;
		n1 = n1->next1;
	}
}
idnode* studentinfo::deleteid(int id)
{
	idnode* b = NULL;
	n2 = NULL;
	if(n1!=NULL)
		n2 = n1->next2;
	while (n2 != NULL)
	{
		if (n2->id == id)
			return b;
		b = n2;
		n2 = n2->next2;
	}
}
void studentinfo::deletename(char* name)
{
	namenode* n = n2->next3;
	namenode* a = n2->next3;
	while (n != NULL)
	{
		if (strcmp(n->name,name)<0)
		{
			a = n;
			n = n->right;
		}
		else if (strcmp(n->name,name)>0)
		{
			a = n;
			n = n->left;
		}
		else if (strcmp(n->name,name)==0)
		{
			if (a->left == n)
			{
				if (n->left != NULL && n->right == NULL)
				{
					a->left = n->left;
					delete n;
					break;
				}
				else if (n->left != NULL && n->right != NULL)
				{
					namenode* s = n->right;
					a = n;
					while (s->left != NULL)
					{
						a = s;
						s = s->left;
					}
					if (n == a)
					{
						strcpy(n->name,s->name);
						n->right = s->right;
						delete s;
						break;
					}
					strcpy(n->name,s->name);
					a->left = s->right;
					delete s;
					break;
				}
				a->left = n->right;
				break;
			}
			else if (a->right == n)
			{
				if (n->left != NULL && n->right == NULL)
				{
					a->right = n->left;
					delete n;
					break;
				}
				else if (n->left != NULL && n->right != NULL)
				{
					namenode* s = n->right;
					a = n;
					while (s->left != NULL)
					{
						a = s;
						s = s->left;
					}
					if (n == a)
					{
						strcpy(n->name,s->name);
						n->right = s->right;
						delete s;
						break;
					}
					strcpy(n->name, s->name);
					a->left = s->right;
					delete s;
					break;
				}
				a->right = n->right;
				break;
			}
			else if (strcmp(n->name,n2->next3->name)==0)
			{
				if (n->left == NULL && n->right == NULL)
				{
					n2->next3 = NULL;
					break;
				}
				else if (n->left != NULL && n->right == NULL)
				{
					n2->next3 = n->left;
					delete n;
					break;
				}
				else if (n->left == NULL && n->right != NULL)
				{
					n2->next3 = n->right;
					delete n;
					break;
				}
				else if (n->left != NULL && n->right != NULL)
				{
					namenode* s = n->right;
					a = n;
					while (s->left != NULL)
					{
						a = s;
						s = s->left;
					}
					if (n == a)
					{
						strcpy(n->name,s->name);
						n->right = s->right;
						delete s;
						break;
					}
					strcpy(n->name,s->name);
					a->left = s->right;
					delete s;
					break;
				}
			}
		}
	}
}
void studentinfo::memoryfree()
{
	majornode* del1 = NULL;
	idnode* del2 = NULL;
	n1 = head;
	if (n1 != NULL)
		n2 = n1->next2;
	if (n2 != NULL)
		n3 = n2->next3;
	while (n1 != NULL)
	{
		while (n2 != NULL)
		{
			namenode* n = n2->next3;
			namenode* a = n;
			while (n2->next3->left != NULL || n2->next3->right != NULL)
			{
				while (1)
				{
					if (n->left != NULL)
					{
						a = n;
						n = n->left;
						if (n->left == NULL && n->right == NULL)
						{
							delete n;
							a->left = NULL;
							break;
						}
					}
					else if (n->right != NULL)
					{
						a = n;
						n = n->right;
						if (n->left == NULL && n->right == NULL)
						{
							delete n;
							a->right = NULL;
							break;
						}
					}
				}
				n = n2->next3;
			}
			delete n2->next3;
			del2 = n2;
			n2 = n2->next2;
			delete del2;
		}
		del1 = n1;
		n1 = n1->next1;
		delete del1;
	}
}

int main()
{
	class studentinfo A;
	char major[50];
	int id;
	char name[30];
	int command = 0;
	ifstream readtxt;
	readtxt.open("Assignment3-3-4.txt");
	if (!readtxt)
	{
		cout << "파일을 열 수 없습니다.";
		exit(0);
	}
	while (!readtxt.eof())
	{
		readtxt >> major >> id >> name;
		A.buildlist(major,id,name);
	}

	readtxt.close();
	while (1)
	{
		cout << "Enter Any command(1: Insert, 2: Delete, 3: Print_all, 4: Print_major, 5: Print_id, 6: Print_name, 7: Exit):";
		cin >> command;
		if (command == 1)
		{
			cin >> major >> id >> name;
			A.buildlist(major, id, name);
		}
		else if (command == 2)
		{
			cin >> major >> id >> name;
			A.deletenode(major, id, name);
		}
		else if (command == 3)
		{
			A.print_all();
		}
		else if (command == 4)
		{
			cin >> major;
			A.print_major(major);
		}
		else if (command == 5)
		{
			cin >> id;
			A.print_id(id);
		}
		else if (command == 6)
		{
			cin >> name;
			A.print_name(name);
		}
		else if (command == 7)
		{
			A.memoryfree();
			break;
		}
	}
	return 0;
}