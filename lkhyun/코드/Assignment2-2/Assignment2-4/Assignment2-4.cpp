#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

char* insert_voca(string str);
int vocalength(char* voca);
char convert_voca(char str1);
int str_length(string word);
int main()
{
	string command;
	string word;
	char** voca = new char*[100];
	int p = 0;
	int i = 0;//현재 비어있는 공간중 가장 첫번째
	while(1)
	{
		cin >> command;
		if (command == "INSERT")
		{
			if (i == 100)
			{
				cout << "FULL! Can't save anymore." << endl;
				continue;
			}
			cin >> word;
			if (i == 0)
			{
				voca[0] = insert_voca(word);
				i++;
				for (int j = 0; j < i; j++)
				{
					cout << j << '.' << voca[j] << endl;
				}
				continue;
			}
				
			for (int j = 0; j < i;)
			{
				if (convert_voca(voca[j][p]) < convert_voca(word[p]))//알파벳 순서비교
				{
					j++;
					p = 0;
					if (j == i)
					{
						voca[j] = insert_voca(word);
						i++;
						p = 0;
						break;
					}
				}
				else if (convert_voca(voca[j][p]) > convert_voca(word[p]))// 알파벳 순서 비교
				{
					for (int k = i - 1; k > j - 1; k--)
					{
						voca[k + 1] = voca[k];
					}
					i++;
					voca[j] = insert_voca(word);
					p = 0;
					break;
				}
				else if (convert_voca(voca[j][p]) == convert_voca(word[p]))//알파벳이 같을때
				{
					if (convert_voca(voca[j][p + 1]) == 0 && convert_voca(word[p + 1]) == NULL)
					{
						p = 0;
						break;
					}
					if (convert_voca(word[p + 1]) == NULL)
					{
						for (int k = i - 1; k > j - 1; k--)
						{
							voca[k + 1] = voca[k];
						}
						i++;
						voca[j] = insert_voca(word);
						p = 0;
						break;
					}
					p++;
				}
			}
			
			for (int j = 0; j < i; j++)
			{
				cout << j << '.' << voca[j] << endl;
			}
		}
		else if (command == "FIND")
		{
			int temp = 0;
			cin >> word;
			for (int k = 0; k < i; k++)
			{
				if (voca[k] == word)
				{
					cout << k << '.' << voca[k] << endl;
					temp++;
				}
			}
			if (temp == 0)
				cout << "Not Found";
		}
		else if (command == "END")
		break;
		
	}
	for (int j = 0; j < i; j++)
		delete[] voca[j];
	delete[] voca;
	return 0;
}
char* insert_voca(string str)
{
	char* word = new char[str_length(str)+1];
	for (int j = 0; j < str_length(str) + 1; j++)
		word[j] = 0;
	for (int j = 0; j < str_length(str); j++)
		word[j] = str[j];
	return word;
}
int vocalength(char* voca)
{
	for (int p = 0;; p++)
	{
		if (voca[p] == 0)
			return p;
	}
}
char convert_voca(char str1)
{
	if (str1 >= 65 && str1<= 90)
		str1 = str1 + 32;
	return str1;
}
int str_length(string word)
{
	int i;
	for (i = 0; word[i] != NULL; i++);
	return i;
}