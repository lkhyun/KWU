#include "nodelist.h"


void Loaded_LIST::initializing(string name,string dir,string number) //first node
    {
        if(list_root == NULL)
        {
            Loaded_LIST_Node* temp1 = new Loaded_LIST_Node(name,dir,number);
            folder.assign(dir);
            list_root = temp1;
        }
    }
void Loaded_LIST::insertnode(string name,string dir,string number)// input node
    {
        if(list_root==NULL)
        {
            initializing(name,dir,number);//first
            return;
        }
        Loaded_LIST_Node* temp1 = list_root;
        Loaded_LIST_Node* temp2 = new Loaded_LIST_Node(name,dir,number);
        while(temp1->nextnode != NULL)
            temp1 = temp1->nextnode;
        temp1->nextnode = temp2;
    }
bool Loaded_LIST::deletenode(string name, string dir, string num)
    {
        Loaded_LIST_Node* temp1 = list_root;
        Loaded_LIST_Node* temp2 = NULL;
        while(temp1 != NULL)
        {
            if(temp1->m_name.compare(name)==0) //if same name
            {
                if(temp1==list_root) //first node
                {
                    temp2 = new Loaded_LIST_Node(name,dir,num);
                    temp2 ->nextnode = temp1->nextnode;
                    delete temp1;
                    temp1 = NULL;
                    list_root = temp2;
                    return true; 
                }
                if(temp1->nextnode == NULL)// finish node
                {
                    Loaded_LIST_Node* temp3 = new Loaded_LIST_Node(name,dir,num);
                    temp2->nextnode = temp3;
                    delete temp1;
                    temp1 = NULL;
                    return true;
                }
                Loaded_LIST_Node* temp3 = new Loaded_LIST_Node(name,dir,num);
                temp2->nextnode = temp3;
                temp3->nextnode = temp1->nextnode;
                delete temp1;
                temp1 = NULL;
                return true; //general situation
            }
            temp2 = temp1;
            temp1=temp1->nextnode;
        }
        return false; //failed to delete
    }

