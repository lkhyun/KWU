#include <stdio.h>
float floatfunc(float x);//floating point 전용 함수
short shortfunc(unsigned short x);//fixed point 전용 함수
void fixedpoint(void);//fixed point 알고리즘
void floatingpoint(void); //floating point 알고리즘

float x1 = 1, x2 = 2, x3 = 0; //floating point 값
unsigned short a1 = 1, a2 = 2, a3 = 0; // fixed point 전체 값
unsigned short b1 = 0, b2 = 0, b3 = 0; // fixed point 소수부
unsigned int c1 = 0, c2 = 0, c3 = 0; // fixed point 소수부를 10진수로 변환한 값을 저장할 변수(출력시에만 사용됨)
const unsigned short export6bits = 63; //소수부 6비트를 추출하기 위한 변수, 이 변수와 값을 and연산함
unsigned int decimalprint = 500000; //소수부를 10진수로 변환하기 위한 변수, 초기값은 2진수 형태 0.1을 뜻하고 쉬프트되어 사용됨(출력시에만 사용됨)
unsigned int decimalpoint = 32; //소수부에서 10진수로 변환하는 과정에서 해당 비트가 1인지를 체크하는 변수, decimalprint변수와 마찬가지로 쉬프트되어 사용됨(출력시에만 사용됨)

int main()
{
	printf("fixed point\n");
	fixedpoint();
	printf("\nfloatingpoint\n");
	floatingpoint();
	return 0;
}
void fixedpoint(void)
{
	a1 = a1 << 6; a2 = a2 << 6; //소수부 6비트를 생각해서 6만큼 좌로 쉬프트한 후 연산 시작
	do
	{
		c1 = 0; c2 = 0; c3 = 0;
		a3 = (a1 + a2) >> 1; //구간의 중간값 얻기
		b1 = a1 & export6bits; //값의 소수부를 추출하는 과정
		b2 = a2 & export6bits;
		b3 = a3 & export6bits;
		for (int i = 0; i < 6; i++) { if ((b1 & (decimalpoint >> i))) { c1 += (decimalprint >> i); } }//매 반복마다 추출한 6개의 비트들을 각각 1인지 조사하여 1이라면 decimalprint 값을 더해준다. 
		for (int i = 0; i < 6; i++) { if ((b2 & (decimalpoint >> i))) { c2 += (decimalprint >> i); } }
		for (int i = 0; i < 6; i++) { if ((b3 & (decimalpoint >> i))) { c3 += (decimalprint >> i); } }

		printf("a1: %u.%u, a2: %u.%u, a3: %u.%u", (a1 >> 6),c1, (a2 >> 6),c2, (a3 >> 6),c3); //정수부는 연산 전에 좌로 6만큼 쉬프트했으니 다시 우로 6만큼 쉬프트한 후 출력,소수부는 위에서 만들어낸 값들을 출력
		if (shortfunc(a3)) { a1 = a3; }//shortfunc은 f(a3)의 값이 양수라면 0을 음수라면 1을 반환한다.
		else { a2 = a3; }
	} while ((a2-a1)>1);//좌로 6만큼 쉬프트하였기에 차가 1보다 커야한다는 것은 소수부 6개비트의 최하위 비트만큼의 차이도 나지 않게 되었을때 반복을 종료한다는 의미가 된다.
}
void floatingpoint(void)
{
	do
	{
		x3 = (x1 + x2) / 2; //구간의 중간값 얻기
		printf("x1:%f ,x2:%f ,x3:%f f(x3):%f\n", x1, x2, x3, floatfunc(x3));//float변수를 사용했기에 그대로 %f을 이용하여 출력
		if (floatfunc(x3) * floatfunc(x1) < 0) { x2 = x3; }//곱이 음수라면 f(x3)는 양수이므로 x3는 x2와 대체
		else { x1 = x3; }
	} while ((x2 - x1) > 0.015625);//fixed와 tolerence value를 동일하게 하여 반복횟수를 같게 조정, 해당값은 2진수로 0.000001에 해당하는 값
		
}
float floatfunc(float x)
{
	return (((x*x)*x) + 4*(x*x) - 10);
}
short shortfunc(unsigned short x)
{
	unsigned short temp1 = x * x;
	temp1 = temp1 >> 6;//소수부가 6비트인 두 수를 곱했기에 소수부가 12비트가 되었음. 따라서 세제곱을 만들기전 다시 소수부를 6으로 맞춰줌
	unsigned short temp2 = temp1; //제곱수는 4x^2에서 사용하므로 변수에 저장해둠
	temp1 = temp1 * x;//세제곱 연산
	temp1 = temp1 >> 6;//다시 소수부 6으로 맞춰줌
	temp2 = temp2 * 4;//저장해둔 제곱수와 4를 곱셈
	unsigned short temp3 = temp1 + temp2;// x^3 + 4x^2
	unsigned short comparesign = 10 << 6; //위에서 연산한 값들은 6만큼 좌로 쉬프트 되어있기에 10을 위 값과 비교하기 위해 자리를 맞춰줌

	temp1 = temp3 & export6bits;//소수부 추출
	unsigned int temp4 = 0;//소수부를 10진수로 변환한 값 저장(출력시에만 사용)
	for (int i = 0; i < 6; i++) { if ((temp1 & (decimalpoint >> i))) { temp4 += (decimalprint >> i); } }//소수부 10진수 정수로 변환
	if ((temp3) > comparesign) // 연산한 값에 -10을 하지 않고 10과 비교
	{
		printf("f(a3)=%d.%u\n", (temp3 >> 6) - 10, temp4);//양수일때는 연산한 값에 10 빼고 소수부 출력
		return 0; //plus
	}
	else
	{
		printf("f(a3)=-%d.%d\n", 9 - (temp3 >> 6), (1000000 - temp4));//음수일때는 연산한 값에 9빼고 1에 소수 빼서 출력
		return 1;//minus
	}
}