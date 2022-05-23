#include<iostream>
using namespace std;

int main()
{
	char name[30];//이름 입력받는 변수
	char major[30];//전공 입력받는 변수
	int id = 0;// 학번 입력받는 변수
	cout << "이름 : ";
	cin >> name;//이름 입력
	cout << "학번 : ";
	cin >> id;//학번 입력
	cout << "전공 : ";
	cin >> major;//전공 입력

	cout << major << " " << id << " " << name;
	return 0;

}