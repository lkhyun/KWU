#include <stdio.h>
int main(void)
{
	char str[20] = "";//���ڿ� ����
	char *ptr = str;//������ ���� ����
	int i, temp;
	int len;
	printf("�Է� ���ڿ�? ");//���ڿ� �Է¹ޱ�
	scanf("%s", str);

	len = sizeof(str);//���ڿ� ���̰��

	for (i = 0; i < len/2; i++)//���ڿ� ���� �յ� �ڸ��� �ݺ����� ���ؼ� �ٲٱ�
	{
		temp = *(ptr + i);
		*(ptr + i) = *(ptr + len-1-i);
		*(ptr + len-1-i) = temp;
	}
	
		printf("%s", *ptr);//���ڿ� ���
	

	printf("%d", len);//���ڿ� ���� ���
	return 0;
}