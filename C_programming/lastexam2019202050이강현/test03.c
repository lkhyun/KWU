#include <stdio.h>
 
int sum_func(int num);//����Լ��� ����

int main(void)
{
	int num;
	printf("���� ���� ��? ");
	scanf("%d", &num);
	
	printf("%d", sum_func(num));//����Լ��� �������ڷ� �޾� ���

	return 0;
}
int sum_func(int num)
{
	if (num>0)//����Լ� �������ڰ� �ڿ������� �����ϱ� ���� ���ǹ�
	{
		return (num + sum_func(num - 1));//���� ��ȯ
	}
	return 0;
}