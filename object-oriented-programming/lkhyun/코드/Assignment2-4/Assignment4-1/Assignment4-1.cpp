#include <iostream>
using namespace std;

class Overloading
{
public:
	Overloading()
	{
	}
	void add(int num1, int num2)
	{
		cout << "Int type add : " << num1+num2 << endl;
	}
	void add(float num1, float num2)
	{
		cout << "Float type add : " << num1 + num2 << endl;
	}
	void add(unsigned int num1, unsigned int num2)
	{
		cout << "Unsigned int type add : " << num1 + num2 << endl;
	}
};

int main()
{
	class Overloading A;
	int int_a = 5, int_b = -10;
	float float_a = 5.1, float_b = 5.3;
	unsigned int unsigned_int_a = 5, unsigned_int_b = 5;

	A.add(int_a, int_b);
	A.add(float_a, float_b);
	A.add(unsigned_int_a, unsigned_int_b);
	return 0;
}