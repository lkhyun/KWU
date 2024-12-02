#include "imagenode.h"

class Loaded_LIST
{
    friend class Manager; //to be managed by the manager.h
private:
    string folder;
    Loaded_LIST_Node* list_root= NULL; 
    Loaded_LIST* list_down = NULL; 
    

public:
    void initializing(string name,string dir,string number); 
    void insertnode(string name,string dir,string number);
    bool deletenode(string name, string dir, string num);
    
};