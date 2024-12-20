#include <stdio.h>//헤더 파일 선언

int main()//main함수 선언
{
	int num1 = 0;//변수 num1선언 및 초기화
	int num2 = 0;//변수 num2선언 및 초기화
	int i = 0;//변수 i선언 및 초기화
	int j = 0;//변수 j선언 및 초기화
	int k = 0;//변수 k선언 및 초기화
	int arr[10] = { 0 };//크기가 10인 배열 선언 및 초기화

	printf("Input range(first): ");//숫자 범위의 처음부분 입력받기
	scanf("%d", &num1);

	printf("Input range(second): ");//숫자 범위의 나중 부분 입력받기
	scanf("%d", &num2);

	j = num1;//반복문에서 간단하게 사용하기 위해 변수 j에 num1값 대입

	for (i = 0; i <= num2 - num1; i++)//범위만큼 반복하는 반복문
	{
		if (j < 10)//한자리수 일때
		{
			k = j % 10;//나머지를 이용
			arr[k]++;//나머지값=배열순서로 저장
		}
		else if (j < 100)//두자리수 일때
		{
			k = (j / 10) % 10;//j가 정수임을 이용하여 나누어서 십의 자리에 접근
			arr[k]++;//나머지값=배열순서로 저장
			k = j % 10;//나머지를 이용
			arr[k]++;//나머지값=배열순서로 저장
		}
		else if (j < 1000)//세자리수 일때
		{
			k = (j / 100) % 10;//j가 정수임을 이용하여 나누어서 백의 자리에 접근
			arr[k]++;//나머지값=배열순서로 저장
			k = (j / 10) % 10;//j가 정수임을 이용하여 나누어서 십의 자리에 접근
			arr[k]++;//나머지값=배열순서로 저장
			k = j % 10;//나머지를 이용
			arr[k]++;//나머지값=배열순서로 저장
		}
		else//네 자리수 일때
		{
			k = (j / 1000) % 10;//j가 정수임을 이용하여 나누어서 천의 자리에 접근
			arr[k]++;//나머지값=배열순서로 저장
			k = (j / 100) % 10;//j가 정수임을 이용하여 나누어서 백의 자리에 접근
			arr[k]++;//나머지값=배열순서로 저장
			k = (j / 10) % 10;//j가 정수임을 이용하여 나누어서 십의 자리에 접근
			arr[k]++;//나머지값=배열순서로 저장
			k = j % 10;//나머지를 이용
			arr[k]++;//나머지값=배열순서로 저장
		}

		j++;//범위 내에서 계속 연산을 하기 위해 후위 증가 연산
	}

	for (i = 0; i < 10; i++)//배열을 출력하기 위한 반복문
	{
		printf("%d: %d \n", i, arr[i]);//출력문
	}
	return 0;//종료
}