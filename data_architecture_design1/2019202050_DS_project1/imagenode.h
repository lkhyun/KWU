#include <iostream>
#include <string>
using namespace std;

class Loaded_LIST_Node
{
    friend class Loaded_LIST;
    friend class Manager;

private:
    string m_name;
    string dirname;
    string unique_number;
    Loaded_LIST_Node* nextnode = NULL;

public:
    Loaded_LIST_Node();
    Loaded_LIST_Node(string name,string dir,string number);

    friend ostream& operator<<(ostream& os, Loaded_LIST_Node* node) //for node printing with operator overloading
	{
		os << "(node.m_name: " << node->m_name << "/"<<node->dirname<< "/" << node->unique_number << ")" <<endl; //Debug with print
		return os;
	}
};