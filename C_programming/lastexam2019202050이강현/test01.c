#include <stdio.h>
int main(void)
{
	char str[30] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //모든 알파벳 배열 선언
	int i, j;

	for (i = 1; i < 27; i++)
	{
		for (j = 0; j < i; j++)//i보다 작다는 조건으로 문자열 길이조절
		{
			printf("%c", str[j]);// 문자열 출력
		}
		printf("\n");
		
		
	}

	return 0;
}