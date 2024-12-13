#include <iostream>
#include <cstdlib>

using namespace std;

char* my_strtok(char* string);//반환 함수
string arr;//처음 문자열을 입력받는 string
int save = 0;// '/'를 만났을 때를 기억하는 save point
int arrlength = 0;
int arr_length(string str);

int main()
{
	int num = 0;// 입력받은 문자열에서 /의 갯수
	
	cout << "Please Enter Any String :";
	cin >> arr;
	arrlength = arr_length(arr);
	char* str = new char[arrlength + 1];// arr을 strtok의 인수에 넣기 위해 형식 맞춰주기
	for (int i = 0; i < arrlength + 1; i++)// 값을 넣기 전에 초기화, arr이 들어가도 0이 남도록 arr의 길이+1만큼 동적할당
		str[i] = 0;

	for (int i = 0; i < arrlength; i++)//맞춰준 형식에 arr넣기
		str[i] = arr[i];

	for (int i = 0;str[i]!=0; i++)//str을 0으로 초기화했으므로 arr의 문자열이 없는 부분은 0이므로 0을 만났을 때 탈출
	{
		if (str[i] == '/')
			num++;
	}
	char** string = new char* [num + 1];//나눠지는 문자열갯수는 '/'의 갯수보다 1크므로 그만큼 동적할당
	string[0] = my_strtok(str); //우선 string의 첫 배열에 str을 인자로 받아 넣기
	for (int i = 1; i < num+1; i++)//그 이후에는 strtok에 NULL값을 계속 넣어 string에 str을 나눠 넣어주기
	{
		string[i] = my_strtok(NULL);
	}
	for (int i = 0; i < num + 1; i++)//나눠지는 문자열 갯수만큼 출력
	{
		for (int j = 0;; j++)
		{
			if (string[i][j] == 0)
				break;
			cout << string[i][j];
			
		}
		cout << endl;
		
	}
	
	delete[] str;//메모리 누수방지를 위한 메모리 해제
	for (int i = 0; i < num + 1; i++)
		delete[] string[i];
	delete[] string;
	return 0;
}
char* my_strtok(char* string)
{
	char* arr1 = new char[arrlength + 1];//arr은 string이므로 출력시 사용할 0을 넣어줄 수 없음. 따라서 arr길이보다 1늘려 0을 넣어줄 arr1동적할당
	arr1[arrlength] = 0;//arr1의 끝에 숫자 0을 넣어 출력시 조건문으로 사용할 예정
	for (int i = 0; i < arrlength; i++)//arr을 arr1에 복사
		arr1[i] = arr[i];
	char* arr2 = new char[arrlength+1];//나눠진 문자열을 반환하기 위한 동적할당 역시 길이를 +1하여 숫자 0을 넣어줘 조건문에 활용할 예정

	if (string != NULL)
	{
		for (int i = 0;; i++)
		{
			if (string[i] == '/' || string[i] == 0)// /를 만나거나 문자열의 끝에 도달하면
			{
				arr[i] = NULL;
				save = i;
				for (int j = 0; j < i; j++)
				{
					arr2[j] = string[j];//인수로 받은 str을 arr2에 저장
				}
				arr2[i] = 0;//문자 끝에는 0을 넣어 끝을 표시
				delete[] arr1;// 메모리 해제
				break;
			}
		}
		return arr2;//arr2는 반환하면서 string[i]가 이 변수를 가리키므로 main에서 string[i]를 해제해주면 누수x
	}
	
	else if (string == NULL)
	{
		if (save == 0)
			return NULL;
		if (save != 0)
		{
			for (int i = save + 1;; i++)
			{
				if (arr1[i] == '/' || arr1[i] == 0)
				{
					arr[i] = NULL;
					int k = save + 1;//전에 /에서 세이브포인트를 save에 저장했으므로 +1한 지점부터 문자열 저장
					save = i;//새로운 세이브 포인트
					for (int j = k; j < i; j++)
					{
						arr2[j - k] = arr1[j];// 세이브 포인트를 활용하여 arr1의 일부 문자열을 arr2의 첫번째배열부터 넣어줌
					}
					arr2[i - k] = 0;//0으로 끝을 표시
					delete[] arr1;//메모리 해제
					break;
				}
			}
			return arr2;// arr2를 반환하면 string[i]가 main에서 arr2를 가리키므로 main에서 string[i]해제해주면 누수 x
		}
	}	
}
int arr_length(string str)
{
	int i;
	for (i = 0; str[i] != NULL; i++);
	return i;
}