#include "bstnode.h"

class Database_BST
{
    friend class Manager;
private:
    Database_BST_Node* bst_root= NULL; 
    
public:

    bool insertnode(string name,string dir,int number);
    bool deletenode();
};