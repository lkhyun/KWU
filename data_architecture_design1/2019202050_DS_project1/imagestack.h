#include <iostream>
using namespace std;
class imageStack
{

private:
    int index; //top index
    unsigned char *ptr; 

public:
    imageStack(int num) //size input
    {
        index = -1;
        ptr = new unsigned char[num];
    }         
    ~imageStack()
    {
        delete ptr;
    }               
    unsigned char Pop()
    {
        if(!Empty())
            return ptr[index--];
        return 0;
    }                
    void Push(const unsigned char &value)
    {
        ptr[++index] = value;
    }
    bool Empty()
    {
        if(index<0)
            return true;
        else
            return false;
    };                     
};