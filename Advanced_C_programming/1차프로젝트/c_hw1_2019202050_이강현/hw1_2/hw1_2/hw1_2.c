#include <stdio.h>//헤더파일 선언

int InputFunc()//값 입력받는 함수
{
	int i = 0;//변수 선언
	printf("값 입력: ");//출력문
	scanf("%d", &i);//i값 입력받기
	return i;//i값 반환

}

int main()//main 함수 선언
{
	int num = 0;//변수 num 선언
	num = InputFunc();//함수 실행 후 num에 값 대입

	while (num < 0 || num>50000)//0과 50000 사이의 값
	{
		printf("다시입력\n");//출력문
		num = InputFunc();//다시 값 입력받기

	}
	/*0에서 50000까지의 int형 변수임을 이용하여 일의 자리 십의 자리 백의 자리 천의 자리 만의 자리에 접근하는 방법*/
	printf("%d,%d,%d,%d,%d \n", (num / 10000) % 10, (num / 1000) % 10, (num / 100) % 10, (num / 10) % 10, num % 10);//출력문
	printf("%d,%d,%d,%d \n", (num / 1000) % 10, (num / 100) % 10, (num / 10) % 10, num % 10);//출력문
	printf("%d,%d,%d \n", (num / 100) % 10, (num / 10) % 10, num % 10);//출력문
	printf("%d,%d \n", (num / 10) % 10, num % 10);//출력문
	printf("%d \n", num % 10);//출력문

	return 0;//종료
}