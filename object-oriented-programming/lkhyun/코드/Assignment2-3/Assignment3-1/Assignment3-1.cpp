#include <iostream>
using namespace std;

class A
{
private:
	int num = 0;

public:
	A()
	{
		cout << "Enter Any Number :";
		cin >> num;
		cout << "Class A is created with" << ' ' << num << endl;
	}
	~A() 
	{
		cout << "Class A is Destroyed with" << ' ' << num;
	}
};
int main()
{
	A ClassA = A();
	return 0;
}