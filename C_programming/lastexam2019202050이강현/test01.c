#include <stdio.h>
int main(void)
{
	char str[30] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //��� ���ĺ� �迭 ����
	int i, j;

	for (i = 1; i < 27; i++)
	{
		for (j = 0; j < i; j++)//i���� �۴ٴ� �������� ���ڿ� ��������
		{
			printf("%c", str[j]);// ���ڿ� ���
		}
		printf("\n");
		
		
	}

	return 0;
}