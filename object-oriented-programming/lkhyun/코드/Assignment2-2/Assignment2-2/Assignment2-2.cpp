#include <iostream>
#include <cstdlib>

using namespace std;

char* my_strtok(char* string);//��ȯ �Լ�
string arr;//ó�� ���ڿ��� �Է¹޴� string
int save = 0;// '/'�� ������ ���� ����ϴ� save point
int arrlength = 0;
int arr_length(string str);

int main()
{
	int num = 0;// �Է¹��� ���ڿ����� /�� ����
	
	cout << "Please Enter Any String :";
	cin >> arr;
	arrlength = arr_length(arr);
	char* str = new char[arrlength + 1];// arr�� strtok�� �μ��� �ֱ� ���� ���� �����ֱ�
	for (int i = 0; i < arrlength + 1; i++)// ���� �ֱ� ���� �ʱ�ȭ, arr�� ���� 0�� ������ arr�� ����+1��ŭ �����Ҵ�
		str[i] = 0;

	for (int i = 0; i < arrlength; i++)//������ ���Ŀ� arr�ֱ�
		str[i] = arr[i];

	for (int i = 0;str[i]!=0; i++)//str�� 0���� �ʱ�ȭ�����Ƿ� arr�� ���ڿ��� ���� �κ��� 0�̹Ƿ� 0�� ������ �� Ż��
	{
		if (str[i] == '/')
			num++;
	}
	char** string = new char* [num + 1];//�������� ���ڿ������� '/'�� �������� 1ũ�Ƿ� �׸�ŭ �����Ҵ�
	string[0] = my_strtok(str); //�켱 string�� ù �迭�� str�� ���ڷ� �޾� �ֱ�
	for (int i = 1; i < num+1; i++)//�� ���Ŀ��� strtok�� NULL���� ��� �־� string�� str�� ���� �־��ֱ�
	{
		string[i] = my_strtok(NULL);
	}
	for (int i = 0; i < num + 1; i++)//�������� ���ڿ� ������ŭ ���
	{
		for (int j = 0;; j++)
		{
			if (string[i][j] == 0)
				break;
			cout << string[i][j];
			
		}
		cout << endl;
		
	}
	
	delete[] str;//�޸� ���������� ���� �޸� ����
	for (int i = 0; i < num + 1; i++)
		delete[] string[i];
	delete[] string;
	return 0;
}
char* my_strtok(char* string)
{
	char* arr1 = new char[arrlength + 1];//arr�� string�̹Ƿ� ��½� ����� 0�� �־��� �� ����. ���� arr���̺��� 1�÷� 0�� �־��� arr1�����Ҵ�
	arr1[arrlength] = 0;//arr1�� ���� ���� 0�� �־� ��½� ���ǹ����� ����� ����
	for (int i = 0; i < arrlength; i++)//arr�� arr1�� ����
		arr1[i] = arr[i];
	char* arr2 = new char[arrlength+1];//������ ���ڿ��� ��ȯ�ϱ� ���� �����Ҵ� ���� ���̸� +1�Ͽ� ���� 0�� �־��� ���ǹ��� Ȱ���� ����

	if (string != NULL)
	{
		for (int i = 0;; i++)
		{
			if (string[i] == '/' || string[i] == 0)// /�� �����ų� ���ڿ��� ���� �����ϸ�
			{
				arr[i] = NULL;
				save = i;
				for (int j = 0; j < i; j++)
				{
					arr2[j] = string[j];//�μ��� ���� str�� arr2�� ����
				}
				arr2[i] = 0;//���� ������ 0�� �־� ���� ǥ��
				delete[] arr1;// �޸� ����
				break;
			}
		}
		return arr2;//arr2�� ��ȯ�ϸ鼭 string[i]�� �� ������ ����Ű�Ƿ� main���� string[i]�� �������ָ� ����x
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
					int k = save + 1;//���� /���� ���̺�����Ʈ�� save�� ���������Ƿ� +1�� �������� ���ڿ� ����
					save = i;//���ο� ���̺� ����Ʈ
					for (int j = k; j < i; j++)
					{
						arr2[j - k] = arr1[j];// ���̺� ����Ʈ�� Ȱ���Ͽ� arr1�� �Ϻ� ���ڿ��� arr2�� ù��°�迭���� �־���
					}
					arr2[i - k] = 0;//0���� ���� ǥ��
					delete[] arr1;//�޸� ����
					break;
				}
			}
			return arr2;// arr2�� ��ȯ�ϸ� string[i]�� main���� arr2�� ����Ű�Ƿ� main���� string[i]�������ָ� ���� x
		}
	}	
}
int arr_length(string str)
{
	int i;
	for (i = 0; str[i] != NULL; i++);
	return i;
}