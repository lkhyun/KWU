#include <stdio.h>//헤더파일 선언

int main()//main함수 선언
{
	int x1, y1 = 0;//point1 의 x,y좌표 변수 선언
	int x3, y3 = 0;//point2 의 x,y좌표 변수 선언

	do //입력 반복문
	{
		printf("직사각형이 만들어지도록 점 두개를 입력하시오. \n");//출력문
		printf("점1 x,y 순서대로 입력(괄호 생략): ");//출력문
		scanf("%d", &x1);// x1값 입력받기
		scanf("%d", &y1);// y1값 입력받기
		/*point1 점 입력받기*/
		printf("점3 x y 순서대로 입력(괄호 생략): ");//출력문
		scanf("%d", &x3); //x3값 입력받기
		scanf("%d", &y3); //y3값 입력받기
		/*point2 점 입력받기*/
	} while (x1 == x3 || y1 == y3);//두 점의 x좌표나 y좌표가 같을시에 직선 혹은 점이 될 수 있기 때문에 삽입한 조건


	printf("AREA:%d \n", (y3 - y1)*(x3 - x1));//면적 출력문

	printf("점2 좌표: (%d,%d) \n", x3, y1);//point2 점 출력문
	printf("점4 좌표: (%d,%d) \n", x1, y3);//point4 점 출력문

	return 0;//종료
}