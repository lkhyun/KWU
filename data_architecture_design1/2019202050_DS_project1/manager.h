#include "nodelist.h"//loaded_list
#include "bst.h"//Database_bst
#include "queue.h"
#include "stack.h"
#include "imagequeue.h"
#include "imagestack.h"
#include <fstream>
#include <cstring>

class Manager
{
private:
    Loaded_LIST* bufferlist = NULL;
    Database_BST* bst = new Database_BST();
    ofstream logout;
    ifstream cmdin;
    ifstream readcsv;
    int listfull= 0;
    int bstfull = 0;
    Database_BST_Node* selectfile = NULL;
    int selectnumber = 0;
    int endflag = 0;

public:
    ~Manager();
    void Run(const char* file_path);
    void PrintERROR(int num);
    void nodeprint(Loaded_LIST* node);
    void nodeisfull();
    void inorderprint(Database_BST_Node* node);
    void preorder(Database_BST_Node* node);
    void bstmemoryfree(Database_BST_Node* node);
};