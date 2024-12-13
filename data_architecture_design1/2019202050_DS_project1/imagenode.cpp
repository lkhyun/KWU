#include "imagenode.h"

Loaded_LIST_Node::Loaded_LIST_Node(string name,string dir,string number)
    {
        m_name.assign(name);
        dirname.assign(dir);
        unique_number.assign(number);
    }