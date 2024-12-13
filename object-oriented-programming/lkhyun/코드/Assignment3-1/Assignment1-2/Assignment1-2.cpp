#include <iostream>
#include <cmath>
using namespace std;

class Polygon
{
private:
	int Area;
	int perimeter;
public:
	Polygon(int a, int b)
	{
		Area = a * b;
		perimeter= ((a * 2) + (b * 2));
	}
	Polygon(int a, int b, int c)
	{
		int h = (a + b + c) / 2;
		Area = sqrt(h * (h - a) * (h - b) * (h - c));
		perimeter = a + b + c;
	}
	void print_Area()
	{
		cout << "Area is " << Area << endl;
	}
	void print_Perimeter()
	{
		cout << "Perimeter is " << perimeter << endl;
	}
};

class Triangle :public Polygon
{
private:
	int A;
	int B;
	int C;
public:
	Triangle(int a, int b, int c) :Polygon(a, b, c) 
	{
		A = a;
		B = b;
		C = c;
	}

};

class Square :public Polygon
{
private:
	int A;
	int B;
public:
	Square(int a, int b) :Polygon(a,b)
	{
		A = a;
		B = b;
	}
};

int main()
{
	class Square A(5, 4);
	class Triangle B(13, 14, 15);

	cout << "--------Square--------" << endl;
	A.print_Area();
	A.print_Perimeter();
	cout << "----------------------" << endl;
	cout << "-------Triangle-------" << endl;
	B.print_Area();
	B.print_Perimeter();
	cout << "-----------------------" << endl;
	return 0;
}