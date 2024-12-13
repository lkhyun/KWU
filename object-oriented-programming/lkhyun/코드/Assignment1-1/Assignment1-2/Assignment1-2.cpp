#include <iostream>
using namespace std;
long long add_func(long long num1, long long num2) 
{
	return (num1 + num2);
}


int main()
{
	long long num1, num2; //문제의 범위를 충족하기 위한 long long자료형 사용
	do
	{
		cout << "Enter Two Numbers : ";
		cin >> num1;
		cin >> num2;
	} while (num1 < 0 || num2 < 0 ||num1>=3000000000||num2>=3000000000);//입력받은 변수가 범위 밖일 때 다시 입력받게 함
	
	cout << add_func(num1, num2);
	return 0;
}