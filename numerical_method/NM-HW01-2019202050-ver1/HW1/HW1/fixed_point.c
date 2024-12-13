#include <stdio.h>
float floatfunc(float x);//floating point ���� �Լ�
short shortfunc(unsigned short x);//fixed point ���� �Լ�
void fixedpoint(void);//fixed point �˰���
void floatingpoint(void); //floating point �˰���

float x1 = 1, x2 = 2, x3 = 0; //floating point ��
unsigned short a1 = 1, a2 = 2, a3 = 0; // fixed point ��ü ��
unsigned short b1 = 0, b2 = 0, b3 = 0; // fixed point �Ҽ���
unsigned int c1 = 0, c2 = 0, c3 = 0; // fixed point �Ҽ��θ� 10������ ��ȯ�� ���� ������ ����(��½ÿ��� ����)
const unsigned short export6bits = 63; //�Ҽ��� 6��Ʈ�� �����ϱ� ���� ����, �� ������ ���� and������
unsigned int decimalprint = 500000; //�Ҽ��θ� 10������ ��ȯ�ϱ� ���� ����, �ʱⰪ�� 2���� ���� 0.1�� ���ϰ� ����Ʈ�Ǿ� ����(��½ÿ��� ����)
unsigned int decimalpoint = 32; //�Ҽ��ο��� 10������ ��ȯ�ϴ� �������� �ش� ��Ʈ�� 1������ üũ�ϴ� ����, decimalprint������ ���������� ����Ʈ�Ǿ� ����(��½ÿ��� ����)

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
	a1 = a1 << 6; a2 = a2 << 6; //�Ҽ��� 6��Ʈ�� �����ؼ� 6��ŭ �·� ����Ʈ�� �� ���� ����
	do
	{
		c1 = 0; c2 = 0; c3 = 0;
		a3 = (a1 + a2) >> 1; //������ �߰��� ���
		b1 = a1 & export6bits; //���� �Ҽ��θ� �����ϴ� ����
		b2 = a2 & export6bits;
		b3 = a3 & export6bits;
		for (int i = 0; i < 6; i++) { if ((b1 & (decimalpoint >> i))) { c1 += (decimalprint >> i); } }//�� �ݺ����� ������ 6���� ��Ʈ���� ���� 1���� �����Ͽ� 1�̶�� decimalprint ���� �����ش�. 
		for (int i = 0; i < 6; i++) { if ((b2 & (decimalpoint >> i))) { c2 += (decimalprint >> i); } }
		for (int i = 0; i < 6; i++) { if ((b3 & (decimalpoint >> i))) { c3 += (decimalprint >> i); } }

		printf("a1: %u.%u, a2: %u.%u, a3: %u.%u", (a1 >> 6),c1, (a2 >> 6),c2, (a3 >> 6),c3); //�����δ� ���� ���� �·� 6��ŭ ����Ʈ������ �ٽ� ��� 6��ŭ ����Ʈ�� �� ���,�Ҽ��δ� ������ ���� ������ ���
		if (shortfunc(a3)) { a1 = a3; }//shortfunc�� f(a3)�� ���� ������ 0�� ������� 1�� ��ȯ�Ѵ�.
		else { a2 = a3; }
	} while ((a2-a1)>1);//�·� 6��ŭ ����Ʈ�Ͽ��⿡ ���� 1���� Ŀ���Ѵٴ� ���� �Ҽ��� 6����Ʈ�� ������ ��Ʈ��ŭ�� ���̵� ���� �ʰ� �Ǿ����� �ݺ��� �����Ѵٴ� �ǹ̰� �ȴ�.
}
void floatingpoint(void)
{
	do
	{
		x3 = (x1 + x2) / 2; //������ �߰��� ���
		printf("x1:%f ,x2:%f ,x3:%f f(x3):%f\n", x1, x2, x3, floatfunc(x3));//float������ ����߱⿡ �״�� %f�� �̿��Ͽ� ���
		if (floatfunc(x3) * floatfunc(x1) < 0) { x2 = x3; }//���� ������� f(x3)�� ����̹Ƿ� x3�� x2�� ��ü
		else { x1 = x3; }
	} while ((x2 - x1) > 0.015625);//fixed�� tolerence value�� �����ϰ� �Ͽ� �ݺ�Ƚ���� ���� ����, �ش簪�� 2������ 0.000001�� �ش��ϴ� ��
		
}
float floatfunc(float x)
{
	return (((x*x)*x) + 4*(x*x) - 10);
}
short shortfunc(unsigned short x)
{
	unsigned short temp1 = x * x;
	temp1 = temp1 >> 6;//�Ҽ��ΰ� 6��Ʈ�� �� ���� ���߱⿡ �Ҽ��ΰ� 12��Ʈ�� �Ǿ���. ���� �������� ������� �ٽ� �Ҽ��θ� 6���� ������
	unsigned short temp2 = temp1; //�������� 4x^2���� ����ϹǷ� ������ �����ص�
	temp1 = temp1 * x;//������ ����
	temp1 = temp1 >> 6;//�ٽ� �Ҽ��� 6���� ������
	temp2 = temp2 * 4;//�����ص� �������� 4�� ����
	unsigned short temp3 = temp1 + temp2;// x^3 + 4x^2
	unsigned short comparesign = 10 << 6; //������ ������ ������ 6��ŭ �·� ����Ʈ �Ǿ��ֱ⿡ 10�� �� ���� ���ϱ� ���� �ڸ��� ������

	temp1 = temp3 & export6bits;//�Ҽ��� ����
	unsigned int temp4 = 0;//�Ҽ��θ� 10������ ��ȯ�� �� ����(��½ÿ��� ���)
	for (int i = 0; i < 6; i++) { if ((temp1 & (decimalpoint >> i))) { temp4 += (decimalprint >> i); } }//�Ҽ��� 10���� ������ ��ȯ
	if ((temp3) > comparesign) // ������ ���� -10�� ���� �ʰ� 10�� ��
	{
		printf("f(a3)=%d.%u\n", (temp3 >> 6) - 10, temp4);//����϶��� ������ ���� 10 ���� �Ҽ��� ���
		return 0; //plus
	}
	else
	{
		printf("f(a3)=-%d.%d\n", 9 - (temp3 >> 6), (1000000 - temp4));//�����϶��� ������ ���� 9���� 1�� �Ҽ� ���� ���
		return 1;//minus
	}
}