#include <iostream>
using namespace std;
class imageQueue //for photo editing
{
public:
    int front;
    int rear;
    int size = 0;
    unsigned char* value;

    imageQueue(int num) //queue size input
    {
        value = new unsigned char[num];
        front = 0;
        rear = 0;
        size = num;
    }
    ~imageQueue()
    {
        delete[] value;
    }

    void push(unsigned char val) 
    {
        value[rear] = val;
        rear = (rear+1) % size; //round queue
    }

    unsigned char pop() 
    {
        if(front != rear)
        {
            front = (front+1) % size;
            return value[front-1];
        }
        return 0;
    }
    
    bool empty()
    {
        if(front == rear)
            return true;
        else    
            return false;
    }
};