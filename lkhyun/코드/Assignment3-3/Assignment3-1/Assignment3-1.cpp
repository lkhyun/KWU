#include <iostream>
using namespace std;

class node
{
public:
	int number;
	node* right = NULL;
	node* left = NULL;
};
class BST
{
private:
	node* root = NULL;
public:
	BST()
	{}
	void nodeinsert(int num)
	{
		node* n = root;
		if (n == NULL)
		{
			root = new node;
			root->number = num;
			return;
		}
		while (n != NULL)
		{
			if (n->number < num)
			{
				if (n->right == NULL)
				{
					n->right = new node;
					n->right->number = num;
					break;
				}
				n = n->right;
			}
			else if (n->number > num)
			{
				if (n->left == NULL)
				{
					n->left = new node;
					n->left->number = num;
					break;
				}
				n = n->left;
			}
			else
				break;
		}
	}
	void deletenode(int num)
	{
		node* n = root;
		node* a = root;
		while (n != NULL)
		{
			if (n->number < num)
			{
				a = n;
				n = n->right;
			}
			else if (n->number > num)
			{
				a = n;
				n = n->left;
			}
			else if(n->number==num)
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
						node* s = n->right;
						a = n;
						while (s->left != NULL)
						{
							a = s;
							s = s->left;
						}
						if (n == a)
						{
							n->number = s->number;
							n->right = s->right;
							delete s;
							break;
						}
						n->number = s->number;
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
						node* s = n->right;
						a = n;
						while (s->left != NULL)
						{
							a = s;
							s = s->left;
						}
						if (n == a)
						{
							n->number = s->number;
							n->right = s->right;
							delete s;
							break;
						}
						n->number = s->number;
						a->left = s->right;
						delete s;
						break;
					}
					a->right = n->right;
					break;
				}
				else if (n->number == root->number)
				{
					if (n->left == NULL && n->right == NULL)
					{
						root = NULL;
						break;
					}
					else if (n->left != NULL && n->right == NULL)
					{
						root = n->left;
						delete n;
						break;
					}
					else if (n->left == NULL && n->right != NULL)
					{
						root = n->right;
						delete n;
						break;
					}
					else if (n->left != NULL && n->right != NULL)
					{
						node* s = n->right;
						a = n;
						while (s->left != NULL)
						{
							a = s;
							s = s->left;
						}
						if (n == a)
						{
							n->number = s->number;
							n->right = s->right;
							delete s;
							break;
						}
						n->number = s->number;
						a->left = s->right;
						delete s;
						break;
					}
				}
			}
		}
	}
	void findnode(int num)
	{
		node* n = root;
		while (n != NULL)
		{
			if (n->number < num)
			{
				n = n->right;
			}
			else if (n->number > num)
			{
				n = n->left;
			}
			else if (n->number == num)
			{
				n = root;
				cout << "path :" << root->number;
				while (1)
				{
					if (n->number < num)
					{
						n = n->right;
					}
					else if (n->number > num)
					{
						n = n->left;
					}
					cout << "->" << n->number;
					if (n->number == num)
						break;
				}
				break;
			}
		}
		cout << endl;
	}
	void memoryfree()
	{
		node* n = root;
		node* a = n;
		while (root->left != NULL || root->right != NULL)
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
			n = root;
		}
		delete root;
	}
};

int main()
{
	BST A;
	int command;
	int number = 0;
	while (1)
	{
		cout << "Enter Any Command(1:insert, 2:Delete, 3:Find, 4:Exit): ";
		cin >> command;
		if (command == 1)
		{
			cin >> number;
			A.nodeinsert(number);
		}
		else if (command == 2)
		{
			cin >> number;
			A.deletenode(number);
		}
		else if (command == 3)
		{
			cin >> number;
			A.findnode(number);
		}
		else if (command == 4)
		{
			A.memoryfree();
			return 0;
		}
	}
}