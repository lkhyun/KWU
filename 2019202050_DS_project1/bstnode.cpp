#include "bstnode.h"

Database_BST_Node::Database_BST_Node(string name,string dir,int number) //when the node create
    {
        m_name.assign(name);
        dirname.assign(dir);
        unique_number = number;
    }