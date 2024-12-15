#include <stdio.h>
 
int sum_func(int num);//재귀함수의 선언

int main(void)
{
	int num;
	printf("합을 구할 값? ");
	scanf("%d", &num);
	
	printf("%d", sum_func(num));//재귀함수를 전달인자로 받아 출력

	return 0;
}
int sum_func(int num)
{
	if (num>0)//재귀함수 전달인자가 자연수임을 한정하기 위한 조건문
	{
		return (num + sum_func(num - 1));//값의 반환
	}
	return 0;
}