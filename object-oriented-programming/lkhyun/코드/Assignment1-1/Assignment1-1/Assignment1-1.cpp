#include<iostream>
using namespace std;

int main()
{
	char name[30];//�̸� �Է¹޴� ����
	char major[30];//���� �Է¹޴� ����
	int id = 0;// �й� �Է¹޴� ����
	cout << "�̸� : ";
	cin >> name;//�̸� �Է�
	cout << "�й� : ";
	cin >> id;//�й� �Է�
	cout << "���� : ";
	cin >> major;//���� �Է�

	cout << major << " " << id << " " << name;
	return 0;

}