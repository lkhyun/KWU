#include <iostream>
using namespace std;
template<typename T> class Queue
{
public:
    int front;
    int rear;
    int size = 0;
    T* valptr = NULL;

    Queue(int num) 
    {
        valptr = new T[num];
        front = 0;
        rear = 0;
        size = num;
    }
    ~Queue()
    {
        delete[] valptr;
    }

    void push(T value) 
    {
        valptr[rear] = value;
        rear = (rear+1) % size; //round queue
    }

    T pop() 
    {
        if(front != rear)
        {
            front = (front+1) % size;
            return valptr[front-1];
        }
        else
            return NULL;
    }
    
    bool empty()
    {
        if(front == rear)
            return true;
        else    
            return false;
    }
};