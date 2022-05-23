#include <iostream>
using namespace std;

class TwoPoint
{
private:
    int a1, a2;
    int b1, b2;
public:
    TwoPoint(int a1, int a2, int b1, int b2)
    {
        this->a1 = a1;
        this->a2 = a2;
        this->b1 = b1;
        this->b2 = b2;
    }
    virtual void print()
    {
        cout << "Point 1 : " << a1 << ',' << a2 << endl;
        cout << "Point 2 : " << b1 << ',' << b2 << endl;
    }
};
class Equation: public TwoPoint
{
private:
    int a1 = 0;
    int a2 = 0;
    int b1 = 0;
    int b2 = 0;
    float a = 0;
    float b = 0;
public:
    Equation(int a1, int a2, int b1, int b2) :TwoPoint(a1, a2, b1, b2) 
    {
        a = (float)(b2 - a2) / (b1 - a1);
        b = (float)a2 - a * (float)a1;
    }
    virtual void print()
    {
        cout << "Equation : y = " << a << "x + " << b << endl;
    }
};

int main()
{
    class TwoPoint* A = new TwoPoint(2, 4, 7, 8);
    class TwoPoint* B = new Equation(2, 4, 7, 8);
    A->print();
    B->print();
    delete A;
    delete B;
}