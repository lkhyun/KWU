#include <iostream>
using namespace std;

void square(int* ptr)
{
	*ptr *= *ptr;
}
void cubic(int* ptr)
{
	*ptr = *ptr * *ptr * *ptr;
}

int main()
{
	int num1; //입력값이 함수의 참조로 변할 것을 대비해 저장해 둘 변수
	int num2; //입력값을 받는 변수
	int* ptr = &num2;
	cout << "Number :";
	cin >> num2;
	num1 = num2;
	square(ptr);
	cout << "Number^2 :" << " " << num2 << endl;
	num2 = num1;//square함수의 의해 변한 num2값을 다시 처음 입력값으로 초기화시키는 과정
	cubic(ptr);
	cout << "Number^3 :" << " " << num2 << endl;
	return 0;
}