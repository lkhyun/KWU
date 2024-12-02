#include "bst.h"

bool Database_BST::insertnode(string name,string dir,int number) 
{
    if(bst_root == NULL) //when bst is empty
    {
        Database_BST_Node* temp = new Database_BST_Node(name,dir,number);
        bst_root = temp;
        return true;
    }
    Database_BST_Node* temp1 = bst_root; //root initializing
    while(1)
    {
        if(temp1->unique_number > number) //when the input is less than the existing node
        {
            Database_BST_Node* temp2 = new Database_BST_Node(name,dir,number);
            if(temp1->left == NULL)
            {
                temp1->left = temp2;
                return true;
            }
            temp1 = temp1->left;
        }
        else if(temp1->unique_number < number)//when the input is larger than the existing node
        {   
            Database_BST_Node* temp2 = new Database_BST_Node(name,dir,number);
            if(temp1->right == NULL)
            {
                temp1->right = temp2;
                return true;
            }
            temp1 = temp1->right;
        }
        else
        {
            return false; //when the unique number is same
        }
    }
}
bool Database_BST:: deletenode()//delete the smallest value
{
    Database_BST_Node* temp1= bst_root;
    Database_BST_Node* temp2= NULL;
   if(bst_root == NULL) //when bst is empty
   {
        return false;
   }
   else if(bst_root->left != NULL)//when the root's left is not empty
   {
        while(temp1->left != NULL)
        {
            temp2 = temp1;
            temp1 = temp1->left;
        }
        temp2->left = temp1->right;
        delete temp1;
        temp1 = NULL;
        return true;
        
   }
   else if(bst_root->left == NULL && bst_root->right != NULL)//only right is not empty
   {
        temp2=temp1;
        temp1= temp1->right;
        if(temp1->left ==NULL)
        {
            bst_root = temp1;
            delete temp2;
            temp2 = NULL;
            return true;
        }
        else
        {
            Database_BST_Node* temp3 = temp1;
            while(temp1->left != NULL)
            {
                temp2 = temp1;
                temp1 = temp1->left;
            }
            temp2->left = temp1->right;
            temp1->right = temp3;
            delete bst_root;
            bst_root = NULL;
            bst_root = temp1;
            return true;
        }
   }
   else //when the only node is root
   {
        delete bst_root;
        bst_root = NULL;
        return true;
   }  
}
