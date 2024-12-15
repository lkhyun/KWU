#include <stdio.h>
int main(void)
{
	char str[20] = "";//문자열 선언
	char *ptr = str;//포인터 변수 선언
	int i, temp;
	int len;
	printf("입력 문자열? ");//문자열 입력받기
	scanf("%s", str);

	len = sizeof(str);//문자열 길이계산

	for (i = 0; i < len/2; i++)//문자열 간에 앞뒤 자리를 반복문을 통해서 바꾸기
	{
		temp = *(ptr + i);
		*(ptr + i) = *(ptr + len-1-i);
		*(ptr + len-1-i) = temp;
	}
	
		printf("%s", *ptr);//문자열 출력
	

	printf("%d", len);//문자열 길이 출력
	return 0;
}