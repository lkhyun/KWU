#include <stdio.h>//������� ����

int InputFunc()//�� �Է¹޴� �Լ�
{
	int i = 0;//���� ����
	printf("�� �Է�: ");//��¹�
	scanf("%d", &i);//i�� �Է¹ޱ�
	return i;//i�� ��ȯ

}

int main()//main �Լ� ����
{
	int num = 0;//���� num ����
	num = InputFunc();//�Լ� ���� �� num�� �� ����

	while (num < 0 || num>50000)//0�� 50000 ������ ��
	{
		printf("�ٽ��Է�\n");//��¹�
		num = InputFunc();//�ٽ� �� �Է¹ޱ�

	}
	/*0���� 50000������ int�� �������� �̿��Ͽ� ���� �ڸ� ���� �ڸ� ���� �ڸ� õ�� �ڸ� ���� �ڸ��� �����ϴ� ���*/
	printf("%d,%d,%d,%d,%d \n", (num / 10000) % 10, (num / 1000) % 10, (num / 100) % 10, (num / 10) % 10, num % 10);//��¹�
	printf("%d,%d,%d,%d \n", (num / 1000) % 10, (num / 100) % 10, (num / 10) % 10, num % 10);//��¹�
	printf("%d,%d,%d \n", (num / 100) % 10, (num / 10) % 10, num % 10);//��¹�
	printf("%d,%d \n", (num / 10) % 10, num % 10);//��¹�
	printf("%d \n", num % 10);//��¹�

	return 0;//����
}