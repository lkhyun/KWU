#include <iostream>
using namespace std;
long long add_func(long long num1, long long num2) 
{
	return (num1 + num2);
}


int main()
{
	long long num1, num2; //������ ������ �����ϱ� ���� long long�ڷ��� ���
	do
	{
		cout << "Enter Two Numbers : ";
		cin >> num1;
		cin >> num2;
	} while (num1 < 0 || num2 < 0 ||num1>=3000000000||num2>=3000000000);//�Է¹��� ������ ���� ���� �� �ٽ� �Է¹ް� ��
	
	cout << add_func(num1, num2);
	return 0;
}