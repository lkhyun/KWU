#include <iostream>
using namespace std;
template <typename T>
class Stack
{

private:
    int index; // top's index
    T *ptr;     //save space

public:
    Stack(int num)
    {
        index = -1;
        ptr = new T[num];
    }         
    ~Stack()
    {
        delete ptr;
    }               
    T Pop()
    {
        if(index < 0) 
            return NULL;
        else
            return ptr[index--];
    }                
    void Push(const T &value)
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
    T Top()
    {
        if(index<0)
            return NULL;
        else
            return ptr[index];
    }             
};