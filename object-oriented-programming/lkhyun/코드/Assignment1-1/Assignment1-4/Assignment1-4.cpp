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
	int num1; //�Է°��� �Լ��� ������ ���� ���� ����� ������ �� ����
	int num2; //�Է°��� �޴� ����
	int* ptr = &num2;
	cout << "Number :";
	cin >> num2;
	num1 = num2;
	square(ptr);
	cout << "Number^2 :" << " " << num2 << endl;
	num2 = num1;//square�Լ��� ���� ���� num2���� �ٽ� ó�� �Է°����� �ʱ�ȭ��Ű�� ����
	cubic(ptr);
	cout << "Number^3 :" << " " << num2 << endl;
	return 0;
}