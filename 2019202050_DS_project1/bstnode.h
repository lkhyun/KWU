#include <iostream>
#include <string>
using namespace std;

class Database_BST_Node
{
    friend class Database_BST;
    friend class Manager;

private:
    string m_name;// picture name
    string dirname; //picture directory
    int unique_number; //picture number
    Database_BST_Node* left = NULL;
    Database_BST_Node* right = NULL;

public:
    Database_BST_Node();
    Database_BST_Node(string name,string dir,int number);

    friend ostream& operator<<(ostream& os, Database_BST_Node* node) //for node print with operator overloading
	{
		os << "(bstnode.m_name: " << node->m_name << "/"<<node->dirname<< "/" << node->unique_number << ")" <<endl; //Debug with print
		return os;
	}
};